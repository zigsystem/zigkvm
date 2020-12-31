#include <vector>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "usbgadget.h"

/*
https://usb.org/sites/default/files/hut1_21.pdf
https://www.usb.org/sites/default/files/documents/hid1_11.pdf
*/
std::vector<uint8_t> hid_bytes{
    0x05, 0x01,
    0x09, 0x06,
    0xa1, 0x01,
    0x05, 0x07,
    0x19, 0xe0,
    0x29, 0xe7,
    0x15, 0x00,
    0x25, 0x01,
    0x75, 0x01,
    0x95, 0x08,
    0x81, 0x02,
    0x95, 0x01,
    0x75, 0x08,
    0x81, 0x03,
    0x95, 0x05,
    0x75, 0x01,
    0x05, 0x08,
    0x19, 0x01,
    0x29, 0x05,
    0x91, 0x02,
    0x95, 0x01,
    0x75, 0x03,
    0x91, 0x03,
    0x95, 0x06,
    0x75, 0x08,
    0x15, 0x00,
    0x25, 0x65,
    0x05, 0x07,
    0x19, 0x00,
    0x29, 0x65,
    0x81, 0x00,
    0xc0
};

namespace bfs = boost::filesystem;

void gadget_init() {
  bfs::path base_confs{"/sys/kernel/config/usb_gadget/"};
  bfs::path zig_conffs{base_confs / "zighid"};
  bfs::create_directories(zig_conffs);

  // disconnect previously connected device is necessary
  if (bfs::file_size(zig_conffs / "UDC") != 0) {
    bfs::ofstream{zig_conffs / "UDC"} << "";
  }

  bfs::ofstream{zig_conffs / "idVendor"} << "0x1d6b";  // Linux Foundation
  bfs::ofstream{zig_conffs / "idProduct"} << "0x0104"; // Multifunction Composite Gadget
  bfs::ofstream{zig_conffs / "bcdDevice"} << "0x0001";
  bfs::ofstream{zig_conffs / "bcdUSB"} << "0x0200";

  bfs::create_directories(zig_conffs / "strings/0x409");

  bfs::ofstream{zig_conffs / "strings/0x409/serialnumber"} << "1234567890";
  bfs::ofstream{zig_conffs / "strings/0x409/manufacturer"} << "zigsystem.com";
  bfs::ofstream{zig_conffs / "strings/0x409/product"} << "pkvm";
  bfs::create_directories(zig_conffs / "configs/c.1/strings/0x409");
  bfs::ofstream{zig_conffs / "configs/c.1/strings/0x409/configuration"} << "Config 1: ECM network";
  bfs::ofstream{zig_conffs / "configs/c.1/MaxPower"} << "250";

  bfs::create_directories(zig_conffs / "functions/hid.usb0");

  bfs::ofstream{zig_conffs / "functions/hid.usb0/protocol"} << "1"; // keyboard
  bfs::ofstream{zig_conffs / "functions/hid.usb0/subclass"} << "1"; // 0 - no subclass?
  bfs::ofstream{zig_conffs / "functions/hid.usb0/report_length"} << "8";
  {
    bfs::ofstream f{zig_conffs / "functions/hid.usb0/report_desc",
                    bfs::ofstream::binary};
    std::ostreambuf_iterator<char> it(f);
    std::copy(hid_bytes.begin(), hid_bytes.end(), it);
  }

  if (!bfs::exists(zig_conffs / "configs/c.1/hid.usb0")) {
    bfs::create_symlink(zig_conffs / "functions/hid.usb0",
                        zig_conffs / "configs/c.1/hid.usb0");
  }

  for (auto &p : bfs::directory_iterator("/sys/class/udc")) {
    bfs::ofstream{zig_conffs / "UDC"} << bfs::basename(p);
  }

  bfs::ofstream{zig_conffs / "UDC"} << "fe980000.usb";
  bfs::ofstream{zig_conffs / "UDC"} << "musb-hdrc.2.auto";
}


int hid_send_key(std::string &command, const char &mods) {
  //  const char *filename = "/dev/hidraw0";
  const char *filename = "/dev/hidg0";
  int fd = open(filename, O_RDWR, 0666);
  if (fd == -1) {
    perror(filename);
    return 3;
  }

  std::string report;
  report.resize(8);
  for (char &x : report) {
    x = 0;
  }

  auto keys_it = report.begin() + 2;

  for (const char &x : command) {
    *keys_it++ = x;
    if (keys_it == report.end()) {
      break;
    }
  }
  report[0] = mods;

  auto to_send = report.size();

  if (write(fd, report.c_str(), to_send) != to_send) {
    perror(filename);
    return 5;
  }

  char zero_report[8] = {0};
  if (write(fd, zero_report, to_send) != to_send) {
    perror(filename);
    return 5;
  }

  close(fd);
  return 0;
}

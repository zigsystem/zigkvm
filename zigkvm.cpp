#include <rfb/rfb.h>
#ifdef LIBVNCSERVER_HAVE_GETTIMEOFDAY
#include <sys/time.h>
#endif

#include "libuvc/libuvc.h"
#include <assert.h>
#include <unistd.h>

#include <algorithm>
#include <string>
#include <thread>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <fstream>
#include <iostream>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "keymapping.h"
#include "usbgadget.h"

rfbScreenInfoPtr vnc_server;
bool vnc_streaming{false};

static void dokey(rfbBool down, rfbKeySym k, rfbClientPtr cl) {
  static char global_mods = 0;
  std::string s;
  static auto rfb2vnc = init_mappings();
  static auto mods_map = init_mods();

  if (mods_map.find(k) != mods_map.end()) {
    if (down) {
      global_mods |= mods_map[k];
    } else {
      global_mods &= ~mods_map[k];
    }
    printf("mods %d 0x%x\n", down, global_mods);
  } else if (rfb2vnc.find(k) != rfb2vnc.end()) {
    s.resize(1);
    s[0] = rfb2vnc[k];
    char local_mods = rfb2vnc[k].mods() | global_mods;
    if (down) {
      printf("sending key %d 0x%3.3x key 0x%x mods=0x%x\n", down, k, s[0],
             local_mods);
      hid_send_key(s, local_mods);
    }
  } else {
    printf("got unknown key %d 0x%3.3x\n", down, k);
  }
}

static void doptr(int buttonMask, int x, int y, rfbClientPtr cl) {
}

int vnc_init(int argc, char **argv) {

  auto WIDTH = 1920;
  auto HEIGHT = 1080;
  auto BPP = 3;

  vnc_server = rfbGetScreen(&argc, argv, WIDTH, HEIGHT, 8, 1, BPP);
  assert(vnc_server);
  vnc_server->desktopName = "Zigkvm";
  vnc_server->frameBuffer = (char *)malloc(WIDTH * HEIGHT * BPP);
  vnc_server->alwaysShared = true;
  vnc_server->kbdAddEvent = dokey;
  vnc_server->ptrAddEvent = doptr;

  rfbInitServer(vnc_server);
  vnc_streaming = true;

  return (0);
}

void cb(uvc_frame_t *frame, void *ptr) {
  enum uvc_frame_format *frame_format = (enum uvc_frame_format *)ptr;
  uvc_frame_t *frame_rgb = uvc_allocate_frame(frame->width * frame->height * 3);
  assert(frame_rgb);

  uvc_error_t ret = uvc_any2rgb(frame, frame_rgb);
  //  assert(ret==UVC_SUCCESS);

  if (ret == UVC_SUCCESS && vnc_streaming) {
    memcpy(vnc_server->frameBuffer, frame_rgb->data, frame_rgb->data_bytes);
    rfbMarkRectAsModified(vnc_server, 0, 0, 1920, 1080);
  }

  uvc_free_frame(frame_rgb);
}

int main(int argc, char **argv) {
  gadget_init();
  init_mappings();

  uvc_context_t *ctx;
  uvc_device_t *dev;
  uvc_device_handle_t *devh;
  uvc_stream_ctrl_t ctrl;
  uvc_error_t res;

  res = uvc_init(&ctx, NULL);
  assert(res == UVC_SUCCESS);

  res = uvc_find_device(ctx, &dev, 0, 0, NULL);
  assert(res == UVC_SUCCESS);

  res = uvc_open(dev, &devh);
  assert(res == UVC_SUCCESS);

  vnc_init(argc, argv);

  enum uvc_frame_format frame_format = UVC_FRAME_FORMAT_MJPEG;
  int width = 1920;
  int height = 1080;
  int fps = 30;

  res = uvc_get_stream_ctrl_format_size(devh, &ctrl, frame_format, width,
                                        height, fps);
  assert(res == UVC_SUCCESS);

  res = uvc_start_streaming(devh, &ctrl, cb, nullptr, 0);
  assert(res == UVC_SUCCESS);

  uvc_set_ae_mode(devh, 1);
  assert(res == UVC_SUCCESS);

  while (rfbIsActive(vnc_server)) {
    auto usec = vnc_server->deferUpdateTime * 1000;
    rfbProcessEvents(vnc_server, usec);
  }

  uvc_stop_streaming(devh);
  uvc_close(devh);
  uvc_unref_device(dev);

  uvc_exit(ctx);

  return 0;
}

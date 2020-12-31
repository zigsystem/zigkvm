#ifndef USBGADGET_H
#define USBGADGET_H

#include <string>

void gadget_init();
int hid_send_key(std::string &command, const char &mods);

#endif // USBGADGET_H

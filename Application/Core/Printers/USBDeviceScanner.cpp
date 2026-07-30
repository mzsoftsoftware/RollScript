#include "USBDeviceScanner.h"

#include <libusb.h>

USBDeviceScanner::USBDeviceScanner()
{
    libusb_context* ctx = nullptr;
    int result = libusb_init(&ctx);
    libusb_exit(ctx);
}

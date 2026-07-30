#include "USBManager.h"

#include <libusb.h>


USBManager::USBManager(QObject *parent)
    : QObject{parent}
{
}

USBManager::~USBManager()
{
}

bool USBManager::init()
{
    int result = libusb_init(&m_ptrLibUsbContext);

    if(result != 0)
    {
        // TASK : Correct tr !!!
        m_qstrLastError = tr("Could not initialize USB support.");
        return false;
    }

    return true;
}

#pragma once

#include <QString>

struct UsbDeviceInfo
{
    uint16_t vendorId = 0;
    uint16_t productId = 0;

    QString manufacturer;
    QString product;
    QString serialNumber;

    QString devicePath;

    bool isValid() const
    {
        return vendorId != 0 &&
               productId != 0;
    }
};

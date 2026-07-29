#pragma once

#include "UsbDeviceInfo.h"

class IPrinterPlugin;

class PrinterInstance
{
public:
    explicit PrinterInstance(const UsbDeviceInfo& device, IPrinterPlugin* ptrPrinterPlugin);

    // Getter
    const UsbDeviceInfo& deviceInfo() const         { return m_deviceInfo; }
    IPrinterPlugin* plugin() const                  { return m_ptrPrinterPlugin; }
    //QString name() const;

private:
    UsbDeviceInfo m_deviceInfo;
    IPrinterPlugin* m_ptrPrinterPlugin = nullptr;
};


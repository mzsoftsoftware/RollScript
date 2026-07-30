#include "PrinterPluginRegistry.h"

#include "Common/Core/Plugins/IPrinterPlugin.h"
#include "Common/Core/Devices/USBDeviceInfo.h"


PrinterPluginRegistry::PrinterPluginRegistry()
{
}

bool PrinterPluginRegistry::registerPlugin(IPrinterPlugin* ptrPrinterPlugin)
{
    if(!ptrPrinterPlugin)
        return false;

    if(m_registryPlugins.contains(ptrPrinterPlugin))
        return false;

    m_registryPlugins.append(ptrPrinterPlugin);

    return true;
}

IPrinterPlugin* PrinterPluginRegistry::supportsUsb(const USBDeviceInfo& deviceInfo)
{
    IPrinterPlugin* ptrPrinterPluginResult = nullptr;

    for(IPrinterPlugin* ptrPrinterPlugin : m_registryPlugins)
    {
        if(!ptrPrinterPlugin->supportsUsb(deviceInfo))
            continue;

        if(ptrPrinterPluginResult != nullptr)
        {
            // TASK : Use tr !!!
            m_qstrLastError = QString("Multiple PrinterPlugins match USB device "
                                      "%1:%2")
                                  .arg(deviceInfo.vendorId, 4, 16, QChar('0'))
                                  .arg(deviceInfo.productId, 4, 16, QChar('0'));
            return nullptr;
        }

        ptrPrinterPluginResult = ptrPrinterPlugin;
    }

    return ptrPrinterPluginResult;
}

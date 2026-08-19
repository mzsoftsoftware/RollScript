#include "PrinterPluginRegistry.h"

#include "Core/Plugins/IPrinterPlugin.h"
#include "Core/USB/USBDeviceInfo.h"


PrinterPluginRegistry::PrinterPluginRegistry(QObject* parent)
    : QObject{parent}
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

IPrinterPlugin* PrinterPluginRegistry::supportsUsb(const USBDeviceInfo* ptrDeviceInfo)
{
    IPrinterPlugin* ptrPrinterPluginResult = nullptr;

    for(IPrinterPlugin* ptrPrinterPlugin : m_registryPlugins)
    {
        if(!ptrPrinterPlugin->supportsUsb(ptrDeviceInfo))
            continue;

        if(ptrPrinterPluginResult != nullptr)
        {
            ROLLSCRIPT_ERROR(tr("PrinterPluginLoadFailed"), QStringLiteral("Multiple PrinterPlugins match USB device "
                                                                    "%1:%2")
                                                                .arg(ptrDeviceInfo->vendorId(), 4, 16, QChar(u'0'))
                                                                .arg(ptrDeviceInfo->productId(), 4, 16, QChar(u'0')));
            return nullptr;
        }

        ptrPrinterPluginResult = ptrPrinterPlugin;
    }

    return ptrPrinterPluginResult;
}

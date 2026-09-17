#include "PrinterPluginRegistry.h"

#include "Core/Plugins/IPrinterPlugin.h"
#include "Core/Plugins/IPluginInfo.h"
#include "Core/USB/USBDeviceInfo.h"


PrinterPluginRegistry::PrinterPluginRegistry(QObject* parent)
    : QObject{parent}
{
}
PrinterPluginRegistry::~PrinterPluginRegistry()
{
}

bool PrinterPluginRegistry::registerPlugin(IPrinterPlugin* ptrPrinterPlugin)
{
    Q_ASSERT(ptrPrinterPlugin);

    const QString qstrPluginId = ptrPrinterPlugin->pluginInfo()->pluginId();
    if(m_qstrPrinterPluginIds.contains(qstrPluginId))
    {
        ROLLSCRIPT_ERROR(tr("PrinterPluginAlreadyRegistered"), QStringLiteral("Plugin ID already registered: %1").arg(qstrPluginId));
        return false;
    }

    m_qhashPrinterPlugins.insert(qstrPluginId, ptrPrinterPlugin);
    m_qstrPrinterPluginIds.append(qstrPluginId);

    return true;
}

IPrinterPlugin* PrinterPluginRegistry::supportsUsb(const USBDeviceInfo* ptrDeviceInfo)
{
    IPrinterPlugin* ptrPrinterPluginResult = nullptr;

    for(const QString& qstrPluginId : m_qstrPrinterPluginIds)
    {
        if(!printerPlugin(qstrPluginId)->supportsUsb(ptrDeviceInfo))
            continue;

        if(ptrPrinterPluginResult != nullptr)
        {
            ROLLSCRIPT_ERROR(tr("PrinterPluginLoadFailed"), QStringLiteral("Multiple PrinterPlugins match USB device "
                                                                    "%1:%2")
                                                                .arg(ptrDeviceInfo->vendorId(), 4, 16, QChar(u'0'))
                                                                .arg(ptrDeviceInfo->productId(), 4, 16, QChar(u'0')));
            return nullptr;
        }

        ptrPrinterPluginResult = printerPlugin(qstrPluginId);
    }

    return ptrPrinterPluginResult;
}

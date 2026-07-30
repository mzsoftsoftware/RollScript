#include "PrinterInstance.h"

#include "Common/Core/Plugins/IPrinterPlugin.h"


PrinterInstance::PrinterInstance(IPrinterPlugin* ptrPrinterPlugin, const USBDeviceInfo& deviceInfo, QObject* parent)
    : QObject{parent}
    , m_deviceInfo(deviceInfo)
    , m_ptrPrinterPlugin(ptrPrinterPlugin)
{
    m_qstrId = QString("USB:%1:%2:%3").arg(deviceInfo.manufacturer(), deviceInfo.product(), deviceInfo.serial());
    m_qstrDisplayName = QString("%1 - %2 - %3").arg(deviceInfo.manufacturer(), deviceInfo.product(), deviceInfo.serial());
    m_icon = ptrPrinterPlugin->icon();
}

#include "PrinterInstance.h"

#include "Common/Core/Plugins/IPrinterPlugin.h"


PrinterInstance::PrinterInstance(const UsbDeviceInfo& device, IPrinterPlugin* ptrPrinterPlugin)
    : m_deviceInfo(device)
    , m_ptrPrinterPlugin(ptrPrinterPlugin)
{
}

/*QString PrinterInstance::name() const
{
    if(m_ptrPrinterPlugin)
    {
        return m_ptrPrinterPlugin->name();
    }

    return m_deviceInfo.product;
}*/


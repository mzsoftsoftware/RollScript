#include "DymoLabelPoint350PrinterPlugin.h"

#include "Common/Core/Devices/USBDeviceInfo.h"


DymoLabelPoint350PrinterPlugin::DymoLabelPoint350PrinterPlugin(QObject* parent)
    : QObject(parent)
{
}


QString DymoLabelPoint350PrinterPlugin::pluginId() const
{
    return "dymo.labelpoint350";
}
QString DymoLabelPoint350PrinterPlugin::displayName() const
{
    return "Dymo LabelPoint 350";
}
QString DymoLabelPoint350PrinterPlugin::version() const
{
    return "1.0.0";
}
QIcon DymoLabelPoint350PrinterPlugin::icon() const
{
    return QIcon();
}

bool DymoLabelPoint350PrinterPlugin::supportsUsb(const UsbDeviceInfo& device) const
{
    // Mein fixer Drucker : PID=, VID=0x0922
    return device.vendorId == 0x0922 && device.productId == 0x0015;
}

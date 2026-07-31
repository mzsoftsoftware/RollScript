#include "DymoLabelPoint350PrinterPlugin.h"

#include "Common/Core/USB/USBDeviceInfo.h"


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

bool DymoLabelPoint350PrinterPlugin::supportsUsb(const USBDeviceInfo* ptrDevice) const
{
    // Mein fixer Drucker : PID=0x0015, VID=0x0922
    return ptrDevice->vendorId() == 0x0922 && ptrDevice->productId() == 0x0015;
}

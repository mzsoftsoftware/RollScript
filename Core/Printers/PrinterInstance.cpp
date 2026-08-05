#include "PrinterInstance.h"

#include "Common/Core/Plugins/IPrinterPlugin.h"


PrinterInstance::PrinterInstance(IPrinterPlugin* ptrPrinterPlugin, QObject* parent)
    : QObject{parent}
    , m_ptrPrinterPlugin(ptrPrinterPlugin)
{
    m_icon = ptrPrinterPlugin->icon();
}
PrinterInstance::~PrinterInstance()
{
}
#include "PrinterPluginInfo.h"

PrinterPluginInfo::PrinterPluginInfo(const char* pszContext,
                                     const QString& qstrPluginId,
                                     const QString& qstrPluginVersion,
                                     const char* pszPluginDisplayNameKey,
                                     const char* pszPrinterDisplayNameKey,
                                     const QIcon& iconPrinter)
    : PluginInfo(pszContext, qstrPluginId, qstrPluginVersion, pszPluginDisplayNameKey)
    , m_pszPrinterDisplayNameKey(pszPrinterDisplayNameKey)
    , m_iconPrinter(iconPrinter)
{
}
PrinterPluginInfo::~PrinterPluginInfo()
{
}

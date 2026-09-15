#include "PrinterPluginInfo.h"

PrinterPluginInfo::PrinterPluginInfo(const char* pszContext,
                                     const QString& qstrPluginId,
                                     const QString& qstrPluginVersion,
                                     const char* pszPluginDisplayNameKey,
                                     const QIcon& iconPlugin)
    : PluginInfo(pszContext, qstrPluginId, qstrPluginVersion, pszPluginDisplayNameKey, iconPlugin)
{
}
PrinterPluginInfo::~PrinterPluginInfo()
{
}

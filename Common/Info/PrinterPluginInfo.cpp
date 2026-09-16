#include "PrinterPluginInfo.h"

PrinterPluginInfo::PrinterPluginInfo(const char* pszContext,
                                     const QString& qstrPluginId,
                                     const QString& qstrPluginVersion,
                                     const char* pszPluginNameKey,
                                     const char* pszPluginDescriptionKey,
                                     const QIcon& iconPlugin)
    : PluginInfo(pszContext, qstrPluginId, qstrPluginVersion, pszPluginNameKey, pszPluginDescriptionKey, iconPlugin)
{
}
PrinterPluginInfo::~PrinterPluginInfo()
{
}

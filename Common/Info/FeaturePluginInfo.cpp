#include "FeaturePluginInfo.h"

FeaturePluginInfo::FeaturePluginInfo(const char* pszContext,
                                     const QString& qstrPluginId,
                                     const QString& qstrPluginVersion,
                                     const char* pszPluginNameKey,
                                     const char* pszPluginDescriptionKey,
                                     const QIcon& iconPlugin)
    : PluginInfo(pszContext, qstrPluginId, qstrPluginVersion, pszPluginNameKey, pszPluginDescriptionKey, iconPlugin)
{
}
FeaturePluginInfo::~FeaturePluginInfo()
{
}

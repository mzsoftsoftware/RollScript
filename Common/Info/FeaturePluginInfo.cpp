#include "FeaturePluginInfo.h"

FeaturePluginInfo::FeaturePluginInfo(const char* pszContext,
                                     const QString& qstrPluginId,
                                     const QString& qstrPluginVersion,
                                     const char* pszPluginDisplayNameKey,
                                     const QIcon& iconPlugin)
    : PluginInfo(pszContext, qstrPluginId, qstrPluginVersion, pszPluginDisplayNameKey, iconPlugin)
{
}
FeaturePluginInfo::~FeaturePluginInfo()
{
}

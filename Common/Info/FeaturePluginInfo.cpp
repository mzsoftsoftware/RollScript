#include "FeaturePluginInfo.h"

FeaturePluginInfo::FeaturePluginInfo(const char* pszContext,
                                     const QString& qstrPluginId,
                                     const QString& qstrPluginVersion,
                                     const char* pszPluginDisplayNameKey)
    : PluginInfo(pszContext, qstrPluginId, qstrPluginVersion, pszPluginDisplayNameKey)
{
}
FeaturePluginInfo::~FeaturePluginInfo()
{
}

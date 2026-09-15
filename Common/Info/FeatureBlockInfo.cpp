#include "FeatureBlockInfo.h"


FeatureBlockInfo::FeatureBlockInfo(const char* pszContext,
                                   const QString& qstrPluginId,
                                   const QString& qstrPluginVersion,
                                   const char* pszPluginDisplayNameKey,
                                   const QIcon& iconPlugin,
                                   const char* pszFeatureBlockTooltipKey)
    : FeaturePluginInfo(pszContext, qstrPluginId, qstrPluginVersion, pszPluginDisplayNameKey, iconPlugin)
    , m_pszFeatureBlockTooltipKey(pszFeatureBlockTooltipKey)
{
}
FeatureBlockInfo::~FeatureBlockInfo()
{
}

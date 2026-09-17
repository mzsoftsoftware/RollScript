#include "FeatureBlockInfo.h"


FeatureBlockInfo::FeatureBlockInfo(const char* pszContext,
                                   const QString& qstrPluginId,
                                   const QString& qstrPluginVersion,
                                   const char* pszPluginNameKey,
                                   const char* pszPluginDescriptionKey,
                                   const QIcon& iconPlugin,
                                   const char* pszFeatureBlockNameKey,
                                   const char* pszFeatureBlockTooltipKey)
    : FeaturePluginInfo(pszContext, qstrPluginId, qstrPluginVersion, pszPluginNameKey, pszPluginDescriptionKey, iconPlugin)
    , m_pszFeatureBlockNameKey(pszFeatureBlockNameKey)
    , m_pszFeatureBlockTooltipKey(pszFeatureBlockTooltipKey)
{
}
FeatureBlockInfo::~FeatureBlockInfo()
{
}

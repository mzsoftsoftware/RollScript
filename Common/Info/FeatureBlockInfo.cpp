#include "FeatureBlockInfo.h"


FeatureBlockInfo::FeatureBlockInfo(const char* pszContext,
                                   const QString& qstrPluginId,
                                   const QString& qstrPluginVersion,
                                   const char* pszPluginDisplayNameKey,
                                   const QString& qstrFeatureBlockId,
                                   const QIcon& iconFeatureBlock,
                                   const char* pszFeatureBlockDisplayNameKey,
                                   const char* pszFeatureBlockTooltipKey)
    : FeaturePluginInfo(pszContext, qstrPluginId, qstrPluginVersion, pszPluginDisplayNameKey)
    , m_qstrFeatureBlockId(qstrFeatureBlockId)
    , m_iconFeatureBlock(iconFeatureBlock)
    , m_pszFeatureBlockDisplayNameKey(pszFeatureBlockDisplayNameKey)
    , m_pszFeatureBlockTooltipKey(pszFeatureBlockTooltipKey)
{
}

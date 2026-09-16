#pragma once

#include "Common/Info/FeaturePluginInfo.h"
#include "Core/Blocks/IFeatureBlockInfo.h"


class FeatureBlockInfo : public FeaturePluginInfo, public virtual IFeatureBlockInfo
{
public:
    // Constructor / Destructor
    explicit FeatureBlockInfo(const char* pszContext,
                              const QString& qstrPluginId,
                              const QString& qstrPluginVersion,
                              const char* pszPluginNameKey,
                              const char* pszPluginDescriptionKey,
                              const QIcon& iconPlugin,
                              const char* pszFeatureBlockNameKey,
                              const char* pszFeatureBlockTooltipKey);
    ~FeatureBlockInfo() override;

    // Getter
    QString featureBlockName() const override       { return translate(m_pszFeatureBlockNameKey); }
    QString featureBlockTooltip() const override    { return translate(m_pszFeatureBlockTooltipKey); }

private:
    const char* m_pszFeatureBlockNameKey;
    const char* m_pszFeatureBlockTooltipKey;
};

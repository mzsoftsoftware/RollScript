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
                              const char* pszPluginDisplayNameKey,
                              const QIcon& iconPlugin,
                              const char* pszFeatureBlockTooltipKey);
    ~FeatureBlockInfo() override;

    // Getter
    QString featureBlockTooltip() const override            { return translate(m_pszFeatureBlockTooltipKey); }

private:
    const char* m_pszFeatureBlockTooltipKey;
};

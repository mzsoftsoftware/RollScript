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
                              const QString& qstrFeatureBlockId,
                              const QIcon& iconFeatureBlock,
                              const char* pszFeatureBlockDisplayNameKey,
                              const char* pszFeatureBlockTooltipKey);
    ~FeatureBlockInfo() override;

    // Getter
    const QString& featureBlockId() const override          { return m_qstrFeatureBlockId; }
    const QIcon& featureBlockIcon() const override          { return m_iconFeatureBlock; }

    QString featureBlockDisplayName() const override        { return translate(m_pszFeatureBlockDisplayNameKey); }
    QString featureBlockTooltip() const override            { return translate(m_pszFeatureBlockTooltipKey); }

private:
    QString m_qstrFeatureBlockId;
    QIcon m_iconFeatureBlock;
    const char* m_pszFeatureBlockDisplayNameKey;
    const char* m_pszFeatureBlockTooltipKey;
};

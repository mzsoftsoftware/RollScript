#pragma once

#include "Core/Plugins/IFeaturePluginInfo.h"


class IFeatureBlockInfo : public virtual IFeaturePluginInfo
{
public:
    ~IFeatureBlockInfo() override = default;
    virtual const QString& featureBlockId() const = 0;
    virtual const QIcon& featureBlockIcon() const = 0;

    virtual QString featureBlockDisplayName() const = 0;
    virtual QString featureBlockTooltip() const = 0;
};

#pragma once

#include "Core/Plugins/IFeaturePluginInfo.h"

#include <QIcon>


class IFeatureBlockInfo : public virtual IFeaturePluginInfo
{
public:
    // Constructor / Destructor
    ~IFeatureBlockInfo() override = default;

    // Getter
    virtual const QString& featureBlockId() const = 0;
    virtual const QIcon& featureBlockIcon() const = 0;

    virtual QString featureBlockDisplayName() const = 0;
    virtual QString featureBlockTooltip() const = 0;
};

#pragma once

#include "Core/Plugins/IFeaturePluginInfo.h"

#include <QIcon>


class IFeatureBlockInfo : public virtual IFeaturePluginInfo
{
public:
    // Constructor / Destructor
    ~IFeatureBlockInfo() override = default;

    // Getter
    virtual QString featureBlockName() const = 0;
    virtual QString featureBlockTooltip() const = 0;
};

#pragma once

#include "Core/Plugins/IFeaturePluginInfo.h"

#include <QIcon>


class IFeatureBlockInfo : public virtual IFeaturePluginInfo
{
public:
    // Constructor / Destructor
    ~IFeatureBlockInfo() override = default;

    // Getter
    virtual QString featureBlockTooltip() const = 0;
};

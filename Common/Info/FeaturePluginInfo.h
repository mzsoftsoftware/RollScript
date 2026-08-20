#pragma once

#include "Common/Info/PluginInfo.h"
#include "Core/Plugins/IFeaturePluginInfo.h"


class FeaturePluginInfo : public PluginInfo, public virtual IFeaturePluginInfo
{
public:
    FeaturePluginInfo(const char* pszContext,
                      const QString& qstrPluginId,
                      const QString& qstrPluginVersion,
                      const char* pszPluginDisplayNameKey);


private:
};

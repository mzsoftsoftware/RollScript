#include "FeaturePluginRegistry.h"

#include "Common/Core/Plugins/IFeaturePlugin.h"


FeaturePluginRegistry::FeaturePluginRegistry()
{
}

bool FeaturePluginRegistry::registerPlugin(IFeaturePlugin* ptrFeaturePlugin)
{
    if(!ptrFeaturePlugin)
        return false;

    if(m_registryPlugins.contains(ptrFeaturePlugin))
        return false;

    m_registryPlugins.append(ptrFeaturePlugin);

    return true;
}


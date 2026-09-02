#include "FeaturePluginRegistry.h"

#include "Core/Plugins/IFeaturePlugin.h"
#include "Core/Plugins/IFeaturePluginInfo.h"


FeaturePluginRegistry::FeaturePluginRegistry(QObject* parent)
    : QObject{parent}
{
}
FeaturePluginRegistry::~FeaturePluginRegistry()
{
}

bool FeaturePluginRegistry::registerPlugin(IFeaturePlugin* ptrFeaturePlugin)
{
    Q_ASSERT(ptrFeaturePlugin);

    const QString qstrPluginId = ptrFeaturePlugin->pluginInfo()->pluginId();
    if(m_qstrFeaturePluginIds.contains(qstrPluginId))
    {
        ROLLSCRIPT_ERROR(tr("FeaturePluginAlreadyRegistered"), QStringLiteral("Plugin ID already registered: %1").arg(qstrPluginId));
        return false;
    }

    m_qhashFeaturePlugins.insert(qstrPluginId, ptrFeaturePlugin);
    m_qstrFeaturePluginIds.append(qstrPluginId);

    return true;
}

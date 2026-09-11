#include "LicenseProviderRegistry.h"


LicenseProviderRegistry::LicenseProviderRegistry(QObject* parent)
    : QObject{parent}
{
}
LicenseProviderRegistry::~LicenseProviderRegistry()
{
}

bool LicenseProviderRegistry::registerProvider(ILicenseProvider* ptrLicenseProvider)
{
    Q_ASSERT(ptrLicenseProvider);

/*    const QString qstrPluginId = ptrFeaturePlugin->pluginInfo()->pluginId();
    if(m_qstrFeaturePluginIds.contains(qstrPluginId))
    {
        ROLLSCRIPT_ERROR(tr("FeaturePluginAlreadyRegistered"), QStringLiteral("Plugin ID already registered: %1").arg(qstrPluginId));
        return false;
    }

    m_qhashFeaturePlugins.insert(qstrPluginId, ptrFeaturePlugin);
    m_qstrFeaturePluginIds.append(qstrPluginId);
*/
    return true;
}

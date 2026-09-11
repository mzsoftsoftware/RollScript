#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"

#include <QHash>

class ILicenseProvider;


class LicenseProviderRegistry : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT

public:
    // Constructor / Destructor
    explicit LicenseProviderRegistry(QObject* parent);
    ~LicenseProviderRegistry() override;

    // Getter
    //QStringList availableFeaturePluginIds() const                       { return m_qstrFeaturePluginIds; }
    //IFeaturePlugin* featurePlugin(const QString& qstrPluginId) const    { return m_qhashFeaturePlugins.value(qstrPluginId, nullptr); }

    // Operations
    bool registerProvider(ILicenseProvider* ptrLicenseProvider);

private:
    //QStringList m_qstrFeaturePluginIds;
    //QHash<QString, IFeaturePlugin*> m_qhashFeaturePlugins;
};

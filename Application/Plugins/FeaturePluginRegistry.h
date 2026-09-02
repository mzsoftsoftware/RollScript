#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"

#include <QHash>

class IFeaturePlugin;


class FeaturePluginRegistry : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT

public:
    // Constructor / Destructor
    explicit FeaturePluginRegistry(QObject* parent);
    ~FeaturePluginRegistry() override;

    // Getter
    QStringList availableFeaturePluginIds() const                       { return m_qstrFeaturePluginIds; }
    IFeaturePlugin* featurePlugin(const QString& qstrPluginId) const    { return m_qhashFeaturePlugins.value(qstrPluginId, nullptr); }

    // Operations
    bool registerPlugin(IFeaturePlugin* ptrFeaturePlugin);

private:
    QStringList m_qstrFeaturePluginIds;
    QHash<QString, IFeaturePlugin*> m_qhashFeaturePlugins;
};

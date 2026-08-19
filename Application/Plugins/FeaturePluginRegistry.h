#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"

#include <QHash>

class IFeaturePlugin;


class FeaturePluginRegistry : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT

public:
    FeaturePluginRegistry(QObject* parent);

    bool registerPlugin(IFeaturePlugin* ptrFeaturePlugin);

    // Getter
    QStringList availableFeaturePluginIds() const                       { return m_qstrFeaturePluginIds; }
    IFeaturePlugin* featurePlugin(const QString& qstrPluginId) const    { return m_hashFeaturePlugins.value(qstrPluginId, nullptr); }

private:
    QStringList m_qstrFeaturePluginIds;
    QHash<QString, IFeaturePlugin*> m_hashFeaturePlugins;
};

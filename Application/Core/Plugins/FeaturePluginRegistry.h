#pragma once

#include <QList>

class IFeaturePlugin;


class FeaturePluginRegistry
{
public:
    FeaturePluginRegistry();

    bool registerPlugin(IFeaturePlugin* ptrFeaturePlugin);

    QString lastError() const       { return m_qstrLastError; }

private:
    QString m_qstrLastError;

    QList<IFeaturePlugin*> m_registryPlugins;
};

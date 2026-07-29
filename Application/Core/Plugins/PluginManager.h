#pragma once

#include <QObject>

class IPlugin;
class QPluginLoader;

#include "PrinterPluginRegistry.h"


class PluginManager : public QObject
{
    Q_OBJECT

public:
    explicit PluginManager(QObject *parent = nullptr);
    virtual ~PluginManager() override;

    bool loadPlugins();

    QString lastError() const                       { return m_qstrLastError; }

private:
    bool loadPluginDirectory(const QString& qstrPluginDirectory);
    bool loadPluginFile(const QString& qstrPluginFileName);



    //void registerPlugin(IPlugin* ptrPlugin);

    //QList<IPlugin*> plugins() const     { return m_qlstPlugins; }

private:
    QString m_qstrLastError;

    QList<QPluginLoader*> m_lstPluginLoaders;


    //QList<IPlugin*> m_qlstPlugins;

    //PrinterPluginRegistry m_registryPrinters;
    // FeaturePluginRegistry m_registryFeatures:

};

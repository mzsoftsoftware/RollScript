#pragma once

#include <QObject>

class IPlugin;
class QPluginLoader;

#include "PrinterPluginRegistry.h"
#include "FeaturePluginRegistry.h"


class PluginManager : public QObject
{
    Q_OBJECT

public:
    explicit PluginManager(QObject *parent = nullptr);
    virtual ~PluginManager() override;

    bool loadPlugins();

    // Getter
    QString lastError() const                     { return m_qstrLastError; }

    PrinterPluginRegistry registryPrinters()            { return m_registryPrinters; }
    FeaturePluginRegistry registryFeatures()            { return m_registryFeatures; }

private:
    bool loadPluginDirectory(const QString& qstrPluginDirectory);
    bool loadPluginFile(const QString& qstrPluginFileName);

    void registerPrinterPlugin(IPrinterPlugin* ptrPrinterPlugin);
    void registerFeaturePlugin(IFeaturePlugin* ptrFeaturePlugin);

    //QList<IPlugin*> plugins() const     { return m_qlstPlugins; }

private:
    QString m_qstrLastError;

    QList<QPluginLoader*> m_lstPluginLoaders;

    PrinterPluginRegistry m_registryPrinters;
    FeaturePluginRegistry m_registryFeatures;
};

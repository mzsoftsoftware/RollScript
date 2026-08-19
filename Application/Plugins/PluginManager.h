#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"

class IPlugin;
class IPrinterPlugin;
class IFeaturePlugin;
class QPluginLoader;

class PrinterPluginRegistry;
class FeaturePluginRegistry;

class PluginManager : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT

public:
    explicit PluginManager(QObject* parent);
    virtual ~PluginManager() override;

    bool init();

    // Getter
    PrinterPluginRegistry* registryPrinters()            { return m_registryPrinters; }
    FeaturePluginRegistry* registryFeatures()            { return m_registryFeatures; }

private:
    bool loadPlugins();

    bool loadPluginDirectory(const QString& qstrPluginDirectory);
    bool loadPluginFile(const QString& qstrPluginFileName);

    void registerPrinterPlugin(IPrinterPlugin* ptrPrinterPlugin);
    void registerFeaturePlugin(IFeaturePlugin* ptrFeaturePlugin);

    //QList<IPlugin*> plugins() const     { return m_qlstPlugins; }

private:
    QList<QPluginLoader*> m_lstPluginLoaders;

    PrinterPluginRegistry* m_registryPrinters;
    FeaturePluginRegistry* m_registryFeatures;
};

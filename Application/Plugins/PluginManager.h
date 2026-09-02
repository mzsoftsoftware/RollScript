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
    ~PluginManager() override;

    bool init();

    // Getter
    PrinterPluginRegistry* registryPrinters()            { return m_ptrRegistryPrinters; }
    FeaturePluginRegistry* registryFeatures()            { return m_ptrRegistryFeatures; }

private:
    bool loadPlugins();

    bool loadPluginDirectory(const QString& qstrPluginDirectory);
    bool loadPluginFile(const QString& qstrPluginFileName);

    void registerPrinterPlugin(IPrinterPlugin* ptrPrinterPlugin);
    void registerFeaturePlugin(IFeaturePlugin* ptrFeaturePlugin);

private:
    QList<QPluginLoader*> m_qlstPluginLoaders;

    PrinterPluginRegistry* m_ptrRegistryPrinters;
    FeaturePluginRegistry* m_ptrRegistryFeatures;
};

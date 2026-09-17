#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"

class IPlugin;
class IPrinterPlugin;
class IFeaturePlugin;
class QPluginLoader;

class LicenseProviderRegistry;
class PrinterPluginRegistry;
class FeaturePluginRegistry;

class TranslationManager;


class PluginManager : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT

public:
    explicit PluginManager(TranslationManager* ptrTranslationManager, QObject* parent);
    ~PluginManager() override;

    bool init();

    // Getter
    LicenseProviderRegistry* registryLicenses()          { return m_ptrRegistryLicenses; }
    PrinterPluginRegistry* registryPrinters()            { return m_ptrRegistryPrinters; }
    FeaturePluginRegistry* registryFeatures()            { return m_ptrRegistryFeatures; }

private:
    bool loadPlugins();

    bool loadPluginDirectory(const QString& qstrPluginDirectory);
    bool loadPluginFile(const QString& qstrPluginFileName);

    void registerPrinterPlugin(IPrinterPlugin* ptrPrinterPlugin);
    void registerFeaturePlugin(IFeaturePlugin* ptrFeaturePlugin);

private:
    TranslationManager* m_ptrTranslationManager;

    QList<QPluginLoader*> m_qlstPluginLoaders;

    LicenseProviderRegistry* m_ptrRegistryLicenses;
    PrinterPluginRegistry* m_ptrRegistryPrinters;
    FeaturePluginRegistry* m_ptrRegistryFeatures;

};

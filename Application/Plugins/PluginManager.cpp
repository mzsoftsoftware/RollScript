#include "PluginManager.h"

#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QPluginLoader>

#include "Core/Plugins/IPlugin.h"
#include "Core/Plugins/IPrinterPlugin.h"
#include "Core/Plugins/IFeaturePlugin.h"

#include "Core/Licensing/ILicenseProvider.h"

#include "LicenseProviderRegistry.h"
#include "PrinterPluginRegistry.h"
#include "FeaturePluginRegistry.h"

#include "Translation/TranslationManager.h"


PluginManager::PluginManager(TranslationManager* ptrTranslationManager, QObject* parent)
    : QObject{parent}
    , m_ptrTranslationManager(ptrTranslationManager)
{
    m_ptrRegistryPrinters = new PrinterPluginRegistry(this);
    m_ptrRegistryFeatures = new FeaturePluginRegistry(this);
}
PluginManager::~PluginManager()
{
    qDeleteAll(m_qlstPluginLoaders);
    m_qlstPluginLoaders.clear();
}

bool PluginManager::init()
{
    return loadPlugins();
}


bool PluginManager::loadPlugins()
{
    const QString qstrBasePath = QDir(QCoreApplication::applicationDirPath()).absoluteFilePath(QStringLiteral(".."));
    const QString qstrPluginPath = QDir::cleanPath(qstrBasePath + QStringLiteral("/plugins"));

    if(!loadPluginDirectory(qstrPluginPath + QStringLiteral("/printers")))
    {
        return false;
    }

    if(!loadPluginDirectory(qstrPluginPath + QStringLiteral("/features")))
    {
        return false;
    }

    return true;
}

bool PluginManager::loadPluginDirectory(const QString& qstrPluginDirectory)
{
    QDir dirPluginDirectory(qstrPluginDirectory);
    if(!dirPluginDirectory.exists())
    {
        ROLLSCRIPT_ERROR(tr("PluginLoadFailed"), QStringLiteral("loadPluginDirectory : path does not exist = %1").arg(qstrPluginDirectory));
        return false;
    }

    bool result = true;
    const QFileInfoList pluginFiles = dirPluginDirectory.entryInfoList(QDir::Files);
    for(const QFileInfo& fileInfo : pluginFiles)
    {
        if(!loadPluginFile(fileInfo.absoluteFilePath()))
        {
            result = false;
            break;
        }

        if(!m_ptrTranslationManager->loadPluginTranslation(fileInfo.completeBaseName()))
        {
            ROLLSCRIPT_ERROR_CAUSE(tr("PluginLoadFailed"), QStringLiteral("loadPluginTranslation failed."), m_ptrTranslationManager->takeError());
            result = false;
            break;
        }
    }

    return result;
}

bool PluginManager::loadPluginFile(const QString& qstrPluginFileName)
{
    QPluginLoader* ptrPluginLoader = new QPluginLoader(qstrPluginFileName, this);
    QObject* ptrInstance = ptrPluginLoader->instance();
    if(!ptrInstance)
    {
        ROLLSCRIPT_ERROR(tr("PluginLoadFailed"), QStringLiteral("ptrInstance is nullptr: %1").arg(ptrPluginLoader->errorString()));
        delete ptrPluginLoader;
        return false;
    }

    m_qlstPluginLoaders.append(ptrPluginLoader);

    ILicenseProvider* ptrLicenseProvider = qobject_cast<ILicenseProvider*>(ptrInstance);
    if(ptrLicenseProvider)
    {
        if(!m_ptrRegistryLicenses->registerProvider(ptrLicenseProvider))
        {
            ROLLSCRIPT_ERROR_CAUSE(tr("PluginLoadFailed"), QStringLiteral("m_registryFeatures.registerPlugin failed."), m_ptrRegistryFeatures->takeError());
            return false;
        }
    }

    IPrinterPlugin* ptrPrinterPlugin = qobject_cast<IPrinterPlugin*>(ptrInstance);
    if(ptrPrinterPlugin)
    {
        if(!m_ptrRegistryPrinters->registerPlugin(ptrPrinterPlugin))
        {
            ROLLSCRIPT_ERROR_CAUSE(tr("PluginLoadFailed"), QStringLiteral("m_registryPrinters.registerPlugin failed."), m_ptrRegistryPrinters->takeError());
            return false;
        }
        return true;
    }

    IFeaturePlugin* ptrFeaturePlugin = qobject_cast<IFeaturePlugin*>(ptrInstance);
    if(ptrFeaturePlugin)
    {
        if(!m_ptrRegistryFeatures->registerPlugin(ptrFeaturePlugin))
        {
            ROLLSCRIPT_ERROR_CAUSE(tr("PluginLoadFailed"), QStringLiteral("m_registryFeatures.registerPlugin failed."), m_ptrRegistryFeatures->takeError());
            return false;
        }
        return true;
    }

    ROLLSCRIPT_ERROR(tr("PluginLoadFailed"), QStringLiteral("unknown plugin type"));
    return false;
}

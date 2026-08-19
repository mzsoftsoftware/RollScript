#include "PluginManager.h"

#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QPluginLoader>

#include "Core/Plugins/IPlugin.h"
#include "Core/Plugins/IPrinterPlugin.h"
#include "Core/Plugins/IFeaturePlugin.h"

#include "PrinterPluginRegistry.h"
#include "FeaturePluginRegistry.h"


PluginManager::PluginManager(QObject *parent)
    : QObject{parent}
{
    m_registryPrinters = new PrinterPluginRegistry(this);
    m_registryFeatures = new FeaturePluginRegistry(this);
}
PluginManager::~PluginManager()
{
    qDeleteAll(m_lstPluginLoaders);
    m_lstPluginLoaders.clear();
}

bool PluginManager::init()
{
    return loadPlugins();
}


bool PluginManager::loadPlugins()
{
    QString qstrBasePath = QCoreApplication::applicationDirPath();
    QDir dir(qstrBasePath);
    if(dir.dirName() == QStringLiteral("Application"))
    {
        qstrBasePath = dir.absolutePath() + QStringLiteral("/..");
    }
    const QString qstrPluginPath = qstrBasePath + QStringLiteral("/plugins");

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

    m_lstPluginLoaders.append(ptrPluginLoader);

    IPrinterPlugin* ptrPrinterPlugin = qobject_cast<IPrinterPlugin*>(ptrInstance);
    if(ptrPrinterPlugin)
    {
        if(!m_registryPrinters->registerPlugin(ptrPrinterPlugin))
        {
            ROLLSCRIPT_ERROR_CAUSE(tr("PluginLoadFailed"), QStringLiteral("m_registryPrinters.registerPlugin failed."), m_registryPrinters->takeError());
            return false;
        }
        return true;
    }

    IFeaturePlugin* ptrFeaturePlugin = qobject_cast<IFeaturePlugin*>(ptrInstance);
    if(ptrFeaturePlugin)
    {
        if(!m_registryFeatures->registerPlugin(ptrFeaturePlugin))
        {
            ROLLSCRIPT_ERROR_CAUSE(tr("PluginLoadFailed"), QStringLiteral("m_registryFeatures.registerPlugin failed."), m_registryFeatures->takeError());
            return false;
        }
        return true;
    }

    ROLLSCRIPT_ERROR(tr("PluginLoadFailed"), QStringLiteral("unknown plugin type"));
    return false;
}

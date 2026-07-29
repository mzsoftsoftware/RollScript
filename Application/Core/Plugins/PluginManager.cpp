#include "PluginManager.h"

#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QPluginLoader>

#include "Common/Core/Plugins/IPlugin.h"
#include "Common/Core/Plugins/IPrinterPlugin.h"
#include "Common/Core/Plugins/IFeaturePlugin.h"


PluginManager::PluginManager(QObject *parent)
    : QObject{parent}
{
}
PluginManager::~PluginManager()
{
    qDeleteAll(m_lstPluginLoaders);
    m_lstPluginLoaders.clear();
}

bool PluginManager::loadPlugins()
{
    QString qstrBasePath = QCoreApplication::applicationDirPath();
    QDir dir(qstrBasePath);
    if(dir.dirName() == "Application")
    {
        qstrBasePath = dir.absolutePath() + "/..";
    }
    const QString qstrPluginPath = qstrBasePath + "/plugins";

    if(!loadPluginDirectory(qstrPluginPath + "/printers"))
    {
        return false;
    }

    if(!loadPluginDirectory(qstrPluginPath + "/features"))
    {
        // TASK : loadPluginDirectory(qstrPluginPath + "/features") always returns true !!!
        return true;
    }

    return true;
}

bool PluginManager::loadPluginDirectory(const QString& qstrPluginDirectory)
{
    QDir dirPluginDirectory(qstrPluginDirectory);
    if(!dirPluginDirectory.exists())
    {
        m_qstrLastError = QString("loadPluginDirectory : path does not exist = %1").arg(qstrPluginDirectory);
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
        m_qstrLastError = ptrPluginLoader->errorString();
        delete ptrPluginLoader;
        return false;
    }

    m_lstPluginLoaders.append(ptrPluginLoader);

    IPrinterPlugin* ptrPrinterPlugin = qobject_cast<IPrinterPlugin*>(ptrInstance);
    if(ptrPrinterPlugin)
    {
        if(!m_registryPrinters.registerPlugin(ptrPrinterPlugin))
        {
            m_qstrLastError = m_registryPrinters.lastError();
            return false;
        }
        return true;
    }

    IFeaturePlugin* ptrFeaturePlugin = qobject_cast<IFeaturePlugin*>(ptrInstance);
    if(ptrFeaturePlugin)
    {
        if(!m_registryFeatures.registerPlugin(ptrFeaturePlugin))
        {
            m_qstrLastError = m_registryFeatures.lastError();
            return false;
        }
        return true;
    }

    // TASK : Use tr !!!
    m_qstrLastError = "Unknown Plugin";
    return false;
}

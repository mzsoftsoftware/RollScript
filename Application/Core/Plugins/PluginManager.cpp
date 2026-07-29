#include "PluginManager.h"

#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QPluginLoader>

#include "Common/Core/Plugins/IPlugin.h"


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

    // TASK : Load FeaturesPlugins
    /*if(!loadPluginDirectory(qstrPluginPath + "/features"))
    {
        return false;
    }*/

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

    qDebug()
        << "Plugin loaded:"
        << qstrPluginFileName;

    return true;
}


/*
    QPluginLoader loader(...);

    QObject* object = loader.instance();

    auto* printerPlugin =
        qobject_cast<IPrinterPlugin*>(object);

    m_printerPluginRegistry.registerPlugin(printerPlugin);
*/

/*
void PluginManager::registerPlugin(IPlugin* ptrPlugin)
{
    if(!ptrPlugin)
    {
        qWarning() << "Cannot register null plugin.";
        return;
    }

    if(m_qlstPlugins.contains(ptrPlugin))
    {
        qWarning() << "Plugin already registered."
                   << ptrPlugin->pluginId();
        return;
    }

    m_qlstPlugins.append(ptrPlugin);

    qInfo() << "Plugin registered:"
            << ptrPlugin->pluginId()
            << ptrPlugin->displayName()
            << ptrPlugin->version();
}
*/
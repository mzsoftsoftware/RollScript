#include "PluginManager.h"

#include <QDebug>
#include "IPlugin.h"


PluginManager::PluginManager(QObject *parent)
    : QObject{parent}
{
}

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

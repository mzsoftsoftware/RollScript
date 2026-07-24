#pragma once

#include <QObject>

class IPlugin;


class PluginManager : public QObject
{
    Q_OBJECT

public:
    explicit PluginManager(QObject *parent = nullptr);

    void registerPlugin(IPlugin* ptrPlugin);

    QList<IPlugin*> plugins() const     { return m_qlstPlugins; }

private:
    QList<IPlugin*> m_qlstPlugins;
};

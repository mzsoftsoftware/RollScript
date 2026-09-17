#pragma once

#include <QString>
#include <QIcon>


class IPluginInfo
{
public:
    virtual ~IPluginInfo() = default;

    virtual const QString& pluginId() const = 0;
    virtual const QString& pluginVersion() const = 0;

    virtual QString pluginName() const = 0;
    virtual QString pluginDescription() const = 0;
    virtual const QIcon& pluginIcon() const = 0;
};

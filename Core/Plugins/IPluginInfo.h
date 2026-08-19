#pragma once

#include <QString>

class IPluginInfo
{
public:
    virtual ~IPluginInfo() = default;

    virtual const QString& pluginId() const = 0;
    virtual const QString& pluginVersion() const = 0;

    virtual QString pluginDisplayName() const = 0;
};

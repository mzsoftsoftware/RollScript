#pragma once

#include <QString>

class IPlugin
{
public:
    virtual ~IPlugin() = default;

    virtual QString pluginId() const = 0;
    virtual QString displayName() const = 0;
    virtual QString version() const = 0;
};

#pragma once

#include <QtPlugin>
#include <QString>

class IPlugin
{
public:
    virtual ~IPlugin() = default;

    virtual QString pluginId() const = 0;
    virtual QString displayName() const = 0;
    virtual QString version() const = 0;
};

#define ROLLSCRIPT_IPLUGIN_IID "de.mzsoft.rollscript.plugins.base"
Q_DECLARE_INTERFACE(IPlugin, ROLLSCRIPT_IPLUGIN_IID)
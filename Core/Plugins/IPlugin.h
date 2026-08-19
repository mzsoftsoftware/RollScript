#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"

#include <QtPlugin>
#include <QString>

class IPluginInfo;


class IPlugin : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT

public:
    explicit IPlugin(QObject* parent)
        : QObject(parent)
    {}
    virtual ~IPlugin() = default;

    virtual const IPluginInfo* pluginInfo() const = 0;
};

#define ROLLSCRIPT_IPLUGIN_IID "de.mzsoft.rollscript.plugins.base"
Q_DECLARE_INTERFACE(IPlugin, ROLLSCRIPT_IPLUGIN_IID)

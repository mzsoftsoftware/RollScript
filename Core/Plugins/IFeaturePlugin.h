#pragma once

#include "IPlugin.h"

#include <QIcon>
#include <QList>

#include "IFeaturePluginInfo.h"


class IFeaturePlugin : public IPlugin
{
    Q_OBJECT

public:
    explicit IFeaturePlugin(QObject* parent)
        : IPlugin(parent)
    {}
    virtual ~IFeaturePlugin() override = default;

    virtual const IFeaturePluginInfo* featurePluginInfo() const = 0;
};

#define ROLLSCRIPT_IFEATUREPLUGIN_IID "de.mzsoft.rollscript.plugins.feature"
Q_DECLARE_INTERFACE(IFeaturePlugin, ROLLSCRIPT_IFEATUREPLUGIN_IID)

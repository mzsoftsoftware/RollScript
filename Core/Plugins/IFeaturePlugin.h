#pragma once

#include "IPlugin.h"

#include <QIcon>
#include <QList>


class IFeaturePlugin : public IPlugin
{
public:
    virtual ~IFeaturePlugin() override = default;

    virtual QIcon icon() const = 0;
};

#define ROLLSCRIPT_IFEATUREPLUGIN_IID "de.mzsoft.rollscript.plugins.feature"
Q_DECLARE_INTERFACE(IFeaturePlugin, ROLLSCRIPT_IFEATUREPLUGIN_IID)

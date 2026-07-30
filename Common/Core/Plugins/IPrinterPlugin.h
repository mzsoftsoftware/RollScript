#pragma once

#include "IPlugin.h"

#include <QIcon>
#include <QList>

struct USBDeviceInfo;


class IPrinterPlugin : public IPlugin
{
public:
    virtual ~IPrinterPlugin() override = default;

    virtual QIcon icon() const = 0;

    virtual bool supportsUsb(const USBDeviceInfo& device) const = 0;

    // TASK : virtual QList<RollScriptMedia> availableMedias() const = 0;
};

#define ROLLSCRIPT_IPRINTERPLUGIN_IID "de.mzsoft.rollscript.plugins.printer"
Q_DECLARE_INTERFACE(IPrinterPlugin, ROLLSCRIPT_IPRINTERPLUGIN_IID)

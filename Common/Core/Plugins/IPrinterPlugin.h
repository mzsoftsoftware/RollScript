#pragma once

#include "IPlugin.h"

#include <QIcon>
#include <QList>

struct UsbDeviceInfo;


class IPrinterPlugin : public IPlugin
{
public:
    virtual ~IPrinterPlugin() override = default;

    virtual QIcon icon() const = 0;

    virtual bool supportsUsb(const UsbDeviceInfo& device) const = 0;

    // TASK : virtual QList<RollScriptMedia> availableMedias() const = 0;
};

#define ROLLSCRIPT_IPRINTERPLUGIN_IID "de.mzsoft.rollscript.plugins.printer"
Q_DECLARE_INTERFACE(IPrinterPlugin, ROLLSCRIPT_IPRINTERPLUGIN_IID)

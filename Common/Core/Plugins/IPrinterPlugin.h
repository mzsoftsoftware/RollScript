#pragma once

#include "IPlugin.h"

#include <QIcon>
#include <QList>

struct USBDeviceInfo;
class PrinterInstance;


class IPrinterPlugin : public IPlugin
{
public:
    virtual ~IPrinterPlugin() override = default;

    virtual QIcon icon() const = 0;

    virtual bool supportsUsb(const USBDeviceInfo* ptrDevice) const = 0;


    /*
     * The plugin operates on one active PrinterInstance.
     *
     * Multiple simultaneously opened printers are not supported
     * by the standard RollScript print workflow.
     */

    virtual QString lastError() const = 0;

    virtual bool open(PrinterInstance* ptrPrinterInstance) = 0;
    virtual bool close() = 0;
};

#define ROLLSCRIPT_IPRINTERPLUGIN_IID "de.mzsoft.rollscript.plugins.printer"
Q_DECLARE_INTERFACE(IPrinterPlugin, ROLLSCRIPT_IPRINTERPLUGIN_IID)

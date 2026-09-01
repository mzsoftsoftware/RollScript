#pragma once

#include "IPlugin.h"

#include <QtPlugin>
#include <QList>
#include "Core/Printers/PrinterDeviceInfo.h"

struct USBDeviceInfo;
class PrinterInstance;
class PrinterMedia;
class IPrinterPluginInfo;


class IPrinterPlugin : public IPlugin
{
    Q_OBJECT

public:
    explicit IPrinterPlugin(QObject* parent)
        : IPlugin(parent)
    {}
    virtual ~IPrinterPlugin() override = default;

    virtual const IPrinterPluginInfo* printerPluginInfo() const = 0;

    virtual bool supportsUsb(const USBDeviceInfo* ptrDevice) const = 0;

    virtual QList<PrinterMedia*> createPrinterMedias() = 0;
    virtual PrinterDeviceInfo createPrinterDeviceInfo() = 0;

    /*
     * The plugin operates on one active PrinterInstance.
     *
     * Multiple simultaneously opened printers are not supported
     * by the standard RollScript print workflow.
     */
    virtual bool open(PrinterInstance* ptrPrinterInstance) = 0;
    virtual bool close() = 0;
    virtual bool print(const QImage& printImage, const PrinterMedia* ptrPrinterMediaId) = 0;

signals:
    void printerError();
    void printerPrintStarted(int iSteps);
    void printerPrintProgress(int iStep);
    void printerPrintFinished();
};

#define ROLLSCRIPT_IPRINTERPLUGIN_IID "de.mzsoft.rollscript.plugins.printer"
Q_DECLARE_INTERFACE(IPrinterPlugin, ROLLSCRIPT_IPRINTERPLUGIN_IID)

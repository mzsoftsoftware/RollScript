#pragma once

#include <QObject>
#include "Core/Plugins/IPrinterPlugin.h"
#include "DLP350PrinterPluginInfo.h"

class QThread;
class QTimer;

class DymoLabelPoint350PrinterWorker;
class PrinterInstanceUSB;
class DymoLabelPoint350PrinterMedia;
class DymoLabelPoint350PrinterJob;


class DymoLabelPoint350PrinterPlugin : public IPrinterPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "de.mzsoft.rollscript.printer.dymolabelpoint350" FILE "DymoLabelPoint350.json")
    Q_INTERFACES(IPrinterPlugin)

public:
    // Constructor / Destructor
    explicit DymoLabelPoint350PrinterPlugin(QObject* parent = nullptr);
    ~DymoLabelPoint350PrinterPlugin() override;

    // Infos
    const IPluginInfo* pluginInfo() const override                  { return &m_pluginInfo; }
    const IPrinterPluginInfo* printerPluginInfo() const override    { return &m_pluginInfo; }

    // Operations
    virtual bool supportsUsb(const USBDeviceInfo* ptrDevice) const override;

    virtual QList<PrinterMedia*> createPrinterMedias() override;
    virtual PrinterDeviceInfo createPrinterDeviceInfo() override;

    virtual bool open(PrinterInstance* ptrPrinterInstance) override;
    virtual bool close() override;
    virtual bool print(const QImage& printImage, const PrinterMedia* ptrPrinterMediaId) override;

signals:
    void enqueueJob(DymoLabelPoint350PrinterJob* ptrJob);

private slots:
    void slot_timerAlive();
    void slot_PrintJob_Started(int iSteps);
    void slot_PrintJob_Progress(int iStep);
    void slot_PrintJob_Finished();
    void slot_PrintJob_Error();
    void slot_JobAlive_Started();
    void slot_JobAlive_Finished();
    void slot_JobAlive_Error();

private:
    DymoLabelPoint350PrinterPluginInfo m_pluginInfo;
    QThread* m_ptrWorkerThread = nullptr;
    DymoLabelPoint350PrinterWorker* m_ptrWorker = nullptr;

    // Active printer instance.
    // Only one active printer is supported.
    // USB specific access for this printer plugin.
    PrinterInstanceUSB* m_ptrPrinterInstanceUSB = nullptr;

    QTimer* m_ptrTimerAlive = nullptr;
};

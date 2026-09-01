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
    explicit DymoLabelPoint350PrinterPlugin(QObject* parent = nullptr);
    ~DymoLabelPoint350PrinterPlugin() override;

    // Infos
    const IPluginInfo* pluginInfo() const override                  { return &m_pluginInfo; }
    const IPrinterPluginInfo* printerPluginInfo() const override    { return &m_pluginInfo; }

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
    //bool fillDataFromImage(const QImage& printImage, const DymoLabelPoint350PrinterMedia* ptrPluginMedia, QVector<QByteArray>& vecArrData);
    //bool fillDataFromImageLine(const int iLine, const QImage& printImage, const int iEmptyBits, const int iImageBits, const int iImageLineOffset, QByteArray& baLineData);

    //bool alive();
    //bool readStatus();
    //bool readMedia();
    //bool sendCommand(const QByteArray& baCommand, QByteArray* baResponse = nullptr);

private:
    DymoLabelPoint350PrinterPluginInfo m_pluginInfo;
    //const QString m_qstrPluginId = "dymo.labelpoint350";
    //const QString m_qstrDisplayName = "Dymo LabelPoint 350";
    //const QString m_qstrVersion = "1.0.0";
    //const QIcon m_icon;

    QThread* m_ptrWorkerThread = nullptr;
    DymoLabelPoint350PrinterWorker* m_ptrWorker = nullptr;


    // Active printer instance.
    // Only one active printer is supported.
    // USB specific access for this printer plugin.
    PrinterInstanceUSB* m_ptrPrinterInstanceUSB = nullptr;

    QTimer* m_ptrTimerAlive = nullptr;

};

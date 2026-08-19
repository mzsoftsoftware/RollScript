#pragma once

#include <QObject>
#include "Core/Plugins/IPrinterPlugin.h"
#include "DymoLabelPoint350PrinterPluginInfo.h"

#include <QTimer>


class PrinterInstanceUSB;


class DymoLabelPoint350PrinterPlugin : public IPrinterPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "de.mzsoft.rollscript.printer.dymolabelpoint350" FILE "DymoLabelPoint350.json")
    Q_INTERFACES(IPrinterPlugin)

public:
    explicit DymoLabelPoint350PrinterPlugin(QObject* parent = nullptr);

    // Infos
    const IPluginInfo* pluginInfo() const override                  { return &m_pluginInfo; }
    const IPrinterPluginInfo* printerPluginInfo() const override    { return &m_pluginInfo; }
    //virtual const QString& pluginId() const override            { return m_qstrPluginId; }
    //virtual const QString& displayName() const override         { return m_qstrDisplayName; }
    //virtual const QString& version() const override             { return m_qstrVersion; }
    //virtual const QIcon& icon() const override                  { return m_icon; }

    virtual bool supportsUsb(const USBDeviceInfo* ptrDevice) const override;

    virtual QList<PrinterMedia*> createPrinterMedias() override;

    virtual bool open(PrinterInstance* ptrPrinterInstance) override;
    virtual bool close() override;

private slots:
    void slot_timerAlive();

private:
    bool alive();
    bool readStatus();
    bool readMedia();
    bool sendCommand(const QByteArray& baCommand, QByteArray* baResponse = nullptr);

private:
    DymoLabelPoint350PrinterPluginInfo m_pluginInfo;
    //const QString m_qstrPluginId = "dymo.labelpoint350";
    //const QString m_qstrDisplayName = "Dymo LabelPoint 350";
    //const QString m_qstrVersion = "1.0.0";
    //const QIcon m_icon;

    // Active printer instance.
    // Only one active printer is supported.
    // USB specific access for this printer plugin.
    PrinterInstanceUSB* m_ptrPrinterInstanceUSB = nullptr;

    QTimer* m_ptrTimerAlive = nullptr;
};

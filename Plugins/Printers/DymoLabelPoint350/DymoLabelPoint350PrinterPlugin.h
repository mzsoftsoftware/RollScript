#pragma once

#include <QObject>

#include <QTimer>

#include "Common/Core/Plugins/IPrinterPlugin.h"

class PrinterInstanceUSB;


class DymoLabelPoint350PrinterPlugin :
        public QObject,
        public IPrinterPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "de.mzsoft.rollscript.printer" FILE "DymoLabelPoint350.json")
    Q_INTERFACES(IPrinterPlugin)

public:

    explicit DymoLabelPoint350PrinterPlugin(QObject* parent = nullptr);

    virtual QString pluginId() const override;
    virtual QString displayName() const override;
    virtual QString version() const override;

    virtual QIcon icon() const override;

    virtual bool supportsUsb(const USBDeviceInfo* ptrDevice) const override;

    virtual QString lastError() const override                      { return m_qstrLastError; }

    virtual bool open(PrinterInstance* ptrPrinterInstance) override;
    virtual bool close() override;

private slots:
    void slot_timerAlive();

private:
    bool alive();
    bool readStatus();
    bool readMedia();
    bool sendCommand(const QByteArray& baCommand, QByteArray& baResponse);

private:
    QString m_qstrLastError;

    // Active printer instance.
    // Only one active printer is supported.
    // USB specific access for this printer plugin.
    PrinterInstanceUSB* m_ptrPrinterInstanceUSB = nullptr;

    QTimer* m_ptrTimerAlive = nullptr;
};

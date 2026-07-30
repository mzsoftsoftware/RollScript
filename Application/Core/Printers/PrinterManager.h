#pragma once

#include <QObject>
#include <QHash>

class PluginManager;
class PrinterInstance;

#include "Common/Core/Printers/USBDeviceInfo.h"


class PrinterManager : public QObject
{
    Q_OBJECT
public:
    explicit PrinterManager(PluginManager* ptrPluginManager, QObject *parent);
    virtual ~PrinterManager() override;

    // Getter
    QString lastError() const                                               { return m_qstrLastError; }
    QStringList availablePrinterIds() const                                 { return m_qstrPrinterIds; }
    PrinterInstance* printerInstance(const QString& qstrDeviceId) const     { return m_hashPrinterInstances.value(qstrDeviceId, nullptr); }

public slots:
    void slot_ScanForDevices();

signals:
    void scanFinished();
    void deviceError(const QString& message);

private:
    QList<USBDeviceInfo> scanForUsbDevices();

/*
    // USB Device handling.
    bool usbScan();
    bool usbCloseActiveConnection();
    //bool usbOpenDevice(DeviceDymo* ptrDevice);
*/
private:
    QString m_qstrLastError;
    PluginManager* m_ptrPluginManager = nullptr;

    QStringList m_qstrPrinterIds;
    QHash<QString, PrinterInstance*> m_hashPrinterInstances;
};

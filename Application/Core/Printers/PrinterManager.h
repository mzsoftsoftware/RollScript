#pragma once

#include <QObject>
#include <QHash>

class PluginManager;
class USBManager;

class PrinterInstance;

#include "Common/Core/USB/USBDeviceInfo.h"


class PrinterManager : public QObject
{
    Q_OBJECT
public:
    explicit PrinterManager(PluginManager* ptrPluginManager, USBManager* ptrUSBManager, QObject *parent);
    virtual ~PrinterManager() override;

    bool init();

    // Getter
    QString lastError() const                                               { return m_qstrLastError; }
    QStringList availablePrinterIds() const                                 { return m_qstrPrinterIds; }
    PrinterInstance* printerInstance(const QString& qstrDeviceId) const     { return m_hashPrinterInstances.value(qstrDeviceId, nullptr); }
    PrinterInstance* currentPrinter() const                                 { return m_ptrCurrentPrinterInstance; }

    bool scanForDevices();
    bool switchPrinter(const QString& qstrPrinterId);

signals:
    void scanFinished();
    void printerChanged();
    void managerError(const QString& message);

private:
    QString m_qstrLastError;
    PluginManager* m_ptrPluginManager = nullptr;
    USBManager* m_ptrUSBManager = nullptr;

    QStringList m_qstrPrinterIds;
    QHash<QString, PrinterInstance*> m_hashPrinterInstances;

    PrinterInstance* m_ptrCurrentPrinterInstance = nullptr;
};

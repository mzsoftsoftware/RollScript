#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"

#include <QHash>

class PluginManager;
class USBManager;

class PrinterInstance;
class PrinterMedia;

#include "Core/USB/USBDeviceInfo.h"


class PrinterManager : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT
public:
    // Constructor / Destructor
    explicit PrinterManager(PluginManager* ptrPluginManager, USBManager* ptrUSBManager, QObject* parent);
    ~PrinterManager() override;

    // Getter
    const QStringList& availablePrinterIds() const                                { return m_qstrPrinterIds; }
    const PrinterInstance* printerInstance(const QString& qstrDeviceId) const     { return m_qhashPrinterInstances.value(qstrDeviceId, nullptr); }
    const PrinterInstance* currentPrinter() const                                 { return m_ptrCurrentPrinterInstance; }

    // Operations
    bool init();

    bool scanForDevices();
    bool switchPrinter(const QString& qstrPrinterId);
    bool print(const QImage& printImage, const PrinterMedia* ptrPrinterMediaId);

private slots:
    void slotPrinterInstanceError();

signals:
    void scanFinished();
    void printerChanged();
    void printStarted(int iSteps);
    void printProgress(int iStep);
    void printFinished();
    void managerError();

private:
    PluginManager* m_ptrPluginManager = nullptr;
    USBManager* m_ptrUSBManager = nullptr;

    QStringList m_qstrPrinterIds;
    QHash<QString, PrinterInstance*> m_qhashPrinterInstances;

    // RollScript supports one active printer only.
    // The current printer is managed by PrinterManager.
    PrinterInstance* m_ptrCurrentPrinterInstance = nullptr;
};

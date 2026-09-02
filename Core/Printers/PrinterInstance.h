#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"

#include <QIcon>
#include <QHash>

class IPrinterPlugin;
class PrinterMedia;
#include "Core/Printers/PrinterDeviceInfo.h"


class PrinterInstance : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT

public:
    // Constructor / Destructor
    explicit PrinterInstance(IPrinterPlugin* ptrPrinterPlugin, QObject* parent);
    ~PrinterInstance() override;

    // Getter
    const QString& id() const                             { return m_qstrId; }
    const QString& displayName() const                    { return m_qstrDisplayName; }
    const QIcon& icon() const                             { return m_icon; }

    const IPrinterPlugin* plugin() const                  { return m_ptrPrinterPlugin; }

    QStringList availableMediaIds() const                               { return m_qstrPrinterMediaIds; }
    const PrinterMedia* media(const QString& qstrPrinterMediaId) const  { return m_qhashPrinterMedias.value(qstrPrinterMediaId, nullptr); }
    const PrinterDeviceInfo& deviceInfo() const                         { return m_printerDeviceInfo; }

    // Operations
    bool print(const QImage& printImage, const PrinterMedia* ptrPrinterMediaId);

    // Connection
    virtual bool open() = 0;
    virtual bool close() = 0;
    virtual bool isConnected() = 0;

private slots:
    void slotPrinterPluginError();

signals:
    void printerError();
    void printerPrintStarted(int iSteps);
    void printerPrintProgress(int iStep);
    void printerPrintFinished();

protected:
    IPrinterPlugin* m_ptrPrinterPlugin = nullptr;

    QString                     m_qstrId;
    QString                     m_qstrDisplayName;
    QIcon                       m_icon;

    QStringList                     m_qstrPrinterMediaIds;
    QHash<QString, PrinterMedia*>   m_qhashPrinterMedias;

    PrinterDeviceInfo           m_printerDeviceInfo;
};

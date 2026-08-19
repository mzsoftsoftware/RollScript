#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"

#include <QIcon>
#include <QHash>

class IPrinterPlugin;
class PrinterMedia;


class PrinterInstance : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT

public:
    explicit PrinterInstance(IPrinterPlugin* ptrPrinterPlugin, QObject* parent);
    virtual ~PrinterInstance() override;

    // Getter
    const QString& id() const                             { return m_qstrId; }
    const QString& displayName() const                    { return m_qstrDisplayName; }
    const QIcon& icon() const                             { return m_icon; }

    const IPrinterPlugin* plugin() const                  { return m_ptrPrinterPlugin; }

    virtual QStringList availableMediaIds() const                               { return m_qstrPrinterMediaIds; }
    virtual const PrinterMedia* media(const QString& qstrPrinterMediaId) const  { return m_hashPrinterMedias.value(qstrPrinterMediaId, nullptr); }

    // Connection
    virtual bool open() = 0;
    virtual bool close() = 0;
    virtual bool isConnected() = 0;

private slots:
    void slotPrinterPluginError();

signals:
    void printerError();

protected:
    IPrinterPlugin* m_ptrPrinterPlugin = nullptr;

    QString                     m_qstrId;
    QString                     m_qstrDisplayName;
    QIcon                       m_icon;

    QStringList                     m_qstrPrinterMediaIds;
    QHash<QString, PrinterMedia*>   m_hashPrinterMedias;
};

#pragma once

#include <QObject>
#include <QIcon>
#include <QHash>

class IPrinterPlugin;
class PrinterMedia;


class PrinterInstance : public QObject
{
    Q_OBJECT

public:
    explicit PrinterInstance(IPrinterPlugin* ptrPrinterPlugin, QObject* parent);
    virtual ~PrinterInstance() override;

    // Getter
    QString lastError() const                       { return m_qstrLastError; }
    QString id() const                              { return m_qstrId; }
    QString displayName() const                     { return m_qstrDisplayName; }
    QIcon icon() const                              { return m_icon; }

    IPrinterPlugin* plugin() const                  { return m_ptrPrinterPlugin; }

    virtual QStringList availableMediaIds() const                   { return m_qstrPrinterMediaIds; }
    virtual PrinterMedia* media(const QString& qstrMediaId) const   { return m_hashPrinterMedias.value(qstrMediaId, nullptr); }

    // Connection
    virtual bool open() = 0;
    virtual bool close() = 0;
    virtual bool isConnected() = 0;

protected:
    QString m_qstrLastError;
    IPrinterPlugin* m_ptrPrinterPlugin = nullptr;

    QString                     m_qstrId;
    QString                     m_qstrDisplayName;
    QIcon                       m_icon;

    QStringList                     m_qstrPrinterMediaIds;
    QHash<QString, PrinterMedia*>   m_hashPrinterMedias;
};

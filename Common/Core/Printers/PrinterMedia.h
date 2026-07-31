#pragma once

#include <QObject>
#include <QIcon>


class PrinterMedia : public QObject
{
    Q_OBJECT

public:
    explicit PrinterMedia(QObject *parent);
    virtual ~PrinterMedia() override;

    // Getter
    QString id() const                              { return m_qstrId; }
    QString displayName() const                     { return m_qstrDisplayName; }
    QIcon icon() const                              { return m_icon; }

protected:
    QString                     m_qstrId;
    QString                     m_qstrDisplayName;
    QIcon                       m_icon;
};

#pragma once

#include <QObject>
#include <QIcon>

#include "PrinterMediaConstraints.h"


class PrinterMedia : public QObject
{
    Q_OBJECT

public:
    explicit PrinterMedia(const QString& qstrId, const QString& qstrDisplayName, QObject *parent);
    virtual ~PrinterMedia() override;

    // Getter
    QString id() const                                  { return m_qstrId; }
    QString displayName() const                         { return m_qstrDisplayName; }
    QIcon icon() const                                  { return m_icon; }
    const PrinterMediaConstraints& constraints() const  { return m_printerMediaConstraints; }

protected:
    QString                     m_qstrId;
    QString                     m_qstrDisplayName;
    QIcon                       m_icon;

    PrinterMediaConstraints     m_printerMediaConstraints;
};

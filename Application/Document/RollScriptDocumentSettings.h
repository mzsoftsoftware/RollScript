#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"

#include <QMarginsF>


class RollScriptDocumentSettings : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT
public:
    explicit RollScriptDocumentSettings(QObject *parent);

    // Getter
    QString printerMediaId() const                  { return m_qstrPrinterMediaId; }
    QMarginsF marginsMm() const                     { return m_marginsMm; }
    double minimumLengthMm() const                  { return m_dblMinimumLengthMm; }

    // Setter
    void setPrinterMediaId(const QString& qstrPrinterMediaId);
    void setMarginsMm(const QMarginsF& marginsMm);
    void setMinimumLengthMm(const double dblLengthMm);

    // JSON
    void clear();
    bool loadFromJson(const QJsonObject& jsonSettings);
    bool saveToJson(QJsonObject& jsonSettings) const;

private:
    bool loadVersion_1(const QJsonObject& jsonSettings);

signals:
    void settingsChanged();

private:
    QString     m_qstrPrinterMediaId;
    QMarginsF   m_marginsMm;
    double      m_dblMinimumLengthMm = 0.0;
};

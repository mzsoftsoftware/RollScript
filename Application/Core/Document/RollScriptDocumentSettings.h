#pragma once

#include <QObject>
#include <QMarginsF>


class RollScriptDocumentSettings : public QObject
{
    Q_OBJECT
public:
    explicit RollScriptDocumentSettings(QObject *parent = nullptr);

    // Getter
    QString lastError() const                       { return m_qstrLastError; }

    QMarginsF marginsMm() const                     { return m_marginsMm; }
    double minimumLengthMm() const                  { return m_dblMinimumLengthMm; }

    // Setter
    void setMarginsMm(const QMarginsF& marginsMm);
    void setMinimumLengthMm(const double dblLengthMm);

    // JSON
    bool loadFromJson(const QJsonObject& jsonSettings);
    bool saveToJson(QJsonObject& jsonSettings) const;

private:
    bool loadVersion_1(const QJsonObject& jsonSettings);

signals:
    void settingsChanged();

private:
    QString     m_qstrLastError;

    QMarginsF   m_marginsMm;
    double      m_dblMinimumLengthMm = 0.0;
};

#pragma once

#include <QObject>


class RollScriptDocumentSettings : public QObject
{
    Q_OBJECT
public:
    explicit RollScriptDocumentSettings(QObject *parent = nullptr);

    // Getter
    QString lastError() const                       { return m_qstrLastError; }

    // Setter

    // JSON
    bool loadFromJson(const QJsonObject& jsonSettings);
    bool saveToJson(QJsonObject& jsonSettings) const;

signals:

private:
    QString m_qstrLastError;
};

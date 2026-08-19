#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"


class RollScriptBlockDocumentBase : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT

public:
    RollScriptBlockDocumentBase(QObject *parent);

    // Getter
    const QString& blockPluginId() const    { return m_qstrBlockPluginId; }

    // Setter

    // JSON
    virtual void clear() = 0;
    virtual bool loadFromJson(const QJsonObject& jsonBlocks) = 0;
    virtual bool saveToJson(QJsonObject& jsonBlocks) const = 0;

signals:
    void blockChanged();

protected:
    QString m_qstrBlockPluginId;
};

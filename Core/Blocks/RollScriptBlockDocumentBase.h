#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"

#include <QMarginsF>


class RollScriptBlockDocumentBase : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT

public:
    explicit RollScriptBlockDocumentBase(const QString& qstrBlockPluginId, QObject* parent);
    ~RollScriptBlockDocumentBase() override;

    // Getter
    const QString& blockPluginId() const    { return m_qstrBlockPluginId; }
    const QMarginsF& marginsMm() const      { return m_marginsMm; }

    // JSON
    virtual void clear() = 0;
    virtual bool loadFromJson(const QJsonObject& jsonBlocks) = 0;
    virtual bool saveToJson(QJsonObject& jsonBlocks) = 0;

signals:
    void blockChanged();

protected:
    QString m_qstrBlockPluginId;
    QMarginsF m_marginsMm;
};

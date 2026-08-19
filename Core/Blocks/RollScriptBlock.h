#pragma once

#include <QObject>
#include <QString>


class RollScriptBlock : public QObject
{
    Q_OBJECT

public:
    explicit RollScriptBlock(const QString& qstrTypeId, QObject* parent);
    virtual ~RollScriptBlock() override;

    //QString typeId() const                      { return m_qstrTypeId; }

private:
    QString m_qstrTypeId;
};

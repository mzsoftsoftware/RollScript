#pragma once

#include <QObject>
#include <QString>


class RollScriptBlockXXX : public QObject
{
    Q_OBJECT

public:
    explicit RollScriptBlockXXX(const QString& qstrTypeId, QObject* parent);
    virtual ~RollScriptBlockXXX() override;

    //QString typeId() const                      { return m_qstrTypeId; }

private:
    QString m_qstrTypeId;
};

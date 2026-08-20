#pragma once

#include <QGroupBox>

class RollScriptBlockDocumentBase;


class RollScriptBlockWidgetBase : public QGroupBox
{
    Q_OBJECT

public:
    explicit RollScriptBlockWidgetBase(const QString &qstrBLockPluginId, const QString &qstrTitle, QWidget *parent);

    virtual void setDocumentBlock(RollScriptBlockDocumentBase* ptrBlockDocumentBase) = 0;

protected:
    QString m_qstrBlockPluginId;
};

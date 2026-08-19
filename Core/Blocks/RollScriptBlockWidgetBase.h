#pragma once

#include <QGroupBox>

class RollScriptBlockDocumentBase;


class RollScriptBlockWidgetBase : public QGroupBox
{
    Q_OBJECT

public:
    explicit RollScriptBlockWidgetBase(const QString &qstrPluginId, const QString &qstrTitle, QWidget *parent);

    virtual void setDocumentBlock(RollScriptBlockDocumentBase *ptrLabelBlockBase) = 0;

protected:
    QString m_qstrPluginId;
};

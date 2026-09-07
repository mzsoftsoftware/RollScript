#pragma once

#include <QGroupBox>

class RollScriptBlockDocumentBase;


class RollScriptBlockWidgetBase : public QGroupBox
{
    Q_OBJECT

public:
    explicit RollScriptBlockWidgetBase(const QString& qstrBLockPluginId, QWidget* parent);
    ~RollScriptBlockWidgetBase() override;

    // Setter
    //void setTitle(const QString& qstrTitle);
    virtual void setDocumentBlock(RollScriptBlockDocumentBase* ptrBlockDocumentBase) = 0;

protected:
    QString m_qstrBlockPluginId;
};

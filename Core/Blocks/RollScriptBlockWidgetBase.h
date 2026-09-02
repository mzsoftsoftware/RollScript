#pragma once

#include <QGroupBox>

class RollScriptBlockDocumentBase;


class RollScriptBlockWidgetBase : public QGroupBox
{
    Q_OBJECT

public:
    explicit RollScriptBlockWidgetBase(const QString& qstrBLockPluginId, const QString& qstrTitle, QWidget* parent);
    ~RollScriptBlockWidgetBase() override;

    // Setter
    virtual void setDocumentBlock(RollScriptBlockDocumentBase* ptrBlockDocumentBase) = 0;

protected:
    QString m_qstrBlockPluginId;
};

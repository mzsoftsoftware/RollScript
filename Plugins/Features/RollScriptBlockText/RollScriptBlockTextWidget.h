#pragma once

#include "Core/Blocks/RollScriptBlockWidgetBase.h"

class RollScriptBlockTextDocument;

namespace Ui {
class RollScriptBlockTextWidget;
}


class RollScriptBlockTextWidget : public RollScriptBlockWidgetBase
{
    Q_OBJECT

public:
    explicit RollScriptBlockTextWidget(const QString &qstrPluginId, const QString &qstrTitle, QWidget *parent);
    ~RollScriptBlockTextWidget();

    void setDocumentBlock(RollScriptBlockDocumentBase* ptrBlockDocumentBase) override;

private slots:
    void updateFromBlockTextDocument();

private:
    Ui::RollScriptBlockTextWidget *ui;

    RollScriptBlockTextDocument*    m_ptrBlockTextDocument;
    QMetaObject::Connection         m_connBlockTextDocumentCleared;
    QMetaObject::Connection         m_connBlockTextDocumentLoaded;
};


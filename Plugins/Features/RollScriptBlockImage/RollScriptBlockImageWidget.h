#pragma once
// clazy:excludeall=connect-by-name

#include "Core/Blocks/RollScriptBlockWidgetBase.h"

class RollScriptBlockImageDocument;

namespace Ui {
class RollScriptBlockImageWidget;
}


class RollScriptBlockImageWidget : public RollScriptBlockWidgetBase
{
    Q_OBJECT

public:
    explicit RollScriptBlockImageWidget(const QString& qstrPluginId, const QString& qstrTitle, QWidget* parent);
    ~RollScriptBlockImageWidget();

    // Setter
    void setDocumentBlock(RollScriptBlockDocumentBase* ptrBlockDocumentBase) override;

private slots:
    void updateFromBlockImageDocument();

    void on_toolButton_Image_clicked();

private:
    void updatePreview();

private:
    Ui::RollScriptBlockImageWidget* ui;

    RollScriptBlockImageDocument*   m_ptrBlockImageDocument;
    QMetaObject::Connection         m_connBlockImageDocumentCleared;
    QMetaObject::Connection         m_connBlockImageDocumentLoaded;
};

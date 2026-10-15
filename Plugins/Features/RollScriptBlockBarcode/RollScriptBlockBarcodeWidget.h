#pragma once
// clazy:excludeall=connect-by-name

#include "Core/Blocks/RollScriptBlockWidgetBase.h"

class RollScriptBlockBarcodeDocument;

namespace Ui {
class RollScriptBlockBarcodeWidget;
}


class RollScriptBlockBarcodeWidget : public RollScriptBlockWidgetBase
{
    Q_OBJECT

public:
    // Constructor / Destructor
    explicit RollScriptBlockBarcodeWidget(const QString& qstrPluginId, const QString& qstrTitle, QWidget* parent);
    ~RollScriptBlockBarcodeWidget() override;

    // Setter
    void setDocumentBlock(RollScriptBlockDocumentBase* ptrBlockDocumentBase) override;

private slots:
    void on_lineEdit_BarcodeText_textChanged(const QString &qstrText);

private:
    void updateFromBlockBarcodeDocument();
    void updatePreview(const QString &qstrQrCodeText);

private:
    Ui::RollScriptBlockBarcodeWidget* ui;

    RollScriptBlockBarcodeDocument* m_ptrBlockBarcodeDocument;
    QMetaObject::Connection         m_connBlockBarcodeDocumentCleared;
    QMetaObject::Connection         m_connBlockBarcodeDocumentLoaded;
};

#pragma once
// clazy:excludeall=connect-by-name

#include "Core/Blocks/RollScriptBlockWidgetBase.h"

class RollScriptBlockQRCodeDocument;

namespace Ui {
class RollScriptBlockQRCodeWidget;
}


class RollScriptBlockQRCodeWidget : public RollScriptBlockWidgetBase
{
    Q_OBJECT

public:
    // Constructor / Destructor
    explicit RollScriptBlockQRCodeWidget(const QString& qstrPluginId, const QString& qstrTitle, QWidget* parent);
    ~RollScriptBlockQRCodeWidget() override;

    // Setter
    void setDocumentBlock(RollScriptBlockDocumentBase* ptrBlockDocumentBase) override;

private slots:
    void on_lineEdit_QrText_textChanged(const QString &qstrText);

private:
    void updateFromBlockQRCodeDocument();
    void updatePreview(const QString &qstrQrCodeText);

private:
    Ui::RollScriptBlockQRCodeWidget* ui;

    RollScriptBlockQRCodeDocument* m_ptrBlockQRCodeDocument;
    QMetaObject::Connection         m_connBlockQRCodeDocumentCleared;
    QMetaObject::Connection         m_connBlockQRCodeDocumentLoaded;
};

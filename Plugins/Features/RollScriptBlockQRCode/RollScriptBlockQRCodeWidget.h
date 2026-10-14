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

private:
    Ui::RollScriptBlockQRCodeWidget* ui;

    RollScriptBlockQRCodeDocument* m_ptrBlockQRCodeDocument;
};

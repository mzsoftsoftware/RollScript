#include "RollScriptBlockQRCodeWidget.h"
#include "ui_RollScriptBlockQRCodeWidget.h"

#include "RollScriptBlockQRCodeDocument.h"


RollScriptBlockQRCodeWidget::RollScriptBlockQRCodeWidget(const QString& qstrPluginId, const QString& qstrTitle, QWidget* parent)
    : RollScriptBlockWidgetBase(qstrPluginId, parent)
    , ui(new Ui::RollScriptBlockQRCodeWidget)
{
    ui->setupUi(this);

    setTitle(qstrTitle);

    m_ptrBlockQRCodeDocument = nullptr;
}
RollScriptBlockQRCodeWidget::~RollScriptBlockQRCodeWidget()
{
    delete ui;
}

void RollScriptBlockQRCodeWidget::setDocumentBlock(RollScriptBlockDocumentBase* ptrBlockDocumentBase)
{
    RollScriptBlockQRCodeDocument* ptrBlockQRCodeDocument = dynamic_cast<RollScriptBlockQRCodeDocument*>(ptrBlockDocumentBase);
    Q_ASSERT(ptrBlockQRCodeDocument);

    m_ptrBlockQRCodeDocument = ptrBlockQRCodeDocument;
}

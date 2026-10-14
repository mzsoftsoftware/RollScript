#include "RollScriptBlockBarcodeWidget.h"
#include "ui_RollScriptBlockBarcodeWidget.h"

#include "RollScriptBlockBarcodeDocument.h"


RollScriptBlockBarcodeWidget::RollScriptBlockBarcodeWidget(const QString& qstrPluginId, const QString& qstrTitle, QWidget* parent)
    : RollScriptBlockWidgetBase(qstrPluginId, parent)
    , ui(new Ui::RollScriptBlockBarcodeWidget)
{
    ui->setupUi(this);

    setTitle(qstrTitle);

    m_ptrBlockBarcodeDocument = nullptr;
}
RollScriptBlockBarcodeWidget::~RollScriptBlockBarcodeWidget()
{
    delete ui;
}

void RollScriptBlockBarcodeWidget::setDocumentBlock(RollScriptBlockDocumentBase* ptrBlockDocumentBase)
{
    RollScriptBlockBarcodeDocument* ptrBlockBarcodeDocument = dynamic_cast<RollScriptBlockBarcodeDocument*>(ptrBlockDocumentBase);
    Q_ASSERT(ptrBlockBarcodeDocument);

    m_ptrBlockBarcodeDocument = ptrBlockBarcodeDocument;
}

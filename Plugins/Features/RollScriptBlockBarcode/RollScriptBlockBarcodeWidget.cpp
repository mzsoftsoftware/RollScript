#include "RollScriptBlockBarcodeWidget.h"
#include "ui_RollScriptBlockBarcodeWidget.h"

#include "RollScriptBlockBarcodeDocument.h"

#include "ZXingQt.h"


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

    if(m_ptrBlockBarcodeDocument)
    {
        disconnect(m_connBlockBarcodeDocumentCleared);
        disconnect(m_connBlockBarcodeDocumentLoaded);
    }
    m_ptrBlockBarcodeDocument = ptrBlockBarcodeDocument;

    m_connBlockBarcodeDocumentCleared = connect(m_ptrBlockBarcodeDocument, &RollScriptBlockBarcodeDocument::documentCleared, this, &RollScriptBlockBarcodeWidget::updateFromBlockBarcodeDocument);
    m_connBlockBarcodeDocumentLoaded = connect(m_ptrBlockBarcodeDocument, &RollScriptBlockBarcodeDocument::documentLoaded, this, &RollScriptBlockBarcodeWidget::updateFromBlockBarcodeDocument);
    updateFromBlockBarcodeDocument();
}

void RollScriptBlockBarcodeWidget::on_lineEdit_BarcodeText_textChanged(const QString &qstrText)
{
    m_ptrBlockBarcodeDocument->setText(qstrText);
    updatePreview(qstrText);
}

void RollScriptBlockBarcodeWidget::updateFromBlockBarcodeDocument()
{
    QSignalBlocker blockerBarcodeText(ui->lineEdit_BarcodeText);

    QString qstrText = m_ptrBlockBarcodeDocument->text();
    ui->lineEdit_BarcodeText->setText(qstrText);
    updatePreview(qstrText);
}

void RollScriptBlockBarcodeWidget::updatePreview(const QString &qstrQrCodeText)
{
    if(qstrQrCodeText.isEmpty())
    {
        ui->label_Preview->setText(tr("Empty QR-Code"));
        return;
    }

    ZXingQt::Barcode barcode = ZXingQt::Barcode::fromText(qstrQrCodeText, ZXingQt::BarcodeFormat::Code128);
    QImage image = barcode.toImage(ZXingQt::WriterOptions().scale(4));
    QImage imageScaled = image.scaledToWidth(ui->label_Preview->size().width());

    ui->label_Preview->setPixmap(QPixmap::fromImage(imageScaled));
}

#include "RollScriptBlockQRCodeWidget.h"
#include "ui_RollScriptBlockQRCodeWidget.h"

#include "RollScriptBlockQRCodeDocument.h"

#include "ZXingQt.h"


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

    if(m_ptrBlockQRCodeDocument)
    {
        disconnect(m_connBlockQRCodeDocumentCleared);
        disconnect(m_connBlockQRCodeDocumentLoaded);
    }
    m_ptrBlockQRCodeDocument = ptrBlockQRCodeDocument;

    m_connBlockQRCodeDocumentCleared = connect(m_ptrBlockQRCodeDocument, &RollScriptBlockQRCodeDocument::documentCleared, this, &RollScriptBlockQRCodeWidget::updateFromBlockQRCodeDocument);
    m_connBlockQRCodeDocumentLoaded = connect(m_ptrBlockQRCodeDocument, &RollScriptBlockQRCodeDocument::documentLoaded, this, &RollScriptBlockQRCodeWidget::updateFromBlockQRCodeDocument);
    updateFromBlockQRCodeDocument();
}

void RollScriptBlockQRCodeWidget::on_lineEdit_QrText_textChanged(const QString &qstrText)
{
    m_ptrBlockQRCodeDocument->setText(qstrText);
    updatePreview(qstrText);
}

void RollScriptBlockQRCodeWidget::updateFromBlockQRCodeDocument()
{
    QSignalBlocker blockerQrText(ui->lineEdit_QrText);

    QString qstrText = m_ptrBlockQRCodeDocument->text();
    ui->lineEdit_QrText->setText(qstrText);
    updatePreview(qstrText);
}

void RollScriptBlockQRCodeWidget::updatePreview(const QString &qstrQrCodeText)
{
    if(qstrQrCodeText.isEmpty())
    {
        ui->label_Preview->setText(tr("Empty QR-Code"));
        return;
    }

    ZXingQt::Barcode barcode = ZXingQt::Barcode::fromText(qstrQrCodeText, ZXingQt::BarcodeFormat::QRCode, QStringLiteral("ecLevel=H"));
    QImage image = barcode.toImage(ZXingQt::WriterOptions().scale(4));


    //QImage image = m_QrCodeGenerator.generateQr(qstrQrCodeText);
    QImage imageScaled = image.scaledToWidth(ui->label_Preview->size().width());

    ui->label_Preview->setPixmap(QPixmap::fromImage(imageScaled));
}

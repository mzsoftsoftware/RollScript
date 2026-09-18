#include "RollScriptBlockImageWidget.h"
#include "ui_RollScriptBlockImageWidget.h"

#include <QFileDialog>

#include "RollScriptBlockImageDocument.h"


RollScriptBlockImageWidget::RollScriptBlockImageWidget(const QString& qstrPluginId, const QString& qstrTitle, QWidget* parent)
    : RollScriptBlockWidgetBase(qstrPluginId, parent)
    , ui(new Ui::RollScriptBlockImageWidget)
{
    ui->setupUi(this);

    setTitle(qstrTitle);
}

RollScriptBlockImageWidget::~RollScriptBlockImageWidget()
{
    delete ui;
}

void RollScriptBlockImageWidget::setDocumentBlock(RollScriptBlockDocumentBase* ptrBlockDocumentBase)
{
    RollScriptBlockImageDocument* ptrBlockImageDocument = dynamic_cast<RollScriptBlockImageDocument*>(ptrBlockDocumentBase);
    Q_ASSERT(ptrBlockImageDocument);

    if(ptrBlockImageDocument)
    {
        disconnect(m_connBlockImageDocumentCleared);
        disconnect(m_connBlockImageDocumentLoaded);
    }
    m_ptrBlockImageDocument = ptrBlockImageDocument;

    m_connBlockImageDocumentCleared = connect(m_ptrBlockImageDocument, &RollScriptBlockImageDocument::documentCleared, this, &RollScriptBlockImageWidget::updateFromBlockImageDocument);
    m_connBlockImageDocumentLoaded = connect(m_ptrBlockImageDocument, &RollScriptBlockImageDocument::documentLoaded, this, &RollScriptBlockImageWidget::updateFromBlockImageDocument);
    updateFromBlockImageDocument();
}

void RollScriptBlockImageWidget::updateFromBlockImageDocument()
{
    ui->lineEdit_Image->setText(m_ptrBlockImageDocument->fileName());
    updatePreview();
}

void RollScriptBlockImageWidget::on_toolButton_Image_clicked()
{
    QString qstrFile = QFileDialog::getOpenFileName(this, tr("Select Image"), QString(), tr("Images (*.png *.jpg *.jpeg *.gif)"));

    if(!qstrFile.isEmpty())
    {
        ui->lineEdit_Image->setText(qstrFile);
        m_ptrBlockImageDocument->setFileName(qstrFile);
        updatePreview();
    }
}

void RollScriptBlockImageWidget::updatePreview()
{
    QPixmap pixmap(ui->lineEdit_Image->text());

    if(pixmap.isNull())
    {
        ui->label_Preview->setText(QStringLiteral("Invalid Image"));
        return;
    }

    ui->label_Preview->setPixmap(pixmap.scaledToWidth(ui->label_Preview->size().width()));
}

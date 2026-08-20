#include "RollScriptBlockTextLineWidget.h"
#include "ui_RollScriptBlockTextLineWidget.h"

#include "RollScriptBlockTextLineDocument.h"


RollScriptBlockTextLineWidget::RollScriptBlockTextLineWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RollScriptBlockTextLineWidget)
{
    ui->setupUi(this);

    setupComboAlignment();
}

RollScriptBlockTextLineWidget::~RollScriptBlockTextLineWidget()
{
    delete ui;
}

void RollScriptBlockTextLineWidget::setupComboAlignment()
{
    QSignalBlocker blockerComboBoxAlignment(ui->comboBox_Alignment);

    ui->comboBox_Alignment->addItem( QIcon(QStringLiteral(":/RollScriptBlockTextFeaturePlugin/icons/FontFormatJustifyLeft")), tr("Left"), Qt::AlignLeft );
    ui->comboBox_Alignment->addItem( QIcon(QStringLiteral(":/RollScriptBlockTextFeaturePlugin/icons/FontFormatJustifyCenter")), tr("Center"), Qt::AlignHCenter );
    ui->comboBox_Alignment->addItem( QIcon(QStringLiteral(":/RollScriptBlockTextFeaturePlugin/icons/FontFormatJustifyRight")), tr("Right"), Qt::AlignRight );

    ui->comboBox_Alignment->setCurrentIndex(1);
}

void RollScriptBlockTextLineWidget::setDocumentBlockTextLine(RollScriptBlockTextLineDocument* ptrBlockTextLineDocument)
{
    Q_ASSERT(ptrBlockTextLineDocument);

    if(m_ptrBlockTextLineDocument)
    {
        disconnect(m_connBlockTextLineDocumentCleared);
        disconnect(m_connBlockTextLineDocumentLoaded);
    }
    m_ptrBlockTextLineDocument = ptrBlockTextLineDocument;

    m_connBlockTextLineDocumentCleared = connect(m_ptrBlockTextLineDocument, &RollScriptBlockTextLineDocument::documentCleared, this, &RollScriptBlockTextLineWidget::updateFromBlockTextLineDocument);
    m_connBlockTextLineDocumentLoaded = connect(m_ptrBlockTextLineDocument, &RollScriptBlockTextLineDocument::documentLoaded, this, &RollScriptBlockTextLineWidget::updateFromBlockTextLineDocument);
    updateFromBlockTextLineDocument();
}

void RollScriptBlockTextLineWidget::updateFromBlockTextLineDocument()
{
    QSignalBlocker blockerCheckBoxActive(ui->checkBox_Active);
    QSignalBlocker blockerLineEditText(ui->lineEdit_Text);
    QSignalBlocker blockerFontComboBoxFont(ui->fontComboBox_Font);
    QSignalBlocker blockerSpinBoxFontSize(ui->spinBox_FontSize);
    QSignalBlocker blockerToolButtonFontBold(ui->toolButton_FontBold);
    QSignalBlocker blockerToolButtonFontItalic(ui->toolButton_FontItalic);
    QSignalBlocker blockerComboBoxAlignment(ui->comboBox_Alignment);

    ui->checkBox_Active->setChecked(m_ptrBlockTextLineDocument->lineActive());
    ui->lineEdit_Text->setText(m_ptrBlockTextLineDocument->lineText());
    ui->fontComboBox_Font->setCurrentFont(m_ptrBlockTextLineDocument->lineFont());
    ui->spinBox_FontSize->setValue(m_ptrBlockTextLineDocument->lineFont().pointSize());
    ui->toolButton_FontBold->setChecked(m_ptrBlockTextLineDocument->lineFont().bold());
    ui->toolButton_FontItalic->setChecked(m_ptrBlockTextLineDocument->lineFont().italic());

    int idx = ui->comboBox_Alignment->findData(QVariant::fromValue(m_ptrBlockTextLineDocument->lineAlignment()));
    if(idx>=0)
        ui->comboBox_Alignment->setCurrentIndex(idx);

    updateActiveStatus(m_ptrBlockTextLineDocument->lineActive());
}

void RollScriptBlockTextLineWidget::updateActiveStatus(bool bActive)
{
    ui->lineEdit_Text->setEnabled(bActive);
    ui->fontComboBox_Font->setEnabled(bActive);
    ui->toolButton_FontBold->setEnabled(bActive);
    ui->toolButton_FontItalic->setEnabled(bActive);
    ui->spinBox_FontSize->setEnabled(bActive);
    ui->comboBox_Alignment->setEnabled(bActive);
}

void RollScriptBlockTextLineWidget::on_checkBox_Active_toggled(bool checked)
{
    m_ptrBlockTextLineDocument->setLineActive(checked);
    updateActiveStatus(checked);

    emit lineActiveChanged();
}


void RollScriptBlockTextLineWidget::on_lineEdit_Text_textChanged(const QString &qstrText)
{
    m_ptrBlockTextLineDocument->setLineText(qstrText);
}


void RollScriptBlockTextLineWidget::on_fontComboBox_Font_currentFontChanged(const QFont &font)
{
    QFont myFont = font;
    myFont.setPointSize(ui->spinBox_FontSize->value());
    m_ptrBlockTextLineDocument->setLineFont(myFont);
}


void RollScriptBlockTextLineWidget::on_toolButton_FontBold_toggled(bool checked)
{
    QFont myFont = m_ptrBlockTextLineDocument->lineFont();
    myFont.setBold(checked);
    m_ptrBlockTextLineDocument->setLineFont(myFont);
}


void RollScriptBlockTextLineWidget::on_toolButton_FontItalic_toggled(bool checked)
{
    QFont myFont = m_ptrBlockTextLineDocument->lineFont();
    myFont.setItalic(checked);
    m_ptrBlockTextLineDocument->setLineFont(myFont);
}


void RollScriptBlockTextLineWidget::on_spinBox_FontSize_valueChanged(int iSize)
{
    QFont myFont = m_ptrBlockTextLineDocument->lineFont();
    myFont.setPointSize(iSize);
    m_ptrBlockTextLineDocument->setLineFont(myFont);
}


void RollScriptBlockTextLineWidget::on_comboBox_Alignment_currentIndexChanged(int index)
{
    m_ptrBlockTextLineDocument->setLineAlignment(static_cast<Qt::Alignment>(ui->comboBox_Alignment->currentData().toInt()));
}


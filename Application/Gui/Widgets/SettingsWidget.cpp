#include "SettingsWidget.h"
#include "ui_SettingsWidget.h"

#include "Core/Document/RollScriptDocument.h"
#include "Core/Document/RollScriptDocumentSettings.h"

#include "Gui/Models/PrinterMediasItemModel.h"


SettingsWidget::SettingsWidget(QWidget *parent)
    : QWidget{parent}
    , ui(new Ui::SettingsWidget)
{
    ui->setupUi(this);
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}

void SettingsWidget::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }

    QWidget::changeEvent(event);
}

void SettingsWidget::setPrinterMediasItemModel(PrinterMediasItemModel* ptrPrinterMediasItemModel)
{
    m_ptrPrinterMediasItemModel = ptrPrinterMediasItemModel;
    ui->comboBox_PrinterMedia->setModel(m_ptrPrinterMediasItemModel);
    rebuildPrinterMediasModel();
}
void SettingsWidget::setRollScriptDocument(RollScriptDocument* ptrDocument)
{
    m_ptrDocument = ptrDocument;
    m_ptrDocumentSettings = ptrDocument->settings();

    connect(m_ptrDocument, &RollScriptDocument::documentCleared, this, &SettingsWidget::updateUiFromDocument);
    connect(m_ptrDocument, &RollScriptDocument::documentLoaded, this, &SettingsWidget::updateUiFromDocument);
    updateUiFromDocument();
}
void SettingsWidget::rebuildPrinterMediasModel()
{
    m_ptrPrinterMediasItemModel->rebuildModel();
    if(m_ptrPrinterMediasItemModel->rowCount() > 0)
    {
        ui->comboBox_PrinterMedia->setPlaceholderText(tr("Select label ..."));
    }
    else
    {
        ui->comboBox_PrinterMedia->setPlaceholderText(tr("No labels found. Select printer ?"));
    }

    if(m_qstrPrinterMediaId.isEmpty())
    {
        ui->comboBox_PrinterMedia->setCurrentIndex(-1);
    }
    else
    {
        int index = ui->comboBox_PrinterMedia->findData(m_qstrPrinterMediaId, Qt::UserRole);
        ui->comboBox_PrinterMedia->setCurrentIndex(index);
        // TASK : updateLabelConstraints();
    }
}

void SettingsWidget::updateUiFromDocument()
{
    QSignalBlocker blockerLengthMin(ui->doubleSpinBox_LengthMin);
    QSignalBlocker blockerMargins(ui->marginsWidget);

    ui->doubleSpinBox_LengthMin->setValue(m_ptrDocumentSettings->minimumLengthMm());
    ui->marginsWidget->setMarginsMm(m_ptrDocumentSettings->marginsMm());
}

void SettingsWidget::on_comboBox_LabelMedia_currentIndexChanged(int index)
{
    if(index >= 0)
    {
        QString qstrId = ui->comboBox_PrinterMedia->itemData(index).toString();
        // TASK : m_ptrDocumentSettings->setPrinterMediaId(qstrId);
        // TASK : updateLabelConstraints();
    }
}
void SettingsWidget::on_doubleSpinBox_LengthMin_valueChanged(double value)
{
    m_ptrDocumentSettings->setMinimumLengthMm(value);
}
void SettingsWidget::on_marginsWidget_marginsMmEdited(QMarginsF margins)
{
    m_ptrDocumentSettings->setMarginsMm(margins);
}

#include "SettingsWidget.h"
#include "ui_SettingsWidget.h"

#include "Document/RollScriptDocument.h"
#include "Document/RollScriptDocumentSettings.h"

#include "Gui/Models/PrinterMediasItemModel.h"

#include "Printers/PrinterManager.h"
#include "Core/Printers/PrinterInstance.h"
#include "Core/Printers/PrinterMedia.h"


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

void SettingsWidget::setPrinterManager(PrinterManager* ptrPrinterManager)
{
    m_ptrPrinterManager = ptrPrinterManager;
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

    if(m_ptrDocumentSettings->printerMediaId().isEmpty())
    {
        ui->comboBox_PrinterMedia->setCurrentIndex(-1);
    }
    else
    {
        int index = ui->comboBox_PrinterMedia->findData(m_ptrDocumentSettings->printerMediaId(), Qt::UserRole);
        ui->comboBox_PrinterMedia->setCurrentIndex(index);
        updatePrinterMediaConstraints();
    }
}

void SettingsWidget::updatePrinterMediaConstraints()
{
    Q_ASSERT(m_ptrDocumentSettings);
    Q_ASSERT(m_ptrPrinterManager);

    QString qstrPrinterMediaId = m_ptrDocumentSettings->printerMediaId();
    if(qstrPrinterMediaId.isEmpty())
    {
        resetPrinterMediaConstraints();
        return;
    }

    const PrinterInstance* ptrPrinterInstance = m_ptrPrinterManager->currentPrinter();
    if(!ptrPrinterInstance)
    {
        resetPrinterMediaConstraints();
        return;
    }

    const PrinterMedia* ptrPrinterMedia = ptrPrinterInstance->media(qstrPrinterMediaId);
    if(!ptrPrinterMedia)
    {
        resetPrinterMediaConstraints();
        return;
    }

    const PrinterMediaConstraints& constraints = ptrPrinterMedia->constraints();
    ui->marginsWidget->setMarginsMinimumMm(constraints.marginsMinMm);

    ui->doubleSpinBox_LengthMin->setMinimum(constraints.lengthMinMm);
    if(ui->doubleSpinBox_LengthMin->value() < constraints.lengthMinMm)
    {
        ui->doubleSpinBox_LengthMin->setValue(constraints.lengthMinMm);
        // TASK : Message Box !!! if needed
    }

    return;
}
void SettingsWidget::resetPrinterMediaConstraints()
{
    ui->marginsWidget->setMarginsMinimumMm(QMarginsF());
    ui->doubleSpinBox_LengthMin->setMinimum(0.0);
}

void SettingsWidget::updateUiFromDocument()
{
    QSignalBlocker blockerLengthMin(ui->doubleSpinBox_LengthMin);
    QSignalBlocker blockerMargins(ui->marginsWidget);

    ui->doubleSpinBox_LengthMin->setValue(m_ptrDocumentSettings->minimumLengthMm());
    ui->marginsWidget->setMarginsMm(m_ptrDocumentSettings->marginsMm());
}

void SettingsWidget::on_comboBox_PrinterMedia_currentIndexChanged(int index)
{
    if(index >= 0)
    {
        QString qstrId = ui->comboBox_PrinterMedia->itemData(index).toString();
        m_ptrDocumentSettings->setPrinterMediaId(qstrId);
        updatePrinterMediaConstraints();
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

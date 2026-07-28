#include "SettingsWidget.h"
#include "ui_SettingsWidget.h"

#include "Core/Document/RollScriptDocument.h"
#include "Core/Document/RollScriptDocumentSettings.h"


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

void SettingsWidget::setRollScriptDocument(RollScriptDocument* ptrDocument)
{
    m_ptrDocument = ptrDocument;
    m_ptrDocumentSettings = ptrDocument->settings();

    connect(m_ptrDocument, &RollScriptDocument::documentCleared, this, &SettingsWidget::updateUiFromDocument);
    connect(m_ptrDocument, &RollScriptDocument::documentLoaded, this, &SettingsWidget::updateUiFromDocument);
    updateUiFromDocument();
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

}
void SettingsWidget::on_doubleSpinBox_LengthMin_valueChanged(double value)
{
    m_ptrDocumentSettings->setMinimumLengthMm(value);
}
void SettingsWidget::on_marginsWidget_marginsMmEdited(QMarginsF margins)
{
    m_ptrDocumentSettings->setMarginsMm(margins);
}

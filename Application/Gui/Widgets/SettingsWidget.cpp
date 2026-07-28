#include "SettingsWidget.h"
#include "ui_SettingsWidget.h"


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

#include "DialogAboutOverviewWidget.h"
#include "ui_DialogAboutOverviewWidget.h"

DialogAboutOverviewWidget::DialogAboutOverviewWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::DialogAboutOverviewWidget)
{
    ui->setupUi(this);

    ui->label_Version->setText(tr("Version %1").arg(ROLLSCRIPT_VERSION));
}

DialogAboutOverviewWidget::~DialogAboutOverviewWidget()
{
    delete ui;
}

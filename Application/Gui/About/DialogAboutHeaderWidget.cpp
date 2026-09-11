#include "DialogAboutHeaderWidget.h"
#include "ui_DialogAboutHeaderWidget.h"


DialogAboutHeaderWidget::DialogAboutHeaderWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::DialogAboutHeaderWidget)
{
    ui->setupUi(this);

    ui->label_Version->setText(tr("Version %1").arg(ROLLSCRIPT_VERSION));
}

DialogAboutHeaderWidget::~DialogAboutHeaderWidget()
{
    delete ui;
}

#include "DialogAbout.h"
#include "ui_DialogAbout.h"

DialogAbout::DialogAbout(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogAbout)
{
    ui->setupUi(this);

    ui->labelVersion->setText(ui->labelVersion->text().arg(ROLLSCRIPT_VERSION));

    // TASK : Make a better AboutDialog
}

DialogAbout::~DialogAbout()
{
    delete ui;
}

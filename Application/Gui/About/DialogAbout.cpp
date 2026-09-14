#include "DialogAbout.h"
#include "ui_DialogAbout.h"

#include "App/ApplicationContext.h"


DialogAbout::DialogAbout(ApplicationContext* ptrApplicationContext, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::DialogAbout)
{
    ui->setupUi(this);

    // Fill the contents
    ui->tab2_Licenses->setLicenseProviderRegistry(ptrApplicationContext->licenseProviderRegistry());

    //ui->labelVersion->setText(ui->labelVersion->text().arg(ROLLSCRIPT_VERSION));
}
DialogAbout::~DialogAbout()
{
    delete ui;
}

void DialogAbout::on_pushButton_Copy_clicked()
{

}

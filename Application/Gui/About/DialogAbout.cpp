#include "DialogAbout.h"
#include "ui_DialogAbout.h"

#include "App/ApplicationContext.h"
#include "Plugins/PluginManager.h"


DialogAbout::DialogAbout(ApplicationContext* ptrApplicationContext, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::DialogAbout)
{
    ui->setupUi(this);

    // Fill the contents
    ui->tab2_Licenses->setLicenseProviderRegistry(ptrApplicationContext->licenseProviderRegistry());
    ui->tab4_Features->setFeaturePluginRegistry(ptrApplicationContext->pluginManager()->registryFeatures());
    ui->tab5_Printers->setPrinterPluginRegistry(ptrApplicationContext->pluginManager()->registryPrinters());
}
DialogAbout::~DialogAbout()
{
    delete ui;
}

void DialogAbout::on_pushButton_Copy_clicked()
{

}

#include "DialogAbout.h"
#include "ui_DialogAbout.h"

#include <QClipboard>

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
    QString text;

    text += QStringLiteral("RollScript Support Information\n");
    text += QStringLiteral("============================\n\n");

    text += QStringLiteral("Components:\n");
    text += ui->tab3_Components->supportInformation();
    text += QStringLiteral("\n");

    text += QStringLiteral("Features:\n");
    text += ui->tab4_Features->supportInformation();
    text += QStringLiteral("\n");

    text += QStringLiteral("Printers:\n");
    text += ui->tab5_Printers->supportInformation();

    QGuiApplication::clipboard()->setText(text);
}

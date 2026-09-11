#include "DialogAboutLicenseWidget.h"
#include "ui_DialogAboutLicenseWidget.h"

DialogAboutLicenseWidget::DialogAboutLicenseWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::DialogAboutLicenseWidget)
{
    ui->setupUi(this);
}

DialogAboutLicenseWidget::~DialogAboutLicenseWidget()
{
    delete ui;
}

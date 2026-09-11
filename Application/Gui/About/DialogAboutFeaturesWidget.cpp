#include "DialogAboutFeaturesWidget.h"
#include "ui_DialogAboutFeaturesWidget.h"

DialogAboutFeaturesWidget::DialogAboutFeaturesWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::DialogAboutFeaturesWidget)
{
    ui->setupUi(this);
}

DialogAboutFeaturesWidget::~DialogAboutFeaturesWidget()
{
    delete ui;
}

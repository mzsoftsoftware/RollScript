#include "DialogAboutPrintersWidget.h"
#include "ui_DialogAboutPrintersWidget.h"

DialogAboutPrintersWidget::DialogAboutPrintersWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::DialogAboutPrintersWidget)
{
    ui->setupUi(this);
}

DialogAboutPrintersWidget::~DialogAboutPrintersWidget()
{
    delete ui;
}

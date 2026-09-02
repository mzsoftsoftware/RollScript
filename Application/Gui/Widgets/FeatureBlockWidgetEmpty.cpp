#include "FeatureBlockWidgetEmpty.h"
#include "ui_FeatureBlockWidgetEmpty.h"


FeatureBlockWidgetEmpty::FeatureBlockWidgetEmpty(QWidget* parent)
    : RollScriptBlockWidgetBase(QStringLiteral("Empty"), QString(), parent)
    , ui(new Ui::FeatureBlockWidgetEmpty)
{
    ui->setupUi(this);
}
FeatureBlockWidgetEmpty::~FeatureBlockWidgetEmpty()
{
    delete ui;
}

void FeatureBlockWidgetEmpty::setDocumentBlock(RollScriptBlockDocumentBase* ptrBlockDocumentBase)
{
}

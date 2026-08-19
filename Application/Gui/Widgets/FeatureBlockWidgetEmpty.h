#pragma once

#include "Core/Blocks/RollScriptBlockWidgetBase.h"

namespace Ui {
class FeatureBlockWidgetEmpty;
}


class FeatureBlockWidgetEmpty : public RollScriptBlockWidgetBase
{
    Q_OBJECT

public:
    explicit FeatureBlockWidgetEmpty(QWidget *parent);
    virtual ~FeatureBlockWidgetEmpty();

    virtual void setDocumentBlock(RollScriptBlockDocumentBase *ptrBlockDocumentBase) override;

private:
    Ui::FeatureBlockWidgetEmpty *ui;
};

#pragma once
// clazy:excludeall=connect-by-name

#include "Core/Blocks/RollScriptBlockWidgetBase.h"

namespace Ui {
class FeatureBlockWidgetEmpty;
}


class FeatureBlockWidgetEmpty : public RollScriptBlockWidgetBase
{
    Q_OBJECT

public:
    // Constructor / Destructor
    explicit FeatureBlockWidgetEmpty(QWidget* parent);
    ~FeatureBlockWidgetEmpty() override;

    // Operations
    virtual void setDocumentBlock(RollScriptBlockDocumentBase* ptrBlockDocumentBase) override;

private:
    Ui::FeatureBlockWidgetEmpty* ui;
};

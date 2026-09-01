#pragma once

#include "DLP350PrinterJob.h"


class DymoLabelPoint350PrinterJobAlive : public DymoLabelPoint350PrinterJob
{
    Q_OBJECT

public:
    explicit DymoLabelPoint350PrinterJobAlive(PrinterInstanceUSB* ptrPrinterInstanceUSB);
    virtual ~DymoLabelPoint350PrinterJobAlive() override;

    bool execute() override;

};

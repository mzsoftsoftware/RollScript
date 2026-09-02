#pragma once

#include "DLP350PrinterJob.h"


class DymoLabelPoint350PrinterJobAlive : public DymoLabelPoint350PrinterJob
{
    Q_OBJECT

public:
    // Constructor / Destructor
    explicit DymoLabelPoint350PrinterJobAlive(PrinterInstanceUSB* ptrPrinterInstanceUSB);
    ~DymoLabelPoint350PrinterJobAlive() override;

    // Operations
    bool execute() override;
};

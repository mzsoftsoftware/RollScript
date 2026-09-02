#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"

class PrinterInstanceUSB;


class DymoLabelPoint350PrinterJob : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT

public:
    // Constructor / Destructor
    explicit DymoLabelPoint350PrinterJob(PrinterInstanceUSB* ptrPrinterInstanceUSB);
    ~DymoLabelPoint350PrinterJob() override;

    // Operations
    virtual bool execute() = 0;

signals:
    void started(int iSteps);
    void progress(int iStep);
    void finished();
    void error(const RollScriptError& error);

protected:
    bool sendCommand(const QByteArray& qbaCommand, QByteArray* ptrQbaResponse = nullptr);

private:
    PrinterInstanceUSB* m_ptrPrinterInstanceUSB = nullptr;
};

#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"

class PrinterInstanceUSB;


class DymoLabelPoint350PrinterJob : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT
public:
    explicit DymoLabelPoint350PrinterJob(PrinterInstanceUSB* ptrPrinterInstanceUSB);
    virtual ~DymoLabelPoint350PrinterJob() override;

    virtual bool execute() = 0;

signals:
    void started(int iSteps);
    void progress(int iStep);
    void finished();
    void error(const RollScriptError& error);

protected:
    bool sendCommand(const QByteArray& baCommand, QByteArray* ptrBaResponse = nullptr);
    //PrinterInstanceUSB* printerInstance() const;
    //void setError(const QString& qstrError);

private:
    PrinterInstanceUSB* m_ptrPrinterInstanceUSB = nullptr;
};

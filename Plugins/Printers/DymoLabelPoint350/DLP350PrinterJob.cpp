#include "DLP350PrinterJob.h"

#include "Core/USB/PrinterInstanceUSB.h"


DymoLabelPoint350PrinterJob::DymoLabelPoint350PrinterJob(PrinterInstanceUSB* ptrPrinterInstanceUSB)
    : m_ptrPrinterInstanceUSB(ptrPrinterInstanceUSB)
{
}
DymoLabelPoint350PrinterJob::~DymoLabelPoint350PrinterJob()
{
}

bool DymoLabelPoint350PrinterJob::sendCommand(const QByteArray& qbaCommand, QByteArray* ptrQbaResponse)
{
    if(!m_ptrPrinterInstanceUSB)
    {
        ROLLSCRIPT_ERROR(tr("NoPrinterInstance"), QStringLiteral("m_ptrPrinterInstanceUSB is nullptr."));
        return false;
    }

    if(!m_ptrPrinterInstanceUSB->send(qbaCommand))
    {
        ROLLSCRIPT_ERROR_CAUSE(tr("SendError"), QStringLiteral("m_ptrPrinterInstanceUSB->send() failed"), m_ptrPrinterInstanceUSB->takeError());
        return false;
    }

    if(ptrQbaResponse)
    {
        ptrQbaResponse->clear();
        if(!m_ptrPrinterInstanceUSB->receive(*ptrQbaResponse))
        {
            ROLLSCRIPT_ERROR_CAUSE(tr("ReceiveError"), QStringLiteral("m_ptrPrinterInstanceUSB->receive() failed"), m_ptrPrinterInstanceUSB->takeError());
            return false;
        }
    }

    return true;
}

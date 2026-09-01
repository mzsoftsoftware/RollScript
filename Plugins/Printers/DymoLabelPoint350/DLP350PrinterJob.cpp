#include "DLP350PrinterJob.h"

#include "Core/USB/PrinterInstanceUSB.h"


DymoLabelPoint350PrinterJob::DymoLabelPoint350PrinterJob(PrinterInstanceUSB* ptrPrinterInstanceUSB)
    : m_ptrPrinterInstanceUSB(ptrPrinterInstanceUSB)
{
}
DymoLabelPoint350PrinterJob::~DymoLabelPoint350PrinterJob()
{
}

/*
bool DymoLabelPoint350PrinterPlugin::readStatus()
{
    return false;
}

bool DymoLabelPoint350PrinterPlugin::readMedia()
{
    return false;
}
*/

bool DymoLabelPoint350PrinterJob::sendCommand(const QByteArray& baCommand, QByteArray* ptrBaResponse)
{
    if(!m_ptrPrinterInstanceUSB)
    {
        ROLLSCRIPT_ERROR(tr("NoPrinterInstance"), QStringLiteral("m_ptrPrinterInstanceUSB is nullptr."));
        return false;
    }

    if(!m_ptrPrinterInstanceUSB->send(baCommand))
    {
        ROLLSCRIPT_ERROR_CAUSE(tr("SendError"), QStringLiteral("m_ptrPrinterInstanceUSB->send() failed"), m_ptrPrinterInstanceUSB->takeError());
        return false;
    }

    if(ptrBaResponse)
    {
        ptrBaResponse->clear();
        if(!m_ptrPrinterInstanceUSB->receive(*ptrBaResponse))
        {
            ROLLSCRIPT_ERROR_CAUSE(tr("ReceiveError"), QStringLiteral("m_ptrPrinterInstanceUSB->receive() failed"), m_ptrPrinterInstanceUSB->takeError());
            return false;
        }
    }

    return true;
}

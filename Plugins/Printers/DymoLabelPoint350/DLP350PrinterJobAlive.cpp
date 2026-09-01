#include "DLP350PrinterJobAlive.h"


DymoLabelPoint350PrinterJobAlive::DymoLabelPoint350PrinterJobAlive(PrinterInstanceUSB* ptrPrinterInstanceUSB)
    : DymoLabelPoint350PrinterJob(ptrPrinterInstanceUSB)
{
}
DymoLabelPoint350PrinterJobAlive::~DymoLabelPoint350PrinterJobAlive()
{
}

bool DymoLabelPoint350PrinterJobAlive::execute()
{
    /*
    * Dymo LabelPoint 350 keep-alive.
    *
    * The original Windows driver does not keep the printer
    * responsive after longer idle periods.
    *
    * This sequence was determined experimentally and keeps
    * the device communication alive without triggering any
    * visible printer action.
    */
    QByteArray cmd;
    QByteArray rsp;

    // ESC A - Read status
    cmd.append(char(0x1B));
    cmd.append('A');

    if(!sendCommand(cmd, &rsp))
    {
        ROLLSCRIPT_ERROR_CAUSE(tr("AliveError"), QStringLiteral("sendCommand() failed"), takeError());
        return false;
    }

    cmd.clear();


    // ESC E
    // ESC C0
    // ESC D0
    cmd.append(char(0x1B));
    cmd.append('E');

    cmd.append(char(0x1B));
    cmd.append('C');
    cmd.append('0');

    cmd.append(char(0x1B));
    cmd.append('D');
    cmd.append('0');

    if(!sendCommand(cmd))
    {
        ROLLSCRIPT_ERROR_CAUSE(tr("AliveError"), QStringLiteral("sendCommand() failed"), takeError());
        return false;
    }

    cmd.clear();


    // ESC A - Read status again
    cmd.append(char(0x1B));
    cmd.append('A');

    if(!sendCommand(cmd, &rsp))
    {
        ROLLSCRIPT_ERROR_CAUSE(tr("AliveError"), QStringLiteral("sendCommand() failed"), takeError());
        return false;
    }

    return true;
}


#include "DymoLabelPoint350PrinterPlugin.h"

#include "Core/USB/PrinterInstanceUSB.h"
#include "Core/USB/USBDeviceInfo.h"
#include "DymoLabelPoint350PrinterMedia.h"


DymoLabelPoint350PrinterPlugin::DymoLabelPoint350PrinterPlugin(QObject* parent)
    : IPrinterPlugin(parent)
{
    m_ptrTimerAlive = new QTimer(this);
    connect(m_ptrTimerAlive, &QTimer::timeout, this, &DymoLabelPoint350PrinterPlugin::slot_timerAlive);
}

bool DymoLabelPoint350PrinterPlugin::supportsUsb(const USBDeviceInfo* ptrDevice) const
{
    if(!ptrDevice)
    {
        return false;
    }

    // Mein fixer Drucker : PID=0x0015, VID=0x0922
    return ptrDevice->vendorId() == 0x0922 && ptrDevice->productId() == 0x0015;
}

QList<PrinterMedia*> DymoLabelPoint350PrinterPlugin::createPrinterMedias()
{
    QList<PrinterMedia*> medias;

    // 19mm
    {
        DymoLabelPoint350PrinterMedia* ptrMedia = new DymoLabelPoint350PrinterMedia(QStringLiteral("DymoLabelPoint350_19mm"), QStringLiteral("19 mm"), this);
        ptrMedia->setMediaDataMm(19.0, 2.9, 0.8, 35.0);
        ptrMedia->setMediaDataPx(180, 0, 0+(13*8)+6);
        medias.append(ptrMedia);
    }

    // 12mm
    {
        DymoLabelPoint350PrinterMedia* ptrMedia = new DymoLabelPoint350PrinterMedia(QStringLiteral("DymoLabelPoint350_12mm"), QStringLiteral("12 mm"), this);
        ptrMedia->setMediaDataMm(12.0, 0.5, 0.8, 35.0);
        ptrMedia->setMediaDataPx(180, (1*8)+4, 4+(9*8)+1);
        medias.append(ptrMedia);
    }

    // 9mm
    {
        DymoLabelPoint350PrinterMedia* ptrMedia = new DymoLabelPoint350PrinterMedia(QStringLiteral("DymoLabelPoint350_9mm"), QStringLiteral("9 mm"), this);
        ptrMedia->setMediaDataMm(9.0, 0.2, 0.2, 35.0);
        ptrMedia->setMediaDataPx(180, (2*8)+3, 5+(7*8)+1);
        medias.append(ptrMedia);
    }

    return medias;
}


bool DymoLabelPoint350PrinterPlugin::open(PrinterInstance* ptrPrinterInstance)
{
    m_ptrPrinterInstanceUSB = qobject_cast<PrinterInstanceUSB*>(ptrPrinterInstance);

    if(!m_ptrPrinterInstanceUSB)
    {
        ROLLSCRIPT_ERROR(tr("NoPrinterInstance"), QStringLiteral("m_ptrPrinterInstanceUSB is nullptr."));
        return false;
    }

    if(!alive())
    {        
        return false;
    }

    m_ptrTimerAlive->start(5000);

    return true;
}

bool DymoLabelPoint350PrinterPlugin::close()
{
    if(!m_ptrPrinterInstanceUSB)
        return true;

    if(m_ptrTimerAlive)
        m_ptrTimerAlive->stop();

    m_ptrPrinterInstanceUSB = nullptr;

    return true;
}

void DymoLabelPoint350PrinterPlugin::slot_timerAlive()
{
    if(!alive())
    {
        m_ptrTimerAlive->stop();
        emit printerError();
    }
}

bool DymoLabelPoint350PrinterPlugin::alive()
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

bool DymoLabelPoint350PrinterPlugin::readStatus()
{
    return false;
}

bool DymoLabelPoint350PrinterPlugin::readMedia()
{
    return false;
}

bool DymoLabelPoint350PrinterPlugin::sendCommand(const QByteArray& baCommand, QByteArray* ptrBaResponse)
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

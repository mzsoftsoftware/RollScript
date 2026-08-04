#include "DymoLabelPoint350PrinterPlugin.h"

#include "Common/Core/USB/PrinterInstanceUSB.h"
#include "Common/Core/USB/USBDeviceInfo.h"


DymoLabelPoint350PrinterPlugin::DymoLabelPoint350PrinterPlugin(QObject* parent)
    : QObject(parent)
{
    m_ptrTimerAlive = new QTimer(this);
    connect(m_ptrTimerAlive, &QTimer::timeout, this, &DymoLabelPoint350PrinterPlugin::slot_timerAlive);
}


QString DymoLabelPoint350PrinterPlugin::pluginId() const
{
    return "dymo.labelpoint350";
}
QString DymoLabelPoint350PrinterPlugin::displayName() const
{
    return "Dymo LabelPoint 350";
}
QString DymoLabelPoint350PrinterPlugin::version() const
{
    return "1.0.0";
}
QIcon DymoLabelPoint350PrinterPlugin::icon() const
{
    return QIcon();
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


bool DymoLabelPoint350PrinterPlugin::open(PrinterInstance* ptrPrinterInstance)
{
    m_ptrPrinterInstanceUSB =
        qobject_cast<PrinterInstanceUSB*>(ptrPrinterInstance);

    if(!m_ptrPrinterInstanceUSB)
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = tr("Invalid printer instance.");
        return false;
    }

    if(!alive())
    {
        return false;
    }

    m_ptrTimerAlive->start(5000);

    /*
     * TODO:
     OK* - initialize printer
     OK* - check alive & read status
     * - load medias
     */

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
        // TASK : DymoLabelPoint350PrinterPlugin::slot_timerAlive() Error handling
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

    if(!sendCommand(cmd, rsp))
        return false;

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

    if(!sendCommand(cmd, rsp))
        return false;

    cmd.clear();


    // ESC A - Read status again
    cmd.append(char(0x1B));
    cmd.append('A');

    if(!sendCommand(cmd, rsp))
        return false;

    return true;
}

bool DymoLabelPoint350PrinterPlugin::readStatus()
{

}

bool DymoLabelPoint350PrinterPlugin::readMedia()
{

}

bool DymoLabelPoint350PrinterPlugin::sendCommand(const QByteArray& baCommand, QByteArray& baResponse)
{
    if(!m_ptrPrinterInstanceUSB)
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = tr("Invalid printer instance.");
        return false;
    }

    if(!m_ptrPrinterInstanceUSB->send(baCommand))
    {
        m_qstrLastError = m_ptrPrinterInstanceUSB->lastError();
        return false;
    }

    baResponse.clear();
    if(!m_ptrPrinterInstanceUSB->receive(baResponse))
    {
        m_qstrLastError = m_ptrPrinterInstanceUSB->lastError();
        return false;
    }

    return true;
}

#include "PrinterInstanceUSB.h"

#include "Core/Plugins/IPrinterPlugin.h"
#include "Core/USB/USBManager.h"


PrinterInstanceUSB::PrinterInstanceUSB(IPrinterPlugin* ptrPrinterPlugin, USBManager* ptrUSBManager, const USBDeviceInfo* ptrDeviceInfo, QObject* parent)
    : PrinterInstance(ptrPrinterPlugin, parent)
    , m_ptrUSBManager(ptrUSBManager)
    , m_ptrDeviceInfo(ptrDeviceInfo)
{
    m_qstrId = QStringLiteral("USB:%1:%2:%3").arg(m_ptrDeviceInfo->manufacturer(), m_ptrDeviceInfo->product(), m_ptrDeviceInfo->serial());
    m_qstrDisplayName = QStringLiteral("%1 - %2 - %3").arg(m_ptrDeviceInfo->manufacturer(), m_ptrDeviceInfo->product(), m_ptrDeviceInfo->serial());
}
PrinterInstanceUSB::~PrinterInstanceUSB()
{
    close();
}

bool PrinterInstanceUSB::open()
{
    if(!m_ptrPrinterPlugin)
    {
        ROLLSCRIPT_ERROR(tr("NoPlugin"), QStringLiteral("m_ptrPrinterPlugin is nullptr."));
        return false;
    }

    if(!m_ptrUSBManager)
    {
        ROLLSCRIPT_ERROR(tr("NoUSBManager"), QStringLiteral("m_ptrUSBManager is nullptr."));
        return false;
    }

    if(m_bConnected)
        return true;

    if(!m_ptrUSBManager->open(m_ptrDeviceInfo))
    {
        ROLLSCRIPT_ERROR_CAUSE(tr("OpenFailed"), QStringLiteral("m_ptrUSBManager->open failed"), m_ptrUSBManager->takeError());
        return false;
    }

    m_bConnected = true;

    if(!m_ptrPrinterPlugin->open(this))
    {
        m_ptrUSBManager->close();

        ROLLSCRIPT_ERROR_CAUSE(tr("OpenFailed"), QStringLiteral("m_ptrPrinterPlugin->open failed"), m_ptrPrinterPlugin->takeError());
        return false;
    }

    return true;
}

bool PrinterInstanceUSB::close()
{
    if(!m_ptrPrinterPlugin)
    {
        ROLLSCRIPT_ERROR(tr("NoPlugin"), QStringLiteral("m_ptrPrinterPlugin is nullptr."));
        return false;
    }

    if(!m_ptrUSBManager)
    {
        ROLLSCRIPT_ERROR(tr("NoUSBManager"), QStringLiteral("m_ptrUSBManager is nullptr."));
        return false;
    }

    if(!m_bConnected)
        return true;

    if(!m_ptrPrinterPlugin->close())
    {
        ROLLSCRIPT_ERROR_CAUSE(tr("CloseFailed"), QStringLiteral("m_ptrPrinterPlugin->close failed"), m_ptrPrinterPlugin->takeError());
        return false;
    }

    if(!m_ptrUSBManager->close())
    {
        ROLLSCRIPT_ERROR_CAUSE(tr("CloseFailed"), QStringLiteral("m_ptrUSBManager->close failed"), m_ptrUSBManager->takeError());
        return false;
    }

    m_bConnected = false;
    return true;
}

bool PrinterInstanceUSB::send(const QByteArray& baData)
{
    if(!m_ptrUSBManager)
    {
        ROLLSCRIPT_ERROR(tr("NoUSBManager"), QStringLiteral("m_ptrUSBManager is nullptr."));
        return false;
    }

    if(!m_bConnected)
    {
        ROLLSCRIPT_ERROR(tr("NotConnected"), QStringLiteral("m_bConnected is false."));
        return false;
    }

    if(!m_ptrUSBManager->send(baData))
    {
        ROLLSCRIPT_ERROR_CAUSE(tr("SendFailed"), QStringLiteral("m_ptrUSBManager->send failed"), m_ptrUSBManager->takeError());
        return false;
    }

    return true;
}
bool PrinterInstanceUSB::receive(QByteArray&baData, int maxLength, int timeoutMs)
{
    if(!m_ptrUSBManager)
    {
        ROLLSCRIPT_ERROR(tr("NoUSBManager"), QStringLiteral("m_ptrUSBManager is nullptr."));
        return false;
    }

    if(!m_bConnected)
    {
        ROLLSCRIPT_ERROR(tr("NotConnected"), QStringLiteral("m_bConnected is false."));
        return false;
    }

    if(!m_ptrUSBManager->receive(baData, maxLength, timeoutMs))
    {
        ROLLSCRIPT_ERROR_CAUSE(tr("ReceiveFailed"), QStringLiteral("m_ptrUSBManager->receive failed"), m_ptrUSBManager->takeError());
        return false;
    }

    return true;
}

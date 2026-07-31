#include "PrinterInstanceUSB.h"

#include "Core/USB/USBManager.h"


PrinterInstanceUSB::PrinterInstanceUSB(IPrinterPlugin* ptrPrinterPlugin, USBManager* ptrUSBManager, const USBDeviceInfo* ptrDeviceInfo, QObject* parent)
    : PrinterInstance(ptrPrinterPlugin, parent)
    , m_ptrUSBManager(ptrUSBManager)
    , m_ptrDeviceInfo(ptrDeviceInfo)
{
    m_qstrId = QString("USB:%1:%2:%3").arg(m_ptrDeviceInfo->manufacturer(), m_ptrDeviceInfo->product(), m_ptrDeviceInfo->serial());
    m_qstrDisplayName = QString("%1 - %2 - %3").arg(m_ptrDeviceInfo->manufacturer(), m_ptrDeviceInfo->product(), m_ptrDeviceInfo->serial());
}
PrinterInstanceUSB::~PrinterInstanceUSB()
{
    if(isConnected())
    {
        close();
    }
}

bool PrinterInstanceUSB::open()
{
    if(m_bConnected)
        return true;

    if(!m_ptrPrinterPlugin)
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = tr("Plugin is not available.");
        return false;
    }

    if(!m_ptrUSBManager)
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = tr("USB Manager is not available.");
        return false;
    }

    if(!m_ptrUSBManager->open(m_ptrDeviceInfo))
    {
        m_qstrLastError = m_ptrUSBManager->lastError();
        return false;
    }

    // TASK : USBManager->Connection handling -> init printer with plugin

    // TASK : Load Medias

    m_bConnected = true;
    return true;
}

bool PrinterInstanceUSB::close()
{
    if(!m_bConnected)
        return true;

    if(!m_ptrPrinterPlugin)
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = tr("Plugin is not available.");
        return false;
    }

    if(!m_ptrUSBManager)
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = tr("USB Manager is not available.");
        return false;
    }

    // TASK : Clear Medias

    // TASK : USBManager->Connection handling -> de-init printer with plugin

    if(!m_ptrUSBManager->close())
    {
        m_qstrLastError = m_ptrUSBManager->lastError();
        return false;
    }

    m_bConnected = false;
    return true;
}

bool PrinterInstanceUSB::send(const QByteArray& baData)
{
    if(!m_bConnected)
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = tr("Printer is not connected.");
        return false;
    }

    if(!m_ptrUSBManager)
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = tr("USB Manager is not available.");
        return false;
    }

    if(!m_ptrUSBManager->send(baData))
    {
        m_qstrLastError = m_ptrUSBManager->lastError();
        return false;
    }

    return true;
}
bool PrinterInstanceUSB::receive(QByteArray&baData, int maxLength, int timeoutMs)
{
    if(!m_bConnected)
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = tr("Printer is not connected.");
        return false;
    }

    if(!m_ptrUSBManager)
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = tr("USB Manager is not available.");
        return false;
    }

    if(!m_ptrUSBManager->receive(baData, maxLength, timeoutMs))
    {
        m_qstrLastError = m_ptrUSBManager->lastError();
        return false;
    }

    return true;
}
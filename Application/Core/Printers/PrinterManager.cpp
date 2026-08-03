#include "PrinterManager.h"

#include "Core/Plugins/PluginManager.h"
#include "Core/USB/USBManager.h"

#include "Common/Core/Plugins/IPrinterPlugin.h"
#include "Common/Core/USB/PrinterInstanceUSB.h"


PrinterManager::PrinterManager(PluginManager* ptrPluginManager, USBManager* ptrUSBManager, QObject *parent)
    : QObject{parent}
    , m_ptrPluginManager(ptrPluginManager)
    , m_ptrUSBManager(ptrUSBManager)
{
}
PrinterManager::~PrinterManager()
{
    if(m_ptrCurrentPrinterInstance)
    {
        m_ptrCurrentPrinterInstance->close();
        m_ptrCurrentPrinterInstance = nullptr;
    }

    qDeleteAll(m_hashPrinterInstances);
    m_hashPrinterInstances.clear();
    m_qstrPrinterIds.clear();
}

bool PrinterManager::init()
{
    if(!m_ptrUSBManager)
    {
        // TASK Use correct tr !!!
        m_qstrLastError = tr("USB Manager missing.");
        return false;
    }

    if(!m_ptrPluginManager)
    {
        // TASK Use correct tr !!!
        m_qstrLastError = tr("Plugin Manager missing.");
        return false;
    }

    return true;
}


bool PrinterManager::scanForDevices()
{
    // Close active printer
    if(m_ptrCurrentPrinterInstance)
    {
        if(!m_ptrCurrentPrinterInstance->close())
        {
            // TASK : Use correct tr !!!
            m_qstrLastError = QString("Could not close current printer.\n%1").arg(m_ptrCurrentPrinterInstance->lastError());
            emit managerError(m_qstrLastError);
            return false;
        }
        m_ptrCurrentPrinterInstance = nullptr;
    }

    // Cleanup
    qDeleteAll(m_hashPrinterInstances);
    m_hashPrinterInstances.clear();
    m_qstrPrinterIds.clear();

    // Scan the USB
    if(!m_ptrUSBManager->scanForDevices())
    {
        m_qstrLastError = m_ptrUSBManager->lastError();
        emit managerError(m_qstrLastError);
        return false;
    }

    const QList<USBDeviceInfo*> lstDevicesUsb = m_ptrUSBManager->devices();
    for(const USBDeviceInfo* ptrDeviceInfo : lstDevicesUsb)
    {
        IPrinterPlugin* ptrPrinterPlugin = m_ptrPluginManager->registryPrinters().supportsUsb(ptrDeviceInfo);
        if(!ptrPrinterPlugin)
            continue;

        PrinterInstance* ptrPrinterInstance = new PrinterInstanceUSB(ptrPrinterPlugin, m_ptrUSBManager, ptrDeviceInfo, this);
        m_hashPrinterInstances.insert(ptrPrinterInstance->id(), ptrPrinterInstance);
        m_qstrPrinterIds.append(ptrPrinterInstance->id());
    }

    emit scanFinished();
    return true;
}

bool PrinterManager::switchPrinter(const QString& qstrPrinterId)
{
    if(!m_hashPrinterInstances.contains(qstrPrinterId))
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = QString("Printer not found: %1").arg(qstrPrinterId);
        emit managerError(m_qstrLastError);
        return false;
    }

    PrinterInstance* ptrPrinterInstance = m_hashPrinterInstances.value(qstrPrinterId);
    if(ptrPrinterInstance == m_ptrCurrentPrinterInstance)
        return true;

    if(m_ptrCurrentPrinterInstance)
    {
        if(!m_ptrCurrentPrinterInstance->close())
        {
            // TASK : Use correct tr !!!
            m_qstrLastError = QString("Could not close current printer.\n%1").arg(m_ptrCurrentPrinterInstance->lastError());
            emit managerError(m_qstrLastError);
            return false;
        }
        m_ptrCurrentPrinterInstance = nullptr;
    }

    if(!ptrPrinterInstance->open())
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = QString("Could not open printer: %1\n%2").arg(qstrPrinterId, ptrPrinterInstance->lastError());
        emit managerError(m_qstrLastError);
        return false;
    }

    m_ptrCurrentPrinterInstance = ptrPrinterInstance;

    emit printerChanged();
    return true;
}

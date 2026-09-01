#include "PrinterManager.h"

#include "Plugins/PluginManager.h"
#include "Core/USB/USBManager.h"

#include "Core/Plugins/IPrinterPlugin.h"
#include "Core/USB/PrinterInstanceUSB.h"

#include "Plugins/PrinterPluginRegistry.h"


PrinterManager::PrinterManager(PluginManager* ptrPluginManager, USBManager* ptrUSBManager, QObject* parent)
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
        ROLLSCRIPT_ERROR(tr("PrinterManagerInitError"), QStringLiteral("m_ptrUSBManager is nullptr."));
        return false;
    }

    if(!m_ptrPluginManager)
    {
        ROLLSCRIPT_ERROR(tr("PrinterManagerInitError"), QStringLiteral("m_ptrPluginManager is nullptr."));
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
            ROLLSCRIPT_ERROR_CAUSE(tr("PrinterManagerScanError"), QStringLiteral("m_ptrCurrentPrinterInstance->close() failed."), m_ptrCurrentPrinterInstance->takeError());
            emit managerError();
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
        ROLLSCRIPT_ERROR_CAUSE(tr("PrinterManagerScanError"), QStringLiteral("m_ptrUSBManager->scanForDevices() failed."), m_ptrUSBManager->takeError());
        emit managerError();
        return false;
    }

    const QList<USBDeviceInfo*> lstDevicesUsb = m_ptrUSBManager->devices();
    for(const USBDeviceInfo* ptrDeviceInfo : lstDevicesUsb)
    {
        IPrinterPlugin* ptrPrinterPlugin = m_ptrPluginManager->registryPrinters()->supportsUsb(ptrDeviceInfo);
        if(!ptrPrinterPlugin)
            continue;

        PrinterInstance* ptrPrinterInstance = new PrinterInstanceUSB(ptrPrinterPlugin, m_ptrUSBManager, ptrDeviceInfo, this);
        connect(ptrPrinterInstance, &PrinterInstance::printerError, this, &PrinterManager::slotPrinterInstanceError);
        connect(ptrPrinterInstance, &PrinterInstance::printerPrintStarted, this, &PrinterManager::printStarted);
        connect(ptrPrinterInstance, &PrinterInstance::printerPrintProgress, this, &PrinterManager::printProgress);
        connect(ptrPrinterInstance, &PrinterInstance::printerPrintFinished, this, &PrinterManager::printFinished);

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
        ROLLSCRIPT_ERROR(tr("PrinterManagerSwitchError"), QStringLiteral("printer not found: %1").arg(qstrPrinterId));
        emit managerError();
        return false;
    }

    PrinterInstance* ptrPrinterInstance = m_hashPrinterInstances.value(qstrPrinterId);
    if(ptrPrinterInstance == m_ptrCurrentPrinterInstance)
        return true;

    if(m_ptrCurrentPrinterInstance)
    {
        if(!m_ptrCurrentPrinterInstance->close())
        {
            ROLLSCRIPT_ERROR_CAUSE(tr("PrinterManagerSwitchError"), QStringLiteral("m_ptrCurrentPrinterInstance->close() failed."), m_ptrCurrentPrinterInstance->takeError());
            emit managerError();
            return false;
        }
        m_ptrCurrentPrinterInstance = nullptr;
    }

    if(!ptrPrinterInstance->open())
    {
        ROLLSCRIPT_ERROR_CAUSE(tr("PrinterManagerSwitchError"), QStringLiteral("ptrPrinterInstance->open() failed."), ptrPrinterInstance->takeError());
        emit managerError();
        return false;
    }

    m_ptrCurrentPrinterInstance = ptrPrinterInstance;

    emit printerChanged();
    return true;
}

bool PrinterManager::print(const QImage& printImage, const PrinterMedia* ptrPrinterMediaId)
{
    if(!m_ptrCurrentPrinterInstance)
    {
        ROLLSCRIPT_ERROR(tr("PrinterManagerPrintError"), QStringLiteral("m_ptrCurrentPrinterInstance not set."));
        emit managerError();
        return false;
    }

    if(!m_ptrCurrentPrinterInstance->print(printImage, ptrPrinterMediaId))
    {
        ROLLSCRIPT_ERROR_CAUSE(tr("PrinterManagerPrintError"), QStringLiteral("m_ptrCurrentPrinterInstance->print() failed."), m_ptrCurrentPrinterInstance->takeError());
        emit managerError();
        return false;
    }

    return true;
}

void PrinterManager::slotPrinterInstanceError()
{
    PrinterInstance* ptrPrinterInstance = qobject_cast<PrinterInstance*>(sender());

    setErrorInternal(ptrPrinterInstance->takeError());
    emit managerError();
}
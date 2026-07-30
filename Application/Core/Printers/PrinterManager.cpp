#include "PrinterManager.h"

#include "Core/Plugins/PluginManager.h"
#include "PrinterInstance.h"
#include "Common/Core/Plugins/IPrinterPlugin.h"


PrinterManager::PrinterManager(PluginManager* ptrPluginManager, QObject *parent)
    : QObject{parent}
    , m_ptrPluginManager(ptrPluginManager)
{
}
PrinterManager::~PrinterManager()
{
    qDeleteAll(m_hashPrinterInstances);
    m_hashPrinterInstances.clear();
    m_qstrPrinterIds.clear();
}

void PrinterManager::slot_ScanForDevices()
{
    QList<USBDeviceInfo> lstDevicesUsb = scanForUsbDevices();
    for(const USBDeviceInfo& deviceInfo : lstDevicesUsb)
    {
        IPrinterPlugin* ptrPrinterPlugin = m_ptrPluginManager->registryPrinters().supportsUsb(deviceInfo);
        if(!ptrPrinterPlugin)
            continue;

        PrinterInstance* ptrPrinterInstance = new PrinterInstance(ptrPrinterPlugin, deviceInfo, this);
        m_qstrPrinterIds.append(ptrPrinterInstance->id());
        m_hashPrinterInstances.insert(ptrPrinterInstance->id(), ptrPrinterInstance);
    }

    emit scanFinished();
}

QList<USBDeviceInfo> PrinterManager::scanForUsbDevices()
{
    return {};
    /*
    // Check for an open device, close it
    if(!usbCloseActiveConnection())
    {
        emit deviceError("ScanForDevices failed during usbCloseActiveConnection.");
        return;
    }

    // Start the Scan
    if(!usbScan())
    {
        emit deviceError("ScanForDevices failed during usbScan.");
        return;
    }

    // Tell the caller the scan is done
    emit scanFinished();
    */
}


/***************************
** From here on USB Handling
****************************/
/*
bool DeviceManager::usbScan()
{
    qDeleteAll(m_hashPtrDeviceDymo);
    m_hashPtrDeviceDymo.clear();
    m_qstrDevices.clear();

    if(!m_ctxUsb)
    {
        emit logMessage("DymoController::usbScan - libusb init missing.");
        return false;
    }

    libusb_device **list = nullptr;
    ssize_t count = libusb_get_device_list(m_ctxUsb, &list);
    if(count<0)
    {
        emit logMessage("DeviceManager::usbScan - libusb_get_device_list returned 0.");
        return false;
    }

    for(ssize_t i=0; i<count; i++)
    {
        libusb_device_descriptor desc;
        libusb_get_device_descriptor(list[i], &desc);

        // Mein fixer Drucker : PID=, VID=0x0922
        if(desc.idVendor != 0x0922 || desc.idProduct != 0x0015)
            continue;

        libusb_device_handle* tmp = nullptr;
        if (libusb_open(list[i], &tmp) == 0)
        {
            char buffer[256];

            // LangID
            int iRet = libusb_get_string_descriptor(tmp, 0, 0, (unsigned char*)buffer, sizeof(buffer));
            if(iRet < 4)
            {
                emit logMessage(QString("DeviceManager::usbScan - LangID: %1").arg(iRet));
                libusb_close(tmp);
                continue;
            }

            DeviceDymo* ptrDeviceDymo = new DeviceDymo();

            // Product String
            if( desc.iProduct )
            {
                libusb_get_string_descriptor_ascii(tmp, desc.iProduct, (unsigned char*)buffer, sizeof(buffer));
                ptrDeviceDymo->setProduct( QString(buffer) );
            }

            // Manufacturer String
            if( desc.iManufacturer )
            {
                libusb_get_string_descriptor_ascii(tmp, desc.iManufacturer, (unsigned char*)buffer, sizeof(buffer));
                ptrDeviceDymo->setManufacturer( QString(buffer) );
            }

            // Serial
            if( desc.iSerialNumber )
            {
                libusb_get_string_descriptor_ascii(tmp, desc.iSerialNumber, (unsigned char*)buffer, sizeof(buffer));
                ptrDeviceDymo->setSerial( QString(buffer) );
            }

            libusb_close(tmp);

            if(ptrDeviceDymo->product().isEmpty() || ptrDeviceDymo->manufacturer().isEmpty() || ptrDeviceDymo->serial().isEmpty())
            {
                emit logMessage(QString("DeviceManager::usbScan - PMS: %1 %2 %3").arg(iRet));
                continue;
            }

            ptrDeviceDymo->setId( QString("%1%2%3").arg(ptrDeviceDymo->manufacturer(), ptrDeviceDymo->product(), ptrDeviceDymo->serial()) );
            ptrDeviceDymo->setName( QString("%1 - %2 - %3").arg(ptrDeviceDymo->manufacturer(), ptrDeviceDymo->product(), ptrDeviceDymo->serial()) );
            ptrDeviceDymo->setUsbDevice( list[i] );
            ptrDeviceDymo->fillLabelMedia();

            if(m_hashPtrDeviceDymo.contains(ptrDeviceDymo->id()))
            {
                emit logMessage(QString("Duplicate DeviceId : %1").arg(ptrDeviceDymo->id()));
                delete ptrDeviceDymo;
                ptrDeviceDymo = nullptr;
            }
            else
            {
                m_hashPtrDeviceDymo.insert(ptrDeviceDymo->id(), ptrDeviceDymo);
                m_qstrDevices.append(ptrDeviceDymo->id());
                //connect(ptrDeviceDymo, &DeviceDymo::logMessage, this, &DeviceManager::logMessage);
                emit logMessage(QString("Vendor and Product found: %1, %2").arg(desc.idVendor).arg(desc.idProduct));
            }
            break;
        }
    }
    return true;
}
bool DeviceManager::usbCloseActiveConnection()
{
    if(!m_ptrActiveConnection)
    {
        return true;
    }

    delete m_ptrActiveConnection;
    m_ptrActiveConnection = nullptr;
    m_qstrActiveDeviceId.clear();

    return true;
}
bool DeviceManager::usbOpenDevice(DeviceDymo* ptrDevice)
{
    if(m_ptrActiveConnection)
    {
        emit deviceError("usbOpenDevice called with active connection !");
        return false;
    }

    m_ptrActiveConnection = new DeviceConnectionDymo(ptrDevice, this);
    connect(m_ptrActiveConnection, &DeviceConnectionDymo::logMessage, this, &DeviceManager::logMessage);
    connect(m_ptrActiveConnection, &DeviceConnectionDymo::usbConnectionLost, this, &DeviceManager::slot_ActiveConnectionLost);
    connect(m_ptrActiveConnection, &DeviceConnectionDymo::usbConnectionError, this, &DeviceManager::slot_ActiveConnectionError);

    return m_ptrActiveConnection->usbOpen();
}
*/

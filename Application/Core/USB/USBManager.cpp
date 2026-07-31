#include "USBManager.h"

#include <libusb.h>


USBManager::USBManager(QObject *parent)
    : QObject{parent}
{
}

USBManager::~USBManager()
{
    close();
    clearUSBDeviceInfo();

    if(m_ptrLibUsbContext)
    {
        libusb_exit(m_ptrLibUsbContext);
        m_ptrLibUsbContext = nullptr;
    }
}

bool USBManager::init()
{
    if(m_ptrLibUsbContext)
        return true;

    int result = libusb_init(&m_ptrLibUsbContext);

    if(result != 0)
    {
        m_ptrLibUsbContext = nullptr;
        // TASK : Correct tr !!!
        m_qstrLastError = tr("Could not initialize USB support.");
        return false;
    }

    return true;
}

bool USBManager::scanForDevices()
{
    clearUSBDeviceInfo();

    if(!m_ptrLibUsbContext)
    {
        // TASK : Error in tr ???
        m_qstrLastError = "USBManager::scanDevices - libusb init missing.";
        return false;
    }

    libusb_device **list = nullptr;
    ssize_t count = libusb_get_device_list(m_ptrLibUsbContext, &list);
    if(count<0)
    {
        libusb_free_device_list(list, 1);
        m_qstrLastError = "DeviceManager::usbScan - libusb_get_device_list returned <0.";
        return false;
    }

    for(ssize_t i=0; i<count; i++)
    {
        libusb_device_descriptor desc;
        if(libusb_get_device_descriptor(list[i], &desc) != 0)
        {
            continue;
        }

        libusb_device_handle* tmp = nullptr;
        if (libusb_open(list[i], &tmp) == 0)
        {
            char buffer[256];

            // LangID
            buffer[0] = '\0';
            int iRet = libusb_get_string_descriptor(tmp, 0, 0, (unsigned char*)buffer, sizeof(buffer));
            if(iRet < 4)
            {
                //emit logMessage(QString("DeviceManager::usbScan - LangID: %1").arg(iRet));
                libusb_close(tmp);
                continue;
            }

            USBDeviceInfo* ptrUSBDeviceInfo = new USBDeviceInfo();
            ptrUSBDeviceInfo->setVendorId(desc.idVendor);
            ptrUSBDeviceInfo->setProductId(desc.idProduct);

            // Product String
            if( desc.iProduct )
            {
                buffer[0] = '\0';
                iRet = libusb_get_string_descriptor_ascii(tmp, desc.iProduct, (unsigned char*)buffer, sizeof(buffer));
                if(iRet > 0)
                {
                    ptrUSBDeviceInfo->setProduct( QString(buffer) );
                }
            }

            // Manufacturer String
            if( desc.iManufacturer )
            {
                buffer[0] = '\0';
                iRet = libusb_get_string_descriptor_ascii(tmp, desc.iManufacturer, (unsigned char*)buffer, sizeof(buffer));
                if(iRet > 0)
                {
                    ptrUSBDeviceInfo->setManufacturer( QString(buffer) );
                }
            }

            // Serial
            if( desc.iSerialNumber )
            {
                buffer[0] = '\0';
                iRet = libusb_get_string_descriptor_ascii(tmp, desc.iSerialNumber, (unsigned char*)buffer, sizeof(buffer));
                if(iRet > 0)
                {
                    ptrUSBDeviceInfo->setSerialNumber( QString(buffer) );
                }
            }

            ptrUSBDeviceInfo->setUSBDevice(list[i]);
            libusb_ref_device(list[i]);

            libusb_close(tmp);

            m_qlstUSBDeviceInfo.append(ptrUSBDeviceInfo);
        }
    }
    libusb_free_device_list(list, 1);

    return true;
}

bool USBManager::open(const USBDeviceInfo* ptrDeviceInfo)
{
    if(!ptrDeviceInfo)
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = "USBManager::open - USBDeviceInfo is null.";
        return false;
    }

    if(!ptrDeviceInfo->usbDevice())
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = "USBManager::open - libusb device is null.";
        return false;
    }

    if(m_ptrLibUsbDeviceHandle)
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = "USBManager::open - USB device already open.";
        return false;
    }

    int rc = libusb_open(ptrDeviceInfo->usbDevice(), &m_ptrLibUsbDeviceHandle);
    if(rc != LIBUSB_SUCCESS)
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = QString("USBManager::open - libusb_open failed: %1").arg(libusb_error_name(rc));
        m_ptrLibUsbDeviceHandle = nullptr;
        return false;
    }

    m_uiInterfaceNumber = -1;
    m_uiEndpointIn = 0;
    m_uiEndpointOut = 0;
    m_uiEndpointInAttr = 0;
    m_uiEndpointOutAttr = 0;

    libusb_config_descriptor* config = nullptr;
    rc = libusb_get_active_config_descriptor(ptrDeviceInfo->usbDevice(), &config);
    if(rc != LIBUSB_SUCCESS)
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = QString( "USBManager::open - libusb_get_active_config_descriptor failed: %1").arg(libusb_error_name(rc));
        close();
        return false;
    }

    bool interfaceFound = false;

    for(uint8_t ifIdx = 0; ifIdx < config->bNumInterfaces; ++ifIdx)
    {
        const libusb_interface& interface = config->interface[ifIdx];
        for(int alt = 0; alt < interface.num_altsetting; ++alt)
        {
            const libusb_interface_descriptor& ifDesc = interface.altsetting[alt];

            // USB Printer Class
            if(ifDesc.bInterfaceClass != 0x07)
                continue;

            m_uiInterfaceNumber = ifDesc.bInterfaceNumber;
            for(uint8_t ep = 0; ep < ifDesc.bNumEndpoints; ++ep)
            {
                const libusb_endpoint_descriptor& epDesc = ifDesc.endpoint[ep];
                if((epDesc.bmAttributes & LIBUSB_TRANSFER_TYPE_MASK) != LIBUSB_ENDPOINT_TRANSFER_TYPE_BULK)
                    continue;

                if(epDesc.bEndpointAddress & LIBUSB_ENDPOINT_IN)
                {
                    m_uiEndpointIn = epDesc.bEndpointAddress;
                    m_uiEndpointInAttr = epDesc.bmAttributes;
                }
                else
                {
                    m_uiEndpointOut = epDesc.bEndpointAddress;
                    m_uiEndpointOutAttr = epDesc.bmAttributes;
                }
            }
            interfaceFound = true;
            break;
        }

        if(interfaceFound)
            break;
    }

    libusb_free_config_descriptor(config);

    if(!interfaceFound)
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = "USBManager::open - No USB printer interface found.";
        close();
        return false;
    }

    if(m_uiEndpointIn == 0 || m_uiEndpointOut == 0)
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = "USBManager::open - Bulk IN/OUT endpoint missing.";
        close();
        return false;
    }

    if(libusb_kernel_driver_active(m_ptrLibUsbDeviceHandle, m_uiInterfaceNumber) == 1)
    {
        rc = libusb_detach_kernel_driver(m_ptrLibUsbDeviceHandle, m_uiInterfaceNumber);
        if(rc != LIBUSB_SUCCESS)
        {
            // TASK : Use correct tr !!!
            m_qstrLastError = QString("USBManager::open - libusb_detach_kernel_driver failed: %1").arg(libusb_error_name(rc));
            close();
            return false;
        }
        m_bKernelDriverDetached = true;
    }

    rc = libusb_claim_interface(m_ptrLibUsbDeviceHandle, m_uiInterfaceNumber);
    if(rc != LIBUSB_SUCCESS)
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = QString("USBManager::open - libusb_claim_interface failed: %1").arg(libusb_error_name(rc));
        close();
        return false;
    }

    m_bOpen = true;
    return true;
}

bool USBManager::close()
{
    // Nichts geöffnet
    if(!m_ptrLibUsbDeviceHandle)
    {
        m_bOpen = false;
        m_bKernelDriverDetached = false;
        m_uiInterfaceNumber = -1;
        m_uiEndpointIn = 0;
        m_uiEndpointOut = 0;
        m_uiEndpointInAttr = 0;
        m_uiEndpointOutAttr = 0;

        return true;
    }

    bool result = true;

    // Interface freigeben
    if(m_uiInterfaceNumber >= 0)
    {
        const int rc = libusb_release_interface(m_ptrLibUsbDeviceHandle, m_uiInterfaceNumber);
        if(rc != LIBUSB_SUCCESS)
        {
            // TASK : Use correct tr !!!
            m_qstrLastError = QString("USBManager::close - libusb_release_interface failed: %1").arg(libusb_error_name(rc));
            result = false;
        }
    }

    // Kernel-Treiber wieder anhängen
    if(m_bKernelDriverDetached && m_uiInterfaceNumber >= 0)
    {
        const int rc = libusb_attach_kernel_driver(m_ptrLibUsbDeviceHandle, m_uiInterfaceNumber);
        if(rc != LIBUSB_SUCCESS)
        {
            // TASK : Use correct tr !!!
            m_qstrLastError = QString("USBManager::close - libusb_attach_kernel_driver failed: %1").arg(libusb_error_name(rc));
            result = false;
        }
        m_bKernelDriverDetached = false;
    }

    // Handle schließen
    libusb_close(m_ptrLibUsbDeviceHandle);
    m_ptrLibUsbDeviceHandle = nullptr;

    // Zustand zurücksetzen
    m_bOpen = false;
    m_uiInterfaceNumber = -1;
    m_uiEndpointIn = 0;
    m_uiEndpointOut = 0;
    m_uiEndpointInAttr = 0;
    m_uiEndpointOutAttr = 0;

    return result;
}

bool USBManager::send(const QByteArray& baData, int timeoutMs)
{
    if(!m_ptrLibUsbDeviceHandle)
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = "USBManager::send - USB device not open.";
        return false;
    }

    if(m_uiEndpointOut == 0)
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = "USBManager::send - Bulk OUT endpoint missing.";
        return false;
    }

    if(baData.isEmpty())
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = "USBManager::send - Data is empty.";
        return false;
    }

    int transferred = 0;

    const int rc = libusb_bulk_transfer(m_ptrLibUsbDeviceHandle, m_uiEndpointOut,
                                        reinterpret_cast<unsigned char*>(const_cast<char*>(baData.constData())),
                                        baData.size(), &transferred, timeoutMs);
    if(rc != LIBUSB_SUCCESS)
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = QString("USBManager::send - libusb_bulk_transfer failed: %1").arg(libusb_error_name(rc));
        return false;
    }

    if(transferred != baData.size())
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = QString("USBManager::send - Incomplete transfer: %1 of %2 bytes.").arg(transferred).arg(baData.size());
        return false;
    }

    return true;
}
bool USBManager::receive(QByteArray&baData, int maxLength, int timeoutMs)
{
    if(!m_ptrLibUsbDeviceHandle)
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = "USBManager::receive - USB device not open.";
        return false;
    }

    if(m_uiEndpointIn == 0)
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = "USBManager::receive - Bulk IN endpoint missing.";
        return false;
    }

    if(maxLength <= 0)
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = "USBManager::receive - Invalid maxLength.";
        return false;
    }

    baData.resize(maxLength);

    int transferred = 0;

    const int rc = libusb_bulk_transfer(m_ptrLibUsbDeviceHandle, m_uiEndpointIn,
                                        reinterpret_cast<unsigned char*>(baData.data()),
                                        maxLength, &transferred, timeoutMs);
    if(rc != LIBUSB_SUCCESS)
    {
        baData.clear();

        // TASK : Use correct tr !!!
        m_qstrLastError = QString("USBManager::receive - libusb_bulk_transfer failed: %1").arg(libusb_error_name(rc));
        return false;
    }

    baData.resize(transferred);

    return true;
}


void USBManager::clearUSBDeviceInfo()
{
    for(const USBDeviceInfo* ptrDeviceInfo : m_qlstUSBDeviceInfo)
    {
        if(ptrDeviceInfo && ptrDeviceInfo->usbDevice())
            libusb_unref_device(ptrDeviceInfo->usbDevice());
    }

    qDeleteAll(m_qlstUSBDeviceInfo);
    m_qlstUSBDeviceInfo.clear();
}

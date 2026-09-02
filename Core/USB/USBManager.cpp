#include "USBManager.h"

#include <libusb.h>

#include <QDebug>

USBManager::USBManager(QObject* parent)
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

        ROLLSCRIPT_ERROR(tr("USBInitError"), QStringLiteral("libusb_init failed."));
        return false;
    }

    return true;
}

bool USBManager::scanForDevices()
{
    clearUSBDeviceInfo();

    if(!m_ptrLibUsbContext)
    {
        ROLLSCRIPT_ERROR(tr("USBInitError"), QStringLiteral("m_ptrLibUsbContext is nullptr."));
        return false;
    }

    libusb_device** list = nullptr;
    ssize_t count = libusb_get_device_list(m_ptrLibUsbContext, &list);
    if(count<0)
    {
        libusb_free_device_list(list, 1);
        ROLLSCRIPT_ERROR(tr("USBScanError"), QStringLiteral("libusb_get_device_list return<0 : %1.").arg(count));
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
                    ptrUSBDeviceInfo->setProduct( QString::fromLatin1(buffer) );
                }
            }

            // Manufacturer String
            if( desc.iManufacturer )
            {
                buffer[0] = '\0';
                iRet = libusb_get_string_descriptor_ascii(tmp, desc.iManufacturer, (unsigned char*)buffer, sizeof(buffer));
                if(iRet > 0)
                {
                    ptrUSBDeviceInfo->setManufacturer( QString::fromLatin1(buffer) );
                }
            }

            // Serial
            if( desc.iSerialNumber )
            {
                buffer[0] = '\0';
                iRet = libusb_get_string_descriptor_ascii(tmp, desc.iSerialNumber, (unsigned char*)buffer, sizeof(buffer));
                if(iRet > 0)
                {
                    ptrUSBDeviceInfo->setSerialNumber( QString::fromLatin1(buffer) );
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
        ROLLSCRIPT_ERROR(tr("ErrorDeviceInfo"), QStringLiteral("ptrDeviceInfo is nullptr."));
        return false;
    }

    if(!ptrDeviceInfo->usbDevice())
    {
        ROLLSCRIPT_ERROR(tr("ErrorDeviceInfo"), QStringLiteral("ptrDeviceInfo->usbDevice() is nullptr."));
        return false;
    }

    if(m_ptrLibUsbDeviceHandle)
    {
        ROLLSCRIPT_ERROR(tr("AlreadyOpen"), QStringLiteral("m_ptrLibUsbDeviceHandle is already valid."));
        return false;
    }

    int rc = libusb_open(ptrDeviceInfo->usbDevice(), &m_ptrLibUsbDeviceHandle);
    if(rc != LIBUSB_SUCCESS)
    {
        ROLLSCRIPT_ERROR(tr("USBOpenError"), QStringLiteral("libusb_open failed: %1").arg(libusb_error_name(rc)));
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
        ROLLSCRIPT_ERROR(tr("USBOpenError"), QStringLiteral("libusb_get_active_config_descriptor failed: %1").arg(libusb_error_name(rc)));
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
        ROLLSCRIPT_ERROR(tr("USBOpenError"), QStringLiteral("interfaceFound is nullptr"));
        close();
        return false;
    }

    if(m_uiEndpointIn == 0 || m_uiEndpointOut == 0)
    {
        ROLLSCRIPT_ERROR(tr("USBOpenError"), QStringLiteral("m_uiEndpointIn or m_uiEndpointOut is 0"));
        close();
        return false;
    }

    if(libusb_kernel_driver_active(m_ptrLibUsbDeviceHandle, m_uiInterfaceNumber) == 1)
    {
        rc = libusb_detach_kernel_driver(m_ptrLibUsbDeviceHandle, m_uiInterfaceNumber);
        if(rc != LIBUSB_SUCCESS)
        {
            ROLLSCRIPT_ERROR(tr("USBOpenError"), QStringLiteral("libusb_detach_kernel_driver failed: %1").arg(libusb_error_name(rc)));
            close();
            return false;
        }
        m_bKernelDriverDetached = true;
    }

    rc = libusb_claim_interface(m_ptrLibUsbDeviceHandle, m_uiInterfaceNumber);
    if(rc != LIBUSB_SUCCESS)
    {
        ROLLSCRIPT_ERROR(tr("USBOpenError"), QStringLiteral("libusb_claim_interface failed: %1").arg(libusb_error_name(rc)));
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
            ROLLSCRIPT_ERROR(tr("USBCloseError"), QStringLiteral("libusb_release_interface failed: %1").arg(libusb_error_name(rc)));
            result = false;
        }
    }

    // Kernel-Treiber wieder anhängen
    if(m_bKernelDriverDetached && m_uiInterfaceNumber >= 0)
    {
        const int rc = libusb_attach_kernel_driver(m_ptrLibUsbDeviceHandle, m_uiInterfaceNumber);
        if(rc != LIBUSB_SUCCESS)
        {
            ROLLSCRIPT_ERROR(tr("USBCloseError"), QStringLiteral("libusb_attach_kernel_driver failed: %1").arg(libusb_error_name(rc)));
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
        ROLLSCRIPT_ERROR(tr("USBSendError"), QStringLiteral("m_ptrLibUsbDeviceHandle is nullptr."));
        return false;
    }

    if(m_uiEndpointOut == 0)
    {
        ROLLSCRIPT_ERROR(tr("USBSendError"), QStringLiteral("m_uiEndpointOut is 0."));
        return false;
    }

    if(baData.isEmpty())
    {
        ROLLSCRIPT_ERROR(tr("USBSendError"), QStringLiteral("baData is emüpty."));
        return false;
    }

    int transferred = 0;

    const int rc = libusb_bulk_transfer(m_ptrLibUsbDeviceHandle, m_uiEndpointOut,
                                        reinterpret_cast<unsigned char*>(const_cast<char*>(baData.constData())),
                                        baData.size(), &transferred, timeoutMs);
    if(rc != LIBUSB_SUCCESS)
    {
        ROLLSCRIPT_ERROR(tr("USBSendError"), QStringLiteral("libusb_bulk_transfer failed: %1").arg(libusb_error_name(rc)));
        return false;
    }

    if(transferred != baData.size())
    {
        ROLLSCRIPT_ERROR(tr("USBSendError"), QStringLiteral("Incomplete transfer: %1 of %2 bytes.").arg(transferred, baData.size()));
        return false;
    }

    return true;
}
bool USBManager::receive(QByteArray&baData, int maxLength, int timeoutMs)
{
    if(!m_ptrLibUsbDeviceHandle)
    {
        ROLLSCRIPT_ERROR(tr("USBReceiveError"), QStringLiteral("m_ptrLibUsbDeviceHandle is nullptr."));
        return false;
    }

    if(m_uiEndpointIn == 0)
    {
        ROLLSCRIPT_ERROR(tr("USBReceiveError"), QStringLiteral("m_uiEndpointIn is 0."));
        return false;
    }

    if(maxLength <= 0)
    {
        ROLLSCRIPT_ERROR(tr("USBReceiveError"), QStringLiteral("maxLength is less or equal 0."));
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

        ROLLSCRIPT_ERROR(tr("USBReceiveError"), QStringLiteral("libusb_bulk_transfer failed: %1").arg(libusb_error_name(rc)));
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

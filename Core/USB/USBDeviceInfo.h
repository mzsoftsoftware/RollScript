#pragma once

#include <QString>

struct libusb_device;

class USBDeviceInfo
{
public:
    explicit USBDeviceInfo();

    // Getter
    uint16_t vendorId() const                       { return m_ui16VendorId; }
    uint16_t productId() const                      { return m_ui16ProductId; }

    QString manufacturer() const                    { return m_qstrManufacturer; }
    QString product() const                         { return m_qstrProduct; }
    QString serial() const                          { return m_qstrSerialNumber; }

    libusb_device* usbDevice() const                { return m_ptrUSBDevice; }

    // Setter
    void setVendorId(const uint16_t ui16Value)      { m_ui16VendorId = ui16Value; }
    void setProductId(const uint16_t ui16Value)     { m_ui16ProductId = ui16Value; }

    void setManufacturer(const QString& qstrValue)  { m_qstrManufacturer = qstrValue; }
    void setProduct(const QString& qstrValue)       { m_qstrProduct = qstrValue; }
    void setSerialNumber(const QString& qstrValue)  { m_qstrSerialNumber = qstrValue; }

    void setUSBDevice(libusb_device* ptrUSBDevice)  { m_ptrUSBDevice = ptrUSBDevice; }

private:
    uint16_t m_ui16VendorId = 0;
    uint16_t m_ui16ProductId = 0;

    QString m_qstrManufacturer;
    QString m_qstrProduct;
    QString m_qstrSerialNumber;

    libusb_device* m_ptrUSBDevice = nullptr;
};

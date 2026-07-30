#pragma once

#include <QString>

class USBDeviceInfo
{
public:
    explicit USBDeviceInfo();

    quint16 vendorId() const            { return m_ui16VendorId; }
    quint16 productId() const           { return m_ui16ProductId; }

    QString manufacturer() const        { return m_qstrManufacturer; }
    QString product() const             { return m_qstrProduct; }
    QString serial() const              { return m_qstrSerialNumber; }

private:
    uint16_t m_ui16VendorId = 0;
    uint16_t m_ui16ProductId = 0;

    QString m_qstrManufacturer;
    QString m_qstrProduct;
    QString m_qstrSerialNumber;
};

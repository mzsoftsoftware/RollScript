#pragma once

#include <QObject>

struct libusb_context;
struct libusb_device_handle;

#include "Common/Core/USB/USBDeviceInfo.h"


class USBManager : public QObject
{
    Q_OBJECT
public:
    explicit USBManager(QObject *parent);
    virtual ~USBManager() override;

    bool init();

    bool scanForDevices();

    bool open(const USBDeviceInfo* ptrDeviceInfo);
    bool close();
    bool send(const QByteArray& baData, int timeoutMs = 1000);
    bool receive(QByteArray&baData, int maxLength = 512, int timeoutMs = 1000);

    // Getter
    QString lastError() const                       { return m_qstrLastError; }
    const QList<USBDeviceInfo*>& devices() const    { return m_qlstUSBDeviceInfo; }

private:
    void clearUSBDeviceInfo();

private:
    QString m_qstrLastError;

    libusb_context* m_ptrLibUsbContext = nullptr;

    QList<USBDeviceInfo*> m_qlstUSBDeviceInfo;

    libusb_device_handle*   m_ptrLibUsbDeviceHandle = nullptr;
    uint8_t                 m_uiInterfaceNumber = 0;
    uint8_t                 m_uiEndpointIn = 0;
    uint8_t                 m_uiEndpointInAttr = 0;
    uint8_t                 m_uiEndpointOut = 0;
    uint8_t                 m_uiEndpointOutAttr = 0;
    bool                    m_bKernelDriverDetached = false;
    bool                    m_bOpen = false;

};

#pragma once

#include "Common/Core/Printers/PrinterInstance.h"

#include "Common/Core/USB/USBDeviceInfo.h"

class USBManager;


class PrinterInstanceUSB : public PrinterInstance
{
    Q_OBJECT

public:
    explicit PrinterInstanceUSB(IPrinterPlugin* ptrPrinterPlugin,
                                USBManager* ptrUSBManager,
                                const USBDeviceInfo* ptrDeviceInfo,
                                QObject* parent);
    virtual ~PrinterInstanceUSB() override;

    // Getter
    const USBDeviceInfo* deviceInfo() const         { return m_ptrDeviceInfo; }

    // Connection
    bool open() override;
    bool close() override;
    bool isConnected() override                     { return m_bConnected; }

    bool send(const QByteArray& baData);
    bool receive(QByteArray&baData, int maxLength = 512, int timeoutMs = 1000);

private:
    USBManager* m_ptrUSBManager = nullptr;
    const USBDeviceInfo* m_ptrDeviceInfo = nullptr;

    bool m_bConnected = false;
};

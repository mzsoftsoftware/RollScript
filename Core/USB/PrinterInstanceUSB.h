#pragma once

#include "Core/Printers/PrinterInstance.h"

#include "Core/USB/USBDeviceInfo.h"

class USBManager;


class PrinterInstanceUSB : public PrinterInstance
{
    Q_OBJECT

public:
    // Constructor / Destructor
    explicit PrinterInstanceUSB(IPrinterPlugin* ptrPrinterPlugin,
                                USBManager* ptrUSBManager,
                                const USBDeviceInfo* ptrDeviceInfo,
                                QObject* parent);
    ~PrinterInstanceUSB() override;

    // Getter
    const USBDeviceInfo* deviceInfo() const         { return m_ptrDeviceInfo; }

    // Connection
    bool open() override;
    bool close() override;
    bool isConnected() override                     { return m_bConnected; }

    // Operations
    bool send(const QByteArray& baData);
    bool receive(QByteArray&baData, int maxLength = 512, int timeoutMs = 1000);

private:
    USBManager* m_ptrUSBManager = nullptr;
    const USBDeviceInfo* m_ptrDeviceInfo = nullptr;

    bool m_bConnected = false;
};

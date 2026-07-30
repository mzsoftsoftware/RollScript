#pragma once

#include <QObject>
#include <QIcon>

#include "Common/Core/Printers/USBDeviceInfo.h"

class IPrinterPlugin;


class PrinterInstance : public QObject
{
    Q_OBJECT

public:
    explicit PrinterInstance(IPrinterPlugin* ptrPrinterPlugin, const USBDeviceInfo& device, QObject* parent);

    // Getter
    QString id() const                              { return m_qstrId; }
    QString displayName() const                     { return m_qstrDisplayName; }
    QIcon icon() const                              { return m_icon; }

    const USBDeviceInfo& deviceInfo() const         { return m_deviceInfo; }
    IPrinterPlugin* plugin() const                  { return m_ptrPrinterPlugin; }

private:
    USBDeviceInfo m_deviceInfo;
    IPrinterPlugin* m_ptrPrinterPlugin = nullptr;

    QString                     m_qstrId;
    QString                     m_qstrDisplayName;
    QIcon                       m_icon;

};


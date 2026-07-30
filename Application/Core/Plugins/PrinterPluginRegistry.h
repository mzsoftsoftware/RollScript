#pragma once

#include <QList>

class IPrinterPlugin;
class USBDeviceInfo;

class PrinterPluginRegistry
{
public:
    PrinterPluginRegistry();

    bool registerPlugin(IPrinterPlugin* ptrPrinterPlugin);
    IPrinterPlugin* supportsUsb(const USBDeviceInfo& device);

    QString lastError() const       { return m_qstrLastError; }

private:
    QString m_qstrLastError;

    QList<IPrinterPlugin*> m_registryPlugins;
};

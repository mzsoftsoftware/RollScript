#pragma once

#include <QList>

class IPrinterPlugin;
class UsbDeviceInfo;

class PrinterPluginRegistry
{
public:
    PrinterPluginRegistry();

    bool registerPlugin(IPrinterPlugin* ptrPrinterPlugin);
    IPrinterPlugin* supportsUsb(const UsbDeviceInfo& device);

    QString lastError() const       { return m_qstrLastError; }

private:
    QString m_qstrLastError;

    QList<IPrinterPlugin*> m_registryPlugins;
};

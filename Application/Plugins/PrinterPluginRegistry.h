#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"

#include <QList>

class IPrinterPlugin;
class USBDeviceInfo;

class PrinterPluginRegistry : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT

public:
    PrinterPluginRegistry(QObject* parent);

    bool registerPlugin(IPrinterPlugin* ptrPrinterPlugin);
    IPrinterPlugin* supportsUsb(const USBDeviceInfo* ptrDevice);

private:
    QList<IPrinterPlugin*> m_registryPlugins;
};

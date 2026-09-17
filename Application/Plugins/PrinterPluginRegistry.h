#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"

#include <QHash>

class IPrinterPlugin;
class USBDeviceInfo;


class PrinterPluginRegistry : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT

public:
    explicit PrinterPluginRegistry(QObject* parent);
    ~PrinterPluginRegistry() override;

    // Getter
    QStringList availablePrinterPluginIds() const                       { return m_qstrPrinterPluginIds; }
    IPrinterPlugin* printerPlugin(const QString& qstrPluginId) const    { return m_qhashPrinterPlugins.value(qstrPluginId, nullptr); }

    // Operations
    bool registerPlugin(IPrinterPlugin* ptrPrinterPlugin);
    IPrinterPlugin* supportsUsb(const USBDeviceInfo* ptrDevice);

private:
    QStringList m_qstrPrinterPluginIds;
    QHash<QString, IPrinterPlugin*> m_qhashPrinterPlugins;
};

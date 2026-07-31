#pragma once

#include <QObject>

#include "Common/Core/Plugins/IPrinterPlugin.h"


class DymoLabelPoint350PrinterPlugin :
        public QObject,
        public IPrinterPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "de.mzsoft.rollscript.printer" FILE "DymoLabelPoint350.json")
    Q_INTERFACES(IPrinterPlugin)

public:

    explicit DymoLabelPoint350PrinterPlugin(QObject* parent = nullptr);

    QString pluginId() const override;
    QString displayName() const override;
    QString version() const override;

    QIcon icon() const override;

    bool supportsUsb(const USBDeviceInfo* ptrDevice) const override;
};

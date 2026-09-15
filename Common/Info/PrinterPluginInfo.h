#pragma once

#include "Common/Info/PluginInfo.h"
#include "Core/Plugins/IPrinterPluginInfo.h"


class PrinterPluginInfo : public PluginInfo, public virtual IPrinterPluginInfo
{
public:
    explicit PrinterPluginInfo(const char* pszContext,
                               const QString& qstrPluginId,
                               const QString& qstrPluginVersion,
                               const char* pszPluginDisplayNameKey,
                               const QIcon& iconPlugin);
    ~PrinterPluginInfo() override;

    // Getter

private:
};

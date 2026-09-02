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
                               const char* pszPrinterDisplayNameKey,
                               const QIcon& iconPrinter);
    ~PrinterPluginInfo() override;

    // Getter
    QString printerDisplayName() const  { return translate(m_pszPrinterDisplayNameKey); }
    const QIcon& printerIcon() const    { return m_iconPrinter; }

private:
    const char* m_pszPrinterDisplayNameKey;
    QIcon m_iconPrinter;
};

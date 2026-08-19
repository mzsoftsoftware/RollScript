#pragma once

#include "Common/Info/PluginInfo.h"
#include "Core/Plugins/IPrinterPluginInfo.h"


class PrinterPluginInfo : public PluginInfo, public virtual IPrinterPluginInfo
{
public:
    PrinterPluginInfo(const char* pszContext,
                      const QString& qstrPluginId,
                      const QString& qstrPluginVersion,
                      const char* pszPluginDisplayNameKey,
                      const char* pszrPrinterDisplayNameKey,
                      const QIcon& iconPrinter);
    ~PrinterPluginInfo() override = default;

    QString printerDisplayName() const  { return translate(m_pszPrinterDisplayNameKey); }
    const QIcon& printerIcon() const    { return m_iconPrinter; }

private:
    const char* m_pszPrinterDisplayNameKey;
    QIcon m_iconPrinter;
};

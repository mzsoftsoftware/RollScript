#pragma once

#include "Common/Info/PrinterPluginInfo.h"

class DymoLabelPoint350PrinterPluginInfo : public PrinterPluginInfo
{
public:
    explicit DymoLabelPoint350PrinterPluginInfo()
        : PrinterPluginInfo(
              "DymoLabelPoint350PrinterPluginInfo",                                                     // Translation Context
              QStringLiteral("printer.dymo.labelpoint350"),                                             // Plugin ID
              QStringLiteral("1.0.0"),                                                                  // Plugin Version
              QT_TRANSLATE_NOOP("DymoLabelPoint350PrinterPluginInfo", "plugin.dymo.labelpoint350"),     // Plugin Display Name Key
              QT_TRANSLATE_NOOP("DymoLabelPoint350PrinterPluginInfo", "priner.dymo.labelpoint350"),     // Printer Display Name Key
              QIcon(QStringLiteral(":/DymoLabelPoint350PrinterPlugin/icons/printer.png")))
    {}
};

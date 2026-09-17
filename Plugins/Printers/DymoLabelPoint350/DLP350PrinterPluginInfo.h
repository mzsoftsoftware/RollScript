#pragma once

#include "Common/Info/PrinterPluginInfo.h"


class DymoLabelPoint350PrinterPluginInfo : public PrinterPluginInfo
{
public:
    // Constructor / Destructor
    explicit DymoLabelPoint350PrinterPluginInfo()
        : PrinterPluginInfo(
              "DymoLabelPoint350PrinterPluginInfo",                                                     // Translation Context
              QStringLiteral("printer.dymo.labelpoint350"),                                             // Plugin ID
              QStringLiteral(ROLLSCRIPT_PLUGIN_VERSION),                                                // Plugin Version
              QT_TRANSLATE_NOOP("DymoLabelPoint350PrinterPluginInfo", "printer.dymo.labelpoint350.name"),     // Name Key
              QT_TRANSLATE_NOOP("DymoLabelPoint350PrinterPluginInfo", "printer.dymo.labelpoint350.description"),     // Description Key
              QIcon(QStringLiteral(":/DymoLabelPoint350PrinterPlugin/icons/printer.png")))
    {}
};

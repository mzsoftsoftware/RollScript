#pragma once

#include "Common/Info/FeatureBlockInfo.h"

#include <QIcon>


class RollScriptBlockBarcodeFeaturePluginInfo : public FeatureBlockInfo
{
public:
    // Constructor / Destructor
    explicit RollScriptBlockBarcodeFeaturePluginInfo()
        : FeatureBlockInfo("RollScriptBlockBarcodeFeaturePluginInfo",                                                              // Translation Context
                           QStringLiteral("de.mzsoft.rollscript.feature.block.barcode"),                                           // Plugin ID
                           QStringLiteral(ROLLSCRIPT_PLUGIN_VERSION),                                                           // Plugin Version
                           QT_TRANSLATE_NOOP("RollScriptBlockBarcodeFeaturePluginInfo", "plugin.feature.block.barcode.name"),         // Plugin Name Key
                           QT_TRANSLATE_NOOP("RollScriptBlockBarcodeFeaturePluginInfo", "plugin.feature.block.barcode.description"),  // Plugin Name Key
                           QIcon(QStringLiteral(":/RollScriptBlockBarcodeFeaturePlugin/icons/FeatureBlockBarcode.icon.svg")),         // Plugin Icon
                           QT_TRANSLATE_NOOP("RollScriptBlockBarcodeFeaturePluginInfo", "feature.block.barcode.name"),                // FeatureBlock Name Key
                           QT_TRANSLATE_NOOP("RollScriptBlockBarcodeFeaturePluginInfo", "feature.block.barcode.tooltip"))             // FeatureBlock Tooltip Key
    {}
};

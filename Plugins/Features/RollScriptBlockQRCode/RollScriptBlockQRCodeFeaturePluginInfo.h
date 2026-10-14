#pragma once

#include "Common/Info/FeatureBlockInfo.h"

#include <QIcon>


class RollScriptBlockQRCodeFeaturePluginInfo : public FeatureBlockInfo
{
public:
    // Constructor / Destructor
    explicit RollScriptBlockQRCodeFeaturePluginInfo()
        : FeatureBlockInfo("RollScriptBlockQRCodeFeaturePluginInfo",                                                              // Translation Context
                           QStringLiteral("de.mzsoft.rollscript.feature.block.qrcode"),                                           // Plugin ID
                           QStringLiteral(ROLLSCRIPT_PLUGIN_VERSION),                                                           // Plugin Version
                           QT_TRANSLATE_NOOP("RollScriptBlockQRCodeFeaturePluginInfo", "plugin.feature.block.qrcode.name"),         // Plugin Name Key
                           QT_TRANSLATE_NOOP("RollScriptBlockQRCodeFeaturePluginInfo", "plugin.feature.block.qrcode.description"),  // Plugin Name Key
                           QIcon(QStringLiteral(":/RollScriptBlockQRCodeFeaturePlugin/icons/FeatureBlockQRCode.icon.svg")),         // Plugin Icon
                           QT_TRANSLATE_NOOP("RollScriptBlockQRCodeFeaturePluginInfo", "feature.block.qrcode.name"),                // FeatureBlock Name Key
                           QT_TRANSLATE_NOOP("RollScriptBlockQRCodeFeaturePluginInfo", "feature.block.qrcode.tooltip"))             // FeatureBlock Tooltip Key
    {}
};

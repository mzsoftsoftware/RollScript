#pragma once

#include "Common/Info/FeatureBlockInfo.h"

#include <QIcon>


class RollScriptBlockTextFeaturePluginInfo : public FeatureBlockInfo
{
public:
    // Constructor / Destructor
    explicit RollScriptBlockTextFeaturePluginInfo()
        : FeatureBlockInfo("RollScriptBlockTextFeaturePluginInfo",                                                              // Translation Context
                           QStringLiteral("de.mzsoft.rollscript.feature.block.text"),                                           // Plugin ID
                           QStringLiteral(ROLLSCRIPT_PLUGIN_VERSION),                                                           // Plugin Version
                           QT_TRANSLATE_NOOP("RollScriptBlockTextFeaturePluginInfo", "plugin.feature.block.text.name"),         // Plugin Name Key
                           QT_TRANSLATE_NOOP("RollScriptBlockTextFeaturePluginInfo", "plugin.feature.block.text.description"),  // Plugin Name Key
                           QIcon(QStringLiteral(":/RollScriptBlockTextFeaturePlugin/icons/FeatureBlockText.icon.svg")),         // Plugin Icon
                           QT_TRANSLATE_NOOP("RollScriptBlockTextFeaturePluginInfo", "feature.block.text.name"),                // FeatureBlock Name Key
                           QT_TRANSLATE_NOOP("RollScriptBlockTextFeaturePluginInfo", "feature.block.text.tooltip"))             // FeatureBlock Tooltip Key
    {}
};

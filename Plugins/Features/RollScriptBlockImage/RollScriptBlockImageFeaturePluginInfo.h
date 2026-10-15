#pragma once

#include "Common/Info/FeatureBlockInfo.h"

#include <QIcon>


class RollScriptBlockImageFeaturePluginInfo : public FeatureBlockInfo
{
public:
    // Constructor / Destructor
    explicit RollScriptBlockImageFeaturePluginInfo()
        : FeatureBlockInfo("RollScriptBlockImageFeaturePluginInfo",                                                              // Translation Context
                           QStringLiteral("de.mzsoft.rollscript.feature.block.image"),                                           // Plugin ID
                           QStringLiteral(ROLLSCRIPT_PLUGIN_VERSION),                                                           // Plugin Version
                           QT_TRANSLATE_NOOP("RollScriptBlockImageFeaturePluginInfo", "plugin.feature.block.image.name"),         // Plugin Name Key
                           QT_TRANSLATE_NOOP("RollScriptBlockImageFeaturePluginInfo", "plugin.feature.block.image.description"),  // Plugin Name Key
                           QIcon(QStringLiteral(":/RollScriptBlockImageFeaturePlugin/icons/FeatureBlockImage.icon.svg")),         // Plugin Icon
                           QT_TRANSLATE_NOOP("RollScriptBlockImageFeaturePluginInfo", "feature.block.image.name"),                // FeatureBlock Name Key
                           QT_TRANSLATE_NOOP("RollScriptBlockImageFeaturePluginInfo", "feature.block.image.tooltip"))             // FeatureBlock Tooltip Key
    {}
};

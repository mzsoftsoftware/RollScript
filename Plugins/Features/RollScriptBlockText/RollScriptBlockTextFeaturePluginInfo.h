#pragma once

#include "Common/Info/FeatureBlockInfo.h"

#include <QIcon>


class RollScriptBlockTextFeaturePluginInfo : public FeatureBlockInfo
{
public:
    // Constructor / Destructor
    explicit RollScriptBlockTextFeaturePluginInfo()
        : FeatureBlockInfo("RollScriptBlockTextFeaturePluginInfo",                                                   // Translation Context
                           QStringLiteral("de.mzsoft.rollscript.feature.block.text"),                                // Plugin ID
                           QStringLiteral("1.0.0"),                                                                  // Plugin Version
                           QT_TRANSLATE_NOOP("RollScriptBlockTextFeaturePluginInfo", "plugin.feature.block.text"),     // Plugin Display Name Key
                           QStringLiteral("feature.block.text"),
                           QIcon(QStringLiteral(":/RollScriptBlockTextFeaturePlugin/icons/FeatureBlockText.icon.svg")),
                           "feature.block.text.name",
                           "feature.block.text.tooltip")
    {}
};

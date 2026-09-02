#pragma once

#include "Core/Plugins/IFeaturePlugin.h"
#include "Core/Blocks/IFeatureBlock.h"
#include "RollScriptBlockTextFeaturePluginInfo.h"

#include <QIcon>


class RollScriptBlockTextFeaturePlugin : public IFeaturePlugin, public IFeatureBlock
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "de.mzsoft.rollscript.feature.block.text")
    Q_INTERFACES(   IFeaturePlugin
                    IFeatureBlock)

public:
    // Constructor / Destructor
    explicit RollScriptBlockTextFeaturePlugin(QObject* parent = nullptr);

    // Infos
    const IPluginInfo* pluginInfo() const override                  { return &m_pluginInfo; }
    const IFeaturePluginInfo* featurePluginInfo() const override    { return &m_pluginInfo; }
    const IFeatureBlockInfo* featureBlockInfo() const override      { return &m_pluginInfo; }

    // IFeatureBlock
    virtual RollScriptBlockWidgetBase* createFeatureBlockWidget(QWidget* parent) override;
    virtual RollScriptBlockDocumentBase* createFeatureBlockDocument(QObject* parent) override;
    virtual RollScriptBlockRendererBase* createFeatureBlockRenderer(QObject* parent) override;

private:
    RollScriptBlockTextFeaturePluginInfo m_pluginInfo;
};


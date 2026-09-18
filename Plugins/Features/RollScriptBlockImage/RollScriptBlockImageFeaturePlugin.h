#pragma once

#include "Core/Plugins/IFeaturePlugin.h"
#include "Core/Blocks/IFeatureBlock.h"
#include "RollScriptBlockImageFeaturePluginInfo.h"

#include <QIcon>


class RollScriptBlockImageFeaturePlugin : public IFeaturePlugin, public IFeatureBlock
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "de.mzsoft.rollscript.feature.block.image")
    Q_INTERFACES(   IFeaturePlugin
                    IFeatureBlock)

public:
    // Constructor / Destructor
    explicit RollScriptBlockImageFeaturePlugin(QObject* parent = nullptr);

    // Infos
    const IPluginInfo* pluginInfo() const override                  { return &m_pluginInfo; }
    const IFeaturePluginInfo* featurePluginInfo() const override    { return &m_pluginInfo; }
    const IFeatureBlockInfo* featureBlockInfo() const override      { return &m_pluginInfo; }

    // IFeatureBlock
    virtual RollScriptBlockWidgetBase* createFeatureBlockWidget(QWidget* parent) override;
    virtual RollScriptBlockDocumentBase* createFeatureBlockDocument(QObject* parent) override;
    virtual RollScriptBlockRendererBase* createFeatureBlockRenderer(QObject* parent) override;

private:
    RollScriptBlockImageFeaturePluginInfo m_pluginInfo;
};


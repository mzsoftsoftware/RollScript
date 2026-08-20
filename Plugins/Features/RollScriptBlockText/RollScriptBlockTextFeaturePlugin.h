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
    explicit RollScriptBlockTextFeaturePlugin(QObject* parent = nullptr);

    // Infos
    const IPluginInfo* pluginInfo() const override                  { return &m_pluginInfo; }
    const IFeaturePluginInfo* featurePluginInfo() const override    { return &m_pluginInfo; }
    const IFeatureBlockInfo* featureBlockInfo() const override      { return &m_pluginInfo; }

    // IFeatureBlock
    virtual RollScriptBlockWidgetBase* createFeatureBlockWidget(QWidget *parent) override;
    virtual RollScriptBlockDocumentBase* createFeatureBlockDocument(QObject* parent) override;

private:
    RollScriptBlockTextFeaturePluginInfo m_pluginInfo;
/*
    const QString m_qstrPluginId = QStringLiteral("de.mzsoft.rollscript.feature.block.text");
    const QString m_qstrDisplayName = QStringLiteral("Text");
    const QString m_qstrVersion = QStringLiteral("1.0.0");
    const QIcon m_icon;

    const QString m_qstrFeatureBlockId = QStringLiteral("text");
    const QString m_qstrFeatureBlockDisplayName = QStringLiteral("Text");
    const QIcon m_featureBlockIcon;
    const QString m_qstrFeatureBlockTooltip = QStringLiteral("text.tooltip");
*/
};


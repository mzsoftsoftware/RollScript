#pragma once

#include "Core/Plugins/IFeaturePlugin.h"
#include "Core/Blocks/IFeatureBlock.h"

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
    const IPluginInfo* pluginInfo() const override;
    const IFeaturePluginInfo* featurePluginInfo() const override;
    const IFeatureBlockInfo* featureBlockInfo() const override;

    // IPlugin

    //const QString& pluginId() const override               { return "de.mzsoft.rollscript.feature.block.text"; }
    //const QString& displayName() const override            { return "Text"; }
    //const QString& version() const override                { return "1.0.0"; }

    // IFeaturePlugin
    //const QIcon& icon() const override                     { return QIcon(); }

    // IFeatureBlock
    //virtual const QString& featureBlockId() const override          { return "text"; }
    //virtual const QString& featureBlockDisplayName() const override { return "Text"; }
    //virtual const QIcon& featureBlockIcon() const override          { return QIcon(); }
    //virtual const QString& featureBlockTooltip() const override     { return "text.tooltip"; }

    virtual RollScriptBlockWidgetBase* createFeatureBlockWidget(QWidget *parent) override;
    virtual RollScriptBlockDocumentBase* createFeatureBlockDocument(QObject* parent) override;

private:
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


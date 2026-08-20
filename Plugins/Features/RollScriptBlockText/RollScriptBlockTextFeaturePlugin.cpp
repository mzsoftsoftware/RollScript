#include "RollScriptBlockTextFeaturePlugin.h"

#include "RollScriptBlockTextWidget.h"
#include "RollScriptBlockTextDocument.h"


RollScriptBlockTextFeaturePlugin::RollScriptBlockTextFeaturePlugin(QObject* parent)
    : IFeaturePlugin(parent)
{
}

RollScriptBlockWidgetBase* RollScriptBlockTextFeaturePlugin::createFeatureBlockWidget(QWidget *parent)
{
    return new RollScriptBlockTextWidget(m_pluginInfo.featureBlockId(), m_pluginInfo.featureBlockDisplayName(), parent);
}

RollScriptBlockDocumentBase* RollScriptBlockTextFeaturePlugin::createFeatureBlockDocument(QObject* parent)
{
    return new RollScriptBlockTextDocument(m_pluginInfo.featureBlockId(), parent);
}

#include "RollScriptBlockImageFeaturePlugin.h"

#include "RollScriptBlockImageWidget.h"
#include "RollScriptBlockImageDocument.h"
#include "RollScriptBlockImageRenderer.h"

#include <QFile>
#include <QDir>


RollScriptBlockImageFeaturePlugin::RollScriptBlockImageFeaturePlugin(QObject* parent)
    : IFeaturePlugin(parent)
{
}

RollScriptBlockWidgetBase* RollScriptBlockImageFeaturePlugin::createFeatureBlockWidget(QWidget* parent)
{
    return new RollScriptBlockImageWidget(m_pluginInfo.pluginId(), m_pluginInfo.featureBlockName(), parent);
}

RollScriptBlockDocumentBase* RollScriptBlockImageFeaturePlugin::createFeatureBlockDocument(QObject* parent)
{
    return new RollScriptBlockImageDocument(m_pluginInfo.pluginId(), parent);
}

RollScriptBlockRendererBase* RollScriptBlockImageFeaturePlugin::createFeatureBlockRenderer(QObject* parent)
{
    return new RollScriptBlockImageRenderer(m_pluginInfo.pluginId(), parent);
}

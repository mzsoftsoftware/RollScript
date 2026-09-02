#include "RollScriptBlockTextFeaturePlugin.h"

#include "RollScriptBlockTextWidget.h"
#include "RollScriptBlockTextDocument.h"
#include "RollScriptBlockTextRenderer.h"

#include <QFile>
#include <QDir>

RollScriptBlockTextFeaturePlugin::RollScriptBlockTextFeaturePlugin(QObject* parent)
    : IFeaturePlugin(parent)
{
    const QString qstrPath =
        QStringLiteral(
            ":/RollScriptBlockTextFeaturePlugin/icons/FeatureBlockText.icon");

    qDebug() << "Constructor Plugin icon:"
             << QFile::exists(qstrPath)
             << QIcon(qstrPath).isNull();

    qDebug() << "Constructor resources:" << QDir(QStringLiteral(":/")).entryList();
}

RollScriptBlockWidgetBase* RollScriptBlockTextFeaturePlugin::createFeatureBlockWidget(QWidget* parent)
{
    return new RollScriptBlockTextWidget(m_pluginInfo.featureBlockId(), m_pluginInfo.featureBlockDisplayName(), parent);
}

RollScriptBlockDocumentBase* RollScriptBlockTextFeaturePlugin::createFeatureBlockDocument(QObject* parent)
{
    return new RollScriptBlockTextDocument(m_pluginInfo.featureBlockId(), parent);
}

RollScriptBlockRendererBase* RollScriptBlockTextFeaturePlugin::createFeatureBlockRenderer(QObject* parent)
{
    return new RollScriptBlockTextRenderer(m_pluginInfo.featureBlockId(), parent);
}
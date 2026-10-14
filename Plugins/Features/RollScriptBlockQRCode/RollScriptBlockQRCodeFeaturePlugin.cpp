#include "RollScriptBlockQRCodeFeaturePlugin.h"

#include "RollScriptBlockQRCodeWidget.h"
#include "RollScriptBlockQRCodeDocument.h"
#include "RollScriptBlockQRCodeRenderer.h"

#include <QFile>
#include <QDir>

RollScriptBlockQRCodeFeaturePlugin::RollScriptBlockQRCodeFeaturePlugin(QObject* parent)
    : IFeaturePlugin(parent)
{
    const QString qstrPath =
        QStringLiteral(
            ":/RollScriptBlockQRCodeFeaturePlugin/icons/FeatureBlockQRCode.icon");

    qDebug() << "Constructor Plugin icon:"
             << QFile::exists(qstrPath)
             << QIcon(qstrPath).isNull();

    qDebug() << "Constructor resources:" << QDir(QStringLiteral(":/")).entryList();
}

RollScriptBlockWidgetBase* RollScriptBlockQRCodeFeaturePlugin::createFeatureBlockWidget(QWidget* parent)
{
    return new RollScriptBlockQRCodeWidget(m_pluginInfo.pluginId(), m_pluginInfo.featureBlockName(), parent);
}

RollScriptBlockDocumentBase* RollScriptBlockQRCodeFeaturePlugin::createFeatureBlockDocument(QObject* parent)
{
    return new RollScriptBlockQRCodeDocument(m_pluginInfo.pluginId(), parent);
}

RollScriptBlockRendererBase* RollScriptBlockQRCodeFeaturePlugin::createFeatureBlockRenderer(QObject* parent)
{
    return new RollScriptBlockQRCodeRenderer(m_pluginInfo.pluginId(), parent);
}

#include "RollScriptBlockBarcodeFeaturePlugin.h"

#include "RollScriptBlockBarcodeWidget.h"
#include "RollScriptBlockBarcodeDocument.h"
#include "RollScriptBlockBarcodeRenderer.h"

#include <QFile>
#include <QDir>

RollScriptBlockBarcodeFeaturePlugin::RollScriptBlockBarcodeFeaturePlugin(QObject* parent)
    : IFeaturePlugin(parent)
{
    const QString qstrPath =
        QStringLiteral(
            ":/RollScriptBlockBarcodeFeaturePlugin/icons/FeatureBlockBarcode.icon");

    qDebug() << "Constructor Plugin icon:"
             << QFile::exists(qstrPath)
             << QIcon(qstrPath).isNull();

    qDebug() << "Constructor resources:" << QDir(QStringLiteral(":/")).entryList();
}

RollScriptBlockWidgetBase* RollScriptBlockBarcodeFeaturePlugin::createFeatureBlockWidget(QWidget* parent)
{
    return new RollScriptBlockBarcodeWidget(m_pluginInfo.pluginId(), m_pluginInfo.featureBlockName(), parent);
}

RollScriptBlockDocumentBase* RollScriptBlockBarcodeFeaturePlugin::createFeatureBlockDocument(QObject* parent)
{
    return new RollScriptBlockBarcodeDocument(m_pluginInfo.pluginId(), parent);
}

RollScriptBlockRendererBase* RollScriptBlockBarcodeFeaturePlugin::createFeatureBlockRenderer(QObject* parent)
{
    return new RollScriptBlockBarcodeRenderer(m_pluginInfo.pluginId(), parent);
}

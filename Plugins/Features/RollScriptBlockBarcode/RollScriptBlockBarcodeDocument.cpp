#include "RollScriptBlockBarcodeDocument.h"

#include <QJsonObject>


RollScriptBlockBarcodeDocument::RollScriptBlockBarcodeDocument(const QString& qstrBlockPluginId, QObject* parent)
    : RollScriptBlockDocumentBase(qstrBlockPluginId, parent)
{
}
RollScriptBlockBarcodeDocument::~RollScriptBlockBarcodeDocument()
{
}

void RollScriptBlockBarcodeDocument::clear()
{
}
bool RollScriptBlockBarcodeDocument::loadFromJson(const QJsonObject& jsonBlocks)
{
    Q_UNUSED(jsonBlocks)

    return true;
}
bool RollScriptBlockBarcodeDocument::saveToJson(QJsonObject& jsonBlocks)
{
    Q_UNUSED(jsonBlocks)

    return true;
}

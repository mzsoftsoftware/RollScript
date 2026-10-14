#include "RollScriptBlockQRCodeDocument.h"

#include <QJsonObject>


RollScriptBlockQRCodeDocument::RollScriptBlockQRCodeDocument(const QString& qstrBlockPluginId, QObject* parent)
    : RollScriptBlockDocumentBase(qstrBlockPluginId, parent)
{
}
RollScriptBlockQRCodeDocument::~RollScriptBlockQRCodeDocument()
{
}

void RollScriptBlockQRCodeDocument::clear()
{
}
bool RollScriptBlockQRCodeDocument::loadFromJson(const QJsonObject& jsonBlocks)
{
    Q_UNUSED(jsonBlocks)

    return true;
}
bool RollScriptBlockQRCodeDocument::saveToJson(QJsonObject& jsonBlocks)
{
    Q_UNUSED(jsonBlocks)

    return true;
}

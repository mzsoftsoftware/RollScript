#include "RollScriptBlockBarcodeDocument.h"

#include <QJsonObject>


RollScriptBlockBarcodeDocument::RollScriptBlockBarcodeDocument(const QString& qstrBlockPluginId, QObject* parent)
    : RollScriptBlockDocumentBase(qstrBlockPluginId, parent)
{
}
RollScriptBlockBarcodeDocument::~RollScriptBlockBarcodeDocument()
{
}

void RollScriptBlockBarcodeDocument::setText(const QString& qstrLineText)
{
    m_qstrText = qstrLineText;
    emit blockChanged();
}

void RollScriptBlockBarcodeDocument::clear()
{
    m_qstrText.clear();

    emit documentCleared();
}
bool RollScriptBlockBarcodeDocument::loadFromJson(const QJsonObject& jsonBlockQrCode)
{
    const int iVersion = jsonBlockQrCode[QStringLiteral("version")].toInt();
    switch(iVersion)
    {
    case 1:
        return loadVersion_1(jsonBlockQrCode);
        break;
    default:
        ROLLSCRIPT_ERROR(tr("DocumentBlockBarcode.LoadFromFile.Json.Version.Error").arg(iVersion), QStringLiteral("version is unknown."));
        return false;
    }

    return false;
}
bool RollScriptBlockBarcodeDocument::loadVersion_1(const QJsonObject& jsonBlockQrCode)
{
    m_qstrText = jsonBlockQrCode[QStringLiteral("text")].toString();

    emit documentLoaded();
    return true;
}
bool RollScriptBlockBarcodeDocument::saveToJson(QJsonObject& jsonBlockBarcode)
{
    jsonBlockBarcode[QStringLiteral("version")] = 1;
    jsonBlockBarcode[QStringLiteral("text")] = m_qstrText;

    return true;
}

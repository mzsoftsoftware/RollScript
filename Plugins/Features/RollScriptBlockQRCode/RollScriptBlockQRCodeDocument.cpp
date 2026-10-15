#include "RollScriptBlockQRCodeDocument.h"

#include <QJsonObject>


RollScriptBlockQRCodeDocument::RollScriptBlockQRCodeDocument(const QString& qstrBlockPluginId, QObject* parent)
    : RollScriptBlockDocumentBase(qstrBlockPluginId, parent)
{
}
RollScriptBlockQRCodeDocument::~RollScriptBlockQRCodeDocument()
{
}

void RollScriptBlockQRCodeDocument::setText(const QString& qstrLineText)
{
    m_qstrText = qstrLineText;
    emit blockChanged();
}

void RollScriptBlockQRCodeDocument::clear()
{
    m_qstrText.clear();

    emit documentCleared();
}
bool RollScriptBlockQRCodeDocument::loadFromJson(const QJsonObject& jsonBlockQrCode)
{
    const int iVersion = jsonBlockQrCode[QStringLiteral("version")].toInt();
    switch(iVersion)
    {
    case 1:
        return loadVersion_1(jsonBlockQrCode);
        break;
    default:
        ROLLSCRIPT_ERROR(tr("DocumentBlockQRCode.LoadFromFile.Json.Version.Error").arg(iVersion), QStringLiteral("version is unknown."));
        return false;
    }

    return false;
}
bool RollScriptBlockQRCodeDocument::loadVersion_1(const QJsonObject& jsonBlockQrCode)
{
    m_qstrText = jsonBlockQrCode[QStringLiteral("text")].toString();

    emit documentLoaded();
    return true;
}
bool RollScriptBlockQRCodeDocument::saveToJson(QJsonObject& jsonBlockQrCode)
{
    jsonBlockQrCode[QStringLiteral("version")] = 1;
    jsonBlockQrCode[QStringLiteral("text")] = m_qstrText;

    return true;
}

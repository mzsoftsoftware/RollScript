#include "RollScriptBlockImageDocument.h"

#include <QJsonObject>
#include <QJsonArray>


RollScriptBlockImageDocument::RollScriptBlockImageDocument(const QString& qstrBlockPluginId, QObject* parent)
    : RollScriptBlockDocumentBase(qstrBlockPluginId, parent)
{
}
RollScriptBlockImageDocument::~RollScriptBlockImageDocument()
{
}

void RollScriptBlockImageDocument::setFileName(const QString& qstrFileName)
{
    m_qstrFileName = qstrFileName;
    emit blockChanged();
}

void RollScriptBlockImageDocument::clear()
{
    m_qstrFileName.clear();
    emit documentCleared();
}
bool RollScriptBlockImageDocument::loadFromJson(const QJsonObject& jsonBlockText)
{
    const int iVersion = jsonBlockText[QStringLiteral("version")].toInt();
    switch(iVersion)
    {
    case 1:
        return loadVersion_1(jsonBlockText);
        break;
    default:
        ROLLSCRIPT_ERROR(tr("DocumentBlockImage.LoadFromFile.Json.Version.Error").arg(iVersion), QStringLiteral("version is unknown."));
        return false;
    }
}
bool RollScriptBlockImageDocument::loadVersion_1(const QJsonObject& jsonBlockImage)
{
    m_qstrFileName = jsonBlockImage[QStringLiteral("fileName")].toString();

    emit documentLoaded();
    return true;
}
bool RollScriptBlockImageDocument::saveToJson(QJsonObject& jsonBlockImage)
{
    jsonBlockImage[QStringLiteral("version")] = 1;
    jsonBlockImage[QStringLiteral("fileName")] = m_qstrFileName;

    return true;
}

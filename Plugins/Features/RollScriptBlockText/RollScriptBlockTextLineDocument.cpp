#include "RollScriptBlockTextLineDocument.h"

#include <QJsonObject>


RollScriptBlockTextLineDocument::RollScriptBlockTextLineDocument(QObject* parent)
    : QObject(parent)
{
}

void RollScriptBlockTextLineDocument::setLineActive(const bool bActive)
{
    m_bActive = bActive;
    emit blockTextLineChanged();
}
void RollScriptBlockTextLineDocument::setLineText(const QString& qstrLineText)
{
    m_qstrText = qstrLineText;
    emit blockTextLineChanged();
}
void RollScriptBlockTextLineDocument::setLineFont(const QFont& font)
{
    m_font = font;
    emit blockTextLineChanged();
}
void RollScriptBlockTextLineDocument::setLineAlignment(const Qt::Alignment& alignment)
{
    m_alignment = alignment;
    emit blockTextLineChanged();
}

void RollScriptBlockTextLineDocument::clear()
{
    m_bActive = false;
    m_qstrText.clear();
    m_font = QFont();
    m_alignment = Qt::AlignHCenter;

    emit documentCleared();
}
bool RollScriptBlockTextLineDocument::loadFromJson(const QJsonObject& jsonBlockTextLine)
{
    const int iVersion = jsonBlockTextLine[QStringLiteral("version")].toInt();
    switch(iVersion)
    {
    case 1:
        return loadVersion_1(jsonBlockTextLine);
        break;
    default:
        ROLLSCRIPT_ERROR(tr("DocumentBlockTextLine.LoadFromFile.Json.Version.Error").arg(iVersion), QStringLiteral("version is unknown."));
        return false;
    }

    return false;
}
bool RollScriptBlockTextLineDocument::loadVersion_1(const QJsonObject& jsonBlockTextLine)
{
    m_bActive = jsonBlockTextLine[QStringLiteral("active")].toBool();
    m_qstrText = jsonBlockTextLine[QStringLiteral("text")].toString();
    m_font.fromString(jsonBlockTextLine[QStringLiteral("font")].toString());
    m_alignment.fromInt(jsonBlockTextLine[QStringLiteral("slignment")].toInteger());

    emit documentLoaded();
    return true;
}

bool RollScriptBlockTextLineDocument::saveToJson(QJsonObject& jsonBlockTextLine)
{
    jsonBlockTextLine[QStringLiteral("version")] = 1;
    jsonBlockTextLine[QStringLiteral("active")] = m_bActive;
    jsonBlockTextLine[QStringLiteral("text")] = m_qstrText;
    jsonBlockTextLine[QStringLiteral("font")] = m_font.toString();
    jsonBlockTextLine[QStringLiteral("alignment")] = static_cast<int>(m_alignment.toInt());

    return true;
}

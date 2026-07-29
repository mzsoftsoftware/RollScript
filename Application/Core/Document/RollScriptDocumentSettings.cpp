#include "RollScriptDocumentSettings.h"

#include <QJsonObject>


RollScriptDocumentSettings::RollScriptDocumentSettings(QObject *parent)
    : QObject{parent}
{
}

void RollScriptDocumentSettings::setMarginsMm(const QMarginsF& marginsMm)
{
    m_marginsMm = marginsMm;
    emit settingsChanged();
}
void RollScriptDocumentSettings::setMinimumLengthMm(const double dblLengthMm)
{
    m_dblMinimumLengthMm = dblLengthMm;
    emit settingsChanged();
}


void RollScriptDocumentSettings::clear()
{
    m_marginsMm = QMarginsF();
    m_dblMinimumLengthMm = 0.0;
}
bool RollScriptDocumentSettings::loadFromJson(const QJsonObject& jsonSettings)
{
    const int iVersion = jsonSettings["version"].toInt();
    switch(iVersion)
    {
    case 1:
        return loadVersion_1(jsonSettings);
        break;
    default:
        m_qstrLastError = tr("DocumentSettings.LoadFromFile.Json.Version.Error").arg(iVersion);
        return false;
    }
}
bool RollScriptDocumentSettings::loadVersion_1(const QJsonObject& jsonSettings)
{
    const QJsonObject jsonMargins = jsonSettings["margins"].toObject();
    m_marginsMm.setLeft(jsonMargins["left"].toDouble());
    m_marginsMm.setRight(jsonMargins["right"].toDouble());
    m_marginsMm.setTop(jsonMargins["top"].toDouble());
    m_marginsMm.setBottom(jsonMargins["bottom"].toDouble());

    m_dblMinimumLengthMm = jsonSettings["minimumLength"].toDouble();

    return true;
}

bool RollScriptDocumentSettings::saveToJson(QJsonObject& jsonSettings) const
{
    jsonSettings["version"] = 1;

    QJsonObject jsonMargins;
    jsonMargins["left"] = m_marginsMm.left();
    jsonMargins["right"] = m_marginsMm.right();
    jsonMargins["top"] = m_marginsMm.top();
    jsonMargins["bottom"] = m_marginsMm.bottom();
    jsonSettings["margins"] = jsonMargins;

    jsonSettings["minimumLength"] = m_dblMinimumLengthMm;

    return true;
}


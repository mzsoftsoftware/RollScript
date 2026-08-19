#include "RollScriptDocumentSettings.h"

#include <QJsonObject>


RollScriptDocumentSettings::RollScriptDocumentSettings(QObject* parent)
    : QObject{parent}
{
}


void RollScriptDocumentSettings::setPrinterMediaId(const QString& qstrPrinterMediaId)
{
    m_qstrPrinterMediaId = qstrPrinterMediaId;
    emit settingsChanged();
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
    m_qstrPrinterMediaId.clear();
    m_marginsMm = QMarginsF();
    m_dblMinimumLengthMm = 0.0;
}
bool RollScriptDocumentSettings::loadFromJson(const QJsonObject& jsonSettings)
{
    const int iVersion = jsonSettings[QStringLiteral("version")].toInt();
    switch(iVersion)
    {
    case 1:
        return loadVersion_1(jsonSettings);
        break;
    default:
        ROLLSCRIPT_ERROR(tr("DocumentSettings.LoadFromFile.Json.Version.Error").arg(iVersion), QStringLiteral("version is unknown."));
        return false;
    }
}
bool RollScriptDocumentSettings::loadVersion_1(const QJsonObject& jsonSettings)
{
    m_qstrPrinterMediaId = jsonSettings[QStringLiteral("printerMediaId")].toString();

    const QJsonObject jsonMargins = jsonSettings[QStringLiteral("margins")].toObject();
    m_marginsMm.setLeft(jsonMargins[QStringLiteral("left")].toDouble());
    m_marginsMm.setRight(jsonMargins[QStringLiteral("right")].toDouble());
    m_marginsMm.setTop(jsonMargins[QStringLiteral("top")].toDouble());
    m_marginsMm.setBottom(jsonMargins[QStringLiteral("bottom")].toDouble());

    m_dblMinimumLengthMm = jsonSettings[QStringLiteral("minimumLength")].toDouble();

    return true;
}

bool RollScriptDocumentSettings::saveToJson(QJsonObject& jsonSettings) const
{
    jsonSettings[QStringLiteral("version")] = 1;

    jsonSettings[QStringLiteral("printerMediaId")] = m_qstrPrinterMediaId;

    QJsonObject jsonMargins;
    jsonMargins[QStringLiteral("left")] = m_marginsMm.left();
    jsonMargins[QStringLiteral("right")] = m_marginsMm.right();
    jsonMargins[QStringLiteral("top")] = m_marginsMm.top();
    jsonMargins[QStringLiteral("bottom")] = m_marginsMm.bottom();
    jsonSettings[QStringLiteral("margins")] = jsonMargins;

    jsonSettings[QStringLiteral("minimumLength")] = m_dblMinimumLengthMm;

    return true;
}

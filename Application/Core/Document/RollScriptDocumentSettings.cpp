#include "RollScriptDocumentSettings.h"


RollScriptDocumentSettings::RollScriptDocumentSettings(QObject *parent)
    : QObject{parent}
{
}

bool RollScriptDocumentSettings::loadFromJson(const QJsonObject& jsonSettings)
{
    // TASK : Load document settings
    return true;
}

bool RollScriptDocumentSettings::saveToJson(QJsonObject& jsonSettings) const
{
    // TASK : Save document settings
    return true;
}
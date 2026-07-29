#include "RollScriptDocument.h"

#include <QFile>
#include <QJsonObject>


RollScriptDocument::RollScriptDocument(QObject *parent)
    : QObject{parent}

{
    m_ptrSettings = new RollScriptDocumentSettings(this);
    connect(m_ptrSettings, &RollScriptDocumentSettings::settingsChanged, this, &RollScriptDocument::slotSettingsChanged);
}

void RollScriptDocument::clear()
{
    m_qstrFileName.clear();
    m_ptrSettings->clear();

    setModified(false);
    emit documentFileNameChanged(m_qstrFileName);
    emit documentCleared();
}
bool RollScriptDocument::load(const QString& qstrFileName)
{
    if(!loadFromFile(qstrFileName))
    {
        return false;
    }

    m_qstrFileName = qstrFileName;

    setModified(false);
    emit documentFileNameChanged(m_qstrFileName);
    emit documentLoaded();
    return true;
}
bool RollScriptDocument::save()
{
    if(m_qstrFileName.isEmpty())
    {
        m_qstrLastError = tr("Document.Save.NoFileName");
        return false;
    }

    if(!saveToFile(m_qstrFileName))
    {
        return false;
    }

    setModified(false);
    emit documentSaved();
    return true;
}
bool RollScriptDocument::saveAs(const QString& qstrFileName)
{
    if(!saveToFile(qstrFileName))
    {
        return false;
    }

    m_qstrFileName = qstrFileName;

    setModified(false);
    emit documentFileNameChanged(m_qstrFileName);
    emit documentSaved();
    return true;
}

void RollScriptDocument::setModified(bool bModified)
{
    if (m_bModified == bModified)
    {
        return;
    }

    m_bModified = bModified;
    emit documentModifiedChanged(m_bModified);
}

bool RollScriptDocument::loadFromFile(const QString& qstrFileName)
{
    QFile fileLoad(qstrFileName);
    if(!fileLoad.open(QIODevice::ReadOnly))
    {
        m_qstrLastError = tr("Document.LoadFromFile.Open.Error").arg(qstrFileName);
        return false;
    }

    const QByteArray baData = fileLoad.readAll();
    fileLoad.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(baData);
    if(!jsonDoc.isObject())
    {
        m_qstrLastError = tr("Document.LoadFromFile.Json.Error");
        return false;
    }

    const QJsonObject jsonRoot = jsonDoc.object();

    if(!jsonRoot.contains("format") || !jsonRoot["format"].isString() || jsonRoot["format"].toString() != "RollScript")
    {
        m_qstrLastError = tr("Document.LoadFromFile.Json.Format.Error");
        return false;
    }

    const int iVersion = jsonRoot["version"].toInt();
    switch(iVersion)
    {
    case 1:
        return loadVersion_1(jsonRoot);
        break;
    default:
        m_qstrLastError = tr("Document.LoadFromFile.Json.Version.Error").arg(iVersion);;
        return false;
    }
}
bool RollScriptDocument::loadVersion_1(const QJsonObject& jsonRoot)
{
    const QJsonObject jsonDocument = jsonRoot["document"].toObject();

    const QJsonObject jsonSettings = jsonDocument["settings"].toObject();
    if(!m_ptrSettings->loadFromJson(jsonSettings))
    {
        m_qstrLastError = m_ptrSettings->lastError();
        return false;
    }

    // TASK : Load document blocks

    return true;
}
bool RollScriptDocument::saveToFile(const QString& qstrFileName)
{
    QFile fileSave(qstrFileName);
    if(!fileSave.open(QIODevice::WriteOnly))
    {
        m_qstrLastError = tr("Document.SaveToFile.Open.Error").arg(qstrFileName);
        return false;
    }

    QJsonObject jsonRoot;
    // Format & Version
    jsonRoot["format"] = "RollScript";
    jsonRoot["version"] = 1;

    QJsonObject jsonDocument;

    QJsonObject jsonSettings;
    if(!m_ptrSettings->saveToJson(jsonSettings))
    {
        m_qstrLastError = m_ptrSettings->lastError();
        return false;
    }
    jsonDocument["settings"] = jsonSettings;

    // TASK : Save document blocks

    jsonRoot["document"] = jsonDocument;

    QJsonDocument jsonDoc(jsonRoot);
    const QByteArray baData = jsonDoc.toJson(QJsonDocument::Indented);

    if(fileSave.write(jsonDoc.toJson(QJsonDocument::Indented)) != baData.size())
    {
        m_qstrLastError = tr("Document.SaveToFile.Save.Error").arg(qstrFileName);
        fileSave.close();
        return false;
    }
    fileSave.close();
    return true;
}

void RollScriptDocument::slotSettingsChanged()
{
    setModified(true);
}

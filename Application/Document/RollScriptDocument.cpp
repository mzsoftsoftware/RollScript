#include "RollScriptDocument.h"

#include <QFile>
#include <QJsonObject>

#include "Document/RollScriptDocumentSettings.h"
#include "Document/RollScriptDocumentBlocks.h"


RollScriptDocument::RollScriptDocument(QObject *parent)
    : QObject{parent}

{
    m_ptrSettings = new RollScriptDocumentSettings(this);
    m_ptrBlocks = new RollScriptDocumentBlocks(this);

    connect(m_ptrSettings, &RollScriptDocumentSettings::settingsChanged, this, &RollScriptDocument::slotSettingsChanged);
    connect(m_ptrBlocks, &RollScriptDocumentBlocks::blocksChanged, this, &RollScriptDocument::slotBlocksChanged);
}

void RollScriptDocument::clear()
{
    m_qstrFileName.clear();
    m_ptrSettings->clear();
    m_ptrBlocks->clear();

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
        ROLLSCRIPT_ERROR(tr("Document.Save.NoFileName"), QStringLiteral("m_qstrFileName is empty."));
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
        ROLLSCRIPT_ERROR(tr("Document.LoadFromFile.Open.Error").arg(qstrFileName), QStringLiteral("QFile->open failed."));
        return false;
    }

    const QByteArray baData = fileLoad.readAll();
    fileLoad.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(baData);
    if(!jsonDoc.isObject())
    {
        ROLLSCRIPT_ERROR(tr("Document.LoadFromFile.Json.Error"), QStringLiteral("jsonDoc is not an Object."));
        return false;
    }

    const QJsonObject jsonRoot = jsonDoc.object();

    if(!jsonRoot.contains(QStringLiteral("format")) || !jsonRoot[QStringLiteral("format")].isString() || jsonRoot[QStringLiteral("format")].toString() != QStringLiteral("RollScript"))
    {
        ROLLSCRIPT_ERROR(tr("Document.LoadFromFile.Json.Format.Error"), QStringLiteral("jsonRoot doesn't contain format='RollScript'."));
        return false;
    }

    const int iVersion = jsonRoot[QStringLiteral("version")].toInt();
    switch(iVersion)
    {
    case 1:
        return loadVersion_1(jsonRoot);
        break;
    default:
        ROLLSCRIPT_ERROR(tr("Document.LoadFromFile.Json.Version.Error").arg(iVersion), QStringLiteral("jsonRoot.version is unknown: %1.").arg(iVersion));
        return false;
    }
}
bool RollScriptDocument::loadVersion_1(const QJsonObject& jsonRoot)
{
    const QJsonObject jsonDocument = jsonRoot[QStringLiteral("document")].toObject();

    const QJsonObject jsonSettings = jsonDocument[QStringLiteral("settings")].toObject();
    if(!m_ptrSettings->loadFromJson(jsonSettings))
    {
        ROLLSCRIPT_ERROR_CAUSE(tr("Document.LoadFromFile.Json.Error"), QStringLiteral("m_ptrSettings->loadFromJson failed."), m_ptrSettings->takeError());
        return false;
    }

    const QJsonObject jsonBlocks = jsonDocument[QStringLiteral("blocks")].toObject();
    if(!m_ptrBlocks->loadFromJson(jsonBlocks))
    {
        ROLLSCRIPT_ERROR_CAUSE(tr("Document.LoadFromFile.Json.Error"), QStringLiteral("m_ptrBlocks->loadFromJson failed."), m_ptrBlocks->takeError());
        return false;
    }

    return true;
}
bool RollScriptDocument::saveToFile(const QString& qstrFileName)
{
    QFile fileSave(qstrFileName);
    if(!fileSave.open(QIODevice::WriteOnly))
    {
        ROLLSCRIPT_ERROR(tr("Document.SaveToFile.Open.Error").arg(qstrFileName), QStringLiteral("QFile->open failed."));
        return false;
    }

    QJsonObject jsonRoot;
    // Format & Version
    jsonRoot[QStringLiteral("format")] = QStringLiteral("RollScript");
    jsonRoot[QStringLiteral("version")] = 1;

    QJsonObject jsonDocument;

    QJsonObject jsonSettings;
    if(!m_ptrSettings->saveToJson(jsonSettings))
    {
        ROLLSCRIPT_ERROR_CAUSE(tr("Document.SaveToFile.Json.Error"), QStringLiteral("m_ptrSettings->saveToJson failed."), m_ptrSettings->takeError());
        return false;
    }
    jsonDocument[QStringLiteral("settings")] = jsonSettings;

    QJsonObject jsonBlocks;
    if(!m_ptrSettings->saveToJson(jsonBlocks))
    {
        ROLLSCRIPT_ERROR_CAUSE(tr("Document.SaveToFile.Json.Error"), QStringLiteral("m_ptrBlocks->saveToJson failed."), m_ptrBlocks->takeError());
        return false;
    }
    jsonDocument[QStringLiteral("blocks")] = jsonBlocks;

    jsonRoot[QStringLiteral("document")] = jsonDocument;

    QJsonDocument jsonDoc(jsonRoot);
    const QByteArray baData = jsonDoc.toJson(QJsonDocument::Indented);

    if(fileSave.write(jsonDoc.toJson(QJsonDocument::Indented)) != baData.size())
    {
        ROLLSCRIPT_ERROR(tr("Document.SaveToFile.Save.Error").arg(qstrFileName), QStringLiteral("QFile->write failed."));
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

void RollScriptDocument::slotBlocksChanged()
{
    setModified(true);
}

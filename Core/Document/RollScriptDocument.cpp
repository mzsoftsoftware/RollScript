#include "RollScriptDocument.h"

#include <QFile>
#include <QJsonObject>


RollScriptDocument::RollScriptDocument(QObject *parent)
    : QObject{parent}
{
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

void RollScriptDocument::setModified(bool bModified)
{
    if (m_bModified == bModified)
    {
        return;
    }

    m_bModified = bModified;
    emit documentModifiedChanged(m_bModified);
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
    // Version
    jsonRoot["Version"] = 1;

    // TASK : Save the File !

    QJsonDocument jsonDoc(jsonRoot);

    fileSave.write(jsonDoc.toJson(QJsonDocument::Indented));
    fileSave.close();
    return true;
}
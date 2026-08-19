#include "RollScriptDocumentBlocks.h"

#include <QJsonObject>

#include "Core/Blocks/RollScriptBlockDocumentBase.h"


RollScriptDocumentBlocks::RollScriptDocumentBlocks(QObject *parent)
    : QObject{parent}
{
}


void RollScriptDocumentBlocks::insertDocumentBlock(const int index, RollScriptBlockDocumentBase* ptrBlock)
{
    if(ptrBlock == nullptr)
        return;

    int iIndex = index;
    if(index<0 || index>m_vecDocumentBlocks.count())
        iIndex = m_vecDocumentBlocks.count();

    connect(ptrBlock, &RollScriptBlockDocumentBase::blockChanged, this, &RollScriptDocumentBlocks::onDocumentBlockChanged);

    emit documentBlockAboutToBeInserted(iIndex);
    m_vecDocumentBlocks.insert(iIndex, ptrBlock);
    emit documentBlockInserted();

    emit blocksChanged();
}
void RollScriptDocumentBlocks::removeDocumentBlock(const int index)
{
    if(index < 0 || index >= m_vecDocumentBlocks.count())
        return;

    emit documentBlockAboutToBeRemoved(index);
    delete m_vecDocumentBlocks[index];
    m_vecDocumentBlocks.removeAt(index);
    emit documentBlockRemoved();

    emit blocksChanged();
}
void RollScriptDocumentBlocks::moveDocumentBlock(const int idxFrom, const int idxTo)
{
    if(idxFrom < 0 || idxFrom >= m_vecDocumentBlocks.count())
        return;
    if(idxTo < 0 || idxTo >= m_vecDocumentBlocks.count())
        return;
    if(idxFrom == idxTo)
        return;

    emit documentBlockAboutToBeMoved(idxFrom, idxTo);
    m_vecDocumentBlocks.move(idxFrom, idxTo);
    emit documentBlockMoved();

    emit blocksChanged();
}
RollScriptBlockDocumentBase* RollScriptDocumentBlocks::documentBlock(const int index)
{
    if(index < 0 || index >= m_vecDocumentBlocks.count())
        return nullptr;

    return m_vecDocumentBlocks[index];
}
void RollScriptDocumentBlocks::onDocumentBlockChanged()
{
    emit blocksChanged();
}




void RollScriptDocumentBlocks::clear()
{
}
bool RollScriptDocumentBlocks::loadFromJson(const QJsonObject& jsonBlocks)
{
    const int iVersion = jsonBlocks[QStringLiteral("version")].toInt();
    switch(iVersion)
    {
    case 1:
        return loadVersion_1(jsonBlocks);
        break;
    default:
        ROLLSCRIPT_ERROR(tr("DocumentBlocks.LoadFromFile.Json.Version.Error").arg(iVersion), QStringLiteral("version is unknown."));
        return false;
    }
}
bool RollScriptDocumentBlocks::loadVersion_1(const QJsonObject& jsonBlocks)
{
    return true;
}

bool RollScriptDocumentBlocks::saveToJson(QJsonObject& jsonBlocks) const
{
    jsonBlocks[QStringLiteral("version")] = 1;

    return true;
}

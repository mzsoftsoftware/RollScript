#include "RollScriptDocumentBlocks.h"

#include <QJsonObject>
#include <QJsonArray>

#include "Core/Blocks/RollScriptBlockDocumentBase.h"
#include "Features/FeatureBlockManager.h"


RollScriptDocumentBlocks::RollScriptDocumentBlocks(FeatureBlockManager* ptrFeatureBlockManager, QObject* parent)
    : QObject{parent}
    , m_ptrFeatureBlockManager(ptrFeatureBlockManager)
{
}
RollScriptDocumentBlocks::~RollScriptDocumentBlocks()
{
}


void RollScriptDocumentBlocks::insertDocumentBlock(const int index, const QString& qstrFeatureBlockId)
{
    RollScriptBlockDocumentBase* ptrDocumentBlockBase = m_ptrFeatureBlockManager->createFeatureBlockDocument(qstrFeatureBlockId, this);
    Q_ASSERT(ptrDocumentBlockBase);

    int iIndex = index;
    if(index<0 || index>m_qvecDocumentBlocks.count())
        iIndex = m_qvecDocumentBlocks.count();

    connect(ptrDocumentBlockBase, &RollScriptBlockDocumentBase::blockChanged, this, &RollScriptDocumentBlocks::onDocumentBlockChanged);

    emit documentBlockAboutToBeInserted(iIndex);
    m_qvecDocumentBlocks.insert(iIndex, ptrDocumentBlockBase);
    emit documentBlockInserted();

    emit blocksChanged();
}
void RollScriptDocumentBlocks::removeDocumentBlock(const int index)
{
    if(index < 0 || index >= m_qvecDocumentBlocks.count())
        return;

    emit documentBlockAboutToBeRemoved(index);
    delete m_qvecDocumentBlocks[index];
    m_qvecDocumentBlocks.removeAt(index);
    emit documentBlockRemoved();

    emit blocksChanged();
}
void RollScriptDocumentBlocks::moveDocumentBlock(const int idxFrom, const int idxTo)
{
    if(idxFrom < 0 || idxFrom >= m_qvecDocumentBlocks.count())
        return;
    if(idxTo < 0 || idxTo >= m_qvecDocumentBlocks.count())
        return;
    if(idxFrom == idxTo)
        return;

    emit documentBlockAboutToBeMoved(idxFrom, idxTo);
    m_qvecDocumentBlocks.move(idxFrom, idxTo);
    emit documentBlockMoved();

    emit blocksChanged();
}
RollScriptBlockDocumentBase* RollScriptDocumentBlocks::documentBlock(const int index)
{
    if(index < 0 || index >= m_qvecDocumentBlocks.count())
        return nullptr;

    return m_qvecDocumentBlocks[index];
}
void RollScriptDocumentBlocks::onDocumentBlockChanged()
{
    emit blocksChanged();
}


void RollScriptDocumentBlocks::clear()
{
    emit documentBlocksAboutToBeReset();

    qDeleteAll(m_qvecDocumentBlocks);
    m_qvecDocumentBlocks.clear();

    emit documentBlocksReset();
}
bool RollScriptDocumentBlocks::loadFromJson(const QJsonObject& jsonBlocks)
{     
    const int iVersion = jsonBlocks[QStringLiteral("version")].toInt();
    switch(iVersion)
    {
    case 1:
        emit documentBlocksAboutToBeReset();
        qDeleteAll(m_qvecDocumentBlocks);
        m_qvecDocumentBlocks.clear();
        if(!loadVersion_1(jsonBlocks))
        {
            emit documentBlocksReset();
            return false;
        }
        emit documentBlocksReset();
        return true;
        break;
    default:
        ROLLSCRIPT_ERROR(tr("DocumentBlocks.LoadFromFile.Json.Version.Error").arg(iVersion), QStringLiteral("version is unknown."));
        return false;
    }

    return false;
}
bool RollScriptDocumentBlocks::loadVersion_1(const QJsonObject& jsonBlocks)
{
    QJsonArray jsonDocumentBlocks = jsonBlocks[QStringLiteral("items")].toArray();

    for(const QJsonValueRef jsonValueRef : jsonDocumentBlocks)
    {
        QJsonObject jsonDocumentBlock = jsonValueRef.toObject();
        QString qstrPluginId = jsonDocumentBlock[QStringLiteral("pluginId")].toString();
        RollScriptBlockDocumentBase* ptrDocumentBlockBase = m_ptrFeatureBlockManager->createFeatureBlockDocument(qstrPluginId, this);
        Q_ASSERT(ptrDocumentBlockBase);

        if(!ptrDocumentBlockBase->loadFromJson(jsonDocumentBlock))
        {
            ROLLSCRIPT_ERROR_CAUSE(tr("Document.LoadFromFile.Json.Error"), QStringLiteral("ptrDocumentBlockBase->loadFromJson failed."), ptrDocumentBlockBase->takeError());
            return false;
        }

        connect(ptrDocumentBlockBase, &RollScriptBlockDocumentBase::blockChanged, this, &RollScriptDocumentBlocks::onDocumentBlockChanged);
        m_qvecDocumentBlocks.append(ptrDocumentBlockBase);
    }

    return true;
}

bool RollScriptDocumentBlocks::saveToJson(QJsonObject& jsonBlocks)
{
    jsonBlocks[QStringLiteral("version")] = 1;

    QJsonArray jsonDocumentBlocks;
    for(RollScriptBlockDocumentBase* ptrDocumentBlock : m_qvecDocumentBlocks)
    {
        Q_ASSERT(ptrDocumentBlock);

        QJsonObject jsonDocumentBlock;
        jsonDocumentBlock[QStringLiteral("pluginId")] = ptrDocumentBlock->blockPluginId();

        if(!ptrDocumentBlock->saveToJson(jsonDocumentBlock))
        {
            ROLLSCRIPT_ERROR_CAUSE(tr("Document.SaveToFile.Json.Error"), QStringLiteral("ptrDocumentBlock->saveToJson failed."), ptrDocumentBlock->takeError());
            return false;
        }
        jsonDocumentBlocks.append(jsonDocumentBlock);
    }

    jsonBlocks[QStringLiteral("items")] = jsonDocumentBlocks;

    return true;
}

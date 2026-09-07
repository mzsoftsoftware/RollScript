#include "FeatureBlocksItemModel.h"

#include "Features/FeatureBlockManager.h"
#include "Document/RollScriptDocumentBlocks.h"
#include "Core/Blocks/RollScriptBlockDocumentBase.h"
#include "Core/Blocks/IFeatureBlock.h"
#include "Core/Blocks/IFeatureBlockInfo.h"


FeatureBlocksItemModel::FeatureBlocksItemModel(QObject* parent)
    : QAbstractListModel(parent)
{
}
FeatureBlocksItemModel::~FeatureBlocksItemModel()
{
}

void FeatureBlocksItemModel::setFeatureBlockManager(FeatureBlockManager* ptrFeatureBlockManager)
{
    Q_ASSERT(ptrFeatureBlockManager);
    Q_ASSERT(!m_ptrFeatureBlockManager);

    m_ptrFeatureBlockManager = ptrFeatureBlockManager;
}
void FeatureBlocksItemModel::setRollScriptDocumentBlocks(RollScriptDocumentBlocks* ptrDocumentBlocks)
{
    Q_ASSERT(ptrDocumentBlocks);
    Q_ASSERT(!m_ptrDocumentBlocks);

    m_ptrDocumentBlocks = ptrDocumentBlocks;

    connect(m_ptrDocumentBlocks, &RollScriptDocumentBlocks::documentBlocksAboutToBeReset, this, &FeatureBlocksItemModel::slotDocumentBlocksAboutToBeReset);
    connect(m_ptrDocumentBlocks, &RollScriptDocumentBlocks::documentBlocksReset, this, &FeatureBlocksItemModel::slotDocumentBlocksReset);

    connect(m_ptrDocumentBlocks, &RollScriptDocumentBlocks::documentBlockAboutToBeInserted, this, &FeatureBlocksItemModel::slotDocumentBlockAboutToBeInserted);
    connect(m_ptrDocumentBlocks, &RollScriptDocumentBlocks::documentBlockInserted, this, &FeatureBlocksItemModel::slotDocumentBlockInserted);

    connect(m_ptrDocumentBlocks, &RollScriptDocumentBlocks::documentBlockAboutToBeRemoved, this, &FeatureBlocksItemModel::slotDocumentBlockAboutToBeRemoved);
    connect(m_ptrDocumentBlocks, &RollScriptDocumentBlocks::documentBlockRemoved, this, &FeatureBlocksItemModel::slotDocumentBlockRemoved);

    connect(m_ptrDocumentBlocks, &RollScriptDocumentBlocks::documentBlockAboutToBeMoved, this, &FeatureBlocksItemModel::slotDocumentBlockAboutToBeMoved);
    connect(m_ptrDocumentBlocks, &RollScriptDocumentBlocks::documentBlockMoved, this, &FeatureBlocksItemModel::slotDocumentBlockMoved);
}


int FeatureBlocksItemModel::rowCount(const QModelIndex& parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if( parent.isValid() || !m_ptrDocumentBlocks)
        return 0;

    return m_ptrDocumentBlocks->documentBlockCount();
}

QVariant FeatureBlocksItemModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || !m_ptrDocumentBlocks || !m_ptrFeatureBlockManager)
        return QVariant();

    RollScriptBlockDocumentBase* ptrDocumentBlockBase = m_ptrDocumentBlocks->documentBlock(index.row());
    if(!ptrDocumentBlockBase)
        return QVariant();

    IFeatureBlock* ptrFeatureBlock = m_ptrFeatureBlockManager->featureBlock(ptrDocumentBlockBase->blockPluginId());
    if( role == Qt::DisplayRole )
    {
        return tr(ptrFeatureBlock->featureBlockInfo()->featureBlockDisplayName().toUtf8().constData());
    }
    if(role == Qt::DecorationRole )
    {
        return ptrFeatureBlock->featureBlockInfo()->featureBlockIcon();
    }
    if( role == Qt::ToolTipRole )
    {
        return ptrFeatureBlock->featureBlockInfo()->featureBlockTooltip();
    }

    return QVariant();
}

bool FeatureBlocksItemModel::moveRows(const QModelIndex& sourceParent, int iSourceRow, int iCount, const QModelIndex& destinationParent, int iDestinationChild)
{
    if (!m_ptrDocumentBlocks)
        return false;

    if (iSourceRow == iDestinationChild || iSourceRow + 1 == iDestinationChild)
        return false;
    if (iSourceRow < 0 || iSourceRow >= m_ptrDocumentBlocks->documentBlockCount())
        return false;
    // Qt erlaubt destinationChild == rowCount() (append)
    if (iDestinationChild > m_ptrDocumentBlocks->documentBlockCount())
        iDestinationChild = m_ptrDocumentBlocks->documentBlockCount();

    // gleiche Position → nix tun
    if (iSourceRow == iDestinationChild || iSourceRow + 1 == iDestinationChild)
        return false;

    beginMoveRows(sourceParent, iSourceRow, iSourceRow, destinationParent, iDestinationChild);

    int adjustedDest = iDestinationChild;
    if (iDestinationChild > iSourceRow)
        adjustedDest--;   // weil Element vorher entfernt wird
    m_ptrDocumentBlocks->moveDocumentBlock(iSourceRow, adjustedDest);

    endMoveRows();
    return true;
}

bool FeatureBlocksItemModel::removeRows(int iRow, int iCount, const QModelIndex& parent)
{
    if (!m_ptrDocumentBlocks || iCount != 1)
        return false;

    beginRemoveRows(parent, iRow, iRow);

    m_ptrDocumentBlocks->removeDocumentBlock(iRow);

    endRemoveRows();
    return true;
}

Qt::ItemFlags FeatureBlocksItemModel::flags(const QModelIndex& index) const
{
    Qt::ItemFlags defaultFlags = QAbstractListModel::flags(index);

    if(index.isValid())
        return defaultFlags | Qt::ItemIsDragEnabled;

    return defaultFlags | Qt::ItemIsDropEnabled;
}

void FeatureBlocksItemModel::slotDocumentBlocksAboutToBeReset()
{
    beginResetModel();
}
void FeatureBlocksItemModel::slotDocumentBlocksReset()
{
    endResetModel();
}

void FeatureBlocksItemModel::slotDocumentBlockAboutToBeInserted(const int index)
{
    beginInsertRows(QModelIndex(), index, index);
}
void FeatureBlocksItemModel::slotDocumentBlockInserted()
{
    endInsertRows();
}

void FeatureBlocksItemModel::slotDocumentBlockAboutToBeRemoved(const int index)
{
    beginRemoveRows(QModelIndex(), index, index);
}
void FeatureBlocksItemModel::slotDocumentBlockRemoved()
{
    endRemoveRows();
}

void FeatureBlocksItemModel::slotDocumentBlockAboutToBeMoved(const int idxFrom, const int idxTo)
{
    int iDestinationChild = idxTo;
    if(idxFrom < idxTo)
        ++iDestinationChild;

    //beginMoveRows(QModelIndex(), idxFrom, idxTo, QModelIndex(), iDestinationChild);
}
void FeatureBlocksItemModel::slotDocumentBlockMoved()
{
    //endMoveRows();
}

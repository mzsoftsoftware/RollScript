#include "FeatureBlocksItemModel.h"

#include "Features/FeatureBlockManager.h"
#include "Document/RollScriptDocumentBlocks.h"
#include "Core/Blocks/RollScriptBlockDocumentBase.h"
#include "Core/Blocks/IFeatureBlock.h"
#include "Core/Blocks/IFeatureBlockInfo.h"


FeatureBlocksItemModel::FeatureBlocksItemModel(FeatureBlockManager *ptrFeatureBlockManager, RollScriptDocumentBlocks* ptrDocumentBlocks, QObject* parent)
    : QAbstractListModel(parent)
    , m_ptrFeatureBlockManager(ptrFeatureBlockManager)
    , m_ptrDocumentBlocks(ptrDocumentBlocks)
{
    connect(m_ptrDocumentBlocks, &RollScriptDocumentBlocks::documentBlocksAboutToBeReset, this, &FeatureBlocksItemModel::slotDocumentBlocksAboutToBeReset);
    connect(m_ptrDocumentBlocks, &RollScriptDocumentBlocks::documentBlocksReset, this, &FeatureBlocksItemModel::slotDocumentBlocksReset);

    connect(m_ptrDocumentBlocks, &RollScriptDocumentBlocks::documentBlockAboutToBeInserted, this, &FeatureBlocksItemModel::slotDocumentBlockAboutToBeInserted);
    connect(m_ptrDocumentBlocks, &RollScriptDocumentBlocks::documentBlockInserted, this, &FeatureBlocksItemModel::slotDocumentBlockInserted);

    connect(m_ptrDocumentBlocks, &RollScriptDocumentBlocks::documentBlockAboutToBeRemoved, this, &FeatureBlocksItemModel::slotDocumentBlockAboutToBeRemoved);
    connect(m_ptrDocumentBlocks, &RollScriptDocumentBlocks::documentBlockRemoved, this, &FeatureBlocksItemModel::slotDocumentBlockRemoved);

    connect(m_ptrDocumentBlocks, &RollScriptDocumentBlocks::documentBlockAboutToBeMoved, this, &FeatureBlocksItemModel::slotDocumentBlockAboutToBeMoved);
    connect(m_ptrDocumentBlocks, &RollScriptDocumentBlocks::documentBlockMoved, this, &FeatureBlocksItemModel::slotDocumentBlockMoved);
}

int FeatureBlocksItemModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if( parent.isValid() || !m_ptrDocumentBlocks)
        return 0;

    return m_ptrDocumentBlocks->documentBlockCount();
}

QVariant FeatureBlocksItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !m_ptrDocumentBlocks)
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
        return tr(ptrFeatureBlock->featureBlockInfo()->featureBlockTooltip().toUtf8().constData());
    }

    return QVariant();
}

bool FeatureBlocksItemModel::moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild)
{
    if (sourceRow == destinationChild || sourceRow + 1 == destinationChild)
        return false;
    if (sourceRow < 0 || sourceRow >= m_ptrDocumentBlocks->documentBlockCount())
        return false;
    // Qt erlaubt destinationChild == rowCount() (append)
    if (destinationChild > m_ptrDocumentBlocks->documentBlockCount())
        destinationChild = m_ptrDocumentBlocks->documentBlockCount();

    // gleiche Position → nix tun
    if (sourceRow == destinationChild || sourceRow + 1 == destinationChild)
        return false;

    beginMoveRows(sourceParent, sourceRow, sourceRow, destinationParent, destinationChild);

    int adjustedDest = destinationChild;
    if (destinationChild > sourceRow)
        adjustedDest--;   // weil Element vorher entfernt wird
    m_ptrDocumentBlocks->moveDocumentBlock(sourceRow, adjustedDest);

    endMoveRows();
    return true;
}

bool FeatureBlocksItemModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(count != 1)
        return false;

    beginRemoveRows(parent, row, row);

    m_ptrDocumentBlocks->removeDocumentBlock(row);

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

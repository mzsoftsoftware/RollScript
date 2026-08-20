#pragma once

#include <QAbstractListModel>

class FeatureBlockManager;
class RollScriptDocumentBlocks;

class FeatureBlocksItemModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit FeatureBlocksItemModel(QObject* parent);

    // Setter
    void setFeatureBlockManager(FeatureBlockManager* ptrFeatureBlockManager);
    void setRollScriptDocumentBlocks(RollScriptDocumentBlocks* ptrDocumentBlocks);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // Fetch data dynamically:
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    Qt::DropActions supportedDropActions() const override { return Qt::MoveAction; }

    bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;

private slots:
    void slotDocumentBlocksAboutToBeReset();
    void slotDocumentBlocksReset();

    void slotDocumentBlockAboutToBeInserted(const int index);
    void slotDocumentBlockInserted();

    void slotDocumentBlockAboutToBeRemoved(const int index);
    void slotDocumentBlockRemoved();

    void slotDocumentBlockAboutToBeMoved(const int idxFrom, const int idxTo);
    void slotDocumentBlockMoved();

private:
    FeatureBlockManager*        m_ptrFeatureBlockManager = nullptr;
    RollScriptDocumentBlocks*   m_ptrDocumentBlocks = nullptr;
};

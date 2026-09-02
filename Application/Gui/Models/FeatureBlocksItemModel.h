#pragma once

#include <QAbstractListModel>

class FeatureBlockManager;
class RollScriptDocumentBlocks;

class FeatureBlocksItemModel : public QAbstractListModel
{
    Q_OBJECT

public:
    // Constructor / Destructor
    explicit FeatureBlocksItemModel(QObject* parent);
    ~FeatureBlocksItemModel() override;

    // Setter
    void setFeatureBlockManager(FeatureBlockManager* ptrFeatureBlockManager);
    void setRollScriptDocumentBlocks(RollScriptDocumentBlocks* ptrDocumentBlocks);

    // Basic functionality:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    // Fetch data dynamically:
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    Qt::DropActions supportedDropActions() const override { return Qt::MoveAction; }

    bool moveRows(const QModelIndex& sourceParent, int iSourceRow, int iCount, const QModelIndex& destinationParent, int iDestinationChild) override;
    bool removeRows(int iRow, int iCount, const QModelIndex& parent) override;

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

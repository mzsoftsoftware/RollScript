#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"

class RollScriptBlockDocumentBase;


class RollScriptDocumentBlocks : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT

public:
    RollScriptDocumentBlocks(QObject *parent);

    // Getter

    // Block handling
    void insertDocumentBlock(const int index, RollScriptBlockDocumentBase* ptrBlock);
    void removeDocumentBlock(const int index);
    void moveDocumentBlock(const int idxFrom, const int idxTo);
    RollScriptBlockDocumentBase* documentBlock(const int index);
    const QVector<RollScriptBlockDocumentBase*>&documentBlocks() const  { return m_vecDocumentBlocks; }
    int documentBlockCount() const                                      { return m_vecDocumentBlocks.count(); }

    // JSON
    void clear();
    bool loadFromJson(const QJsonObject& jsonBlocks);
    bool saveToJson(QJsonObject& jsonBlocks) const;

private:
    bool loadVersion_1(const QJsonObject& jsonBlocks);

private slots:
    void onDocumentBlockChanged();

signals:
    void blocksChanged();

    void documentBlockAboutToBeInserted(const int index);
    void documentBlockInserted();
    void documentBlockAboutToBeRemoved(const int index);
    void documentBlockRemoved();
    void documentBlockAboutToBeMoved(const int idxFrom, const int idxTo);
    void documentBlockMoved();
    void documentBlocksAboutToBeReset();
    void documentBlocksReset();

private:
    QVector<RollScriptBlockDocumentBase*> m_vecDocumentBlocks;
};

#pragma once

#include <QObject>
#include <QHash>

#include "Core/Errors/RollScriptErrorOwner.h"

class IFeatureBlock;


class FeatureBlockRegistry : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT

public:
    FeatureBlockRegistry(QObject* parent);

    bool registerFeatureBlock(IFeatureBlock* ptrFeatureBlock);

    // Getter
    QStringList availableFeatureBlockIds() const                            { return m_qstrFeatureBlockIds; }
    IFeatureBlock* featureBlock(const QString& qstrfeatureBlockId) const    { return m_hashFeatureBlocks.value(qstrfeatureBlockId, nullptr); }

private:
    QStringList m_qstrFeatureBlockIds;
    QHash<QString, IFeatureBlock*> m_hashFeatureBlocks;
};

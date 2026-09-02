#pragma once

#include <QObject>
#include <QHash>

#include "Core/Errors/RollScriptErrorOwner.h"

class IFeatureBlock;


class FeatureBlockRegistry : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT

public:
    explicit FeatureBlockRegistry(QObject* parent);
    ~FeatureBlockRegistry() override;

    // Getter
    QStringList availableFeatureBlockIds() const                            { return m_qstrFeatureBlockIds; }
    IFeatureBlock* featureBlock(const QString& qstrfeatureBlockId) const    { return m_qhashFeatureBlocks.value(qstrfeatureBlockId, nullptr); }

    // Operations
    bool registerFeatureBlock(IFeatureBlock* ptrFeatureBlock);

private:
    QStringList m_qstrFeatureBlockIds;
    QHash<QString, IFeatureBlock*> m_qhashFeatureBlocks;
};

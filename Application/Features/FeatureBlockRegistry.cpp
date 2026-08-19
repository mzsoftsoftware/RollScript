#include "FeatureBlockRegistry.h"

#include "Core/Blocks/IFeatureBlock.h"
#include "Core/Blocks/IFeatureBlockInfo.h"


FeatureBlockRegistry::FeatureBlockRegistry(QObject *parent)
    : QObject{parent}
{
}

bool FeatureBlockRegistry::registerFeatureBlock(IFeatureBlock* ptrFeatureBlock)
{
    Q_ASSERT(ptrFeatureBlock);

    const QString qstrFeatureBlockId = ptrFeatureBlock->featureBlockInfo()->featureBlockId();
    if(m_qstrFeatureBlockIds.contains(qstrFeatureBlockId))
    {
        ROLLSCRIPT_ERROR(tr("FeatureBlockAlreadyRegistered"), QStringLiteral("FeatureBlock ID already registered: %1").arg(qstrFeatureBlockId));
        return false;
    }

    m_hashFeatureBlocks.insert(qstrFeatureBlockId, ptrFeatureBlock);
    m_qstrFeatureBlockIds.append(qstrFeatureBlockId);

    return true;
}

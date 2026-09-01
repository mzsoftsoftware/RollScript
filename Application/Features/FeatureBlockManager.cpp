#include "FeatureBlockManager.h"

#include "FeatureBlockRegistry.h"
#include "Core/Plugins/IFeaturePlugin.h"
#include "Core/Blocks/IFeatureBlock.h"
#include "Plugins/PluginManager.h"
#include "Plugins/FeaturePluginRegistry.h"


FeatureBlockManager::FeatureBlockManager(PluginManager* ptrPluginManager, QObject* parent)
    : QObject{parent}
    , m_ptrPluginManager(ptrPluginManager)
{
    Q_ASSERT(m_ptrPluginManager);
    m_ptrRegistryFeatureBlocks = new FeatureBlockRegistry(this);
}
FeatureBlockManager::~FeatureBlockManager()
{
}

bool FeatureBlockManager::init()
{
    FeaturePluginRegistry* ptrFeaturePluginRegistry = m_ptrPluginManager->registryFeatures();
    if(!ptrFeaturePluginRegistry)
    {
        ROLLSCRIPT_ERROR(tr("FeatureBlockManagerInitFailed"), QStringLiteral("FeaturePluginRegistry is nullptr."));
        return false;
    }

    const QStringList qstrPluginIds = ptrFeaturePluginRegistry->availableFeaturePluginIds();

    for(const QString& qstrPluginId : qstrPluginIds)
    {
        IFeaturePlugin* ptrFeaturePlugin = ptrFeaturePluginRegistry->featurePlugin(qstrPluginId);
        if(!ptrFeaturePlugin)
        {
            ROLLSCRIPT_ERROR(tr("FeatureBlockManagerInitFailed"), QStringLiteral("FeatureBlockRegistry::ptrFeaturePlugin nullptr."));
            return false;
        }

        IFeatureBlock* ptrFeatureBlock = qobject_cast<IFeatureBlock*>(ptrFeaturePlugin);
        if(!ptrFeatureBlock)
            continue;

        if(!m_ptrRegistryFeatureBlocks->registerFeatureBlock(ptrFeatureBlock))
        {
            ROLLSCRIPT_ERROR_CAUSE(tr("FeatureBlockManagerInitFailed"), QStringLiteral("FeatureBlockRegistry::registerFeature failed."), m_ptrRegistryFeatureBlocks->takeError());
            return false;
        }
    }

    return true;
}

QStringList FeatureBlockManager::availableFeatureBlockIds() const
{
    Q_ASSERT(m_ptrRegistryFeatureBlocks);

    return m_ptrRegistryFeatureBlocks->availableFeatureBlockIds();
}
IFeatureBlock* FeatureBlockManager::featureBlock(const QString& qstrfeatureBlockId) const
{
    Q_ASSERT(m_ptrRegistryFeatureBlocks);

    return m_ptrRegistryFeatureBlocks->featureBlock(qstrfeatureBlockId);
}
RollScriptBlockWidgetBase* FeatureBlockManager::createFeatureBlockWidget(const QString& qstrFeatureBlockId, QWidget *parent)
{
    Q_ASSERT(m_ptrRegistryFeatureBlocks);
    Q_ASSERT(parent);

    IFeatureBlock* ptrFeatureBlock = m_ptrRegistryFeatureBlocks->featureBlock(qstrFeatureBlockId);
    Q_ASSERT(ptrFeatureBlock);

    return ptrFeatureBlock->createFeatureBlockWidget(parent);
}
RollScriptBlockDocumentBase* FeatureBlockManager::createFeatureBlockDocument(const QString& qstrFeatureBlockId, QObject* parent)
{
    Q_ASSERT(m_ptrRegistryFeatureBlocks);
    Q_ASSERT(parent);

    IFeatureBlock* ptrFeatureBlock = m_ptrRegistryFeatureBlocks->featureBlock(qstrFeatureBlockId);
    Q_ASSERT(ptrFeatureBlock);

    return ptrFeatureBlock->createFeatureBlockDocument(parent);
}
RollScriptBlockRendererBase* FeatureBlockManager::createFeatureBlockRenderer(const QString& qstrFeatureBlockId, QObject* parent)
{
    Q_ASSERT(m_ptrRegistryFeatureBlocks);
    Q_ASSERT(parent);

    IFeatureBlock* ptrFeatureBlock = m_ptrRegistryFeatureBlocks->featureBlock(qstrFeatureBlockId);
    Q_ASSERT(ptrFeatureBlock);

    return ptrFeatureBlock->createFeatureBlockRenderer(parent);
}
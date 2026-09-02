#pragma once

#include <QObject>
#include <QList>

#include "Core/Errors/RollScriptErrorOwner.h"

class PluginManager;
class FeatureBlockRegistry;
class IFeatureBlock;
class RollScriptBlockWidgetBase;
class RollScriptBlockDocumentBase;
class RollScriptBlockRendererBase;


class FeatureBlockManager : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT

public:
    // Constructor / Destructor
    explicit FeatureBlockManager(PluginManager* ptrPluginManager, QObject* parent);
    ~FeatureBlockManager() override;

    // Getter
    QStringList availableFeatureBlockIds() const;
    IFeatureBlock* featureBlock(const QString& qstrfeatureBlockId) const;
    RollScriptBlockWidgetBase* createFeatureBlockWidget(const QString& qstrFeatureBlockId, QWidget* parent);
    RollScriptBlockDocumentBase* createFeatureBlockDocument(const QString& qstrFeatureBlockId, QObject* parent);
    RollScriptBlockRendererBase* createFeatureBlockRenderer(const QString& qstrFeatureBlockId, QObject* parent);

    // Operations
    bool init();

signals:
    void managerError();

private:
    PluginManager* m_ptrPluginManager = nullptr;
    FeatureBlockRegistry* m_ptrRegistryFeatureBlocks = nullptr;
};

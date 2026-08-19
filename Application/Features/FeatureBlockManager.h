#pragma once

#include <QObject>
#include <QList>

#include "Core/Errors/RollScriptErrorOwner.h"

class PluginManager;
class FeatureBlockRegistry;
class IFeatureBlock;
class RollScriptBlockWidgetBase;
class RollScriptBlockDocumentBase;


class FeatureBlockManager : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT

public:
    explicit FeatureBlockManager(PluginManager* ptrPluginManager, QObject* parent);
    virtual ~FeatureBlockManager() override;

    bool init();

    // Getter
    QStringList availableFeatureBlockIds() const;
    IFeatureBlock* featureBlock(const QString& qstrfeatureBlockId) const;
    RollScriptBlockWidgetBase* createFeatureBlockWidget(const QString& qstrFeatureBlockId, QWidget *parent);
    RollScriptBlockDocumentBase* createFeatureBlockDocument(const QString& qstrFeatureBlockId, QObject* parent);

signals:
    void managerError();

private:
    PluginManager* m_ptrPluginManager = nullptr;
    FeatureBlockRegistry* m_ptrRegistryFeatureBlocks = nullptr;
};

#pragma once

#include <QIcon>
#include <QString>

#include <QtPlugin>

class IFeatureBlockInfo;
class RollScriptBlockWidgetBase;
class RollScriptBlockDocumentBase;
class RollScriptBlockRendererBase;


class IFeatureBlock
{
public:
    // Constructor / Destructor
    virtual ~IFeatureBlock() = default;

    // Getter
    virtual const IFeatureBlockInfo* featureBlockInfo() const = 0;
    //virtual const QString& featureBlockId() const = 0;
    //virtual const QString& featureBlockDisplayName() const = 0;
    //virtual const QIcon& featureBlockIcon() const = 0;
    //virtual const QString& featureBlockTooltip() const = 0;

    // Instances
    virtual RollScriptBlockWidgetBase* createFeatureBlockWidget(QWidget* parent) = 0;
    virtual RollScriptBlockDocumentBase* createFeatureBlockDocument(QObject* parent) = 0;
    virtual RollScriptBlockRendererBase* createFeatureBlockRenderer(QObject* parent) = 0;
};

#define ROLLSCRIPT_IFEATUREBLOCK_IID \
    "de.mzsoft.rollscript.features.block"

Q_DECLARE_INTERFACE(IFeatureBlock, ROLLSCRIPT_IFEATUREBLOCK_IID)


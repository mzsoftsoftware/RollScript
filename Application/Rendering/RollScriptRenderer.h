#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"

#include <QHash>
#include <QImage>

class PrinterManager;
class FeatureBlockManager;
class RollScriptDocument;
class RollScriptBlockRendererBase;
class RenderDeviceInfo;
class RenderLayout;
class RenderContext;


class RollScriptRenderer : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT

public:
    explicit RollScriptRenderer(PrinterManager* ptrPrinterManager, FeatureBlockManager* ptrFeatureBlockManager, QObject *parent);
    virtual ~RollScriptRenderer() override;

    // Getter
    const QImage& image() const;

    bool init();
    void setRollScriptDocument(const RollScriptDocument* ptrDocument);

    bool render();

private:
    void reset();
    bool createDeviceInfo();
    bool createLayout();
    bool createRendering();

signals:
    void renderingError();

private:
    PrinterManager* m_ptrPrinterManager;
    FeatureBlockManager* m_ptrFeatureBlockManager = nullptr;
    const RollScriptDocument* m_ptrDocument = nullptr;

    QHash<QString, RollScriptBlockRendererBase*> m_hashFeatureBlockRenderers;

    RenderDeviceInfo* m_ptrRenderDeviceInfo;
    RenderLayout* m_ptrRenderLayout = nullptr;
    RenderContext* m_ptrRenderContext = nullptr;
};

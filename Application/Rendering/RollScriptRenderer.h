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
    explicit RollScriptRenderer(PrinterManager* ptrPrinterManager, FeatureBlockManager* ptrFeatureBlockManager, QObject* parent);
    ~RollScriptRenderer() override;

    // Getter
    const QImage& image() const;

    // Setter
    void setRollScriptDocument(const RollScriptDocument* ptrDocument);

    // Operations
    bool init();
    bool render();

signals:
    void renderingError();

private:
    void reset();
    bool createDeviceInfo();
    bool createLayout();
    bool createRendering();

private:
    PrinterManager*             m_ptrPrinterManager;
    FeatureBlockManager*        m_ptrFeatureBlockManager = nullptr;
    const RollScriptDocument*   m_ptrDocument = nullptr;

    QHash<QString, RollScriptBlockRendererBase*> m_qhashFeatureBlockRenderers;

    RenderDeviceInfo*   m_ptrRenderDeviceInfo;
    RenderLayout*       m_ptrRenderLayout = nullptr;
    RenderContext*      m_ptrRenderContext = nullptr;
};

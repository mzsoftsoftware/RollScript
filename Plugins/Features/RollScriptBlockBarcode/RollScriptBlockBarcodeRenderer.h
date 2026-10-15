#pragma once

#include "Core/Blocks/RollScriptBlockRendererBase.h"


class RollScriptBlockBarcodeRenderer : public RollScriptBlockRendererBase
{
    Q_OBJECT

public:
    // Constructor / Destructor
    explicit RollScriptBlockBarcodeRenderer(const QString& qstrBlockPluginId, QObject* parent);
    ~RollScriptBlockBarcodeRenderer() override;

    // Operations
    QSize measureContent(const RenderDeviceInfo* ptrDeviceInfo, const unsigned int uiAvailableHeightPx, const RollScriptBlockDocumentBase* ptrDocumentBlockBase) const override;
    bool render(RenderContext* ptrRenderContext, const RenderGeometry& geometry, const RollScriptBlockDocumentBase* ptrDocumentBlockBase) override;
};

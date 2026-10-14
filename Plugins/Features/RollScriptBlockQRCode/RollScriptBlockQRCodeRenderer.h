#pragma once

#include "Core/Blocks/RollScriptBlockRendererBase.h"


class RollScriptBlockQRCodeRenderer : public RollScriptBlockRendererBase
{
    Q_OBJECT

public:
    // Constructor / Destructor
    explicit RollScriptBlockQRCodeRenderer(const QString& qstrBlockPluginId, QObject* parent);
    ~RollScriptBlockQRCodeRenderer() override;

    // Operations
    QSize measureContent(const RenderDeviceInfo* ptrDeviceInfo, const unsigned int uiAvailableHeightPx, const RollScriptBlockDocumentBase* ptrDocumentBlockBase) const override;
    bool render(RenderContext* ptrRenderContext, const RenderGeometry& geometry, const RollScriptBlockDocumentBase* ptrDocumentBlockBase) override;
};

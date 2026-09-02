#pragma once

#include "Core/Blocks/RollScriptBlockRendererBase.h"


class RollScriptBlockTextRenderer: public RollScriptBlockRendererBase
{
    Q_OBJECT

public:
    // Constructor / Destructor
    explicit RollScriptBlockTextRenderer(const QString& qstrBlockPluginId, QObject* parent);
    ~RollScriptBlockTextRenderer() override;

    // Operations
    QSize measureContent(const RenderDeviceInfo* ptrDeviceInfo, const unsigned int uiAvailableHeightPx, const RollScriptBlockDocumentBase* ptrDocumentBlockBase) const override;
    bool render(RenderContext* ptrRenderContext, const RenderGeometry& geometry, const RollScriptBlockDocumentBase* ptrDocumentBlockBase) override;
};

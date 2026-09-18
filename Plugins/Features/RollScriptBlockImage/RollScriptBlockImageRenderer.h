#pragma once

#include "Core/Blocks/RollScriptBlockRendererBase.h"


class RollScriptBlockImageRenderer: public RollScriptBlockRendererBase
{
    Q_OBJECT

public:
    // Constructor / Destructor
    explicit RollScriptBlockImageRenderer(const QString& qstrBlockPluginId, QObject* parent);
    ~RollScriptBlockImageRenderer() override;

    // Operations
    QSize measureContent(const RenderDeviceInfo* ptrDeviceInfo, const unsigned int uiAvailableHeightPx, const RollScriptBlockDocumentBase* ptrDocumentBlockBase) const override;
    bool render(RenderContext* ptrRenderContext, const RenderGeometry& geometry, const RollScriptBlockDocumentBase* ptrDocumentBlockBase) override;
};

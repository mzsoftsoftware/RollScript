#pragma once

#include "Core/Blocks/RollScriptBlockRendererBase.h"


class RollScriptBlockTextRenderer: public RollScriptBlockRendererBase
{
    Q_OBJECT

public:
    RollScriptBlockTextRenderer(const QString& qstrBlockPluginId, QObject* parent);
    virtual ~RollScriptBlockTextRenderer();

    QSize measureContent(const RenderDeviceInfo* ptrDeviceInfo, const unsigned int uiAvailableHeightPx, const RollScriptBlockDocumentBase* ptrDocumentBlockBase) const override;
    bool render(RenderContext* ptrRenderContext, const RenderGeometry& geometry, const RollScriptBlockDocumentBase* ptrDocumentBlockBase) override;

private:

private:
};

#include "RollScriptBlockQRCodeRenderer.h"

#include <QSize>
#include "RollScriptBlockQRCodeDocument.h"
#include "Core/Rendering/RenderGeometry.h"
#include "Core/Rendering/RenderContext.h"


RollScriptBlockQRCodeRenderer::RollScriptBlockQRCodeRenderer(const QString& qstrBlockPluginId, QObject* parent)
    : RollScriptBlockRendererBase(qstrBlockPluginId, parent)
{
}
RollScriptBlockQRCodeRenderer::~RollScriptBlockQRCodeRenderer()
{
}


QSize RollScriptBlockQRCodeRenderer::measureContent(const RenderDeviceInfo* ptrDeviceInfo, const unsigned int uiAvailableHeightPx, const RollScriptBlockDocumentBase* ptrDocumentBlockBase) const
{
    Q_UNUSED(ptrDeviceInfo)
    Q_UNUSED(uiAvailableHeightPx)
    Q_UNUSED(ptrDocumentBlockBase)

    return QSize(0, 0);
}

bool RollScriptBlockQRCodeRenderer::render(RenderContext* ptrRenderContext, const RenderGeometry& geometry, const RollScriptBlockDocumentBase* ptrDocumentBlockBase)
{
    Q_UNUSED(ptrRenderContext)
    Q_UNUSED(geometry)
    Q_UNUSED(ptrDocumentBlockBase)

    // TODO: QR-Code-Generierung implementieren

    return true;
}

#include "RollScriptBlockBarcodeRenderer.h"

#include <QSize>
#include "RollScriptBlockBarcodeDocument.h"
#include "Core/Rendering/RenderGeometry.h"
#include "Core/Rendering/RenderContext.h"


RollScriptBlockBarcodeRenderer::RollScriptBlockBarcodeRenderer(const QString& qstrBlockPluginId, QObject* parent)
    : RollScriptBlockRendererBase(qstrBlockPluginId, parent)
{
}
RollScriptBlockBarcodeRenderer::~RollScriptBlockBarcodeRenderer()
{
}


QSize RollScriptBlockBarcodeRenderer::measureContent(const RenderDeviceInfo* ptrDeviceInfo, const unsigned int uiAvailableHeightPx, const RollScriptBlockDocumentBase* ptrDocumentBlockBase) const
{
    Q_UNUSED(ptrDeviceInfo)
    Q_UNUSED(uiAvailableHeightPx)
    Q_UNUSED(ptrDocumentBlockBase)

    return QSize(0, 0);
}

bool RollScriptBlockBarcodeRenderer::render(RenderContext* ptrRenderContext, const RenderGeometry& geometry, const RollScriptBlockDocumentBase* ptrDocumentBlockBase)
{
    Q_UNUSED(ptrRenderContext)
    Q_UNUSED(geometry)
    Q_UNUSED(ptrDocumentBlockBase)

    // TODO: Barcode-Generierung implementieren

    return true;
}

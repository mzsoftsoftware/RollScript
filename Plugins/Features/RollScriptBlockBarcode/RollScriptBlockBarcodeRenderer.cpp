#include "RollScriptBlockBarcodeRenderer.h"

#include <QSize>
#include "RollScriptBlockBarcodeDocument.h"
#include "Core/Rendering/RenderGeometry.h"
#include "Core/Rendering/RenderContext.h"
#include "ZXingQt.h"


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

    const RollScriptBlockBarcodeDocument* ptrDocumentBlockBarcode = dynamic_cast<const RollScriptBlockBarcodeDocument*>(ptrDocumentBlockBase);
    ZXingQt::Barcode barcode = ZXingQt::Barcode::fromText(ptrDocumentBlockBarcode->text(), ZXingQt::BarcodeFormat::Code128);
    QImage image = barcode.toImage(ZXingQt::WriterOptions().scale(4));
    QImage imageScaled = image.scaledToHeight(uiAvailableHeightPx);

    return imageScaled.size();
}

bool RollScriptBlockBarcodeRenderer::render(RenderContext* ptrRenderContext, const RenderGeometry& geometry, const RollScriptBlockDocumentBase* ptrDocumentBlockBase)
{
    const RollScriptBlockBarcodeDocument* ptrDocumentBlockBarcode = dynamic_cast<const RollScriptBlockBarcodeDocument*>(ptrDocumentBlockBase);
    ZXingQt::Barcode barcode = ZXingQt::Barcode::fromText(ptrDocumentBlockBarcode->text(), ZXingQt::BarcodeFormat::Code128);
    QImage image = barcode.toImage(ZXingQt::WriterOptions().scale(4));
    QImage imageScaled = image.scaledToHeight(geometry.rectContent().height());

    ptrRenderContext->painter()->drawImage(geometry.rectContent().topLeft(), imageScaled);

    return true;
}

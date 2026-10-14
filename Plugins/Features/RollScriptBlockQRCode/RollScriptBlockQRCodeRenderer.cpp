#include "RollScriptBlockQRCodeRenderer.h"

#include <QSize>
#include "RollScriptBlockQRCodeDocument.h"
#include "Core/Rendering/RenderGeometry.h"
#include "Core/Rendering/RenderContext.h"
#include "ZXingQt.h"


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

    const RollScriptBlockQRCodeDocument* ptrDocumentBlockQrCode = dynamic_cast<const RollScriptBlockQRCodeDocument*>(ptrDocumentBlockBase);
    ZXingQt::Barcode qrcode = ZXingQt::Barcode::fromText(ptrDocumentBlockQrCode->text(), ZXingQt::BarcodeFormat::QRCode, QStringLiteral("ecLevel=H"));
    QImage image = qrcode.toImage(ZXingQt::WriterOptions().scale(4));
    QImage imageScaled = image.scaledToHeight(uiAvailableHeightPx);

    return imageScaled.size();
}

bool RollScriptBlockQRCodeRenderer::render(RenderContext* ptrRenderContext, const RenderGeometry& geometry, const RollScriptBlockDocumentBase* ptrDocumentBlockBase)
{
    const RollScriptBlockQRCodeDocument* ptrDocumentBlockQrCode = dynamic_cast<const RollScriptBlockQRCodeDocument*>(ptrDocumentBlockBase);
    ZXingQt::Barcode qrcode = ZXingQt::Barcode::fromText(ptrDocumentBlockQrCode->text(), ZXingQt::BarcodeFormat::QRCode, QStringLiteral("ecLevel=H"));
    QImage image = qrcode.toImage(ZXingQt::WriterOptions().scale(4));
    QImage imageScaled = image.scaledToHeight(geometry.rectContent().height());

    ptrRenderContext->painter()->drawImage(geometry.rectContent().topLeft(), imageScaled);

    return true;
}

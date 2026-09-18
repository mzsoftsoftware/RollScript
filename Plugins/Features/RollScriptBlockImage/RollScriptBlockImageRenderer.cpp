#include "RollScriptBlockImageRenderer.h"

#include <QSize>
#include <QFontMetrics>
#include <QRect>
#include "RollScriptBlockImageDocument.h"
#include "Core/Rendering/RenderGeometry.h"
#include "Core/Rendering/RenderContext.h"


RollScriptBlockImageRenderer::RollScriptBlockImageRenderer(const QString& qstrBlockPluginId, QObject* parent)
    : RollScriptBlockRendererBase(qstrBlockPluginId, parent)
{
}
RollScriptBlockImageRenderer::~RollScriptBlockImageRenderer()
{
}


QSize RollScriptBlockImageRenderer::measureContent(const RenderDeviceInfo* ptrDeviceInfo, const unsigned int uiAvailableHeightPx, const RollScriptBlockDocumentBase* ptrDocumentBlockBase) const
{
    Q_ASSERT(ptrDeviceInfo);
    Q_ASSERT(ptrDocumentBlockBase);

    const RollScriptBlockImageDocument* ptrDocumentBlockImage = dynamic_cast<const RollScriptBlockImageDocument*>(ptrDocumentBlockBase);

    QImage imageScaled;
    if(!ptrDocumentBlockImage->fileName().isEmpty())
    {
        QImage image(ptrDocumentBlockImage->fileName());
        if(!image.isNull())
        {
            imageScaled = image.scaledToHeight(uiAvailableHeightPx, Qt::SmoothTransformation);
        }
    }

    return imageScaled.size();
}

bool RollScriptBlockImageRenderer::render(RenderContext* ptrRenderContext, const RenderGeometry& geometry, const RollScriptBlockDocumentBase* ptrDocumentBlockBase)
{
    Q_ASSERT(ptrRenderContext);
    Q_ASSERT(ptrDocumentBlockBase);

    QRect rectDraw = geometry.rectContent();

    const RollScriptBlockImageDocument* ptrDocumentBlockImage = dynamic_cast<const RollScriptBlockImageDocument*>(ptrDocumentBlockBase);
    if(!ptrDocumentBlockImage->fileName().isEmpty())
    {
        QImage image(ptrDocumentBlockImage->fileName());
        if(!image.isNull())
        {
            QImage imageScaled = image.scaled(rectDraw.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

            ptrRenderContext->painter()->drawImage(rectDraw.topLeft(), imageScaled);
        }
    }

    return true;
}
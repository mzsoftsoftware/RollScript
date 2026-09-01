#include "RollScriptBlockTextRenderer.h"

#include <QSize>
#include <QFontMetrics>
#include <QRect>
#include "RollScriptBlockTextDocument.h"
#include "RollScriptBlockTextLineDocument.h"
#include "Core/Rendering/RenderGeometry.h"
#include "Core/Rendering/RenderContext.h"


RollScriptBlockTextRenderer::RollScriptBlockTextRenderer(const QString& qstrBlockPluginId, QObject* parent)
    : RollScriptBlockRendererBase(qstrBlockPluginId, parent)
{
}
RollScriptBlockTextRenderer::~RollScriptBlockTextRenderer()
{
}


QSize RollScriptBlockTextRenderer::measureContent(const RenderDeviceInfo* ptrDeviceInfo, const unsigned int uiAvailableHeightPx, const RollScriptBlockDocumentBase* ptrDocumentBlockBase) const
{
    Q_ASSERT(ptrDeviceInfo);
    Q_ASSERT(ptrDocumentBlockBase);

    const RollScriptBlockTextDocument* ptrDocumentBlockText = dynamic_cast<const RollScriptBlockTextDocument*>(ptrDocumentBlockBase);

    int iWidth = 0;
    int iHeight = 0;

    for(int index=0; index<ptrDocumentBlockText->lineCount(); index++)
    {
        const RollScriptBlockTextLineDocument* ptrBlockTextLine = ptrDocumentBlockText->textLine(index);
        if(ptrBlockTextLine->lineActive())
        {
            QFontMetrics fm(ptrBlockTextLine->lineFont());

            QRect boundingRect = fm.boundingRect(ptrBlockTextLine->lineText());

            iWidth = qMax(iWidth, boundingRect.width());
            iHeight += boundingRect.height();
        }
    }

    return QSize(iWidth, iHeight);
}

bool RollScriptBlockTextRenderer::render(RenderContext* ptrRenderContext, const RenderGeometry& geometry, const RollScriptBlockDocumentBase* ptrDocumentBlockBase)
{
    Q_ASSERT(ptrRenderContext);
    Q_ASSERT(ptrDocumentBlockBase);

    QRect rectDraw = geometry.rectContent();
    ptrRenderContext->painter()->drawRect(rectDraw);

    const RollScriptBlockTextDocument* ptrDocumentBlockText = dynamic_cast<const RollScriptBlockTextDocument*>(ptrDocumentBlockBase);
    for(int index=0; index<ptrDocumentBlockText->lineCount(); index++)
    {
        const RollScriptBlockTextLineDocument* ptrBlockTextLine = ptrDocumentBlockText->textLine(index);
        if(ptrBlockTextLine->lineActive())
        {
            ptrRenderContext->painter()->setFont(ptrBlockTextLine->lineFont());
            int drawFlags = ptrBlockTextLine->lineAlignment() | Qt::AlignTop | Qt::TextSingleLine;

            ptrRenderContext->painter()->drawText(rectDraw, drawFlags, ptrBlockTextLine->lineText());

            QFontMetrics fm(ptrBlockTextLine->lineFont());
            rectDraw.adjust(0, fm.height(), 0, 0);
        }
    }

    return true;
}
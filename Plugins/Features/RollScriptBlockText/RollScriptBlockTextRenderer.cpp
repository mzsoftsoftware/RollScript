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

            int iLineWidth = fm.horizontalAdvance(ptrBlockTextLine->lineText());
            int iLineHeight = fm.height();

            iWidth = qMax(iWidth, iLineWidth);
            iHeight += iLineHeight;
        }
    }

    return QSize(iWidth, iHeight);
}

bool RollScriptBlockTextRenderer::render(RenderContext* ptrRenderContext, const RenderGeometry& geometry, const RollScriptBlockDocumentBase* ptrDocumentBlockBase)
{
    Q_ASSERT(ptrRenderContext);
    Q_ASSERT(ptrDocumentBlockBase);

    QRect rectDraw = geometry.rectContent();

    const RollScriptBlockTextDocument* ptrDocumentBlockText = dynamic_cast<const RollScriptBlockTextDocument*>(ptrDocumentBlockBase);
    for(int index=0; index<ptrDocumentBlockText->lineCount(); index++)
    {
        const RollScriptBlockTextLineDocument* ptrBlockTextLine = ptrDocumentBlockText->textLine(index);
        if(ptrBlockTextLine->lineActive())
        {
            QFont font = ptrBlockTextLine->lineFont();
            QFontMetrics fm(font);

            ptrRenderContext->painter()->setFont(font);

            int drawFlags = ptrBlockTextLine->lineAlignment() | Qt::AlignTop | Qt::TextSingleLine;

            QString qstrText = ptrBlockTextLine->lineText();
            QRect textBoundingRect = fm.boundingRect(rectDraw, drawFlags, qstrText);

            ptrRenderContext->painter()->drawText(rectDraw, drawFlags, qstrText);

            rectDraw.adjust(0, fm.height(), 0, 0);
        }
    }

    return true;
}
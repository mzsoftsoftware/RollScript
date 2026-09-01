#include "RenderLayout.h"

#include <QRect>

#include "Document/RollScriptDocument.h"
#include "Document/RollScriptDocumentSettings.h"
#include "Core/Blocks/RollScriptBlockDocumentBase.h"
#include "Core/Blocks/RollScriptBlockRendererBase.h"
#include "Rendering/RenderDeviceInfo.h"


RenderLayout::RenderLayout(QObject* parent)
    : QObject(parent)
{
}

void RenderLayout::reset()
{
    m_vecRenderGeometries.clear();
    m_sizeRendering = QSize();
    m_bClipping = false;

    m_uiHeightPx = 0;
    m_uiLengthPx = 0;
    m_uiLengthMinPx = 0;
    m_marginsPx = QMargins();
}

bool RenderLayout::create(const RollScriptDocument* ptrDocument, const RenderDeviceInfo* ptrRenderDeviceInfo)
{
    Q_ASSERT(ptrDocument);
    Q_ASSERT(ptrRenderDeviceInfo);

    if( ptrDocument->settings()->marginsMm().top() < ptrRenderDeviceInfo->minimumMarginTopMm() )
        return false;
    if( ptrDocument->settings()->marginsMm().bottom() < ptrRenderDeviceInfo->minimumMarginBottomMm() )
        return false;

    m_marginsPx = ptrRenderDeviceInfo->convertMmToPx(ptrDocument->settings()->marginsMm());

    m_uiLengthPx = m_marginsPx.left();;
    m_uiLengthMinPx = ptrRenderDeviceInfo->convertMmToPx(ptrDocument->settings()->minimumLengthMm());
    m_uiHeightPx = ptrRenderDeviceInfo->heightPx();

    return true;
}

bool RenderLayout::addBlock(const RollScriptBlockDocumentBase* ptrBlockDocument, RollScriptBlockRendererBase* ptrBlockRenderer, const RenderDeviceInfo* ptrRenderDeviceInfo)
{
    Q_ASSERT(ptrBlockDocument);
    Q_ASSERT(ptrBlockRenderer);
    Q_ASSERT(ptrRenderDeviceInfo);

    m_uiAvailableHeight = m_uiHeightPx - m_marginsPx.top() - m_marginsPx.bottom();
    QMargins marginsBlockPx = ptrRenderDeviceInfo->convertMmToPx(ptrBlockDocument->marginsMm());
    int availableContentHeight = m_uiAvailableHeight - marginsBlockPx.top() - marginsBlockPx.bottom();

    QSize sizeContent = ptrBlockRenderer->measureContent(ptrRenderDeviceInfo, availableContentHeight, ptrBlockDocument);
    QSize checkedContentSize = sizeContent;
    if(sizeContent.height() > availableContentHeight )
    {
        m_bClipping = true;
        checkedContentSize.setHeight(availableContentHeight);
    }

    QSize sizeBlock(checkedContentSize.width() + marginsBlockPx.left() + marginsBlockPx.right(),
                    checkedContentSize.height() + marginsBlockPx.top() + marginsBlockPx.bottom());

    QRect rectBlock(m_uiLengthPx, m_marginsPx.top(), sizeBlock.width(), sizeBlock.height());

    QRect rectContent(rectBlock.left() + marginsBlockPx.left(),
                      rectBlock.top() + marginsBlockPx.top(),
                      checkedContentSize.width(),
                      checkedContentSize.height());

    RenderGeometry blockGeometry(ptrBlockDocument, ptrBlockRenderer);
    blockGeometry.setRectBlock(rectBlock);
    blockGeometry.setRectContent(rectContent);

    m_vecRenderGeometries.append(blockGeometry);
    m_uiLengthPx += sizeBlock.width();

    return true;
}

bool RenderLayout::finalize()
{
    m_uiLengthPx += m_marginsPx.right() + 1;
    if(m_uiLengthPx < m_uiLengthMinPx)
        m_uiLengthPx= m_uiLengthMinPx;

    m_sizeRendering = QSize(m_uiLengthPx, m_uiHeightPx);

    return true;
}

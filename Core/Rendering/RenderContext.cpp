#include "RenderContext.h"


RenderContext::RenderContext(QObject* parent)
    : QObject(parent)
{
    m_ptrPainter = new QPainter();
    m_ptrPainter->setPen(Qt::black);
}

void RenderContext::reset()
{
    if(m_bPainterActive)
    {
        m_ptrPainter->end();
        m_bPainterActive = false;
    }

    m_image = QImage();
    m_bClipped = false;
}

bool RenderContext::createImage(const QSize& size)
{
    Q_ASSERT(!m_bPainterActive);

    if(size.isEmpty())
    {
        ROLLSCRIPT_ERROR(tr("RenderContextError"), QStringLiteral("size.isEmpty in createImage."));
        return false;
    }

    m_image = QImage(size, QImage::Format_Grayscale8);
    m_image.fill(Qt::white);

    m_ptrPainter->begin(&m_image);
    m_bPainterActive = true;

    return true;
}

bool RenderContext::finishImage()
{
    if(m_bPainterActive)
    {
        m_ptrPainter->end();
        m_bPainterActive = false;
    }

    return true;
}

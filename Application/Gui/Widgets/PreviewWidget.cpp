#include "PreviewWidget.h"

#include <QTimer>
#include <QPainter>

#include "Document/RollScriptDocument.h"
#include "Rendering/RollScriptRenderer.h"


PreviewWidget::PreviewWidget(QWidget* parent)
    : QWidget{parent}
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setFixedHeight(100);

    m_ptrTimerUpdate = new QTimer(this);
    m_ptrTimerUpdate->setSingleShot(true);
    m_ptrTimerUpdate->setInterval(100);
    connect(m_ptrTimerUpdate, &QTimer::timeout, this, &PreviewWidget::slot_TimerUpdate);
}
PreviewWidget::~PreviewWidget()
{
    m_ptrTimerUpdate->stop();
}

void PreviewWidget::setRollScriptRenderer(RollScriptRenderer* ptrRenderer)
{
    Q_ASSERT(ptrRenderer);
    Q_ASSERT(!m_ptrRenderer);

    m_ptrRenderer = ptrRenderer;
}
void PreviewWidget::setRollScriptDocument(RollScriptDocument* ptrDocument)
{
    Q_ASSERT(ptrDocument);
    Q_ASSERT(!m_ptrDocument);

    m_ptrDocument = ptrDocument;
    connect(m_ptrDocument, &RollScriptDocument::documentModifiedChanged, this, &PreviewWidget::slot_RollScriptDocument_Changed);
}
void PreviewWidget::slot_RollScriptDocument_Changed()
{
    if(m_ptrRenderer && m_ptrDocument)
    {
        m_ptrTimerUpdate->start();
    }
}
void PreviewWidget::slot_TimerUpdate()
{
    Q_ASSERT(m_ptrRenderer);

    if(!m_ptrRenderer->render())
        return;

    m_imagePreview = m_ptrRenderer->image();

    update();
}

void PreviewWidget::paintEvent(QPaintEvent* ptrEvent)
{
    if(m_imagePreview.isNull())
    {
        QWidget::paintEvent(ptrEvent);
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    QRect rectPreview = rect().adjusted(0, 0, -1, -1);
    painter.setPen(QPen(Qt::red, 1, Qt::SolidLine));
    painter.drawRect(rectPreview);

    QRect rectImage = rectPreview.adjusted(2, 2, -1, -1);
    QImage imagePreview = m_imagePreview.scaledToHeight(rectImage.height(), Qt::SmoothTransformation);
    painter.drawImage(rectImage.left(), rectImage.top(), imagePreview);

    QWidget::paintEvent(ptrEvent);
}

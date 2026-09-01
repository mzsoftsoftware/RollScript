#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"

#include <QSize>
#include <QImage>
#include <QPainter>


class RenderContext : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT

public:
    RenderContext(QObject* parent);

    // Getter
    const QImage& image() const             { return m_image; }
    QPainter* painter() const               { return m_ptrPainter; }

    // Functions
    void reset();
    bool createImage(const QSize& size);
    bool finishImage();

private:
    QImage m_image;
    QPainter* m_ptrPainter = nullptr;

    bool m_bPainterActive = false;
    bool m_bClipped = false;
};

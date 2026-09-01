#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"

#include <QVector>
#include <QSize>
#include "Core/Rendering/RenderGeometry.h"

class RollScriptDocument;
class RollScriptBlockDocumentBase;
class RollScriptBlockRendererBase;

class RenderDeviceInfo;


class RenderLayout : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT

public:
    RenderLayout(QObject* parent);

    void reset();
    bool create(const RollScriptDocument* ptrDocument, const RenderDeviceInfo* ptrRenderDeviceInfo);
    bool addBlock(const RollScriptBlockDocumentBase* ptrBlockDocument, RollScriptBlockRendererBase* ptrBlockRenderer, const RenderDeviceInfo* ptrRenderDeviceInfo);
    bool finalize();

    // Getter
    const QSize& renderSize() const { return m_sizeRendering; }
    const QVector<RenderGeometry>& renderGeometries() const    { return m_vecRenderGeometries; }

private:
    QVector<RenderGeometry> m_vecRenderGeometries;
    QSize m_sizeRendering;
    bool m_bClipping = false;

    unsigned int m_uiAvailableHeight;
    unsigned int m_uiHeightPx;
    unsigned int m_uiLengthPx;       // Current calculated length, starts with global margin, increases with every block
    unsigned int m_uiLengthMinPx;
    QMargins m_marginsPx;
};

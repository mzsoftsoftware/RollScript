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
    explicit RenderLayout(QObject* parent);
    ~RenderLayout() override;

    // Getter
    const QSize& renderSize() const { return m_sizeRendering; }
    const QVector<RenderGeometry>& renderGeometries() const    { return m_qvecRenderGeometries; }

    // Operations
    void reset();
    bool create(const RollScriptDocument* ptrDocument, const RenderDeviceInfo* ptrRenderDeviceInfo);
    bool addBlock(const RollScriptBlockDocumentBase* ptrBlockDocument, RollScriptBlockRendererBase* ptrBlockRenderer, const RenderDeviceInfo* ptrRenderDeviceInfo);
    bool finalize();

private:
    QVector<RenderGeometry> m_qvecRenderGeometries;
    QSize m_sizeRendering;
    bool m_bClipping = false;

    unsigned int m_uiAvailableHeight = 0;
    unsigned int m_uiHeightPx = 0;
    unsigned int m_uiLengthPx = 0;       // Current calculated length, starts with global margin, increases with every block
    unsigned int m_uiLengthMinPx = 0;
    QMargins m_marginsPx;
};

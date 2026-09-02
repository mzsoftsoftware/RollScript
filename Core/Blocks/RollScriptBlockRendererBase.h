#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"

class RenderContext;
class RenderGeometry;
class RenderDeviceInfo;
class RollScriptBlockDocumentBase;


class RollScriptBlockRendererBase : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT

public:
    // Constructor / Destructor
    explicit RollScriptBlockRendererBase(const QString& qstrBlockPluginId, QObject* parent);
    ~RollScriptBlockRendererBase() override;

    // Operations
    virtual QSize measureContent(const RenderDeviceInfo* ptrDeviceInfo, const unsigned int uiAvailableHeightPx, const RollScriptBlockDocumentBase* ptrDocumentBlockBase) const = 0;
    virtual bool render(RenderContext* ptrRenderContext, const RenderGeometry& geometry, const RollScriptBlockDocumentBase* ptrDocumentBlockBase) = 0;

protected:
    QString m_qstrBlockPluginId;
};

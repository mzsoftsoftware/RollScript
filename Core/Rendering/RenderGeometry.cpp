#include "Core/Rendering/RenderGeometry.h"


RenderGeometry::RenderGeometry(const RollScriptBlockDocumentBase* ptrBlockDocument, RollScriptBlockRendererBase* ptrBlockRenderer)
    : m_ptrBlockDocument(ptrBlockDocument)
    , m_ptrBlockRenderer(ptrBlockRenderer)
{
}
RenderGeometry::~RenderGeometry()
{
}

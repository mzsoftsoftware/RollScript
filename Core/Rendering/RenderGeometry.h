#pragma once

#include <QRect>

class RollScriptBlockDocumentBase;
class RollScriptBlockRendererBase;


class RenderGeometry
{
public:
    // Constructor / Destructor
    explicit RenderGeometry(const RollScriptBlockDocumentBase* ptrBlockDocument, RollScriptBlockRendererBase* ptrBlockRenderer);
    virtual ~RenderGeometry();

    // Getter
    const RollScriptBlockDocumentBase* blockDocument() const    { return m_ptrBlockDocument; }
    RollScriptBlockRendererBase* blockRenderer() const          { return m_ptrBlockRenderer; }
    const QRect& rectBlock() const                              { return m_rectBlock; }
    const QRect& rectContent() const                            { return m_rectContent; }

    // Setter
    void setRectBlock(const QRect& rectBlock)                   { m_rectBlock = rectBlock; }
    void setRectContent(const QRect& rectContent)               { m_rectContent = rectContent; }

private:
    const RollScriptBlockDocumentBase* m_ptrBlockDocument;
    RollScriptBlockRendererBase* m_ptrBlockRenderer;

    QRect m_rectBlock;
    QRect m_rectContent;
};

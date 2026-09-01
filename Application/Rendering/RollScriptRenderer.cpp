#include "RollScriptRenderer.h"

#include "Printers/PrinterManager.h"
#include "Core/Printers/PrinterInstance.h"

#include "Features/FeatureBlockManager.h"

#include "RenderDeviceInfo.h"
#include "RenderLayout.h"
#include "Document/RollScriptDocument.h"
#include "Document/RollScriptDocumentSettings.h"
#include "Document/RollScriptDocumentBlocks.h"
#include "Core/Blocks/RollScriptBlockDocumentBase.h"
#include "Core/Blocks/RollScriptBlockRendererBase.h"
#include "Core/Rendering/RenderContext.h"


RollScriptRenderer::RollScriptRenderer(PrinterManager* ptrPrinterManager, FeatureBlockManager* ptrFeatureBlockManager, QObject *parent)
    : QObject{parent}
    , m_ptrPrinterManager(ptrPrinterManager)
    , m_ptrFeatureBlockManager(ptrFeatureBlockManager)
{
    Q_ASSERT(m_ptrPrinterManager);
    Q_ASSERT(m_ptrFeatureBlockManager);

    m_ptrRenderDeviceInfo = new RenderDeviceInfo(this);
    m_ptrRenderLayout = new RenderLayout(this);
    m_ptrRenderContext = new RenderContext(this);
}
RollScriptRenderer::~RollScriptRenderer()
{
    m_hashFeatureBlockRenderers.clear();
}

const QImage& RollScriptRenderer::image() const
{
    return m_ptrRenderContext->image();
}

bool RollScriptRenderer::init()
{
    Q_ASSERT(m_ptrFeatureBlockManager);

    const QStringList qstrFeatureBlockIds = m_ptrFeatureBlockManager->availableFeatureBlockIds();
    for(const QString& qstrFeatureBlockId : qstrFeatureBlockIds)
    {
        RollScriptBlockRendererBase* ptrRenderer = m_ptrFeatureBlockManager->createFeatureBlockRenderer(qstrFeatureBlockId, this);
        Q_ASSERT(ptrRenderer);

        m_hashFeatureBlockRenderers.insert(qstrFeatureBlockId, ptrRenderer);
    }


    return true;
}
void RollScriptRenderer::setRollScriptDocument(const RollScriptDocument* ptrDocument)
{
    Q_ASSERT(ptrDocument);
    Q_ASSERT(!m_ptrDocument);

    m_ptrDocument = ptrDocument;
}

bool RollScriptRenderer::render()
{
    Q_ASSERT(m_ptrDocument);

    reset();
    if(!createDeviceInfo())
    {
        return false;
    }

    if(!createLayout())
    {
        return false;
    }

    if(!createRendering())
    {
        return false;
    }

    return true;
}

void RollScriptRenderer::reset()
{
    m_ptrRenderDeviceInfo->reset();
    m_ptrRenderLayout->reset();
    m_ptrRenderContext->reset();
}
bool RollScriptRenderer::createDeviceInfo()
{
    QString qstrPrinterMediaId = m_ptrDocument->settings()->printerMediaId();
    if(qstrPrinterMediaId.isEmpty())
        return false;

    const PrinterInstance* ptrPrinterInstance = m_ptrPrinterManager->currentPrinter();
    if(!ptrPrinterInstance)
    {
        ROLLSCRIPT_ERROR(tr("RollScriptRendererCreateDeviceInfoError"), QStringLiteral("ptrPrinterInstance is null."));
        emit renderingError();
        return false;
    }

    const PrinterMedia* ptrPrinterMedia = ptrPrinterInstance->media(qstrPrinterMediaId);
    if(!ptrPrinterMedia)
    {
        ROLLSCRIPT_ERROR(tr("RollScriptRendererCreateDeviceInfoError"), QStringLiteral("ptrPrinterMedia is null."));
        emit renderingError();
        return false;
    }

    if(!m_ptrRenderDeviceInfo->create(ptrPrinterInstance, ptrPrinterMedia))
    {
        ROLLSCRIPT_ERROR_CAUSE(tr("RollScriptRendererCreateDeviceInfoError"), QStringLiteral("error in m_renderDeviceInfo.create."), m_ptrRenderDeviceInfo->takeError());
        emit renderingError();
        return false;
    }

    return true;
}
bool RollScriptRenderer::createLayout()
{
    if(!m_ptrRenderLayout->create(m_ptrDocument, m_ptrRenderDeviceInfo))
    {
        ROLLSCRIPT_ERROR_CAUSE(tr("RollScriptRendererCreateLayoutError"), QStringLiteral("error in m_renderLayout.create."), m_ptrRenderLayout->takeError());
        emit renderingError();
        return false;
    }

    const QVector<RollScriptBlockDocumentBase*>& vecDocumentBlocks = m_ptrDocument->blocks()->documentBlocks();
    for(const RollScriptBlockDocumentBase* ptrBlockDocument : vecDocumentBlocks)
    {
        Q_ASSERT(ptrBlockDocument);

        RollScriptBlockRendererBase* ptrBlockRenderer = m_hashFeatureBlockRenderers[ptrBlockDocument->blockPluginId()];
        Q_ASSERT(ptrBlockRenderer);

        if(!m_ptrRenderLayout->addBlock(ptrBlockDocument, ptrBlockRenderer, m_ptrRenderDeviceInfo))
        {
            ROLLSCRIPT_ERROR_CAUSE(tr("RollScriptRendererCreateLayoutError"), QStringLiteral("error in m_renderLayout.addBlock."), m_ptrRenderLayout->takeError());
            emit renderingError();
            return false;
        }
    }

    if(!m_ptrRenderLayout->finalize())
    {
        ROLLSCRIPT_ERROR_CAUSE(tr("RollScriptRendererCreateLayoutError"), QStringLiteral("error in m_renderLayout.finalize."), m_ptrRenderLayout->takeError());
        emit renderingError();
        return false;
    }

    return true;
}
bool RollScriptRenderer::createRendering()
{
    if(!m_ptrRenderContext->createImage(m_ptrRenderLayout->renderSize()))
    {
        ROLLSCRIPT_ERROR_CAUSE(tr("RollScriptRendererCreateRenderingError"), QStringLiteral("error in m_renderContext.createImage."), m_ptrRenderContext->takeError());
        emit renderingError();
        return false;
    }

    for(const RenderGeometry& geometry : m_ptrRenderLayout->renderGeometries())
    {
        if(!geometry.blockRenderer()->render(m_ptrRenderContext, geometry, geometry.blockDocument()))
        {
            ROLLSCRIPT_ERROR_CAUSE(tr("RollScriptRendererCreateRenderingError"), QStringLiteral("error in blockRenderer.render."), m_ptrRenderContext->takeError());
            emit renderingError();
            return false;
        }
    }

    if(!m_ptrRenderContext->finishImage())
    {
        ROLLSCRIPT_ERROR_CAUSE(tr("RollScriptRendererCreateRenderingError"), QStringLiteral("error in m_renderContext.finalize."), m_ptrRenderContext->takeError());
        emit renderingError();
        return false;
    }

    return true;
}

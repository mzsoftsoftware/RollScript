#include "DLP350PrinterWorker.h"

#include <QThread>
#include "DLP350PrinterJob.h"


DymoLabelPoint350PrinterWorker::DymoLabelPoint350PrinterWorker(QObject *parent)
    : QObject{parent}
{
}

DymoLabelPoint350PrinterWorker::~DymoLabelPoint350PrinterWorker()
{
    qDeleteAll(m_queue);
    m_queue.clear();
}

void DymoLabelPoint350PrinterWorker::enqueueJob(DymoLabelPoint350PrinterJob* ptrJob)
{
    Q_ASSERT(ptrJob);

    m_queue.enqueue(ptrJob);

    if(!m_bProcessing)
    {
        QMetaObject::invokeMethod(this, "slotProcessQueue", Qt::QueuedConnection);
    }
}

void DymoLabelPoint350PrinterWorker::slotProcessQueue()
{
    if(m_bProcessing)
        return;

    if(m_queue.isEmpty())
        return;

    m_bProcessing = true;

    DymoLabelPoint350PrinterJob* ptrJob = m_queue.dequeue();
    if(!ptrJob->execute())
    {
        m_ptrLastError = ptrJob->takeError();
    }
    delete ptrJob;

    m_bProcessing = false;

    if(!m_queue.isEmpty())
        QMetaObject::invokeMethod(this, "slotProcessQueue", Qt::QueuedConnection);
}

RollScriptError* DymoLabelPoint350PrinterWorker::jobError()
{
    RollScriptError* ptr = m_ptrLastError;
    m_ptrLastError = nullptr;

    return ptr;
}

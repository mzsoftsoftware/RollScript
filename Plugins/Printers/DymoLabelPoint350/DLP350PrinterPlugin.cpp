#include "DLP350PrinterPlugin.h"

#include <QThread>
#include <QTimer>

#include "DLP350PrinterWorker.h"
#include "DLP350PrinterMedia.h"

#include "Core/USB/PrinterInstanceUSB.h"
#include "Core/USB/USBDeviceInfo.h"

#include "DLP350PrinterJobAlive.h"
#include "DLP350PrinterJobPrint.h"


DymoLabelPoint350PrinterPlugin::DymoLabelPoint350PrinterPlugin(QObject* parent)
    : IPrinterPlugin(parent)
{
    m_ptrWorkerThread = new QThread(this);
    m_ptrWorker = new DymoLabelPoint350PrinterWorker();
    m_ptrWorker->moveToThread(m_ptrWorkerThread);

    connect(this, &DymoLabelPoint350PrinterPlugin::enqueueJob, m_ptrWorker, &DymoLabelPoint350PrinterWorker::enqueueJob, Qt::QueuedConnection);
    connect(m_ptrWorkerThread, &QThread::finished, m_ptrWorker, &QObject::deleteLater);

    m_ptrWorkerThread->start();

    m_ptrTimerAlive = new QTimer(this);
    connect(m_ptrTimerAlive, &QTimer::timeout, this, &DymoLabelPoint350PrinterPlugin::slot_timerAlive);
}
DymoLabelPoint350PrinterPlugin::~DymoLabelPoint350PrinterPlugin()
{
    m_ptrWorkerThread->quit();
    m_ptrWorkerThread->wait();

    delete m_ptrWorkerThread;
    m_ptrWorkerThread = nullptr;
    m_ptrWorker = nullptr;
}

bool DymoLabelPoint350PrinterPlugin::supportsUsb(const USBDeviceInfo* ptrDevice) const
{
    if(!ptrDevice)
    {
        return false;
    }

    // Mein fixer Drucker : PID=0x0015, VID=0x0922
    return ptrDevice->vendorId() == 0x0922 && ptrDevice->productId() == 0x0015;
}

QList<PrinterMedia*> DymoLabelPoint350PrinterPlugin::createPrinterMedias()
{
    QList<PrinterMedia*> medias;

    // 19mm
    // 14*8 = 112px wobei nur 110px druckbar sind, 2px ist der "untere Rand".
    // Image = 135px
    // ImageOffsetTop=20
    // ImageOffsetBottom = 5
    // ==> Image=135-25 = 110...
    {
        DymoLabelPoint350PrinterMedia* ptrMedia = new DymoLabelPoint350PrinterMedia(QStringLiteral("DymoLabelPoint350_19mm"), QStringLiteral("19 mm"), this);
        ptrMedia->setMediaDataMm(19.0, 2.9, 0.8, 25.0);
        ptrMedia->setMediaDataPx(180, 0, 0+(13*8)+6);
        medias.append(ptrMedia);
    }

    // 12mm
    // 12*8 = 96px wobei 12px Rand oben sind, 77px druckbar, 7px ist der "untere Rand".
    // Image = 85px
    // ImageOffsetTop=3
    // ImageOffsetBottom=5
    // ==> Image= 85-8 = 77...
    {
        DymoLabelPoint350PrinterMedia* ptrMedia = new DymoLabelPoint350PrinterMedia(QStringLiteral("DymoLabelPoint350_12mm"), QStringLiteral("12 mm"), this);
        ptrMedia->setMediaDataMm(12.0, 0.5, 0.8, 25.0);
        ptrMedia->setMediaDataPx(180, (1*8)+4, 4+(9*8)+1);
        medias.append(ptrMedia);
    }

    // 9mm
    // 11*8 = 88px wobei 19px Rand oben sind, 62px druckbar, 7px ist der "untere Rand".
    // Image = 64px
    // ImageOffsetTop=1
    // ImageOffsetBottom=1
    // ==> Image= 62px !
    {
        DymoLabelPoint350PrinterMedia* ptrMedia = new DymoLabelPoint350PrinterMedia(QStringLiteral("DymoLabelPoint350_9mm"), QStringLiteral("9 mm"), this);
        ptrMedia->setMediaDataMm(9.0, 0.2, 0.2, 25.0);
        ptrMedia->setMediaDataPx(180, (2*8)+3, 5+(7*8)+1);
        medias.append(ptrMedia);
    }

    return medias;
}
PrinterDeviceInfo DymoLabelPoint350PrinterPlugin::createPrinterDeviceInfo()
{
    return PrinterDeviceInfo(180);
}

bool DymoLabelPoint350PrinterPlugin::open(PrinterInstance* ptrPrinterInstance)
{
    m_ptrPrinterInstanceUSB = qobject_cast<PrinterInstanceUSB*>(ptrPrinterInstance);
    if(!m_ptrPrinterInstanceUSB)
    {
        ROLLSCRIPT_ERROR(tr("NoPrinterInstance"), QStringLiteral("m_ptrPrinterInstanceUSB is nullptr."));
        return false;
    }

    m_ptrTimerAlive->start(5000);
    slot_timerAlive();

    return true;
}

bool DymoLabelPoint350PrinterPlugin::close()
{
    if(!m_ptrPrinterInstanceUSB)
        return true;

    if(m_ptrTimerAlive)
        m_ptrTimerAlive->stop();

    m_ptrPrinterInstanceUSB = nullptr;

    return true;
}

bool DymoLabelPoint350PrinterPlugin::print(const QImage& printImage, const PrinterMedia* ptrPrinterMedia)
{
    Q_ASSERT(m_ptrPrinterInstanceUSB);
    Q_ASSERT(m_ptrWorker);

    if(!m_ptrPrinterInstanceUSB->isConnected())
    {
        ROLLSCRIPT_ERROR(tr("PrintError"), QStringLiteral("m_ptrPrinterInstanceUSB not connected."));
        return false;
    }

    if(!ptrPrinterMedia)
    {
        ROLLSCRIPT_ERROR(tr("PrintError"), QStringLiteral("ptrPrinterMediaId is nullptr."));
        return false;
    }
    const DymoLabelPoint350PrinterMedia* ptrPluginMedia = dynamic_cast<const DymoLabelPoint350PrinterMedia*>(ptrPrinterMedia);
    if(!ptrPluginMedia)
    {
        ROLLSCRIPT_ERROR(tr("PrintError"), QStringLiteral("ptrPluginMedia is nullptr."));
        return false;
    }

    DymoLabelPoint350PrinterJobPrint* ptrJob = new  DymoLabelPoint350PrinterJobPrint(m_ptrPrinterInstanceUSB, printImage, ptrPluginMedia, createPrinterDeviceInfo());
    connect(ptrJob, &DymoLabelPoint350PrinterJobPrint::started, this, &DymoLabelPoint350PrinterPlugin::slot_PrintJob_Started);
    connect(ptrJob, &DymoLabelPoint350PrinterJobPrint::progress, this, &DymoLabelPoint350PrinterPlugin::slot_PrintJob_Progress);
    connect(ptrJob, &DymoLabelPoint350PrinterJobPrint::finished, this, &DymoLabelPoint350PrinterPlugin::slot_PrintJob_Finished);
    connect(ptrJob, &DymoLabelPoint350PrinterJobPrint::error, this, &DymoLabelPoint350PrinterPlugin::slot_PrintJob_Error);

    ptrJob->moveToThread(m_ptrWorkerThread);
    emit enqueueJob(ptrJob);

    return true;
}

void DymoLabelPoint350PrinterPlugin::slot_timerAlive()
{
    DymoLabelPoint350PrinterJobAlive* ptrJob = new  DymoLabelPoint350PrinterJobAlive(m_ptrPrinterInstanceUSB);
    connect(ptrJob, &DymoLabelPoint350PrinterJobAlive::started, this, &DymoLabelPoint350PrinterPlugin::slot_JobAlive_Started);
    connect(ptrJob, &DymoLabelPoint350PrinterJobAlive::finished, this, &DymoLabelPoint350PrinterPlugin::slot_JobAlive_Finished);
    connect(ptrJob, &DymoLabelPoint350PrinterJobAlive::error, this, &DymoLabelPoint350PrinterPlugin::slot_JobAlive_Error);

    ptrJob->moveToThread(m_ptrWorkerThread);
    emit enqueueJob(ptrJob);
}

void DymoLabelPoint350PrinterPlugin::slot_PrintJob_Started(int iSteps)
{
    emit printerPrintStarted(iSteps);
}
void DymoLabelPoint350PrinterPlugin::slot_PrintJob_Progress(int iStep)
{
    emit printerPrintProgress(iStep);
}
void DymoLabelPoint350PrinterPlugin::slot_PrintJob_Finished()
{
    emit printerPrintFinished();
}
void DymoLabelPoint350PrinterPlugin::slot_PrintJob_Error()
{
    setErrorInternal(m_ptrWorker->jobError());
    emit printerError();
}

void DymoLabelPoint350PrinterPlugin::slot_JobAlive_Started()
{
}
void DymoLabelPoint350PrinterPlugin::slot_JobAlive_Finished()
{
}
void DymoLabelPoint350PrinterPlugin::slot_JobAlive_Error()
{
    setErrorInternal(m_ptrWorker->jobError());
    emit printerError();
}






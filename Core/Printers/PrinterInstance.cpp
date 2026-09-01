#include "PrinterInstance.h"

#include "Core/Plugins/IPrinterPlugin.h"
#include "Core/Plugins/IPrinterPluginInfo.h"
#include "Core/Printers/PrinterMedia.h"


PrinterInstance::PrinterInstance(IPrinterPlugin* ptrPrinterPlugin, QObject* parent)
    : QObject{parent}
    , m_ptrPrinterPlugin(ptrPrinterPlugin)
    , m_printerDeviceInfo(ptrPrinterPlugin->createPrinterDeviceInfo())
{
    Q_ASSERT(m_ptrPrinterPlugin);

    // TASK : Braucht PrinterInstance wirklich das Icon oder besser durchreichen ?
    m_icon = ptrPrinterPlugin->printerPluginInfo()->printerIcon();

    const QList<PrinterMedia*> medias = m_ptrPrinterPlugin->createPrinterMedias();
    for(PrinterMedia* ptrMedia : medias)
    {
        Q_ASSERT(m_ptrPrinterPlugin);

        const QString qstrMediaId = ptrMedia->id();
        Q_ASSERT(!qstrMediaId.isEmpty());
        Q_ASSERT(!m_hashPrinterMedias.contains(qstrMediaId));

        m_qstrPrinterMediaIds.append(qstrMediaId);
        m_hashPrinterMedias.insert(qstrMediaId, ptrMedia);
    }

    connect(m_ptrPrinterPlugin, &IPrinterPlugin::printerError, this, &PrinterInstance::slotPrinterPluginError);
    connect(m_ptrPrinterPlugin, &IPrinterPlugin::printerPrintStarted, this, &PrinterInstance::printerPrintStarted);
    connect(m_ptrPrinterPlugin, &IPrinterPlugin::printerPrintProgress, this, &PrinterInstance::printerPrintProgress);
    connect(m_ptrPrinterPlugin, &IPrinterPlugin::printerPrintFinished, this, &PrinterInstance::printerPrintFinished);
}
PrinterInstance::~PrinterInstance()
{
    qDeleteAll(m_hashPrinterMedias);
    m_hashPrinterMedias.clear();
}

bool PrinterInstance::print(const QImage& printImage, const PrinterMedia* ptrPrinterMediaId)
{
    Q_ASSERT(m_ptrPrinterPlugin);
    if(!m_ptrPrinterPlugin->print(printImage, ptrPrinterMediaId))
    {
        ROLLSCRIPT_ERROR_CAUSE(tr("PrinterInstancePrintError"), QStringLiteral("m_ptrPrinterPlugin->print() failed."), m_ptrPrinterPlugin->takeError());
        return false;
    }

    return true;
}

void PrinterInstance::slotPrinterPluginError()
{
    setErrorInternal(m_ptrPrinterPlugin->takeError());
    emit printerError();
}

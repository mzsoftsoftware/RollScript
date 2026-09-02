#include "RenderDeviceInfo.h"

#include "Core/Printers/PrinterInstance.h"
#include "Core/Printers/PrinterMedia.h"


RenderDeviceInfo::RenderDeviceInfo(QObject* parent)
    : QObject(parent)
{
}
RenderDeviceInfo::~RenderDeviceInfo()
{
}

void RenderDeviceInfo::reset()
{
    m_dblPxPerMm = 0.0;
    m_dblMinimumMarginTopMm = 0.0;
    m_dblMinimumMarginBottomMm = 0.0;
    m_iHeightPx = 0;
}

bool RenderDeviceInfo::create(const PrinterInstance* ptrPrinterInstance, const PrinterMedia* ptrPrinterMedia)
{
    m_dblPxPerMm = static_cast<double>(ptrPrinterInstance->deviceInfo().renderDpi()) / 25.4;

    m_dblMinimumMarginTopMm = ptrPrinterMedia->constraints().marginsMinMm.top();
    m_dblMinimumMarginBottomMm = ptrPrinterMedia->constraints().marginsMinMm.bottom();
    m_iHeightPx = convertMmToPx(ptrPrinterMedia->heightMm());

    return true;
}

int RenderDeviceInfo::convertMmToPx(double dblValueMm) const
{
    return qRound(dblValueMm * m_dblPxPerMm);
}

QMargins RenderDeviceInfo::convertMmToPx(const QMarginsF& marginsMm ) const
{
    return QMargins(convertMmToPx(marginsMm.left()),
                    convertMmToPx(marginsMm.top()),
                    convertMmToPx(marginsMm.right()),
                    convertMmToPx(marginsMm.bottom()));
}

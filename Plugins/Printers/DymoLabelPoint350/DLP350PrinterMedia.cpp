#include "DLP350PrinterMedia.h"


DymoLabelPoint350PrinterMedia::DymoLabelPoint350PrinterMedia(const QString& qstrId, const QString& qstrDisplayName, QObject* parent)
    : PrinterMedia(qstrId, qstrDisplayName, parent)
{
}
DymoLabelPoint350PrinterMedia::~DymoLabelPoint350PrinterMedia()
{
}

int DymoLabelPoint350PrinterMedia::mediaHeightBytes() const
{
    int iPx = m_iHeadOffsetTopPx + m_iHeadPrintablePx;
    return (iPx+7)/8;
}

void DymoLabelPoint350PrinterMedia::setMediaDataMm(double dblHeightMm, double dblMarginTopMm, double dblMarginBottomMm, double dblLengthMinMm)
{
    m_dblHeightMm = dblHeightMm;

    m_printerMediaConstraints.marginsMinMm.setTop(dblMarginTopMm);
    m_printerMediaConstraints.marginsMinMm.setBottom(dblMarginBottomMm);
    m_printerMediaConstraints.lengthMinMm = dblLengthMinMm;
}

void DymoLabelPoint350PrinterMedia::setMediaDataPx(int iDpi, int iHeadOffsetTopPx, int iHeadPrintablePx)
{
    m_iDpi = iDpi;
    m_iHeadOffsetTopPx = iHeadOffsetTopPx;
    m_iHeadPrintablePx = iHeadPrintablePx;
}

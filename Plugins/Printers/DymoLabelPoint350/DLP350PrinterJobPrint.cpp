#include "DLP350PrinterJobPrint.h"

#include <QDebug>

#include "Core/Printers/PrinterDeviceInfo.h"
#include "DLP350PrinterMedia.h"


DymoLabelPoint350PrinterJobPrint::DymoLabelPoint350PrinterJobPrint(PrinterInstanceUSB* ptrPrinterInstanceUSB,
                                                                   const QImage& imagePrint,
                                                                   const DymoLabelPoint350PrinterMedia* ptrPrinterMedia,
                                                                   const PrinterDeviceInfo& printerDeviceInfo)
    : DymoLabelPoint350PrinterJob(ptrPrinterInstanceUSB)
    , m_imagePrint(imagePrint)
    , m_ptrPrinterMedia(ptrPrinterMedia)
    , m_printerDeviceInfo(printerDeviceInfo)
{
}
DymoLabelPoint350PrinterJobPrint::~DymoLabelPoint350PrinterJobPrint()
{
}

bool DymoLabelPoint350PrinterJobPrint::execute()
{
    QVector<QByteArray> vecByteImage;
    if(!fillDataFromImage(m_imagePrint, m_ptrPrinterMedia, vecByteImage))
    {
        return false;
    }

    emit started(vecByteImage.count());
    int iProgress = 0;

    for(const QByteArray& data : vecByteImage)
    {
        if(!sendCommand(data))
        {
            ROLLSCRIPT_ERROR_CAUSE(tr("PrintError"), QStringLiteral("sendCommand() failed"), takeError());
            return false;
        }

        iProgress++;
        emit progress(iProgress);
    }

    emit finished();

    return true;
}

bool DymoLabelPoint350PrinterJobPrint::fillDataFromImage(const QImage& printImage, const DymoLabelPoint350PrinterMedia* ptrPluginMedia, QVector<QByteArray>& vecArrData)
{
    int iHeightBytes = ptrPluginMedia->mediaHeightBytes();
    int iOffsetTopPx = ptrPluginMedia->headOffsetTopPx();
    int iPrintablePx = ptrPluginMedia->headPrintablePx();
    //int iOffsetBottomPx = (iHeightBytes*8) - iOffsetTopPx - iPrintablePx;

    //int iHeightImage = printImage.height();

    double px = static_cast<double>(m_printerDeviceInfo.renderDpi()) / 25.4;

    int iImageOffsetTop = ptrPluginMedia->constraints().marginsMinMm.top() * px;
    //int iImageOffsetBottom = ptrPluginMedia->constraints().marginsMinMm.bottom() * px;

    QByteArray arrHeader;
    arrHeader.append(char(0x1B));
    arrHeader.append('C');
    arrHeader.append(char(0));

    arrHeader.append(char(0x1B));
    arrHeader.append('D');
    arrHeader.append(char(iHeightBytes));

    vecArrData.append(arrHeader);

    int iWidthImage = printImage.width();
    //for(int iLine=0; iLine<iWidthImage; iLine++)
    for(int iLine=iWidthImage-1; iLine>=0; iLine--)
    {
        QByteArray arrLine;

        // Begin of each line
        arrLine.append(char(0x16));

        QByteArray baLine;
        if(!fillDataFromImageLine(iLine, printImage, iOffsetTopPx, iPrintablePx, iImageOffsetTop, baLine))
            return false;
        arrLine.append(baLine);

        vecArrData.append(arrLine);
    }

    int yMax = px*10; // Footer 10mm
    QByteArray arrFooter;
    for(int y=0;y<yMax;y++)
    {
        arrFooter.append(char(0x16));
        for(int x=0; x<iHeightBytes; x++)
        {
            arrFooter.append(char(0x00));
        }
        vecArrData.append(arrFooter);
        arrFooter.clear();
    }

    return true;
}
bool DymoLabelPoint350PrinterJobPrint::fillDataFromImageLine(const int iLine, const QImage& printImage, const int iEmptyBits, const int iImageBits, const int iImageLineOffset, QByteArray& baLineData)
{
    int totalBits = iEmptyBits + iImageBits;
    int totalBytes = (totalBits + 7) / 8;

    baLineData.fill(0, totalBytes);

    int iBitIndex = iEmptyBits;
    int iImageLineIndex = iImageLineOffset;

    // Bildbits
    for(int i = 0; i < iImageBits; ++i)
    {
        int iGray = qGray(printImage.pixel(iLine, iImageLineIndex));
        if(iGray < 128)
        {
            int iByteIndex = iBitIndex / 8;
            int iBitInByte = iBitIndex % 8;

            baLineData[iByteIndex] |= static_cast<char>(1 << (7 - iBitInByte));
        }
        iBitIndex++;
        iImageLineIndex++;
    }

    return true;
}

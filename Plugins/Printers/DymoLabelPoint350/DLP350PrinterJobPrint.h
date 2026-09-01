#pragma once

#include "DLP350PrinterJob.h"

#include <QImage>

class DymoLabelPoint350PrinterMedia;
#include "Core/Printers/PrinterDeviceInfo.h"
//"class PrinterDeviceInfo;


class DymoLabelPoint350PrinterJobPrint : public DymoLabelPoint350PrinterJob
{
    Q_OBJECT

public:
    explicit DymoLabelPoint350PrinterJobPrint(PrinterInstanceUSB* ptrPrinterInstanceUSB,
                                              const QImage& imagePrint,
                                              const DymoLabelPoint350PrinterMedia* ptrPrinterMedia,
                                              const PrinterDeviceInfo& ptrPrinterDeviceInfo);
    virtual ~DymoLabelPoint350PrinterJobPrint() override;

    bool execute() override;

private:
    bool fillDataFromImage(const QImage& printImage,
                           const DymoLabelPoint350PrinterMedia* ptrPluginMedia,
                           QVector<QByteArray>& vecArrData);
    bool fillDataFromImageLine(const int iLine,
                               const QImage& printImage,
                               const int iEmptyBits,
                               const int iImageBits,
                               const int iImageLineOffset,
                               QByteArray& baLineData);

private:
    const QImage m_imagePrint;
    const DymoLabelPoint350PrinterMedia* m_ptrPrinterMedia = nullptr;
    const PrinterDeviceInfo m_printerDeviceInfo;
};

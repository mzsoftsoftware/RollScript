#pragma once

#include "Core/Printers/PrinterMedia.h"


class DymoLabelPoint350PrinterMedia : public PrinterMedia
{
    Q_OBJECT

public:
    explicit DymoLabelPoint350PrinterMedia(const QString& qstrId, const QString& qstrDisplayName, QObject* parent);
    virtual ~DymoLabelPoint350PrinterMedia() override;

    // Getter

    // Setter
    void setMediaDataMm(double dblHeightMm, double dblMarginTopMm, double dblMarginBottomMm, double dblLengthMinMm);
    void setMediaDataPx(int iDpi, int iHeadOffsetTopPx, int iHeadPrintablePx);


private:
    int     m_iDpi;                 // Druckauflösung
    int     m_iHeadOffsetTopPx;     // Oberer Rand des Kopfes = Anzahl der auszulassenden Pixel
    int     m_iHeadPrintablePx;     // Nutzbare Anzahl von Pixeln

};

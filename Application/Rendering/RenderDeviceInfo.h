#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"

class PrinterInstance;
class PrinterMedia;

#include <QMargins>


class RenderDeviceInfo : public QObject, public RollScriptErrorOwner
{
public:
    // Constructor / Destructor
    explicit RenderDeviceInfo(QObject* parent);
    ~RenderDeviceInfo() override;

    // Getters
    double minimumMarginTopMm() const       { return m_dblMinimumMarginTopMm; }
    double minimumMarginBottomMm() const    { return m_dblMinimumMarginBottomMm; }

    int heightPx() const                    { return m_iHeightPx; }

    // Operations
    void reset();
    bool create(const PrinterInstance* ptrPrinterInstance, const PrinterMedia* ptrPrinterMedia);

    int convertMmToPx(double dblValueMm) const;
    QMargins convertMmToPx(const QMarginsF& marginsMm ) const;

private:
    double m_dblPxPerMm = 0.0;

    double m_dblMinimumMarginTopMm = 0.0;
    double m_dblMinimumMarginBottomMm = 0.0;

    int m_iHeightPx = 0;
};

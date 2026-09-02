#pragma once


class PrinterDeviceInfo
{
public:
    explicit PrinterDeviceInfo(const unsigned int iRenderDpi);
    virtual ~PrinterDeviceInfo();

    // Getter
    const unsigned int renderDpi() const        { return m_uiRenderDpi; }

private:
    unsigned int m_uiRenderDpi;
};

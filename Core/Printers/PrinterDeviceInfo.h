#pragma once


class PrinterDeviceInfo
{
public:
    PrinterDeviceInfo(const unsigned int iRenderDpi);

    // Getter
    const unsigned int renderDpi() const        { return m_uiRenderDpi; }

private:
    unsigned int m_uiRenderDpi;
};

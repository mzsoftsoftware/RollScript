#pragma once

#include <QObject>

struct libusb_context;


class USBManager : public QObject
{
    Q_OBJECT
public:
    explicit USBManager(QObject *parent);
    virtual ~USBManager() override;

    bool init();

    // Getter
    QString lastError() const                     { return m_qstrLastError; }

private:
    QString m_qstrLastError;

    libusb_context* m_ptrLibUsbContext = nullptr;
};

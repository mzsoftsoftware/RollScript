#pragma once

#include <QByteArray>


class IUSBConnection
{
public:

    virtual ~IUsbConnection() = default;


    virtual bool open() = 0;
    virtual void close() = 0;

    virtual bool send(const QByteArray& data) = 0;
    virtual QByteArray receive() = 0;
};
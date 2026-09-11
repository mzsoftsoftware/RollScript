#pragma once

#include <QObject>


class ILicenseProvider : public QObject
{
    Q_OBJECT

public:
    explicit ILicenseProvider(QObject* parent)
        : QObject(parent)
    {}
    virtual ~ILicenseProvider() = default;

};

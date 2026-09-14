#pragma once

class LicenseInfo;


class ILicenseProvider
{
public:
    virtual ~ILicenseProvider() = default;

    virtual QList<const LicenseInfo*> licenses() const = 0;
};

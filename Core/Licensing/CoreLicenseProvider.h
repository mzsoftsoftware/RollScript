#pragma once

#include "ILicenseProvider.h"


class CoreLicenseProvider : public ILicenseProvider
{
public:
    CoreLicenseProvider(QObject* parent);
};

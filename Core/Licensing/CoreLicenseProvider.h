#pragma once

#include <QObject>
#include "ILicenseProvider.h"

#include <QList>


class CoreLicenseProvider : public QObject, public ILicenseProvider
{
    Q_OBJECT

public:
    CoreLicenseProvider(QObject* parent);

    // Getter
    QList<const LicenseInfo*> licenses() const override     { return m_qlstLicenses; }

    // Operations
    void init();

private:
    QList<const LicenseInfo*> m_qlstLicenses;
};

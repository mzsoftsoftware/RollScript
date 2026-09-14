#pragma once

#include <QObject>
#include "Core/Licensing/ILicenseProvider.h"

#include <QList>


class RollScriptLicenseProvider : public QObject, public ILicenseProvider
{
    Q_OBJECT

public:
    RollScriptLicenseProvider(QObject* parent);

    // Getter
    QList<const LicenseInfo*> licenses() const override     { return m_qlstLicenses; }

    // Operations
    void init();

private:
    QList<const LicenseInfo*> m_qlstLicenses;
};

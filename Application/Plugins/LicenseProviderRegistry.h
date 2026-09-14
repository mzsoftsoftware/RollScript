#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"

#include <QHash>

class ILicenseProvider;
class LicenseInfo;


class LicenseProviderRegistry : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT

public:
    // Constructor / Destructor
    explicit LicenseProviderRegistry(QObject* parent);
    ~LicenseProviderRegistry() override;

    // Getter
    QStringList availableLicenseIds() const                         { return m_qstrLicenseIds; }
    const LicenseInfo* license(const QString& qstrLicenseId) const  { return m_qhashLicenses.value(qstrLicenseId, nullptr); }

    // Operations
    bool registerProvider(ILicenseProvider* ptrLicenseProvider);

private:
    QStringList m_qstrLicenseIds;
    QHash<QString, const LicenseInfo*> m_qhashLicenses;
};

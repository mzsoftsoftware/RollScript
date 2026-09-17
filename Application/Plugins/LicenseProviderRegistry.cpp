#include "LicenseProviderRegistry.h"

#include "Core/Licensing/ILicenseProvider.h"
#include "Core/Licensing/LicenseInfo.h"


LicenseProviderRegistry::LicenseProviderRegistry(QObject* parent)
    : QObject{parent}
{
}
LicenseProviderRegistry::~LicenseProviderRegistry()
{
    // No delete because the Registry doesn't own the License pointers.
}

bool LicenseProviderRegistry::registerProvider(ILicenseProvider* ptrLicenseProvider)
{
    Q_ASSERT(ptrLicenseProvider);

    const QList<const LicenseInfo*> licenses = ptrLicenseProvider->licenses();
    for(const LicenseInfo* ptrLicense : licenses)
    {
        const QString qstrLicenseId = ptrLicense->id();
        Q_ASSERT(!qstrLicenseId.isEmpty());

        if(m_qhashLicenses.contains(qstrLicenseId))
            continue;

        m_qstrLicenseIds.append(qstrLicenseId);
        m_qhashLicenses.insert(qstrLicenseId, ptrLicense);
    }

    return true;
}

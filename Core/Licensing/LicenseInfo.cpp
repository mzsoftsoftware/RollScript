#include "LicenseInfo.h"

LicenseInfo::LicenseInfo(const QString& qstrId, const QString& qstrName, const QString& qstrLicense, const QString& qstrResource)
    : m_qstrId(qstrId)
    , m_qstrName(qstrName)
    , m_qstrLicense(qstrLicense)
    , m_qstrResource(qstrResource)
{
}

#pragma once

#include <QString>


class LicenseInfo
{
public:
    LicenseInfo(const QString& qstrId, const QString& qstrName, const QString& qstrLicense, const QString& qstrResource);

    // Getter
    const QString& id() const         { return m_qstrId; }
    const QString& name() const         { return m_qstrName; }
    const QString& license() const      { return m_qstrLicense; }
    const QString& resource() const     { return m_qstrResource; }

private:
    QString m_qstrId;
    QString m_qstrName;
    QString m_qstrLicense;
    QString m_qstrResource;
};

#include "CoreLicenseProvider.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

#include "LicenseInfo.h"


CoreLicenseProvider::CoreLicenseProvider(QObject* parent)
    : QObject(parent)
{
}

void CoreLicenseProvider::init()
{
    QFile file(QStringLiteral(":/Licenses/libusb-license.json"));
    if (!file.open(QIODevice::ReadOnly))
        return;

    const QJsonDocument document = QJsonDocument::fromJson(file.readAll());
    if (!document.isObject())
        return;

    const QJsonObject object = document.object();

    const QString qstrId = object.value(QStringLiteral("repository")).toString();
    //const QString qstrName = object.value(QStringLiteral("name")).toString(); Use value from JSON -> NOT
    const QString qstrName = QStringLiteral("libusb");
    const QString qstrLicense = object.value(QStringLiteral("spdx_id")).toString();

    LicenseInfo* ptrLicenseLibUsb = new LicenseInfo(qstrId, qstrName, qstrLicense, QStringLiteral(":/Licenses/libusb-license.txt"));
    m_qlstLicenses.append(ptrLicenseLibUsb);
}

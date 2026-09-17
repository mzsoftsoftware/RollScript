#include "RollScriptLicenseProvider.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

#include "Core/Licensing/LicenseInfo.h"


RollScriptLicenseProvider::RollScriptLicenseProvider(QObject* parent)
    : QObject(parent)
{
}

void RollScriptLicenseProvider::init()
{
    QFile file(QStringLiteral(":/Licenses/RollScript-license.json"));
    if (!file.open(QIODevice::ReadOnly))
        return;

    const QJsonDocument document = QJsonDocument::fromJson(file.readAll());
    if (!document.isObject())
        return;

    const QJsonObject object = document.object();

    const QString qstrId = object.value(QStringLiteral("repository")).toString();
    const QString qstrName = object.value(QStringLiteral("name")).toString();
    const QString qstrLicense = object.value(QStringLiteral("spdx_id")).toString();

    LicenseInfo* ptrLicenseLibUsb = new LicenseInfo(qstrId, qstrName, qstrLicense, QStringLiteral(":/Licenses/RollScript-license.txt"));
    m_qlstLicenses.append(ptrLicenseLibUsb);
}

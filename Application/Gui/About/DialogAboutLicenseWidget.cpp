#include "DialogAboutLicenseWidget.h"
#include "ui_DialogAboutLicenseWidget.h"

#include <QFile>

#include "Plugins/LicenseProviderRegistry.h"
#include "Core/Licensing/LicenseInfo.h"


DialogAboutLicenseWidget::DialogAboutLicenseWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::DialogAboutLicenseWidget)
{
    ui->setupUi(this);
}

DialogAboutLicenseWidget::~DialogAboutLicenseWidget()
{
    delete ui;
}

void DialogAboutLicenseWidget::setLicenseProviderRegistry(const LicenseProviderRegistry* ptrLicenseProviderRegistry)
{
    Q_ASSERT(ptrLicenseProviderRegistry);

    ui->comboBox_Licenses->clear();

    m_ptrLicenseProviderRegistry = ptrLicenseProviderRegistry;
    const QStringList qstrLicenseIds = m_ptrLicenseProviderRegistry->availableLicenseIds();
    for(const QString& qstrLicenseId : qstrLicenseIds)
    {
        const LicenseInfo* ptrLicenseInfo = m_ptrLicenseProviderRegistry->license(qstrLicenseId);
        Q_ASSERT(ptrLicenseInfo);

        const QString qstrText = ptrLicenseInfo->name() + QStringLiteral(" - ") + ptrLicenseInfo->license();

        ui->comboBox_Licenses->addItem(qstrText,ptrLicenseInfo->id());
    }
}

void DialogAboutLicenseWidget::on_comboBox_Licenses_currentIndexChanged(int index)
{
    ui->textBrowser_License->clear();

    if(index<0 || !m_ptrLicenseProviderRegistry)
        return;

    const QString qstrLicenseId = ui->comboBox_Licenses->itemData(index).toString();
    if(qstrLicenseId.isEmpty())
        return;

    const LicenseInfo* ptrLicenseInfo = m_ptrLicenseProviderRegistry->license(qstrLicenseId);
    if(!ptrLicenseInfo)
        return;

    QFile file(ptrLicenseInfo->resource());
    if(!file.open(QIODevice::ReadOnly))
        return;

    ui->textBrowser_License->setPlainText(QString::fromUtf8(file.readAll()));
}


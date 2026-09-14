#pragma once

#include <QWidget>

class LicenseProviderRegistry;

namespace Ui {
class DialogAboutLicenseWidget;
}


class DialogAboutLicenseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DialogAboutLicenseWidget(QWidget* parent = nullptr);
    ~DialogAboutLicenseWidget();

    // Setter
    void setLicenseProviderRegistry(const LicenseProviderRegistry* ptrLicenseProviderRegistry);


private slots:
    void on_comboBox_Licenses_currentIndexChanged(int index);

private:
    Ui::DialogAboutLicenseWidget* ui;

    const LicenseProviderRegistry* m_ptrLicenseProviderRegistry = nullptr;
};

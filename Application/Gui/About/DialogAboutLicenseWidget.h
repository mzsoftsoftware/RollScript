#pragma once

#include <QWidget>

namespace Ui {
class DialogAboutLicenseWidget;
}


class DialogAboutLicenseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DialogAboutLicenseWidget(QWidget* parent = nullptr);
    ~DialogAboutLicenseWidget();

private:
    Ui::DialogAboutLicenseWidget* ui;
};

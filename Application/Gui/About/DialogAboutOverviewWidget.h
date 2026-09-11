#pragma once

#include <QWidget>

namespace Ui {
class DialogAboutOverviewWidget;
}


class DialogAboutOverviewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DialogAboutOverviewWidget(QWidget* parent = nullptr);
    ~DialogAboutOverviewWidget();

private:
    Ui::DialogAboutOverviewWidget* ui;
};

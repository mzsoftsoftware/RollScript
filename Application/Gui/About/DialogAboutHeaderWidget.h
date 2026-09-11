#pragma once

#include <QWidget>

namespace Ui {
class DialogAboutHeaderWidget;
}


class DialogAboutHeaderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DialogAboutHeaderWidget(QWidget* parent = nullptr);
    ~DialogAboutHeaderWidget();

private:
    Ui::DialogAboutHeaderWidget* ui;
};

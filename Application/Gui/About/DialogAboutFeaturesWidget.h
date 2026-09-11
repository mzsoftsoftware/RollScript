#pragma once

#include <QWidget>

namespace Ui {
class DialogAboutFeaturesWidget;
}


class DialogAboutFeaturesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DialogAboutFeaturesWidget(QWidget* parent = nullptr);
    ~DialogAboutFeaturesWidget();

private:
    Ui::DialogAboutFeaturesWidget* ui;
};

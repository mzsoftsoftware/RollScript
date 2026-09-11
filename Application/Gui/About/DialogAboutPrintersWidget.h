#pragma once

#include <QWidget>

namespace Ui {
class DialogAboutPrintersWidget;
}


class DialogAboutPrintersWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DialogAboutPrintersWidget(QWidget* parent = nullptr);
    ~DialogAboutPrintersWidget();

private:
    Ui::DialogAboutPrintersWidget* ui;
};

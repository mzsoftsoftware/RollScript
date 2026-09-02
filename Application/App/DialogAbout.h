#pragma once

#include <QDialog>

namespace Ui {
class DialogAbout;
}


class DialogAbout : public QDialog
{
    Q_OBJECT

public:
    // Constructor / Destructor
    explicit DialogAbout(QWidget* parent);
    ~DialogAbout() override;

private:
    Ui::DialogAbout* ui;
};

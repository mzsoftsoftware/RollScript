#pragma once

#include <QWidget>

namespace Ui {
class SettingsWidget;
}


class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget *parent);
    virtual ~SettingsWidget();

protected:
    void changeEvent(QEvent *event) override;

private:
    Ui::SettingsWidget *ui;
};

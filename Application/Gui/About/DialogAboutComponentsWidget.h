#pragma once

#include <QWidget>

namespace Ui {
class DialogAboutComponentsWidget;
}


class DialogAboutComponentsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DialogAboutComponentsWidget(QWidget* parent = nullptr);
    ~DialogAboutComponentsWidget();

    // Getters
    QString supportInformation() const;

private:
    void addComponent(const QString& title, const QString& description, const QString& value);
    QString targetOperatingSystem();
    QString targetWindowingSystem();
    QString targetSystem();

private:
    Ui::DialogAboutComponentsWidget* ui;
};

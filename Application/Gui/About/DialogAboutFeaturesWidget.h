#pragma once

#include <QWidget>

class FeaturePluginRegistry;

namespace Ui {
class DialogAboutFeaturesWidget;
}


class DialogAboutFeaturesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DialogAboutFeaturesWidget(QWidget* parent = nullptr);
    ~DialogAboutFeaturesWidget();

    // Setter
    void setFeaturePluginRegistry(const FeaturePluginRegistry* ptrFeaturePluginRegistry);

private:
    Ui::DialogAboutFeaturesWidget* ui;
};

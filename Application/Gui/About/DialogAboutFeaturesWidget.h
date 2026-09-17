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

    // Getters
    QString supportInformation() const;

    // Setter
    void setFeaturePluginRegistry(const FeaturePluginRegistry* ptrFeaturePluginRegistry);

private:
    Ui::DialogAboutFeaturesWidget* ui;
};

#pragma once

#include <QWidget>

class PrinterPluginRegistry;

namespace Ui {
class DialogAboutPrintersWidget;
}


class DialogAboutPrintersWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DialogAboutPrintersWidget(QWidget* parent = nullptr);
    ~DialogAboutPrintersWidget();

    // Setter
    void setPrinterPluginRegistry(const PrinterPluginRegistry* ptrPrinterPluginRegistry);

private:
    Ui::DialogAboutPrintersWidget* ui;
};

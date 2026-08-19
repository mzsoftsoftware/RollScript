#pragma once

#include <QWidget>

class PrinterManager;
class PrinterMediasItemModel;

class RollScriptDocument;
class RollScriptDocumentSettings;

namespace Ui {
class SettingsWidget;
}


class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget *parent);
    virtual ~SettingsWidget();

    void setPrinterManager(PrinterManager* ptrPrinterManager);
    void setPrinterMediasItemModel(PrinterMediasItemModel* ptrPrinterMediasItemModel);
    void setRollScriptDocument(RollScriptDocument* ptrDocument);

    void rebuildPrinterMediasModel();

    protected:
        void changeEvent(QEvent *event) override;

private:
    void updatePrinterMediaConstraints();
    void resetPrinterMediaConstraints();

private slots:
    void updateUiFromDocument();

    void on_comboBox_PrinterMedia_currentIndexChanged(int index);
    void on_doubleSpinBox_LengthMin_valueChanged(double value);
    void on_marginsWidget_marginsMmEdited(QMarginsF margins);

private:
    Ui::SettingsWidget *ui;

    PrinterManager* m_ptrPrinterManager = nullptr;
    PrinterMediasItemModel* m_ptrPrinterMediasItemModel = nullptr;

    RollScriptDocument* m_ptrDocument = nullptr;
    RollScriptDocumentSettings* m_ptrDocumentSettings = nullptr;
};

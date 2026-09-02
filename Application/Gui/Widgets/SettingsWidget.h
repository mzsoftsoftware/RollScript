#pragma once
// clazy:excludeall=connect-by-name

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
    // Constructor / Destructor
    explicit SettingsWidget(QWidget* parent);
    ~SettingsWidget() override;

    // Operations
    void setPrinterManager(PrinterManager* ptrPrinterManager);
    void setPrinterMediasItemModel(PrinterMediasItemModel* ptrPrinterMediasItemModel);
    void setRollScriptDocument(RollScriptDocument* ptrDocument);

    void rebuildPrinterMediasModel();

private slots:
    void updateUiFromDocument();

    void on_comboBox_PrinterMedia_currentIndexChanged(int iIndex);
    void on_doubleSpinBox_LengthMin_valueChanged(double dblValue);
    void on_marginsWidget_marginsMmEdited(QMarginsF margins);

protected:
    void changeEvent(QEvent* ptrEvent) override;

private:
    void updatePrinterMediaConstraints(const QString& qstrPrinterMediaId);
    void resetPrinterMediaConstraints();

private:
    Ui::SettingsWidget* ui;

    PrinterManager* m_ptrPrinterManager = nullptr;
    PrinterMediasItemModel* m_ptrPrinterMediasItemModel = nullptr;

    RollScriptDocument* m_ptrDocument = nullptr;
    RollScriptDocumentSettings* m_ptrDocumentSettings = nullptr;
};

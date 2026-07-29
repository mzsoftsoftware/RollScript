#pragma once
// clazy:excludeall=connect-by-name

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class QComboBox;
class PrintersItemModel;

class ApplicationContext;
class RollScriptDocument;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(ApplicationContext* ptrApplicationContext, QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    void createLanguageMenu();
    void updateLanguageMenu();

    void setupActions();
    void setupToolBar();
    void setupDocument();

    bool documentConfirmDiscardChanges();
    bool documentClear();
    bool documentOpen();
    bool documentSave();
    bool documentSaveAs();

    void setupDeviceManager();

private slots:
    void slot_SwitchLanguage();

    void slot_Document_Cleared();
    void slot_Document_Loaded();
    void slot_Document_Saved();

    void slot_DeviceManager_ScanFinished();
    // TASK : void slot_DeviceManager_DeviceOpened();
    // TASK : void slot_DeviceManager_DeviceClosed();
    void slot_DeviceManager_DeviceError(const QString& message);

    void on_actionAboutRollScript_triggered();
    void on_actionFileNew_triggered();
    void on_actionFileOpen_triggered();
    void on_actionFileSave_triggered();
    void on_actionFileSaveAs_triggered();
    void on_actionPrintersPrint_triggered();

    void slot_ComboBoxPrinters_IndexChanged(int index);

    void updateWindowTitle();
    void updateActionAvailability();

private:
    Ui::MainWindow *ui;

    QComboBox*          m_ptrComboBoxPrinters = nullptr;
    PrintersItemModel*  m_ptrPrintersItemModel = nullptr;

    ApplicationContext* m_ptrApplicationContext = nullptr;

    RollScriptDocument* m_ptrRollScriptDocument = nullptr;
};

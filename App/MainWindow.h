#pragma once
// clazy:excludeall=connect-by-name

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class TranslationManager;
class PluginManager;
class RollScriptDocument;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(TranslationManager* ptrTranslationManager, PluginManager* ptrPluginManager, QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    bool confirmClose();

    void createLanguageMenu();
    void updateLanguageMenu();

    void setupActions();
    void setupDocument();

private slots:
    void slot_SwitchLanguage();

    void slot_Document_Cleared();
    void slot_Document_Loaded();
    void slot_Document_Saved();

    void on_actionAboutRollScript_triggered();
    void on_actionFileNew_triggered();
    void on_actionFileOpen_triggered();
    void on_actionFileSave_triggered();
    void on_actionFileSaveAs_triggered();
    void on_actionPrintersScan_triggered();
    void on_actionPrintersPrint_triggered();

    void updateWindowTitle();
    void updateActionAvailability();

private:
    bool documentSave();
    bool documentSaveAs();

private:
    Ui::MainWindow *ui;

    TranslationManager* m_ptrTranslationManager;
    PluginManager* m_ptrPluginManager;

    RollScriptDocument* m_ptrRollScriptDocument;
};

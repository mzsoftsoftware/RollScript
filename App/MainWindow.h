#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class TranslationManager;
class PluginManager;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(TranslationManager* ptrTranslationManager, PluginManager* ptrPluginManager, QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    void createLanguageMenu();
    void updateLanguageMenu();

private slots:
    void slotSwitchLanguage();

    void on_actionAboutRollScript_triggered();
    void on_actionFileNew_triggered();
    void on_actionFileOpen_triggered();
    void on_actionFileSave_triggered();
    void on_actionFileSaveAs_triggered();
    void on_actionPrintersScan_triggered();
    void on_actionPrintersPrint_triggered();

private:
    Ui::MainWindow *ui;

    TranslationManager* m_ptrTranslationManager;
    PluginManager* m_ptrPluginManager;
};

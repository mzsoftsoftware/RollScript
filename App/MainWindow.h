#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class TranslationManager;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(TranslationManager* ptrTranslationManager, QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    void createLanguageMenu();
    void updateLanguageMenu();

private slots:
    void slotSwitchLanguage();

private:
    Ui::MainWindow *ui;

    TranslationManager* m_ptrTranslationManager;
};
#endif // MAINWINDOW_H

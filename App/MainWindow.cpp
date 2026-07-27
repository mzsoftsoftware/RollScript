#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QCloseEvent>
#include <QMessageBox>

#include "Core/Translation/TranslationManager.h"
#include "App/DialogAbout.h"


MainWindow::MainWindow(TranslationManager* ptrTranslationManager, PluginManager* ptrPluginManager, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_ptrTranslationManager(ptrTranslationManager)
    , m_ptrPluginManager(ptrPluginManager)
{
    ui->setupUi(this);

    createLanguageMenu();
    updateLanguageMenu();

    setupActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if(confirmClose())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

bool MainWindow::confirmClose()
{
    // TASK : Check for Document modified
    const QMessageBox::StandardButton result = QMessageBox::warning(
        this, tr("ConfirmClose.Title"), tr("ConfirmClose.Message"),
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
        QMessageBox::Save);

    switch(result)
    {
    case QMessageBox::Save:
        // TASK : Save Document
        return true;
    case QMessageBox::Discard:
        return true;
    case QMessageBox::Cancel:
    default:
        return false;
    }
}

void MainWindow::createLanguageMenu()
{
    const QList<TranslationInfo> translations =
        m_ptrTranslationManager->availableTranslations();

    for (const TranslationInfo &translation :
         translations)
    {
        QAction *action =
            new QAction(
                translation.qstrLanguageName,
                this
                );

        action->setCheckable(true);
        action->setData(
            translation.qLocale
            );
        connect(action, &QAction::triggered, this, &MainWindow::slotSwitchLanguage);

        ui->menuViewLanguage->addAction(action);
    }
}
void MainWindow::updateLanguageMenu()
{
    const QLocale currentLocale = m_ptrTranslationManager->currentLocale();

    const QList<QAction *> actions = ui->menuViewLanguage->actions();
    for (QAction *action : actions)
    {
        const QLocale locale = action->data().value<QLocale>();
        action->setChecked( locale == currentLocale );
    }
}
void MainWindow::slotSwitchLanguage()
{
    QAction *action = qobject_cast<QAction*>(sender());
    if(!action)
        return;

    const QLocale locale = action->data().value<QLocale>();
    m_ptrTranslationManager->loadLanguage(locale);

    updateLanguageMenu();
    ui->retranslateUi(this);
}

void MainWindow::setupActions()
{
    // Connect fixed actions
    connect(ui->actionExit, &QAction::triggered, this, &QWidget::close);
    connect(ui->actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);

    // TASK : Connect logMessage from other components
}



void MainWindow::on_actionAboutRollScript_triggered()
{
    DialogAbout dialog(this);
    dialog.exec();
}
void MainWindow::on_actionFileNew_triggered()
{
    qInfo() << "on_actionFileNew_triggered";
}
void MainWindow::on_actionFileOpen_triggered()
{
    qInfo() << "on_actionFileOpen_triggered";
}
void MainWindow::on_actionFileSave_triggered()
{
    qInfo() << "on_actionFileSave_triggered";
}
void MainWindow::on_actionFileSaveAs_triggered()
{
    qInfo() << "on_actionFileSaveAs_triggered";
}
void MainWindow::on_actionPrintersScan_triggered()
{
    qInfo() << "on_actionPrintersScan_triggered";
}
void MainWindow::on_actionPrintersPrint_triggered()
{
    qInfo() << "on_actionPrintersPrint_triggered";
}


#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Core/Translation/TranslationManager.h"


MainWindow::MainWindow(TranslationManager* ptrTranslationManager, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_ptrTranslationManager(ptrTranslationManager)
{
    ui->setupUi(this);

    createLanguageMenu();
    updateLanguageMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
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

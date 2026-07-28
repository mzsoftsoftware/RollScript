#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QCloseEvent>
#include <QMessageBox>
#include <QFileInfo>
#include <QFileDialog>

#include "Core/Translation/TranslationManager.h"
#include "Core/Document/RollScriptDocument.h"

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

    setupDocument();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if(documentConfirmDiscardChanges())
    {
        event->accept();
    }
    else
    {
        event->ignore();
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
        connect(action, &QAction::triggered, this, &MainWindow::slot_SwitchLanguage);

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
void MainWindow::slot_SwitchLanguage()
{
    QAction *action = qobject_cast<QAction*>(sender());
    if(!action)
        return;

    const QLocale locale = action->data().value<QLocale>();
    m_ptrTranslationManager->loadLanguage(locale);

    updateLanguageMenu();
    ui->retranslateUi(this);
    updateWindowTitle();
}

void MainWindow::setupActions()
{
    // Connect fixed actions
    connect(ui->actionExit, &QAction::triggered, this, &QWidget::close);
    connect(ui->actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
}
void MainWindow::setupDocument()
{
    m_ptrRollScriptDocument = new RollScriptDocument(this);

    // Connect RollScriptDocument to Widgets
    // TASK : Connect RollScriptDocument to Widgets
    ui->widget_Settings->setRollScriptDocument(m_ptrRollScriptDocument);

    // Connect RollScriptDocument signals
    connect(m_ptrRollScriptDocument, &RollScriptDocument::documentModifiedChanged, this, &MainWindow::updateWindowTitle);
    connect(m_ptrRollScriptDocument, &RollScriptDocument::documentModifiedChanged, this, &MainWindow::updateActionAvailability);

    connect(m_ptrRollScriptDocument, &RollScriptDocument::documentFileNameChanged, this, &MainWindow::updateWindowTitle);

    connect(m_ptrRollScriptDocument, &RollScriptDocument::documentCleared, this, &MainWindow::slot_Document_Cleared);
    connect(m_ptrRollScriptDocument, &RollScriptDocument::documentLoaded, this, &MainWindow::slot_Document_Loaded);
    connect(m_ptrRollScriptDocument, &RollScriptDocument::documentSaved, this, &MainWindow::slot_Document_Saved);

    updateWindowTitle();
    updateActionAvailability();
}

bool MainWindow::documentConfirmDiscardChanges()
{
    if(!m_ptrRollScriptDocument->isModified())
    {
        return true;
    }

    const QMessageBox::StandardButton result = QMessageBox::warning(
        this, tr("ConfirmDiscardChanges.Title"), tr("ConfirmDiscardChanges.Message"),
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
        QMessageBox::Save);

    switch(result)
    {
    case QMessageBox::Save:
        return documentSave();
    case QMessageBox::Discard:
        return true;
    case QMessageBox::Cancel:
    default:
        return false;
    }
}
bool MainWindow::documentClear()
{
    if(!documentConfirmDiscardChanges())
    {
        return false;
    }

    m_ptrRollScriptDocument->clear();
    return true;
}
bool MainWindow::documentOpen()
{
    if(!documentConfirmDiscardChanges())
    {
        return false;
    }

    const QString qstrFileFilter = tr("FileOpen.Filter").arg(m_ptrRollScriptDocument->fileExtension());
    const QString qstrFileName = QFileDialog::getOpenFileName(this, tr("FileOpen.Title"), QString(), qstrFileFilter);
    if(qstrFileName.isEmpty())
    {
        return false;
    }

    if(!m_ptrRollScriptDocument->load(qstrFileName))
    {
        QMessageBox::critical(
            this, tr("FileOpen.Error.Title"),
            m_ptrRollScriptDocument->lastError());
        return false;
    }
    return true;

}
bool MainWindow::documentSave()
{
    if(m_ptrRollScriptDocument->fileName().isEmpty())
    {
        return documentSaveAs();
    }

    if(!m_ptrRollScriptDocument->save())
    {
        QMessageBox::critical(
            this, tr("FileSave.Error.Title"),
            m_ptrRollScriptDocument->lastError());
        return false;
    }
    return true;
}
bool MainWindow::documentSaveAs()
{
    const QString qstrFileFilter = tr("FileSaveAs.Filter").arg(m_ptrRollScriptDocument->fileExtension());

    QString qstrFileName = QFileDialog::getSaveFileName(this, tr("FileSaveAs.Title"), QString(), qstrFileFilter);
    if(qstrFileName.isEmpty())
    {
        return false;
    }

    if(!qstrFileName.endsWith(m_ptrRollScriptDocument->fileExtension(), Qt::CaseInsensitive))
    {
        qstrFileName += m_ptrRollScriptDocument->fileExtension();
    }

    if(!m_ptrRollScriptDocument->saveAs(qstrFileName))
    {
        QMessageBox::critical(
            this, tr("FileSave.Error.Title"),
            m_ptrRollScriptDocument->lastError());
        return false;
    }
    return true;
}

void MainWindow::slot_Document_Cleared()
{
    updateWindowTitle();
    updateActionAvailability();
    ui->statusbar->showMessage(tr("Document.Cleared"));
}
void MainWindow::slot_Document_Loaded()
{
    updateWindowTitle();
    updateActionAvailability();
    ui->statusbar->showMessage(tr("Document.Loaded"));
}
void MainWindow::slot_Document_Saved()
{
    updateWindowTitle();
    updateActionAvailability();
    ui->statusbar->showMessage(tr("Document.Saved"));
}

void MainWindow::on_actionAboutRollScript_triggered()
{
    DialogAbout dialog(this);
    dialog.exec();
}
void MainWindow::on_actionFileNew_triggered()
{
    documentClear();
}
void MainWindow::on_actionFileOpen_triggered()
{
    documentOpen();
}
void MainWindow::on_actionFileSave_triggered()
{
    documentSave();
}
void MainWindow::on_actionFileSaveAs_triggered()
{
    documentSaveAs();
}
void MainWindow::on_actionPrintersScan_triggered()
{
    qInfo() << "on_actionPrintersScan_triggered";
}
void MainWindow::on_actionPrintersPrint_triggered()
{
    qInfo() << "on_actionPrintersPrint_triggered";
}




void MainWindow::updateWindowTitle()
{
    const QString qstrFileName = m_ptrRollScriptDocument->fileName().isEmpty()
        ? tr("MainWindow.DocumentUntitled")
        : QFileInfo(m_ptrRollScriptDocument->fileName()).fileName();

    const QString qstrModified = m_ptrRollScriptDocument->isModified()
        ? tr("MainWindow.DocumentModified")
        : QString();

    const QString strTitle = tr("MainWindow.WindowTitle").arg(qstrFileName, qstrModified);

    setWindowTitle(strTitle);
}
void MainWindow::updateActionAvailability()
{
    ui->actionFileSave->setEnabled(m_ptrRollScriptDocument->isModified());
}

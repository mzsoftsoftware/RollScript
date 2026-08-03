#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QCloseEvent>
#include <QMessageBox>
#include <QFileInfo>
#include <QFileDialog>
#include <QComboBox>

#include "App/DialogAbout.h"

#include "App/ApplicationContext.h"
#include "Core/Translation/TranslationManager.h"
#include "Core/Printers/PrinterManager.h"

#include "Core/Document/RollScriptDocument.h"

#include "Gui/Models/PrintersItemModel.h"
#include "Gui/Models/PrinterMediasItemModel.h"


MainWindow::MainWindow(ApplicationContext* ptrApplicationContext, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_ptrApplicationContext(ptrApplicationContext)
{
    ui->setupUi(this);

    createLanguageMenu();
    updateLanguageMenu();

    setupActions();
    setupToolBar();

    setupDocument();

    setupPrinterManager();
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
        m_ptrApplicationContext->translationManager()->availableTranslations();

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
    const QLocale currentLocale = m_ptrApplicationContext->translationManager()->currentLocale();

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
    m_ptrApplicationContext->translationManager()->loadLanguage(locale);

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
void MainWindow::setupToolBar()
{
    // Setup the GUI models for the printer informations
    m_ptrPrintersItemModel = new PrintersItemModel(m_ptrApplicationContext->printerManager(), this);
    m_ptrPrinterMediasItemModel = new PrinterMediasItemModel(m_ptrApplicationContext->printerManager(), this);

    // Add a QComboBox with the Devices found from Scan.
    m_ptrComboBoxPrinters = new QComboBox(this);
    m_ptrComboBoxPrinters->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    // TASK : Use correct tr !!!
    m_ptrComboBoxPrinters->setPlaceholderText(tr("No printers found, please rescan."));
    m_ptrComboBoxPrinters->setCurrentIndex(-1);

    // Set Models inside GUI
    m_ptrComboBoxPrinters->setModel(m_ptrPrintersItemModel);
    ui->widget_Settings->setPrinterMediasItemModel(m_ptrPrinterMediasItemModel);

    // Setup Toolbar and connect events
    ui->toolBar->insertWidget(ui->actionPrintersPrint, m_ptrComboBoxPrinters);
    connect(m_ptrComboBoxPrinters, &QComboBox::currentIndexChanged, this, &MainWindow::slot_ComboBoxPrinters_IndexChanged);
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

void MainWindow::setupPrinterManager()
{
    PrinterManager* ptrPrinterManager = m_ptrApplicationContext->printerManager();
    // Connect DeviceManager signals
    connect(ptrPrinterManager, &PrinterManager::scanFinished, this, &MainWindow::slot_PrinterManager_ScanFinished);
    connect(ptrPrinterManager, &PrinterManager::printerChanged, this, &MainWindow::slot_PrinterManager_PrinterChanged);
    connect(ptrPrinterManager, &PrinterManager::managerError, this, &MainWindow::slot_PrinterManager_ManagerError);

    connect(ui->actionPrintersScan, &QAction::triggered, this, &MainWindow::slot_PrinterManager_Scan);
}

void MainWindow::slot_PrinterManager_Scan()
{
    if(!m_ptrApplicationContext->printerManager()->scanForDevices())
    {
        //ui->textEdit_Debug->append(QString("PrinterManager Error : ") + message);
    }
}
void MainWindow::slot_PrinterManager_ScanFinished()
{
    QSignalBlocker blocker(m_ptrComboBoxPrinters);
    m_ptrPrintersItemModel->rebuildModel();
    if(m_ptrPrintersItemModel->rowCount() > 0)
    {
        // TASK : Use correct tr !!!
        m_ptrComboBoxPrinters->setPlaceholderText(tr("Please select a printer ..."));
    }
    else
    {
        // TASK : Use correct tr !!!
        m_ptrComboBoxPrinters->setPlaceholderText(tr("No printers found, Please rescan."));
    }
    m_ptrComboBoxPrinters->setCurrentIndex(-1);
    ui->widget_Settings->rebuildPrinterMediasModel();
}
void MainWindow::slot_PrinterManager_PrinterChanged()
{
    ui->widget_Settings->rebuildPrinterMediasModel();
}
void MainWindow::slot_PrinterManager_ManagerError(const QString& message)
{
    ui->textEdit_Debug->append(QString("PrinterManager Error : ") + message);
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
void MainWindow::on_actionPrintersPrint_triggered()
{
    qInfo() << "on_actionPrintersPrint_triggered";
}

void MainWindow::slot_ComboBoxPrinters_IndexChanged(int index)
{
    if(index < 0)
        return;

    QString qstrPrinterId = m_ptrComboBoxPrinters->currentData(Qt::UserRole).toString();
    m_ptrApplicationContext->printerManager()->switchPrinter(qstrPrinterId);
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

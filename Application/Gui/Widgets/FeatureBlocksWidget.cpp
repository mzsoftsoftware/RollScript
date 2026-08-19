#include "FeatureBlocksWidget.h"
#include "ui_FeatureBlocksWidget.h"

#include "Features/FeatureBlockManager.h"
#include "Core/Blocks/IFeatureBlock.h"
#include "Core/Blocks/IFeatureBlockInfo.h"
#include "Core/Blocks/RollScriptBlockWidgetBase.h"
#include "FeatureBlockWidgetEmpty.h"

#include "Document/RollScriptDocument.h"
#include "Document/RollScriptDocumentBlocks.h"
#include "Core/Blocks/RollScriptBlockDocumentBase.h"

#include "Gui/Models/FeatureBlocksItemModel.h"
#include "Gui/Helper/FeatureBlocksItemDelegate.h"


FeatureBlocksWidget::FeatureBlocksWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FeatureBlocksWidget)
{
    ui->setupUi(this);
}

FeatureBlocksWidget::~FeatureBlocksWidget()
{
    delete ui;
}

void FeatureBlocksWidget::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }

    QWidget::changeEvent(event);
}

void FeatureBlocksWidget::setFeatureBlockManager(FeatureBlockManager* ptrFeatureBlockManager)
{
    m_ptrFeatureBlockManager = ptrFeatureBlockManager;

    setupButtons();
    setupStackedWidget();
    setupListView();
}

void FeatureBlocksWidget::setRollScriptDocument(RollScriptDocument* ptrDocument)
{
    m_ptrDocument = ptrDocument;
    m_ptrDocumentBlocks = ptrDocument->blocks();

    connect(m_ptrDocument, &RollScriptDocument::documentCleared, this, &FeatureBlocksWidget::updateUiFromDocument);
    connect(m_ptrDocument, &RollScriptDocument::documentLoaded, this, &FeatureBlocksWidget::updateUiFromDocument);
    updateUiFromDocument();
}

void FeatureBlocksWidget::setupListView()
{
    ui->listView->setItemDelegate(new FeatureBlocksItemDelegate(this));
    m_ptrFeatureBlocksItemModel = new FeatureBlocksItemModel(m_ptrFeatureBlockManager, m_ptrDocumentBlocks, this);
    ui->listView->setModel(m_ptrFeatureBlocksItemModel);
}

void FeatureBlocksWidget::setupButtons()
{
    Q_ASSERT(m_ptrFeatureBlockManager);

    // The Add Button
    m_ptrFeatureBlocksAddMenu = new QMenu(this);
    QStringList qstrFeatureBlockIds = m_ptrFeatureBlockManager->availableFeatureBlockIds();
    for(const QString& qstrFeatureBlockId : qstrFeatureBlockIds)
    {
        IFeatureBlock *ptrFeatureBlock = m_ptrFeatureBlockManager->featureBlock(qstrFeatureBlockId);

        QAction* ptrAction = new QAction(this);
        ptrAction->setText(tr(ptrFeatureBlock->featureBlockInfo()->featureBlockDisplayName().toUtf8().constData()));
        ptrAction->setIcon(ptrFeatureBlock->featureBlockInfo()->featureBlockIcon());
        ptrAction->setData(qstrFeatureBlockId);

        m_ptrFeatureBlocksAddMenu->addAction(ptrAction);
    }
    ui->toolButton_Add->setMenu(m_ptrFeatureBlocksAddMenu);
    connect(m_ptrFeatureBlocksAddMenu, &QMenu::triggered, this, &FeatureBlocksWidget::slotAddFeatureBlockFromMenu);

    // The Remove Button
    connect(ui->listView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &FeatureBlocksWidget::slotUpdateButtons);
    slotUpdateButtons();
}

void FeatureBlocksWidget::setupStackedWidget()
{
    QStringList qstrFeatureBlockIds = m_ptrFeatureBlockManager->availableFeatureBlockIds();
    for(const QString& qstrFeatureBlockId : qstrFeatureBlockIds)
    {
        IFeatureBlock *ptrFeatureBlock = m_ptrFeatureBlockManager->featureBlock(qstrFeatureBlockId);

        RollScriptBlockWidgetBase* ptrWidget = m_ptrFeatureBlockManager->createFeatureBlockWidget(qstrFeatureBlockId, this);
        ui->stackedWidget->addWidget(ptrWidget);
        m_hashFeatureBlockWidgets[qstrFeatureBlockId] = ptrWidget;
    }

    RollScriptBlockWidgetBase* ptrWidgetEmpty = new FeatureBlockWidgetEmpty(this);
    ui->stackedWidget->addWidget(ptrWidgetEmpty);
    m_hashFeatureBlockWidgets[QStringLiteral("Empty")] = ptrWidgetEmpty;
}

void FeatureBlocksWidget::slotUpdateButtons()
{
    const bool hasSelection = ui->listView->selectionModel()->hasSelection();
    ui->toolButton_Remove->setEnabled(hasSelection);

    // Update the Stack too
    if(!hasSelection)
    {
        ui->stackedWidget->setEnabled(false);
        ui->stackedWidget->setCurrentWidget(m_hashFeatureBlockWidgets[QStringLiteral("Empty")]);
    }
    else
    {
        QModelIndex index = ui->listView->currentIndex();
        RollScriptBlockDocumentBase *ptrLabelBlock = m_ptrDocumentBlocks->documentBlock(index.row());
        if(ptrLabelBlock)
        {
            RollScriptBlockWidgetBase* ptrWidgetBase = m_hashFeatureBlockWidgets[ptrLabelBlock->blockPluginId()];
            if(ptrWidgetBase)
            {
                ptrWidgetBase->setDocumentBlock(ptrLabelBlock);
                ui->stackedWidget->setCurrentWidget(ptrWidgetBase);
                ui->stackedWidget->setEnabled(true);
            }
        }
        else
        {
            ui->stackedWidget->setEnabled(false);
            ui->stackedWidget->setCurrentWidget(m_hashFeatureBlockWidgets[QStringLiteral("Empty")]);
        }
    }
}

void FeatureBlocksWidget::slotAddFeatureBlockFromMenu(QAction *ptrAction)
{
    if(!ptrAction)
        return;

    QString qstrFeatureBlockId = ptrAction->data().toString();
    if( qstrFeatureBlockId.isEmpty())
        return;

    RollScriptBlockDocumentBase* ptrDocumentBlockBase = m_ptrFeatureBlockManager->createFeatureBlockDocument(qstrFeatureBlockId, this);
    if(!ptrDocumentBlockBase)
        return;

    QModelIndex currentIndex = ui->listView->currentIndex();
    int iInsertIndex;
    if (currentIndex.isValid())
        iInsertIndex = currentIndex.row() + 1;
    else
        iInsertIndex = m_ptrDocumentBlocks->documentBlockCount();

    m_ptrDocumentBlocks->insertDocumentBlock(iInsertIndex, ptrDocumentBlockBase);

    QModelIndex newIndex = m_ptrFeatureBlocksItemModel->index(iInsertIndex, 0);
    ui->listView->setCurrentIndex(newIndex);
}
void FeatureBlocksWidget::on_toolButton_Remove_clicked()
{
    QModelIndex index = ui->listView->currentIndex();

    if(!index.isValid())
        return;

    int iRow = index.row();
    m_ptrDocumentBlocks->removeDocumentBlock(iRow);

    if(iRow >= m_ptrFeatureBlocksItemModel->rowCount())
        iRow = m_ptrFeatureBlocksItemModel->rowCount() - 1;

    if(iRow >= 0)
    {
        QModelIndex newIndex = m_ptrFeatureBlocksItemModel->index(iRow, 0);
        ui->listView->setCurrentIndex(newIndex);
    }
}


void FeatureBlocksWidget::updateUiFromDocument()
{
    //QSignalBlocker blockerLengthMin(ui->doubleSpinBox_LengthMin);
    //QSignalBlocker blockerMargins(ui->marginsWidget);

    //ui->doubleSpinBox_LengthMin->setValue(m_ptrDocumentSettings->minimumLengthMm());
    //ui->marginsWidget->setMarginsMm(m_ptrDocumentSettings->marginsMm());
}

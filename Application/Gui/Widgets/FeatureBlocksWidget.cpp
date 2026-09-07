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


FeatureBlocksWidget::FeatureBlocksWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::FeatureBlocksWidget)
{
    ui->setupUi(this);

    setupListView();
}
FeatureBlocksWidget::~FeatureBlocksWidget()
{
    delete ui;
}

void FeatureBlocksWidget::changeEvent(QEvent* ptrEvent)
{
    if(ptrEvent->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
        retranslateActions();
        retranslateFeatureBlockWidgets();
    }

    QWidget::changeEvent(ptrEvent);
}

void FeatureBlocksWidget::setFeatureBlockManager(FeatureBlockManager* ptrFeatureBlockManager)
{
    m_ptrFeatureBlockManager = ptrFeatureBlockManager;
    m_ptrFeatureBlocksItemModel->setFeatureBlockManager(m_ptrFeatureBlockManager);

    setupStackedWidget();
    setupButtons();
}

void FeatureBlocksWidget::setRollScriptDocument(RollScriptDocument* ptrDocument)
{
    m_ptrDocument = ptrDocument;
    m_ptrDocumentBlocks = ptrDocument->blocks();
    m_ptrFeatureBlocksItemModel->setRollScriptDocumentBlocks(m_ptrDocumentBlocks);

    connect(m_ptrDocument, &RollScriptDocument::documentCleared, this, &FeatureBlocksWidget::updateUiFromDocument);
    connect(m_ptrDocument, &RollScriptDocument::documentLoaded, this, &FeatureBlocksWidget::updateUiFromDocument);
    updateUiFromDocument();
}

void FeatureBlocksWidget::setupListView()
{
    ui->listView->setItemDelegate(new FeatureBlocksItemDelegate(this));
    m_ptrFeatureBlocksItemModel = new FeatureBlocksItemModel(this);
    ui->listView->setModel(m_ptrFeatureBlocksItemModel);
}

void FeatureBlocksWidget::setupButtons()
{
    Q_ASSERT(m_ptrFeatureBlockManager);

    // The Add Button
    m_ptrFeatureBlocksAddMenu = new QMenu(this);
    const QStringList qstrFeatureBlockIds = m_ptrFeatureBlockManager->availableFeatureBlockIds();
    for(const QString& qstrFeatureBlockId : qstrFeatureBlockIds)
    {
        IFeatureBlock* ptrFeatureBlock = m_ptrFeatureBlockManager->featureBlock(qstrFeatureBlockId);

        QAction* ptrAction = new QAction(this);
        ptrAction->setText(ptrFeatureBlock->featureBlockInfo()->featureBlockDisplayName());
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
    Q_ASSERT(m_ptrFeatureBlockManager);

    const QStringList qstrFeatureBlockIds = m_ptrFeatureBlockManager->availableFeatureBlockIds();
    for(const QString& qstrFeatureBlockId : qstrFeatureBlockIds)
    {
        RollScriptBlockWidgetBase* ptrWidget = m_ptrFeatureBlockManager->createFeatureBlockWidget(qstrFeatureBlockId, this);
        Q_ASSERT(ptrWidget);

        ui->stackedWidget->addWidget(ptrWidget);
        m_qhashFeatureBlockWidgets[qstrFeatureBlockId] = ptrWidget;
    }

    RollScriptBlockWidgetBase* ptrWidgetEmpty = new FeatureBlockWidgetEmpty(this);
    ui->stackedWidget->addWidget(ptrWidgetEmpty);
    m_qhashFeatureBlockWidgets[QStringLiteral("Empty")] = ptrWidgetEmpty;
}

void FeatureBlocksWidget::slotUpdateButtons()
{
    const bool hasSelection = ui->listView->selectionModel()->hasSelection();
    ui->toolButton_Remove->setEnabled(hasSelection);

    // Update the Stack too
    if(!hasSelection)
    {
        ui->stackedWidget->setEnabled(false);
        ui->stackedWidget->setCurrentWidget(m_qhashFeatureBlockWidgets[QStringLiteral("Empty")]);
    }
    else
    {
        QModelIndex index = ui->listView->currentIndex();
        RollScriptBlockDocumentBase* ptrLabelBlock = m_ptrDocumentBlocks->documentBlock(index.row());
        if(ptrLabelBlock)
        {
            RollScriptBlockWidgetBase* ptrWidgetBase = m_qhashFeatureBlockWidgets[ptrLabelBlock->blockPluginId()];
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
            ui->stackedWidget->setCurrentWidget(m_qhashFeatureBlockWidgets[QStringLiteral("Empty")]);
        }
    }
}

void FeatureBlocksWidget::slotAddFeatureBlockFromMenu(QAction* ptrAction)
{
    if(!ptrAction)
        return;

    QString qstrFeatureBlockId = ptrAction->data().toString();
    if( qstrFeatureBlockId.isEmpty())
        return;

    QModelIndex currentIndex = ui->listView->currentIndex();
    int iInsertIndex;
    if (currentIndex.isValid())
        iInsertIndex = currentIndex.row() + 1;
    else
        iInsertIndex = m_ptrDocumentBlocks->documentBlockCount();

    m_ptrDocumentBlocks->insertDocumentBlock(iInsertIndex, qstrFeatureBlockId);

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
    slotUpdateButtons();
    //QSignalBlocker blockerLengthMin(ui->doubleSpinBx_LengthMin);
    //QSignalBlocker blockerMargins(ui->marginsWidget);

    //ui->doubleSpinBox_LengthMin->setValue(m_ptrDocumentSettings->minimumLengthMm());
    //ui->marginsWidget->setMarginsMm(m_ptrDocumentSettings->marginsMm());
}

void FeatureBlocksWidget::retranslateActions()
{
    const QList<QAction*> qlstActions = m_ptrFeatureBlocksAddMenu->actions();
    for(QAction* ptrAction : qlstActions)
    {
        Q_ASSERT(ptrAction);

        const QString qstrFeatureBlockId = ptrAction->data().toString();
        Q_ASSERT(!qstrFeatureBlockId.isEmpty());

        IFeatureBlock* ptrFeatureBlock = m_ptrFeatureBlockManager->featureBlock(qstrFeatureBlockId);
        Q_ASSERT(ptrFeatureBlock);

        ptrAction->setText(ptrFeatureBlock->featureBlockInfo()->featureBlockDisplayName());
    }
}

void FeatureBlocksWidget::retranslateFeatureBlockWidgets()
{
    QHash<QString, RollScriptBlockWidgetBase*>::const_iterator iterator = m_qhashFeatureBlockWidgets.constBegin();
    while(iterator != m_qhashFeatureBlockWidgets.constEnd())
    {
        RollScriptBlockWidgetBase* ptrWidget = iterator.value();
        if(ptrWidget)
        {
            IFeatureBlock* ptrFeatureBlock = m_ptrFeatureBlockManager->featureBlock(iterator.key());
            if(ptrFeatureBlock)
            {
                ptrWidget->setTitle(ptrFeatureBlock->featureBlockInfo()->featureBlockDisplayName());
            }
        }

        ++iterator;
    }
}

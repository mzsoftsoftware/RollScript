#pragma once

#include <QWidget>
#include <QMenu>

class FeatureBlockManager;
class FeatureBlocksItemModel;
class RollScriptBlockWidgetBase;

class RollScriptDocument;
class RollScriptDocumentBlocks;

namespace Ui {
class FeatureBlocksWidget;
}


class FeatureBlocksWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FeatureBlocksWidget(QWidget *parent);
    virtual ~FeatureBlocksWidget();

    void setFeatureBlockManager(FeatureBlockManager* ptrFeatureBlockManager);
    void setRollScriptDocument(RollScriptDocument* ptrDocument);

protected:
    void changeEvent(QEvent *event) override;

private slots:
    void slotUpdateButtons();
    void slotAddFeatureBlockFromMenu(QAction *ptrAction);

    void on_toolButton_Remove_clicked();

    void updateUiFromDocument();

private:
    void setupListView();
    void setupButtons();
    void setupStackedWidget();

private:
    Ui::FeatureBlocksWidget *ui;

    FeatureBlockManager* m_ptrFeatureBlockManager;

    RollScriptDocument* m_ptrDocument = nullptr;
    RollScriptDocumentBlocks* m_ptrDocumentBlocks = nullptr;

    QMenu* m_ptrFeatureBlocksAddMenu;
    QHash<QString, RollScriptBlockWidgetBase*> m_hashFeatureBlockWidgets;

    FeatureBlocksItemModel* m_ptrFeatureBlocksItemModel;
};

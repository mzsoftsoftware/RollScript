#pragma once
// clazy:excludeall=connect-by-name

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
    // Constructor / Destructor
    explicit FeatureBlocksWidget(QWidget* parent);
    ~FeatureBlocksWidget() override;

    // Operations
    void setFeatureBlockManager(FeatureBlockManager* ptrFeatureBlockManager);
    void setRollScriptDocument(RollScriptDocument* ptrDocument);

private slots:
    void slotUpdateButtons();
    void slotAddFeatureBlockFromMenu(QAction* ptrAction);

    void on_toolButton_Remove_clicked();

    void updateUiFromDocument();

protected:
    void changeEvent(QEvent* ptrEvent) override;

private:
    void setupListView();
    void setupButtons();
    void setupStackedWidget();

private:
    Ui::FeatureBlocksWidget* ui;

    FeatureBlockManager*                        m_ptrFeatureBlockManager = nullptr;

    RollScriptDocument*                         m_ptrDocument = nullptr;
    RollScriptDocumentBlocks*                   m_ptrDocumentBlocks = nullptr;

    QMenu*                                      m_ptrFeatureBlocksAddMenu = nullptr;
    QHash<QString, RollScriptBlockWidgetBase*>  m_qhashFeatureBlockWidgets;

    FeatureBlocksItemModel*                     m_ptrFeatureBlocksItemModel = nullptr;
};

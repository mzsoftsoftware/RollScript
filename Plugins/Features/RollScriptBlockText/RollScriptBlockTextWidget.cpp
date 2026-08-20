#include "RollScriptBlockTextWidget.h"
#include "ui_RollScriptBlockTextWidget.h"

#include "RollScriptBlockTextDocument.h"
#include "RollScriptBlockTextLineDocument.h"


RollScriptBlockTextWidget::RollScriptBlockTextWidget(const QString &qstrPluginId, const QString &qstrTitle, QWidget *parent)
    : RollScriptBlockWidgetBase(qstrPluginId, qstrTitle, parent)
    , ui(new Ui::RollScriptBlockTextWidget)
{
    ui->setupUi(this);

    connect(ui->widget_TextLine0, &RollScriptBlockTextLineWidget::lineActiveChanged, this, &RollScriptBlockTextWidget::updateFromBlockTextDocument);
    connect(ui->widget_TextLine1, &RollScriptBlockTextLineWidget::lineActiveChanged, this, &RollScriptBlockTextWidget::updateFromBlockTextDocument);
    connect(ui->widget_TextLine2, &RollScriptBlockTextLineWidget::lineActiveChanged, this, &RollScriptBlockTextWidget::updateFromBlockTextDocument);
    connect(ui->widget_TextLine3, &RollScriptBlockTextLineWidget::lineActiveChanged, this, &RollScriptBlockTextWidget::updateFromBlockTextDocument);
}

RollScriptBlockTextWidget::~RollScriptBlockTextWidget()
{
    delete ui;
}

void RollScriptBlockTextWidget::setDocumentBlock(RollScriptBlockDocumentBase* ptrBlockDocumentBase)
{
    RollScriptBlockTextDocument* ptrBlockTextDocument = dynamic_cast<RollScriptBlockTextDocument*>(ptrBlockDocumentBase);
    Q_ASSERT(ptrBlockTextDocument);

    if(m_ptrBlockTextDocument)
    {
        disconnect(m_connBlockTextDocumentCleared);
        disconnect(m_connBlockTextDocumentLoaded);
    }
    m_ptrBlockTextDocument = ptrBlockTextDocument;

    ui->widget_TextLine0->setDocumentBlockTextLine(m_ptrBlockTextDocument->textLine(0));
    ui->widget_TextLine1->setDocumentBlockTextLine(m_ptrBlockTextDocument->textLine(1));
    ui->widget_TextLine2->setDocumentBlockTextLine(m_ptrBlockTextDocument->textLine(2));
    ui->widget_TextLine3->setDocumentBlockTextLine(m_ptrBlockTextDocument->textLine(3));

    m_connBlockTextDocumentCleared = connect(m_ptrBlockTextDocument, &RollScriptBlockTextDocument::documentCleared, this, &RollScriptBlockTextWidget::updateFromBlockTextDocument);
    m_connBlockTextDocumentLoaded = connect(m_ptrBlockTextDocument, &RollScriptBlockTextDocument::documentLoaded, this, &RollScriptBlockTextWidget::updateFromBlockTextDocument);
    updateFromBlockTextDocument();
}

void RollScriptBlockTextWidget::updateFromBlockTextDocument()
{
    QSignalBlocker blockerTextLine3(ui->widget_TextLine3);
    QSignalBlocker blockerTextLine2(ui->widget_TextLine2);
    QSignalBlocker blockerTextLine1(ui->widget_TextLine1);
    QSignalBlocker blockerTextLine0(ui->widget_TextLine0);

    ui->widget_TextLine0->setEnabled(true);

    bool bEnabled = m_ptrBlockTextDocument->textLine(0)->lineActive();
    ui->widget_TextLine1->setEnabled(bEnabled);

    if(bEnabled)
        bEnabled = m_ptrBlockTextDocument->textLine(1)->lineActive();

    ui->widget_TextLine2->setEnabled(bEnabled);

    if(bEnabled)
        bEnabled = m_ptrBlockTextDocument->textLine(2)->lineActive();

    ui->widget_TextLine3->setEnabled(bEnabled);
}

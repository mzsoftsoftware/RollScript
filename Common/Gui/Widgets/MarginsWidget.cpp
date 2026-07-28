#include "MarginsWidget.h"
#include "ui_MarginsWidget.h"


MarginsWidget::MarginsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MarginsWidget)
{
    ui->setupUi(this);

    ui->doublePairWidget_MarginsLeftRight->setSuffixOne(" mm");
    ui->doublePairWidget_MarginsLeftRight->setSuffixTwo(" mm");

    ui->doublePairWidget_MarginsTopBottom->setSuffixOne(" mm");
    ui->doublePairWidget_MarginsTopBottom->setSuffixTwo(" mm");

    retranslateUi();

    connect(ui->doublePairWidget_MarginsLeftRight, &DoublePairWidget::valueOneEdited, this, &MarginsWidget::slot_LeftValueEdited);
    connect(ui->doublePairWidget_MarginsLeftRight, &DoublePairWidget::valueTwoEdited, this, &MarginsWidget::slot_RightValueEdited);

    connect(ui->doublePairWidget_MarginsTopBottom, &DoublePairWidget::valueOneEdited, this, &MarginsWidget::slot_TopValueEdited);
    connect(ui->doublePairWidget_MarginsTopBottom, &DoublePairWidget::valueTwoEdited, this, &MarginsWidget::slot_BottomValueEdited);
}

MarginsWidget::~MarginsWidget()
{
    delete ui;
}

void MarginsWidget::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        retranslateUi();
    }

    QWidget::changeEvent(event);
}
void MarginsWidget::retranslateUi() const
{
    ui->doublePairWidget_MarginsLeftRight->setLabelOne(tr("Left"));
    ui->doublePairWidget_MarginsLeftRight->setLabelTwo(tr("Right"));

    ui->doublePairWidget_MarginsTopBottom->setLabelOne(tr("Top"));
    ui->doublePairWidget_MarginsTopBottom->setLabelTwo(tr("Bottom"));
}

QMarginsF MarginsWidget::marginsMm() const
{
    QMarginsF marginsMm;
    marginsMm.setLeft(ui->doublePairWidget_MarginsLeftRight->valueOne());
    marginsMm.setRight(ui->doublePairWidget_MarginsLeftRight->valueTwo());
    marginsMm.setTop(ui->doublePairWidget_MarginsTopBottom->valueOne());
    marginsMm.setBottom(ui->doublePairWidget_MarginsTopBottom->valueTwo());
    return marginsMm;
}
QMarginsF MarginsWidget::marginsMinimumMm() const
{
    QMarginsF marginsMinMm;
    marginsMinMm.setLeft(ui->doublePairWidget_MarginsLeftRight->minimumOne());
    marginsMinMm.setRight(ui->doublePairWidget_MarginsLeftRight->minimumTwo());
    marginsMinMm.setTop(ui->doublePairWidget_MarginsTopBottom->minimumOne());
    marginsMinMm.setBottom(ui->doublePairWidget_MarginsTopBottom->minimumTwo());
    return marginsMinMm;
}

void MarginsWidget::setMarginsMm(const QMarginsF& marginsMm)
{
    QSignalBlocker blockerLeftRight(ui->doublePairWidget_MarginsLeftRight);
    QSignalBlocker blockerTopBottom(ui->doublePairWidget_MarginsTopBottom);
    ui->doublePairWidget_MarginsLeftRight->setValueOne(marginsMm.left());
    ui->doublePairWidget_MarginsLeftRight->setValueTwo(marginsMm.right());
    ui->doublePairWidget_MarginsTopBottom->setValueOne(marginsMm.top());
    ui->doublePairWidget_MarginsTopBottom->setValueTwo(marginsMm.bottom());
}
void MarginsWidget::setMarginsMinimumMm(const QMarginsF& marginsMinMm)
{
    QSignalBlocker blockerLeftRight(ui->doublePairWidget_MarginsLeftRight);
    QSignalBlocker blockerTopBottom(ui->doublePairWidget_MarginsTopBottom);
    ui->doublePairWidget_MarginsLeftRight->setMinimumOne(marginsMinMm.left());
    ui->doublePairWidget_MarginsLeftRight->setMinimumTwo(marginsMinMm.right());
    ui->doublePairWidget_MarginsTopBottom->setMinimumOne(marginsMinMm.top());
    ui->doublePairWidget_MarginsTopBottom->setMinimumTwo(marginsMinMm.bottom());
}

void MarginsWidget::slot_LeftValueEdited(const double value)
{
    emit marginsMmEdited(marginsMm());
}
void MarginsWidget::slot_RightValueEdited(const double value)
{
    emit marginsMmEdited(marginsMm());
}
void MarginsWidget::slot_TopValueEdited(const double value)
{
    emit marginsMmEdited(marginsMm());
}
void MarginsWidget::slot_BottomValueEdited(const double value)
{
    emit marginsMmEdited(marginsMm());
}

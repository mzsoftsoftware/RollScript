#include "DoublePairWidget.h"
#include "ui_DoublePairWidget.h"


DoublePairWidget::DoublePairWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::DoublePairWidget)
{
    ui->setupUi(this);
}
DoublePairWidget::~DoublePairWidget()
{
    delete ui;
}

QString DoublePairWidget::labelOne() const
{
    return ui->label_One->text();
}
QString DoublePairWidget::suffixOne() const
{
    return ui->doubleSpinBox_One->suffix();
}

QString DoublePairWidget::labelTwo() const
{
    return ui->label_Two->text();
}
QString DoublePairWidget::suffixTwo() const
{
    return ui->doubleSpinBox_Two->suffix();
}

double DoublePairWidget::valueOne() const
{
    return ui->doubleSpinBox_One->value();
}
double DoublePairWidget::valueTwo() const
{
    return ui->doubleSpinBox_Two->value();
}

double DoublePairWidget::minimumOne() const
{
    return ui->doubleSpinBox_One->minimum();
}
double DoublePairWidget::minimumTwo() const
{
    return ui->doubleSpinBox_Two->minimum();
}

void DoublePairWidget::setLabelOne(const QString& qstrLabel)
{
    ui->label_One->setText(qstrLabel);
}
void DoublePairWidget::setSuffixOne(const QString& qstrSuffix)
{
    ui->doubleSpinBox_One->setSuffix(qstrSuffix);
}

void DoublePairWidget::setLabelTwo(const QString& qstrLabel)
{
    ui->label_Two->setText(qstrLabel);
}
void DoublePairWidget::setSuffixTwo(const QString& qstrSuffix)
{
    ui->doubleSpinBox_Two->setSuffix(qstrSuffix);
}

void DoublePairWidget::setValueOne(const double dblValue)
{
    QSignalBlocker b(ui->doubleSpinBox_One);
    ui->doubleSpinBox_One->setValue(dblValue);
    if(ui->toolButton->isChecked())
    {
        QSignalBlocker b(ui->doubleSpinBox_Two);
        ui->doubleSpinBox_Two->setValue(dblValue);
    }
}
void DoublePairWidget::setMinimumOne(const double dblValue)
{
    //QSignalBlocker b(ui->doubleSpinBox_One);
    ui->doubleSpinBox_One->setMinimum(dblValue);
    if(ui->doubleSpinBox_One->value() < dblValue)
    {
        ui->doubleSpinBox_One->setValue(dblValue);
    }
}

void DoublePairWidget::setValueTwo(const double dblValue)
{
    QSignalBlocker b(ui->doubleSpinBox_Two);
    ui->doubleSpinBox_Two->setValue(dblValue);
}
void DoublePairWidget::setMinimumTwo(const double dblValue)
{
    //QSignalBlocker b(ui->doubleSpinBox_Two);
    ui->doubleSpinBox_Two->setMinimum(dblValue);
    if(ui->doubleSpinBox_Two->value() < dblValue)
    {
        ui->doubleSpinBox_Two->setValue(dblValue);
    }
}

bool DoublePairWidget::isLocked() const
{
    return ui->toolButton->isChecked();
}
void DoublePairWidget::setLocked(const bool bLocked)
{
    if(bLocked != ui->toolButton->isChecked())
    {
        QSignalBlocker bTwo(ui->doubleSpinBox_Two);
        QSignalBlocker bLock(ui->toolButton);
        ui->toolButton->setChecked(bLocked);
        updateLockState();
    }
}


void DoublePairWidget::on_toolButton_toggled(bool bChecked)
{
    updateLockState();
    emit lockedToggled(bChecked);
}
void DoublePairWidget::on_doubleSpinBox_One_valueChanged(const double dblValue)
{
    emit valueOneEdited(dblValue);
    if(ui->toolButton->isChecked())
    {
        ui->doubleSpinBox_Two->setValue(dblValue);
    }
}
void DoublePairWidget::on_doubleSpinBox_Two_valueChanged(const double dblValue)
{
    emit valueTwoEdited(dblValue);
}

void DoublePairWidget::updateLockState()
{
    if(ui->toolButton->isChecked())
    {
        ui->label_Two->setEnabled(false);
        ui->doubleSpinBox_Two->setValue(ui->doubleSpinBox_One->value());
        ui->doubleSpinBox_Two->setEnabled(false);
    }
    else
    {
        ui->label_Two->setEnabled(true);
        ui->doubleSpinBox_Two->setEnabled(true);
    }
}


#include "DoublePairWidget.h"
#include "ui_DoublePairWidget.h"


DoublePairWidget::DoublePairWidget(QWidget *parent)
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

void DoublePairWidget::setLabelOne(const QString& label)
{
    ui->label_One->setText(label);
}
void DoublePairWidget::setSuffixOne(const QString& suffix)
{
    ui->doubleSpinBox_One->setSuffix(suffix);
}

void DoublePairWidget::setLabelTwo(const QString& label)
{
    ui->label_Two->setText(label);
}
void DoublePairWidget::setSuffixTwo(const QString& suffix)
{
    ui->doubleSpinBox_Two->setSuffix(suffix);
}

void DoublePairWidget::setValueOne(const double value)
{
    QSignalBlocker b(ui->doubleSpinBox_One);
    ui->doubleSpinBox_One->setValue(value);
    if(ui->toolButton->isChecked())
    {
        QSignalBlocker b(ui->doubleSpinBox_Two);
        ui->doubleSpinBox_Two->setValue(value);
    }
}
void DoublePairWidget::setMinimumOne(const double value)
{
    QSignalBlocker b(ui->doubleSpinBox_One);
    ui->doubleSpinBox_One->setMinimum(value);
    if(ui->doubleSpinBox_One->value() < value)
    {
        ui->doubleSpinBox_One->setValue(value);
    }
}

void DoublePairWidget::setValueTwo(const double value)
{
    QSignalBlocker b(ui->doubleSpinBox_Two);
    ui->doubleSpinBox_Two->setValue(value);
}
void DoublePairWidget::setMinimumTwo(const double value)
{
    QSignalBlocker b(ui->doubleSpinBox_Two);
    ui->doubleSpinBox_Two->setMinimum(value);
    if(ui->doubleSpinBox_Two->value() < value)
    {
        ui->doubleSpinBox_Two->setValue(value);
    }
}

bool DoublePairWidget::isLocked() const
{
    return ui->toolButton->isChecked();
}
void DoublePairWidget::setLocked(const bool locked)
{
    if(locked != ui->toolButton->isChecked())
    {
        QSignalBlocker bTwo(ui->doubleSpinBox_Two);
        QSignalBlocker bLock(ui->toolButton);
        ui->toolButton->setChecked(locked);
        updateLockState();
    }
}


void DoublePairWidget::on_toolButton_toggled(bool checked)
{
    updateLockState();
    emit lockedToggled(checked);
}
void DoublePairWidget::on_doubleSpinBox_One_valueChanged(const double value)
{
    emit valueOneEdited(value);
    if(ui->toolButton->isChecked())
    {
        ui->doubleSpinBox_Two->setValue(value);
    }
}
void DoublePairWidget::on_doubleSpinBox_Two_valueChanged(const double value)
{
    emit valueTwoEdited(value);
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


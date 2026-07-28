#pragma once

#include <QWidget>
#include <QString>

namespace Ui {
class DoublePairWidget;
}


class DoublePairWidget : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QString labelOne READ labelOne WRITE setLabelOne)
    Q_PROPERTY(QString suffixOne READ suffixOne WRITE setSuffixOne)
    Q_PROPERTY(double valueOne READ valueOne WRITE setValueOne NOTIFY valueOneEdited)
    Q_PROPERTY(double minimumOne READ minimumOne WRITE setMinimumOne)

    Q_PROPERTY(QString labelTwo READ labelTwo WRITE setLabelTwo)
    Q_PROPERTY(QString suffixTwo READ suffixTwo WRITE setSuffixTwo)
    Q_PROPERTY(double valueTwo READ valueTwo WRITE setValueTwo NOTIFY valueTwoEdited)
    Q_PROPERTY(double minimumTwo READ minimumTwo WRITE setMinimumTwo)

    Q_PROPERTY(bool locked READ isLocked WRITE setLocked NOTIFY lockedToggled)

public:
    explicit DoublePairWidget(QWidget *parent);
    virtual ~DoublePairWidget() override;

    QString labelOne() const;
    QString suffixOne() const;
    QString labelTwo() const;
    QString suffixTwo() const;

    double valueOne() const;
    double minimumOne() const;
    double valueTwo() const;
    double minimumTwo() const;

    void setLabelOne(const QString& label);
    void setSuffixOne(const QString& suffix);
    void setLabelTwo(const QString& label);
    void setSuffixTwo(const QString& suffix);

    void setValueOne(const double value);
    void setMinimumOne(const double value);
    void setValueTwo(const double value);
    void setMinimumTwo(const double value);

    bool isLocked() const;
    void setLocked(const bool locked);

signals:
    void valueOneEdited(const double value);
    void valueTwoEdited(const double value);
    void lockedToggled(const bool locked);

private slots:
    void on_toolButton_toggled(bool checked);
    void on_doubleSpinBox_One_valueChanged(const double value);
    void on_doubleSpinBox_Two_valueChanged(const double value);

private:
    void updateLockState();

private:
    Ui::DoublePairWidget *ui;
};


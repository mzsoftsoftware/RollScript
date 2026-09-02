#pragma once
// clazy:excludeall=connect-by-name

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
    // Constructor / Destructor
    explicit DoublePairWidget(QWidget* parent);
    ~DoublePairWidget() override;

    // Getters
    QString labelOne() const;
    QString suffixOne() const;
    QString labelTwo() const;
    QString suffixTwo() const;

    double valueOne() const;
    double minimumOne() const;
    double valueTwo() const;
    double minimumTwo() const;

    // Setters
    void setLabelOne(const QString& qstrLabel);
    void setSuffixOne(const QString& qstrSuffix);
    void setLabelTwo(const QString& qstrLabel);
    void setSuffixTwo(const QString& qstrSuffix);

    void setValueOne(const double dblValue);
    void setMinimumOne(const double dblValue);
    void setValueTwo(const double dblValue);
    void setMinimumTwo(const double dblValue);

    // Operations
    bool isLocked() const;
    void setLocked(const bool bLocked);

signals:
    void valueOneEdited(const double dblValue);
    void valueTwoEdited(const double dblValue);
    void lockedToggled(const bool bLocked);

private slots:
    void on_toolButton_toggled(bool bChecked);
    void on_doubleSpinBox_One_valueChanged(const double dblValue);
    void on_doubleSpinBox_Two_valueChanged(const double dblValue);

private:
    void updateLockState();

private:
    Ui::DoublePairWidget* ui;
};


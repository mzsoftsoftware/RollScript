#pragma once

#include <QWidget>

namespace Ui {
class MarginsWidget;
}


class MarginsWidget : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QMarginsF marginsMm READ marginsMm WRITE setMarginsMm NOTIFY marginsMmEdited)
    Q_PROPERTY(QMarginsF marginsMinimumMm READ marginsMinimumMm WRITE setMarginsMinimumMm)

public:
    explicit MarginsWidget(QWidget *parent);
    virtual ~MarginsWidget() override;

    QMarginsF marginsMm() const;
    QMarginsF marginsMinimumMm() const;

    void setMarginsMm(const QMarginsF& marginsMm);
    void setMarginsMinimumMm(const QMarginsF& marginsMinMm);

protected:
    void changeEvent(QEvent *event) override;

private:
    void retranslateUi() const;

signals:
    void marginsMmEdited(const QMarginsF& marginsMm);

private slots:
    void slot_LeftValueEdited(const double value);
    void slot_RightValueEdited(const double value);
    void slot_TopValueEdited(const double value);
    void slot_BottomValueEdited(const double value);

private:
    Ui::MarginsWidget *ui;
};

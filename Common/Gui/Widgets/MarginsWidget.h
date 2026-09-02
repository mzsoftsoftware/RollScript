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
    // Constructor / Destructor
    explicit MarginsWidget(QWidget* parent);
    ~MarginsWidget() override;

    // Getter
    QMarginsF marginsMm() const;
    QMarginsF marginsMinimumMm() const;

    // Setter
    void setMarginsMm(const QMarginsF& marginsMm);
    void setMarginsMinimumMm(const QMarginsF& marginsMinMm);

signals:
    void marginsMmEdited(const QMarginsF& marginsMm);

protected:
    void changeEvent(QEvent* ptrEvent) override;

private:
    void retranslateUi() const;

private slots:
    void slot_LeftValueEdited(const double dblValue);
    void slot_RightValueEdited(const double dblValue);
    void slot_TopValueEdited(const double dblValue);
    void slot_BottomValueEdited(const double dblValue);

private:
    Ui::MarginsWidget* ui;
};

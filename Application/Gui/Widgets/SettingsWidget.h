#pragma once

#include <QWidget>

class RollScriptDocument;
class RollScriptDocumentSettings;

namespace Ui {
class SettingsWidget;
}


class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget *parent);
    virtual ~SettingsWidget();

    void setRollScriptDocument(RollScriptDocument* ptrDocument);

protected:
    void changeEvent(QEvent *event) override;

private slots:
    void updateUiFromDocument();

    void on_comboBox_LabelMedia_currentIndexChanged(int index);
    void on_doubleSpinBox_LengthMin_valueChanged(double value);
    void on_marginsWidget_marginsMmEdited(QMarginsF margins);

private:
    Ui::SettingsWidget *ui;

    RollScriptDocument* m_ptrDocument;
    RollScriptDocumentSettings* m_ptrDocumentSettings;
};

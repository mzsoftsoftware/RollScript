#pragma once
// clazy:excludeall=connect-by-name

#include <QWidget>

class RollScriptBlockTextLineDocument;

namespace Ui {
class RollScriptBlockTextLineWidget;
}


class RollScriptBlockTextLineWidget : public QWidget
{
    Q_OBJECT

public:
    // Constructor / Destructor
    explicit RollScriptBlockTextLineWidget(QWidget* parent);
    ~RollScriptBlockTextLineWidget() override;

    // Setter
    void setDocumentBlockTextLine(RollScriptBlockTextLineDocument* ptrBlockTextLineDocument);

signals:
    void lineActiveChanged();

private slots:
    void updateFromBlockTextLineDocument();
    void on_checkBox_Active_toggled(bool checked);
    void on_lineEdit_Text_textChanged(const QString& qstrText);
    void on_fontComboBox_Font_currentFontChanged(const QFont& font);
    void on_toolButton_FontBold_toggled(bool checked);
    void on_toolButton_FontItalic_toggled(bool checked);
    void on_spinBox_FontSize_valueChanged(int iSize);
    void on_comboBox_Alignment_currentIndexChanged(int index);

private:
    void setupComboAlignment();
    void updateActiveStatus(bool bActive);

private:
    Ui::RollScriptBlockTextLineWidget* ui;

    RollScriptBlockTextLineDocument*    m_ptrBlockTextLineDocument;
    QMetaObject::Connection             m_connBlockTextLineDocumentCleared;
    QMetaObject::Connection             m_connBlockTextLineDocumentLoaded;
};

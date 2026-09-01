#pragma once

#include <QWidget>

class RollScriptRenderer;
class RollScriptDocument;


class PreviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PreviewWidget(QWidget *parent);
    virtual ~PreviewWidget();

    void setRollScriptRenderer(RollScriptRenderer* ptrRenderer);
    void setRollScriptDocument(RollScriptDocument* ptrDocument);

private slots:
    void slot_RollScriptDocument_Changed();
    void slot_TimerUpdate();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    RollScriptRenderer* m_ptrRenderer = nullptr;
    RollScriptDocument* m_ptrDocument = nullptr;

    QTimer* m_ptrTimerUpdate = nullptr;
    QImage m_imagePreview;
};

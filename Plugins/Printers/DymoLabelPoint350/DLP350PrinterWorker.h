#pragma once

#include <QObject>

#include <QQueue>

class QThread;
class DymoLabelPoint350PrinterJob;
class RollScriptError;


class DymoLabelPoint350PrinterWorker : public QObject
{
    Q_OBJECT
public:
    explicit DymoLabelPoint350PrinterWorker(QObject *parent = nullptr);
    ~DymoLabelPoint350PrinterWorker() override;

    RollScriptError* jobError();

public slots:
    void enqueueJob(DymoLabelPoint350PrinterJob* ptrJob);

private slots:
    void slotProcessQueue();

private:
    QQueue<DymoLabelPoint350PrinterJob*> m_queue;
    bool m_bProcessing = false;

    RollScriptError* m_ptrLastError = nullptr;
};

#pragma once

#include <QAbstractListModel>

class PrinterManager;


class PrintersItemModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit PrintersItemModel(PrinterManager* ptrPrinterManager, QObject *parent);
    virtual ~PrintersItemModel();

    void rebuildModel();

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    PrinterManager*  m_ptrPrinterManager = nullptr;
    QStringList     m_qstrPrinterIds;
};

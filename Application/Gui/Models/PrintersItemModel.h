#pragma once

#include <QAbstractListModel>

class PrinterManager;


class PrintersItemModel : public QAbstractListModel
{
    Q_OBJECT

public:
    // Constructor / Destructor
    explicit PrintersItemModel(PrinterManager* ptrPrinterManager, QObject* parent);
    ~PrintersItemModel() override;

    // Operations
    void rebuildModel();

    // Basic functionality:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int iRole = Qt::DisplayRole) const override;

private:
    PrinterManager* m_ptrPrinterManager = nullptr;
    QStringList     m_qstrPrinterIds;
};

#pragma once

#include <QAbstractListModel>

class PrinterManager;


class PrinterMediasItemModel : public QAbstractListModel
{
    Q_OBJECT

public:
    // Constructor / Destructor
    explicit PrinterMediasItemModel(PrinterManager* ptrPrinterManager, QObject* parent);
    ~PrinterMediasItemModel() override;

    // Operations
    void rebuildModel();

    // Basic functionality:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

private:
    PrinterManager* m_ptrPrinterManager = nullptr;
    QStringList     m_qstrPrinterMediaIds;
};

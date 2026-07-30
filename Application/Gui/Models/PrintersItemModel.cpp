#include "PrintersItemModel.h"

#include "Core/Printers/PrinterManager.h"
#include "Core/Printers/PrinterInstance.h"


PrintersItemModel::PrintersItemModel(PrinterManager* ptrPrinterManager, QObject *parent)
    : QAbstractListModel(parent)
    , m_ptrPrinterManager(ptrPrinterManager)
{
}
PrintersItemModel::~PrintersItemModel()
{
}

int PrintersItemModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_qstrPrinterIds.count();
}

QVariant PrintersItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(index.row() < 0 || index.row() >= m_qstrPrinterIds.count())
        return QVariant();

    const QString& qstrId = m_qstrPrinterIds.at(index.row());
    PrinterInstance* ptrPrinterInstance = m_ptrPrinterManager->printerInstance(qstrId);

    switch(role)
    {
    case Qt::DisplayRole:
        return ptrPrinterInstance->displayName();
    case Qt::DecorationRole:
        return ptrPrinterInstance->icon();
    case Qt::UserRole:
        return qstrId;
    }

    return QVariant();
}

void PrintersItemModel::rebuildModel()
{
    beginResetModel();

    m_qstrPrinterIds.clear();
    m_qstrPrinterIds = m_ptrPrinterManager->availablePrinterIds();

    endResetModel();
}

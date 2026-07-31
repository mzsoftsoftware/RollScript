#include "PrinterMediasItemModel.h"

#include "Core/Printers/PrinterManager.h"
#include "Common/Core/Printers/PrinterInstance.h"
#include "Common/Core/Printers/PrinterMedia.h"


PrinterMediasItemModel::PrinterMediasItemModel(PrinterManager* ptrPrinterManager, QObject *parent)
    : QAbstractListModel(parent)
    , m_ptrPrinterManager(ptrPrinterManager)
{
}
PrinterMediasItemModel::~PrinterMediasItemModel()
{
}

int PrinterMediasItemModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_qstrPrinterMediaIds.count();
}

QVariant PrinterMediasItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(index.row() < 0 || index.row() >= m_qstrPrinterMediaIds.count())
        return QVariant();

    const QString& qstrId = m_qstrPrinterMediaIds.at(index.row());
    PrinterInstance* ptrPrinterInstance = m_ptrPrinterManager->currentPrinter();
    PrinterMedia* ptrPrinterMedia = ptrPrinterInstance->media(qstrId);

    switch(role)
    {
    case Qt::DisplayRole:
        return ptrPrinterMedia->displayName();
    case Qt::DecorationRole:
        return ptrPrinterMedia->icon();
    case Qt::UserRole:
        return qstrId;
    }

    return QVariant();
}

void PrinterMediasItemModel::rebuildModel()
{
    beginResetModel();

    m_qstrPrinterMediaIds.clear();

    PrinterInstance* ptrPrinterInstance = m_ptrPrinterManager->currentPrinter();
    if(ptrPrinterInstance)
    {
        m_qstrPrinterMediaIds = ptrPrinterInstance->availableMediaIds();
    }

    endResetModel();
}

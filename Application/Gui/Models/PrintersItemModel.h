#pragma once

#include <QAbstractListModel>

class DeviceManager;


class PrintersItemModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit PrintersItemModel(DeviceManager* ptrDeviceManager, QObject *parent);
    virtual ~PrintersItemModel();

    void rebuildModel();

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    DeviceManager*  m_ptrDeviceManager = nullptr;
    QStringList     m_qstrPrinterIds;
};

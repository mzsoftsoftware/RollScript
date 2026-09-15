#include "DialogAboutPrintersWidget.h"
#include "ui_DialogAboutPrintersWidget.h"

#include "DialogAboutTableItemDelegate.h"
#include "Plugins/PrinterPluginRegistry.h"
#include "Core/Plugins/IPrinterPlugin.h"
#include "Core/Plugins/IPrinterPluginInfo.h"


DialogAboutPrintersWidget::DialogAboutPrintersWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::DialogAboutPrintersWidget)
{
    ui->setupUi(this);

    ui->tableWidget->setItemDelegate(new DialogAboutTableItemDelegate(ui->tableWidget));
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
}

DialogAboutPrintersWidget::~DialogAboutPrintersWidget()
{
    delete ui;
}

void DialogAboutPrintersWidget::setPrinterPluginRegistry(const PrinterPluginRegistry* ptrPrinterPluginRegistry)
{
    Q_ASSERT(ptrPrinterPluginRegistry);

    const QStringList qstrPluginIds = ptrPrinterPluginRegistry->availablePrinterPluginIds();
    for(const QString& qstrPluginId : qstrPluginIds)
    {
        IPrinterPlugin* ptrPrinterPlugin = ptrPrinterPluginRegistry->printerPlugin(qstrPluginId);
        Q_ASSERT(ptrPrinterPlugin);

        const IPrinterPluginInfo* ptrPluginInfo = ptrPrinterPlugin->printerPluginInfo();
        Q_ASSERT(ptrPluginInfo);

        const int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        QTableWidgetItem* ptrItem = new QTableWidgetItem(ptrPluginInfo->pluginDisplayName());
        ptrItem->setData( Qt::DecorationRole, ptrPluginInfo->pluginIcon());
        ui->tableWidget->setItem(row, 0, ptrItem);

        QTableWidgetItem* ptrItemVersion = new QTableWidgetItem(ptrPluginInfo->pluginVersion());
        ui->tableWidget->setItem(row, 1, ptrItemVersion);

        ui->tableWidget->setRowHeight(row, 52);
    }
}

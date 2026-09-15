#include "DialogAboutFeaturesWidget.h"
#include "ui_DialogAboutFeaturesWidget.h"

#include "DialogAboutTableItemDelegate.h"
#include "Plugins/FeaturePluginRegistry.h"
#include "Core/Plugins/IFeaturePlugin.h"
#include "Core/Plugins/IFeaturePluginInfo.h"


DialogAboutFeaturesWidget::DialogAboutFeaturesWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::DialogAboutFeaturesWidget)
{
    ui->setupUi(this);

    ui->tableWidget->setItemDelegate(new DialogAboutTableItemDelegate(ui->tableWidget));
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
}

DialogAboutFeaturesWidget::~DialogAboutFeaturesWidget()
{
    delete ui;
}

void DialogAboutFeaturesWidget::setFeaturePluginRegistry(const FeaturePluginRegistry* ptrFeaturePluginRegistry)
{
    Q_ASSERT(ptrFeaturePluginRegistry);

    const QStringList qstrPluginIds = ptrFeaturePluginRegistry->availableFeaturePluginIds();
    for(const QString& qstrPluginId : qstrPluginIds)
    {
        IFeaturePlugin* ptrFeaturePlugin = ptrFeaturePluginRegistry->featurePlugin(qstrPluginId);
        Q_ASSERT(ptrFeaturePlugin);

        const IFeaturePluginInfo* ptrPluginInfo = ptrFeaturePlugin->featurePluginInfo();
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
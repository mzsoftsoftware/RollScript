#include "DialogAboutComponentsWidget.h"
#include "ui_DialogAboutComponentsWidget.h"

#include "DialogAboutTableItemDelegate.h"

#include <QTableWidgetItem>
#include <QGuiApplication>
#include <QSysInfo>


DialogAboutComponentsWidget::DialogAboutComponentsWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::DialogAboutComponentsWidget)
{
    ui->setupUi(this);

    ui->tableWidget->setItemDelegate(new DialogAboutTableItemDelegate(ui->tableWidget));
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);

    addComponent(tr("Application"), tr("Rollscript application"), QStringLiteral(ROLLSCRIPT_APPLICATION_VERSION));
    addComponent(tr("Core"), tr("Rollscript Core library"), QStringLiteral("0.1.0"));
    addComponent(tr("USB"), tr("LibUSB Libraray"), QStringLiteral(LIBUSB_VERSION));
    addComponent(tr("Qt"), tr("Qt Version"), QString::fromLatin1(qVersion()));
    addComponent(tr("Target system"), tr("Operating system and windowing system"), targetSystem());
}

DialogAboutComponentsWidget::~DialogAboutComponentsWidget()
{
    delete ui;
}

void DialogAboutComponentsWidget::addComponent(const QString& title, const QString& description, const QString& value)
{
    const int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    QTableWidgetItem* pItem = new QTableWidgetItem(title);
    pItem->setData(DialogAboutTableItemDelegate::DescriptionRole, description);
    ui->tableWidget->setItem(row, 0, pItem);

    QTableWidgetItem* pItemValue = new QTableWidgetItem(value);
    ui->tableWidget->setItem(row, 1, pItemValue);

    ui->tableWidget->setRowHeight(row, 52);
}

QString DialogAboutComponentsWidget::targetOperatingSystem()
{
    return QSysInfo::prettyProductName();
}
QString DialogAboutComponentsWidget::targetWindowingSystem()
{
    const QString platform = QGuiApplication::platformName();
    if (platform == QStringLiteral("wayland"))
        return QStringLiteral("Wayland");
    if (platform == QStringLiteral("xcb"))
        return QStringLiteral("X11");
    if (platform == QStringLiteral("windows"))
        return QStringLiteral("Windows");
    if (platform == QStringLiteral("cocoa"))
        return QStringLiteral("Cocoa");
    return platform;
}
QString DialogAboutComponentsWidget::targetSystem()
{
    const QString operatingSystem = targetOperatingSystem();
    const QString windowingSystem = targetWindowingSystem();

    if (windowingSystem.isEmpty())
        return operatingSystem;

    return QStringLiteral("%1 (%2)").arg(operatingSystem, windowingSystem);
}

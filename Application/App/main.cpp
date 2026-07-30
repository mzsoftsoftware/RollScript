#include "MainWindow.h"

#include <QApplication>
#include <QLockFile>
#include <QDir>
#include <QMessageBox>

#include "Core/ApplicationContext.h"
#include "Core/Translation/TranslationManager.h"
#include "Core/Plugins/PluginManager.h"
#include "Core/Printers/PrinterManager.h"


#include <iostream>
void messageHandler(
    QtMsgType type,
    const QMessageLogContext &context,
    const QString &msg
    )
{
    Q_UNUSED(type)
    Q_UNUSED(context)

    std::cerr
        << "MESSAGE HANDLER: "
        //<< type.
        << msg.toStdString()
        << std::endl;
}


int main(int argc, char *argv[])
{
    qInstallMessageHandler(messageHandler);

    QApplication app(argc, argv);

    //qDebug() << "qDebug funktioniert";
    //qInfo() << "qInfo funktioniert";
    //qWarning() << "qWarning funktioniert";
    //qCritical() << "qCritical funktioniert";

    QLockFile lockFile(
        QDir::temp().absoluteFilePath("DymoLabelKit.lock"));
    if (!lockFile.tryLock())
    {
        // TASK : Use correct tr !!!
        QMessageBox::warning(
            nullptr,
            QObject::tr("Programm läuft bereits"),
            QObject::tr("DymoLabelKit ist bereits gestartet."));
        return 1;
    }


    TranslationManager translationManager(&app);
    if(!translationManager.loadSystemLanguage())
    {
        QMessageBox::critical(nullptr, "Startup", translationManager.lastError());
        return EXIT_FAILURE;
    }

    PluginManager pluginManager(&app);
    if(!pluginManager.loadPlugins())
    {
        QMessageBox::critical(nullptr, "Startup", pluginManager.lastError());
        return EXIT_FAILURE;
    }

    PrinterManager printerManager(&pluginManager, &app);

    ApplicationContext context(&translationManager, &pluginManager, &printerManager);

    MainWindow w(&context);
    w.show();

    return app.exec();
}

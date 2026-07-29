#include "MainWindow.h"

#include <QApplication>
#include <QMessageBox>

#include "Core/Translation/TranslationManager.h"
#include "Core/Plugins/PluginManager.h"

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

    MainWindow w(&translationManager, &pluginManager);
    w.show();

    return app.exec();
}

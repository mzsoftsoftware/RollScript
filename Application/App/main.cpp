#include "MainWindow.h"

#include <QApplication>

#include "App/ApplicationContext.h"


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

    ApplicationContext context(&app);
    if(!context.init())
        return EXIT_FAILURE;

    MainWindow w(&context);
    w.show();

    return app.exec();
}

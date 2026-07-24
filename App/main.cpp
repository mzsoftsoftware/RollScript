#include "MainWindow.h"

#include <QApplication>

#include "Core/Translation/TranslationManager.h"

//#include <QDebug>
//#include <QLoggingCategory>

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

    QApplication a(argc, argv);

    //qDebug() << "qDebug funktioniert";
    //qInfo() << "qInfo funktioniert";
    //qWarning() << "qWarning funktioniert";
    //qCritical() << "qCritical funktioniert";

    TranslationManager translationManager;
    translationManager.loadSystemLanguage();

    MainWindow w(&translationManager);
    w.show();

    return QApplication::exec();
}

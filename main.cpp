#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "SimpleFileExporter.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    SimpleFileExporter exporter;
    engine.rootContext()->setContextProperty("fileExporter", &exporter);

    const QUrl url(u"qrc:/Page2.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
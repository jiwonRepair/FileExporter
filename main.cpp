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

    // ✅ QML 로딩
    engine.load(QUrl::fromLocalFile("D:/qtprojects/FileExporter/Page2.qml"));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

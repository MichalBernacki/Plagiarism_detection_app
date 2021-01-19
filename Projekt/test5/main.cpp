#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "counter.h"
#include "speed.h"
#include "displacement.h"
#include "acceleration.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<Counter>("pl.gwizdz", 1, 0, "Counter");
    qmlRegisterType<Acceleration>("pl.acc", 1, 0, "Acceleration");
    qmlRegisterType<Displacement>("pl.dsc", 1, 0, "Displacement");
    qmlRegisterType<Speed>("pl.spd", 1, 0, "Speed");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    auto counter = engine.rootObjects().first()->findChild<Counter*>();
    counter->initialise(10);

    return app.exec();
}

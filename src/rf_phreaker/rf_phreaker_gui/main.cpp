#include <QtWidgets/QApplication>
#include <QtQml/QQmlApplicationEngine>
#include "rf_phreaker/rf_phreaker_gui/RpPlugin.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    registerQmlTypes();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

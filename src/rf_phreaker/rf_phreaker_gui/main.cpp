#include <QApplication>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtGui/QFontDatabase>
#include <QtCore/QDir>

#include "rf_phreaker/rf_phreaker_gui/ApiPlugin.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	//app.setOrganizationName("Cappeen");
	app.setOrganizationDomain("cappeen.com");
	app.setApplicationName("rf_phreaker");

	registerQmlTypes();

	QQmlApplicationEngine engine;
	if (qgetenv("QT_QUICK_CONTROLS_STYLE").isEmpty()) {
		qputenv("QT_QUICK_CONTROLS_STYLE", "Flat");
	}
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

	return app.exec();
}

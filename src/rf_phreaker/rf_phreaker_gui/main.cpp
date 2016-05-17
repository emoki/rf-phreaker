#include <QApplication>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtGui/QFontDatabase>
#include <QtCore/QDir>

#include "marble/declarative/MarbleDeclarativePlugin.h"
#include "rf_phreaker/rf_phreaker_gui/ApiPlugin.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	//app.setOrganizationName("Cappeen");
	app.setOrganizationDomain("cappeen.com");
	app.setApplicationName("rf_phreaker");

	MarbleDeclarativePlugin declarativePlugin;
	const char * marbleUri = "org.kde.edu.marble";
	declarativePlugin.registerTypes(marbleUri);

	registerQmlTypes();

	QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QQmlApplicationEngine engine;
	if (qgetenv("QT_QUICK_CONTROLS_STYLE").isEmpty()) {
		qputenv("QT_QUICK_CONTROLS_STYLE", "Material");
	}
	declarativePlugin.initializeEngine(&engine, marbleUri);
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

	return app.exec();
}

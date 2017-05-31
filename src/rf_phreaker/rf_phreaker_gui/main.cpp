#include <QApplication>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtGui/QFontDatabase>
#include <QtCore/QDir>
#include "marble/declarative/MarbleDeclarativePlugin.h"
#include "rf_phreaker/rf_phreaker_gui/ApiPlugin.h"
#include "rf_phreaker/rf_phreaker_gui/MarbleLayerManager.h"
#include "rf_phreaker/rf_phreaker_gui/MessageHandler.h"
#include <QtDataVisualization/qutils.h>// Has to go after ApiPlugin.h

int main(int argc, char *argv[]) {
	int status = 0;

	// Construct message handler.
	MessageHandler::instance();

	//qputenv("QML_IMPORT_TRACE", "1");
	QApplication app(argc, argv);
	app.setOrganizationDomain("cappeen.com");
	app.setApplicationName("rf_phreaker");

	MarbleDeclarativePlugin declarativePlugin;
	const char * marbleUri = "org.kde.edu.marble";
	declarativePlugin.registerTypes(marbleUri);

	// Instantiate MarbleLayerManager so that we can use the MarbleModel
	// within multiple MarbleMaps.
	MarbleLayers::instance();

	registerQmlTypes();

	{
		QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
		QQmlApplicationEngine engine;
		declarativePlugin.initializeEngine(&engine, marbleUri);
		MessageHandler::logToApi(true);
		engine.load(QUrl(QStringLiteral("qrc:/MaterialMain.qml")));
		
		//// Enable antialiasing in direct rendering mode
		//// TODO - Look into using this for spectrum graph.
		//auto windowList = app.topLevelWindows();
		//for(auto &i : windowList) {
		//	i->setFormat(QtDataVisualization::qDefaultSurfaceFormat());
		//}

		status = app.exec();

		// When the event loop is destroyed for the application we have to disable the MessageHandler
		// from posting events to the event loop.
		MessageHandler::logToApi(false);
	}

	// MarbleLayers is destroyed after qml has destroy MarbleManager to stop a crash from occurring inside
	// qt5network.dll.  It seems to happen when exiting while we are loading new tiles.
	MarbleLayers::destroy();

	return status;
}

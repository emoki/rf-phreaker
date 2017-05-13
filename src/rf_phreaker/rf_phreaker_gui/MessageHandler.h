#pragma once
#include <QDateTime>
#include <QString>
#include <QDebug>
#include <QDir>
#include "rf_phreaker/rf_phreaker_gui/Api.h"
#include "rf_phreaker/rf_phreaker_gui/ApiMessage.h"
#include "rf_phreaker/rf_phreaker_gui/Events.h"
#include "rf_phreaker/qt_specific/qt_utility.h"
#include "rf_phreaker/qt_specific/settings_io.h"

class MessageHandler {
public:
	static MessageHandler& instance() {
		static MessageHandler handler;
		return handler;
	}

	static void stopLogging() {
		qInstallMessageHandler(0);
	}

	static void logToApi(bool enable) {
		outputToApi_ = enable;
	}
	
	static void output(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
		auto s = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss.z\t");
		switch(type) {
		case QtDebugMsg:
			s += "DEBUG ";
			break;
		case QtInfoMsg:
			s += "INFO ";
			break;
		case QtWarningMsg:
			s += "WARNING ";
			break;
		case QtCriticalMsg:
			s += "CRITICAL ";
			break;
		case QtFatalMsg: 
			{
				QByteArray localMsg = msg.toLocal8Bit();
				fprintf(stderr, "FATAL: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
				abort();
			}
			break;
		default:;
		}

		QString fn(context.file);
		fn = fn.remove(0, fn.lastIndexOf(QRegExp("[/\\\\]")) + 1);
		s += "[" + fn + " L: " + QString::number(context.line) + "]\t\"" + msg + "\"";

		if(outputToApi_)
			QCoreApplication::postEvent(Api::instance(), new LogUpdateEvent(s));

		static std::ofstream f;
		static bool fileOpenAttempt = false;
		if (!fileOpenAttempt) {
			fileOpenAttempt = true;
			rf_phreaker::settings_io io("rf_phreaker_api", rf_phreaker::qt_utility::app_name());
			QString filePath;
			if (io.does_exist()) {
				rf_phreaker::settings config;
				io.read(config);
				filePath = config.output_directory_.c_str();
			}
			f.open(QString(filePath + QDir::separator() + "rf_phreaker_gui.log").toStdString());
		}
		f << s.toStdString().c_str() << std::endl;
	}

private:
	MessageHandler() {
		qInstallMessageHandler(MessageHandler::output);
		//qSetMessagePattern("%{time yyyy/MM/dd hh:mm:ss.zzzzzzz}\t%{category}\t%{file}:%{line}\t%{message}");
	}
	static bool outputToApi_;
};
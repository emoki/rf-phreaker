#pragma once
#include <QDateTime>
#include <QString>
#include <QDebug>
#include "rf_phreaker/rf_phreaker_gui/Api.h"
#include "rf_phreaker/rf_phreaker_gui/ApiMessage.h"
#include "rf_phreaker/rf_phreaker_gui/Events.h"

class MessageHandler {
public:
	static MessageHandler& instance() {
		static MessageHandler handler;
		return handler;
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

		QCoreApplication::postEvent(Api::instance(), new LogUpdateEvent(s));

		static std::ofstream f("gui_log.txt");
		f << s.toStdString().c_str() << std::endl;
	}

private:
	MessageHandler() {
		qInstallMessageHandler(MessageHandler::output);
		//qSetMessagePattern("%{time yyyy/MM/dd hh:mm:ss.zzzzzzz}\t%{category}\t%{file}:%{line}\t%{message}");
	}
};
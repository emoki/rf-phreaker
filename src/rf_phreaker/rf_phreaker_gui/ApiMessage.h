#pragma once
#include <QObject>
#include <QString>
#include "rf_phreaker/rf_phreaker_gui/ApiTypes.h"
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_conversion.h"
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"

// Only processes a formatted message.
// Example: "2016/12/11 12:13:51.877	DEBUG [qqmldebug.cpp L: 46]	"QML debugging is enabled. Only use this in a safe environment.""
class ApiMessage : public QObject {
	Q_OBJECT
	Q_PROPERTY(QString rpStatusStr READ rpStatusStr CONSTANT)
	Q_PROPERTY(QString mainDescription READ mainDescription CONSTANT)
	Q_PROPERTY(QString details READ details CONSTANT)
	Q_PROPERTY(QString time READ time CONSTANT)
	Q_PROPERTY(QString fileLine READ fileLine CONSTANT)
	Q_PROPERTY(QString detailsMsg READ detailsMsg CONSTANT)

public:
	ApiMessage(QObject *parent = 0) : QObject(parent) {}
	ApiMessage(rp_status status, const QString &mainDescription, const QString &details, QObject *parent = 0)
		: QObject(parent)
		, status_(status)
		, statusStr_(QString(rp_status_message(status_)))
		, mainDescription_(mainDescription)
		, details_(details) 
		, pos_(details_.indexOf("\t"))
	{}

	QString rpStatusStr() { return statusStr_; }
	QString mainDescription() { return mainDescription_; }
	QString details() { return details_; }
	QString time() { return details_.left(details_.indexOf("\t")); }
	QString fileLine() { return details_.mid(pos_ + 1, details_.indexOf("\t", pos_ + 1)); }
	QString detailsMsg() { return details_.right(details_.length() - details_.indexOf("\t", pos_ + 1)); }

	rp_status status_;
	QString statusStr_;
	QString mainDescription_;
	QString details_;
	int pos_;
};
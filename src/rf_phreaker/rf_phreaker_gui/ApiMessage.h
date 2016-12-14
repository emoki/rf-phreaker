#pragma once
#include <QObject>
#include <QString>
#include "rf_phreaker/rf_phreaker_gui/ApiTypes.h"
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_conversion.h"
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"

class ApiMessage : public QObject {
	Q_OBJECT
	Q_PROPERTY(QString rpStatusStr READ rpStatusStr CONSTANT)
	Q_PROPERTY(QString mainDescription READ mainDescription CONSTANT)
	Q_PROPERTY(QString details READ details CONSTANT)

public:
	ApiMessage(QObject *parent = 0) : QObject(parent) {}
	ApiMessage(rp_status status, const QString &mainDescription, const QString &details, QObject *parent = 0)
		: QObject(parent)
		, status_(status)
		, statusStr_(QString(rp_status_message(status_)))
		, mainDescription_(mainDescription)
		, details_(details) 
	{}

	QString rpStatusStr() { return statusStr_; }
	QString mainDescription() { return mainDescription_; }
	QString details() { return details_; }

	rp_status status_;
	QString statusStr_;
	QString mainDescription_;
	QString details_;
};
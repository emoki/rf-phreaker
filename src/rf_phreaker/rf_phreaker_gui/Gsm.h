#pragma once
#include <QObject>
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/rf_phreaker_gui/ApiTypes.h"
#include "rf_phreaker/rf_phreaker_gui/Base.h"
#include "rf_phreaker/common/measurements.h"

//namespace rf_phreaker { namespace gui {

class Gsm : public Base
{
	Q_OBJECT
//	Q_PROPERTY( READ WRITE set NOTIFY Changed)
//	Q_PROPERTY( READ WRITE set NOTIFY Changed)
//	Q_PROPERTY( READ WRITE set NOTIFY Changed)
//	Q_PROPERTY( READ WRITE set NOTIFY Changed)
//	Q_PROPERTY( READ WRITE set NOTIFY Changed)

public:
	explicit Gsm(QObject *parent = 0)
		: Base(gsm_, ApiTypes::GSM_FULL_SCAN, parent) {
		make_connections();
	}
	explicit Gsm(const rf_phreaker::gsm_data &gsm, QObject *parent = 0)
		: Base(gsm_, ApiTypes::GSM_FULL_SCAN, parent)
		, gsm_(gsm) {
		make_connections();
	}

	~Gsm() {}

void make_connections() {

}

signals:
	void serialChanged();

public slots:

private:
	rf_phreaker::gsm_data gsm_;
};

//}}

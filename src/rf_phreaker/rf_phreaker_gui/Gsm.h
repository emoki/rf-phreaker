#pragma once
#include <QObject>
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/rf_phreaker_gui/ApiTypes.h"
#include "rf_phreaker/rf_phreaker_gui/Base.h"

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
		: Base(parent)
	{}
	explicit Gsm(const rp_gsm& gsm, QObject *parent = 0)
		: Base(gsm.base_, parent)
	{}

	~Gsm() {}



signals:
	void serialChanged();

public slots:

private:
};

//}}

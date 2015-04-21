#pragma once
#include <QObject>
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/rf_phreaker_gui/ApiTypes.h"
#include "rf_phreaker/rf_phreaker_gui/Base.h"

//namespace rf_phreaker { namespace gui {

class Sweep : public Base {
	Q_OBJECT
//	Q_PROPERTY( READ WRITE set NOTIFY Changed)
//	Q_PROPERTY( READ WRITE set NOTIFY Changed)
//	Q_PROPERTY( READ WRITE set NOTIFY Changed)
//	Q_PROPERTY( READ WRITE set NOTIFY Changed)
//	Q_PROPERTY( READ WRITE set NOTIFY Changed)

public:
	explicit Sweep(QObject *parent = 0)
		: Base(parent)
	{}
	explicit Sweep(const rp_base &base, QObject *parent = 0)
		: Base(base, parent)
	{}

	~Sweep() {}



signals:
	void serialChanged();

public slots:

private:
};

//}}

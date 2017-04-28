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
		: Base(sweep_, ApiTypes::Tech::UNKNOWN_TECH, parent) {}
	explicit Sweep(ApiTypes::Tech tech, QObject *parent = 0)
		: Base(sweep_, ApiTypes::Tech::UNKNOWN_TECH, parent) {}
	explicit Sweep(const rf_phreaker::basic_data &base, ApiTypes::Tech tech, QObject *parent = 0)
		: Base(sweep_, tech, parent)
		, sweep_(base) {}

	~Sweep() {}

	// Normalize signal level
	QString carrierSignalLevelStr() const Q_DECL_OVERRIDE {
		return QString::number(base_.measurement_signal_level_, 'f', 1);
	}

signals:
public slots:

private:
	rf_phreaker::basic_data sweep_;
};

class GsmSweep : public Sweep {
	Q_OBJECT
public:
	explicit GsmSweep(QObject *parent = 0)
		: Sweep(ApiTypes::Tech::GSM_SWEEP, parent) {}
	explicit GsmSweep(const rf_phreaker::basic_data &base, QObject *parent = 0)
		: Sweep(base, ApiTypes::GSM_SWEEP, parent) {}
	~GsmSweep() {}

signals:
	public slots :
private:
};

class WcdmaSweep : public Sweep {
	Q_OBJECT
public:
	explicit WcdmaSweep(QObject *parent = 0)
		: Sweep(ApiTypes::Tech::WCDMA_SWEEP, parent) {}
	explicit WcdmaSweep(const rf_phreaker::basic_data &base, QObject *parent = 0)
		: Sweep(base, ApiTypes::WCDMA_SWEEP, parent) {}
	~WcdmaSweep() {}

signals:
	public slots :
private:
};

class LteSweep : public Sweep {
	Q_OBJECT
public:
	explicit LteSweep(QObject *parent = 0)
		: Sweep(ApiTypes::Tech::LTE_SWEEP, parent) {}
	explicit LteSweep(const rf_phreaker::basic_data &base, QObject *parent = 0)
		: Sweep(base, ApiTypes::LTE_SWEEP, parent) {}
	~LteSweep() {}

signals:
	public slots :
private:
};



//}}

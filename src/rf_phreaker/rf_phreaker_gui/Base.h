#pragma once
#include <QObject>
#include <QTime>
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/rf_phreaker_gui/ApiTypes.h"
#include "rf_phreaker/common/measurements.h"

//namespace rf_phreaker { namespace gui {

class Base : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString serial READ serial NOTIFY serialChanged)
	Q_PROPERTY(QString collectionRound READ collectionRound NOTIFY collectionRoundChanged)
	Q_PROPERTY(double measurementFreq READ measurementFreq NOTIFY measurementFreqChanged)
	Q_PROPERTY(double measurementBandwidth READ measurementBandwidth NOTIFY measurementBandwidthChanged)
	Q_PROPERTY(double measurementSignalLevel READ measurementSignalLevel NOTIFY measurementSignalLevelChanged)
	Q_PROPERTY(ApiTypes::Tech cellTech READ cellTech NOTIFY cellTechChanged)
	Q_PROPERTY(ApiTypes::OperatingBand cellBand READ cellBand NOTIFY cellBandChanged)
	Q_PROPERTY(int cellChannel READ cellChannel NOTIFY cellChannelChanged)
	Q_PROPERTY(int cellId READ cellId NOTIFY cellIdChanged)
	Q_PROPERTY(double cellSignalLevel READ cellSignalLevel NOTIFY cellSignalLevelChanged)
	Q_PROPERTY(double cellInterference READ cellInterference NOTIFY cellInterferenceChanged)
	Q_PROPERTY(QTime timeElapsed READ timeElapsed NOTIFY timeElapsedChanged)
	Q_PROPERTY(QString measurementFreqStr READ measurementFreqStr NOTIFY measurementFreqChanged)
	Q_PROPERTY(QString measurementBandwidthStr READ measurementBandwidthStr NOTIFY measurementBandwidthChanged)
	Q_PROPERTY(QString measurementSignalLevelStr READ measurementSignalLevelStr NOTIFY measurementSignalLevelChanged)
	Q_PROPERTY(QString cellMccStr READ cellMccStr NOTIFY cellLayer3Changed)
	Q_PROPERTY(QString cellMncStr READ cellMncStr NOTIFY cellLayer3Changed)
	Q_PROPERTY(QString cellLacTacStr READ cellLacTacStr NOTIFY cellLayer3Changed)
	Q_PROPERTY(QString cellCidStr READ cellCidStr NOTIFY cellLayer3Changed)


public:
	explicit Base(rf_phreaker::basic_data& base, ApiTypes::Tech tech, QObject *parent = 0)
		: QObject(parent)
		, base_(base)
		, tech_(tech) {
		timeElapsed_.start();
	}

	~Base() {}

	virtual void update(const rf_phreaker::basic_data &a) {
		if(base_.serial_ != a.serial_) {
			base_.serial_ = a.serial_;
			emit serialChanged();
		}
		if(base_.collection_round_ != a.collection_round_) {
			base_.collection_round_ = a.collection_round_;
			emit collectionRoundChanged();
		}
		if(base_.measurement_frequency_ != a.measurement_frequency_) {
			base_.measurement_frequency_ = a.measurement_frequency_;
			emit measurementFreqChanged();
		}
		if(base_.measurement_bandwidth_ != a.measurement_bandwidth_) {
			base_.measurement_bandwidth_ = a.measurement_bandwidth_;
			emit measurementBandwidthChanged();
		}
		if(base_.measurement_signal_level_ != a.measurement_signal_level_) {
			base_.measurement_signal_level_ = a.measurement_signal_level_;
			emit measurementSignalLevelChanged();
		}
		timeElapsed_.start();
		emit timeElapsedChanged();
	}

	virtual double measurementFreq() const { return base_.measurement_frequency_ / 1e6; }
	virtual double measurementBandwidth() const { return base_.measurement_bandwidth_ / 1e6; }
	virtual double measurementSignalLevel() const { return base_.measurement_signal_level_; }
	virtual ApiTypes::Tech cellTech() const { return tech_; }
	virtual ApiTypes::OperatingBand cellBand() const { return ApiTypes::OPERATING_BAND_UNKNOWN; }
	virtual int32_t cellChannel() const { return -1; }
	virtual int32_t cellId() const { return -1; }
	virtual double cellSignalLevel() const { return -9999; }
	virtual double cellInterference() const { return -9999; }
	virtual QString cellMccStr() const { return ""; }
	virtual QString cellMncStr() const { return ""; }
	virtual QString cellLacTacStr() const { return ""; }
	virtual QString cellCidStr() const { return ""; }

	QTime timeElapsed() const { return timeElapsed_; }
	QString serial() const { return base_.serial_.c_str(); }
	virtual int64_t collectionRound() const { return base_.collection_round_; }
	virtual QString measurementFreqStr() const { return QString::number(base_.measurement_frequency_ / 1e6, 'f', 1); }
	virtual QString measurementBandwidthStr() const { return QString::number(base_.measurement_bandwidth_ / 1e6, 'f', 1); }
	virtual QString measurementSignalLevelStr() const { return QString::number(base_.measurement_signal_level_, 'f', 1); }
	const rf_phreaker::basic_data& base() const { return base_; }

signals:
	void timeElapsedChanged();
	void serialChanged();
	void collectionRoundChanged();
	void measurementFreqChanged();
	void measurementBandwidthChanged();
	void measurementSignalLevelChanged();
	void cellTechChanged();
	void cellBandChanged();
	void cellIdChanged();
	void cellChannelChanged();
	void cellSignalLevelChanged();
	void cellInterferenceChanged();
	void cellLayer3Changed();

protected:
	rf_phreaker::basic_data &base_;
	ApiTypes::Tech tech_;
	QTime timeElapsed_;
};

class GenericMeasurement : public Base {
public:
	explicit GenericMeasurement(QObject *parent = 0)
		: Base(meas_, ApiTypes::UNKNOWN_TECH, parent) {}

	explicit GenericMeasurement(const rf_phreaker::basic_data &base, ApiTypes::Tech tech, QObject *parent = 0)
		: Base(meas_, tech, parent)
		, meas_(base) {}

protected:
	rf_phreaker::basic_data meas_;
};

//}}

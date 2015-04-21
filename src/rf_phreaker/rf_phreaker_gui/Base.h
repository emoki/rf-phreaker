#pragma once
#include <QObject>
#include <QDateTime>
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/rf_phreaker_gui/ApiTypes.h"

//namespace rf_phreaker { namespace gui {

class Base : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString serial READ serial NOTIFY serialChanged)
	Q_PROPERTY(QString collectionRound READ collectionRound NOTIFY collectionRoundChanged)
	Q_PROPERTY(QString carrierFreq READ carrierFreq NOTIFY carrierFreqChanged)
	Q_PROPERTY(QString carrierBandwidth  READ carrierBandwidth NOTIFY carrierBandwidthChanged)
	Q_PROPERTY(QString carrierSignalLevel READ carrierSignalLevel NOTIFY carrierSignalLevelChanged)

public:
	explicit Base(QObject *parent = 0)
		: QObject(parent) {}
	explicit Base(const rp_base& base, QObject *parent = 0)
		: QObject(parent)
		, base_(base) {}

	~Base() {}

	void copy(const Base &a) {
		if(memcmp(base_.serial_.serial_, a.base_.serial_.serial_, RP_SERIAL_LENGTH)) {
			memcpy(base_.serial_.serial_, a.base_.serial_.serial_, RP_SERIAL_LENGTH);
			emit serialChanged();
		}
		if(base_.collection_round_ != a.base_.collection_round_) {
			base_.collection_round_ = a.base_.collection_round_;
			emit collectionRoundChanged();
		}
		if(base_.carrier_frequency_ != a.base_.carrier_frequency_) {
			base_.carrier_frequency_ = a.base_.carrier_frequency_;
			emit carrierFreqChanged();
		}
		if(base_.carrier_bandwidth_ != a.base_.carrier_bandwidth_) {
			base_.carrier_bandwidth_ = a.base_.carrier_bandwidth_;
			emit carrierBandwidthChanged();
		}
		if(base_.carrier_signal_level_ != a.base_.carrier_signal_level_) {
			base_.carrier_signal_level_ = a.base_.carrier_signal_level_;
			emit carrierSignalLevelChanged();
		}
	}
	void copy(const rp_base &a) {
		if(memcmp(base_.serial_.serial_, a.serial_.serial_, RP_SERIAL_LENGTH)) {
			memcpy(base_.serial_.serial_, a.serial_.serial_, RP_SERIAL_LENGTH);
			emit serialChanged();
		}
		if(base_.collection_round_ != a.collection_round_) {
			base_.collection_round_ = a.collection_round_;
			emit collectionRoundChanged();
		}
		if(base_.carrier_frequency_ != a.carrier_frequency_) {
			base_.carrier_frequency_ = a.carrier_frequency_;
			emit carrierFreqChanged();
		}
		if(base_.carrier_bandwidth_ != a.carrier_bandwidth_) {
			base_.carrier_bandwidth_ = a.carrier_bandwidth_;
			emit carrierBandwidthChanged();
		}
		if(base_.carrier_signal_level_ != a.carrier_signal_level_) {
			base_.carrier_signal_level_ = a.carrier_signal_level_;
			emit carrierSignalLevelChanged();
		}
	}

	QString serial() { return ApiTypes::toQString(base_.serial_); }
	QString collectionRound() { return QString::number(base_.collection_round_); }
	QString carrierFreq() { return QString::number(base_.carrier_frequency_/1e6, 'f', 1); }
	QString carrierBandwidth() { return QString::number(base_.carrier_bandwidth_/1e6, 'f', 1); }
	QString carrierSignalLevel() { return QString::number(base_.carrier_signal_level_, 'f', 1); }

signals:
	void serialChanged();
	void collectionRoundChanged();
	void carrierFreqChanged();
	void carrierBandwidthChanged();
	void carrierSignalLevelChanged();

public slots:

protected:
	rp_base base_;
};

//}}

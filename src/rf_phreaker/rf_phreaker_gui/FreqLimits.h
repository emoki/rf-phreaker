#pragma once
#include <QObject>
#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"

class FreqLimits : public QObject {
	Q_OBJECT
	Q_PROPERTY(int low MEMBER low_ NOTIFY lowestFreqChanged)
	Q_PROPERTY(int high MEMBER high_ NOTIFY highestFreqChanged)

signals:
	void lowestFreqChanged(int);
	void highestFreqChanged(int);
		
public:
	FreqLimits(QObject *parent = nullptr)
		: QObject(parent) {
		clear();
	}

	void clear() {
		low_ = std::numeric_limits<int>::max();
		high_ = std::numeric_limits<int>::min();
	}

	void update(rf_phreaker::frequency_type a, rf_phreaker::frequency_type b) {
		auto low = a < b ? a : b;
		auto high = a > b ? a : b;
		low /= 1e6L;
		high /= 1e6L;
		if(low < low_) {
			low_ = low;
			emit lowestFreqChanged(low_);
		}
		if(high > high_) {
			high_ = high;
			emit highestFreqChanged(high_);
		}
	}

	void update(const rp_power_spectrum_spec &spec) {
		update(spec.start_frequency_, spec.start_frequency_ + spec.span_);
	}

	void update(const rf_phreaker::power_spectrum_data &spec) {
		update(spec.params_.start_frequency_, spec.params_.start_frequency_ + spec.params_.span_);
	}

	int low_;
	int high_;
};



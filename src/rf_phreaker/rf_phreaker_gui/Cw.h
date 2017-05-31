#pragma once
#include <QObject>
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/rf_phreaker_gui/ApiTypes.h"
#include "rf_phreaker/rf_phreaker_gui/Base.h"
#include "rf_phreaker/common/measurements.h"

class Cw : public Base {
	Q_OBJECT
	Q_PROPERTY(double identifier READ identifier NOTIFY identifierChanged)
	Q_PROPERTY(double binSize READ binSize NOTIFY binSizeChanged)
	Q_PROPERTY(double cwSignalLevel READ cwSignalLevel NOTIFY cwSignalLevelChanged)
	Q_PROPERTY(double dwellTime READ dwellTime NOTIFY dwellTimeChanged)

public:
	explicit Cw(QObject *parent = 0)
		: Base(spec_, ApiTypes::CW, parent) {}

	explicit Cw(const rf_phreaker::power_spectrum_data &spec, QObject *parent = 0)
		: Base(spec_, ApiTypes::CW, parent)
		, spec_(spec) {
		make_connections();
	}

	void make_connections() {
		QObject::connect(this, &Cw::identifierChanged, this, &Base::cellIdChanged);
		QObject::connect(this, &Cw::cwSignalLevelChanged, this, &Base::cellSignalLevelChanged);
	}

	virtual void update(const rf_phreaker::basic_data &t) {
		Base::update(spec_);
		const auto &a = (const rf_phreaker::power_spectrum_data &)t;
		bool b = false, i = false , p = false, d = false;
		if(spec_.params_.bin_size_ != a.params_.bin_size_) {
			b = true;
		}
		if(spec_.params_.identifier_ != a.params_.identifier_) {
			i = true;
		}
		if(spec_.power_.size() != a.power_.size() || cellSignalLevel() != a.power_[get_power_index()]) {
			p = true;
		}
		if(spec_.params_.dwell_time_ != a.params_.dwell_time_)
			d = true;
		spec_.params_ = a.params_;
		spec_.power_ = a.power_;
		if(b)
			emit binSizeChanged();
		if(i)
			emit identifierChanged();
		if(p)
			emit cwSignalLevelChanged();
		if(d)
			emit dwellTimeChanged();
	}

	int32_t cellId() const { return spec_.params_.identifier_; }
	double cellSignalLevel() const { return cwSignalLevel(); }

	double identifier() const { return spec_.params_.identifier_ / 1e6; }
	double binSize() const { return spec_.params_.bin_size_ / 1e3; }
	double cwSignalLevel() const { return spec_.power_[get_power_index()]; }
	int dwellTime() const { return spec_.params_.dwell_time_ / 1e6; }

signals:
	void identifierChanged();
	void binSizeChanged();
	void cwSignalLevelChanged();
	void dwellTimeChanged();

private:
	int get_power_index() const { 
		auto pos = (spec_.measurement_frequency_ - spec_.params_.start_frequency_) / spec_.params_.step_size_; 
		return (pos >= 0 && pos < spec_.power_.size()) ? pos : 0;
	}

protected:
	rf_phreaker::power_spectrum_data spec_;
};

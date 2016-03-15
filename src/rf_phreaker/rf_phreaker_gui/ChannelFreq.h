#pragma once
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QLocale>
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/rf_phreaker_gui/ApiTypes.h"

//namespace rf_phreaker { namespace gui {

class ChannelFreq : public QObject {
	Q_OBJECT
	Q_PROPERTY(QString channel READ toChannelStr WRITE setChannel NOTIFY channelChanged)
	Q_PROPERTY(QString freq READ toFreqStr WRITE setFreq NOTIFY freqChanged)
	Q_PROPERTY(QString band READ toBandStr WRITE setBand NOTIFY bandChanged)
	Q_PROPERTY(QString tech READ toTechStr WRITE setTech NOTIFY techChanged)

public:
	ChannelFreq(QObject *parent = 0)
		: QObject(parent)
		, tech_(ApiTypes::UNKNOWN_TECH)
	{}
	ChannelFreq(rf_phreaker::channel_freq cf, ApiTypes::Tech t, QObject *parent = 0)
		: QObject(parent)
		, cf_(cf)
		, tech_(t)
	{}

	ChannelFreq(const QString &c, const QString &f, const QString &b, const QString &t, QObject *parent = 0)
		: QObject(parent) {
		setChannel(c);
		setFreq(f);
		setBand(b);
		setTech(t);
	}

	ChannelFreq& operator=(const ChannelFreq &cf) {
		cf_ = cf.cf_;
		return *this;
	}

	bool operator==(const ChannelFreq &cf) {
		return cf_ == cf.cf_;
	}
	bool operator!=(const ChannelFreq &cf) {
		return !(cf_ == cf.cf_);
	}

	void setChannel(const QString &a) {
		bool ok = false;
		rf_phreaker::channel_type t = a.toInt(&ok);
		Q_ASSERT(ok);
		if(t != cf_.channel_) {
			cf_.channel_ = t;
			emit channelChanged();
		}
	}
	void setFreq(const QString &a) {
		bool ok = false;
		auto t = a.toDouble(&ok) * 1000000;
		Q_ASSERT(ok);
		if(t != cf_.freq_) {
			cf_.freq_ = t;
			emit freqChanged();
		}
	}
	void setBand(const QString &a) {
		auto t = (rf_phreaker::operating_band)ApiTypes::toOperatingBand(a);
		if(t != cf_.band_) {
			cf_.band_ = t;
			emit bandChanged();
		}
	}
	void setTech(const QString &a) {
		auto t = ApiTypes::toTech(a);
		if(t != tech_) {
			tech_ = t;
			emit techChanged();
		}
	}

	QString toChannelStr() const { return QString::number(cf_.channel_); }
	QString toFreqStr() const { return QString::number(cf_.freq_/1e6, 'f', 1); }
	QString toBandStr() const { return ApiTypes::toQString(cf_.band_); }
	QString toTechStr() const { return ApiTypes::toQString(tech_); }

	double freqMhz() const { return cf_.freq_ / 1e6; }

	ApiTypes::OperatingBand band() {
		return ApiTypes::toOperatingBand(cf_.band_);
	}

	const rf_phreaker::channel_freq& channelFreq() const { return cf_; }

	rp_frequency_band toRpFrequencyBand() const {
		rp_frequency_band fb;
		fb.freq_ = cf_.freq_;
		fb.band_ = ApiTypes::toRpOperatingBand(cf_.band_);
		return fb;
	}
	rp_operating_band toRpBand() const { return ApiTypes::toRpOperatingBand(cf_.band_); }
	rp_frequency_type toRpFreq() const { return (rp_frequency_type)cf_.freq_; }
	rp_channel_type toRpChannel() const { return (rp_channel_type)cf_.channel_; }
	ApiTypes::Tech tech() const { return tech_; }

signals:
	void channelChanged();
	void freqChanged();
	void bandChanged();
	void techChanged();

private:
	rf_phreaker::channel_freq cf_;
	ApiTypes::Tech tech_;
};


//}}



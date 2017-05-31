#pragma once
#include <QObject>
#include "rf_phreaker/rf_phreaker_gui/ChannelFreq.h"

//namespace rf_phreaker { namespace gui {

class CollectionInfo : public QObject
{
	Q_OBJECT
	Q_PROPERTY(ChannelFreq* channelFreqLow READ channelFreqLow WRITE setChannelFreqLow NOTIFY channelFreqLowChanged)
	Q_PROPERTY(ChannelFreq* channelFreqHigh READ channelFreqHigh WRITE setChannelFreqHigh NOTIFY channelFreqHighChanged)
	Q_PROPERTY(bool isSweep READ isSweep NOTIFY channelFreqLowChanged)
	Q_PROPERTY(bool isGsm READ isGsm NOTIFY channelFreqLowChanged)
	Q_PROPERTY(bool isWcdma READ isWcdma NOTIFY channelFreqLowChanged)
	Q_PROPERTY(bool isLte READ isLte NOTIFY channelFreqLowChanged)
	Q_PROPERTY(QString infoStr READ toInfoStr NOTIFY infoChanged)

	Q_PROPERTY(QString channels READ toChannelsStr NOTIFY infoChanged)
	Q_PROPERTY(QString freqs READ toFreqsStr NOTIFY infoChanged)
	Q_PROPERTY(QString band READ toBandStr NOTIFY infoChanged)
	Q_PROPERTY(QString tech READ toTechStr NOTIFY infoChanged)
	Q_PROPERTY(QString radioType READ toRadioTypeStr NOTIFY infoChanged)

public:
	explicit CollectionInfo(QObject *parent = 0) : QObject(parent) {}
	explicit CollectionInfo(const rf_phreaker::channel_freq &cf1, ApiTypes::Tech tech, QObject *parent = 0)
		: QObject(parent)
		, cfLow_(cf1, tech)
	{}
	explicit CollectionInfo(const rf_phreaker::channel_freq &cf1, const rf_phreaker::channel_freq &cf2,
							  ApiTypes::Tech tech, QObject *parent = 0)
		: QObject(parent)
		, cfLow_(cf1, tech)
		, cfHigh_(cf2, tech)
	{}

	~CollectionInfo() {}

	ChannelFreq* channelFreqLow() { return &cfLow_; }
	ChannelFreq* channelFreqHigh() { return &cfHigh_; }
	void setChannelFreqLow(const ChannelFreq *cf) {
		if(cfLow_ != *cf) {
			cfLow_ = *cf;
			emit channelFreqLowChanged();
		}
	}
	void setChannelFreqHigh(const ChannelFreq *cf) {
		if(cfHigh_ != *cf) {
			cfHigh_ = *cf;
			emit channelFreqHighChanged();
		}
	}

	bool isSweep() const { return cfLow_.channelFreq().is_valid() && cfHigh_.channelFreq().is_valid(); }
	bool isGsm() const { return cfLow_.tech() == ApiTypes::GSM_SWEEP || cfLow_.tech() == ApiTypes::GSM_FULL_SCAN; }
	bool isWcdma() const { return cfLow_.tech() == ApiTypes::WCDMA_SWEEP || cfLow_.tech() == ApiTypes::WCDMA_FULL_SCAN; }
	bool isLte() const { return cfLow_.tech() == ApiTypes::LTE_SWEEP || cfLow_.tech() == ApiTypes::LTE_FULL_SCAN; }

	QString toInfoStr() const { return "Info placeholder"; }
	QString toChannelsStr() const {
		if(cfHigh_.isChannelValid())
			return cfLow_.toChannelStr() + " - " + cfHigh_.toChannelStr();
		else if(cfLow_.isChannelValid())
			return cfLow_.toChannelStr();
		else
			return "";
	}
	QString toFreqsStr() const {
		if(cfHigh_.isFreqValid())
			return cfLow_.toFreqStr() + " - " + cfHigh_.toFreqStr() + " MHz";
		else
			return cfLow_.toFreqStr() + " MHz";
	}
	QString toBandStr() const {
		if(cfLow_.tech() == ApiTypes::IQ_DATA)
			return "";
		else
			return cfLow_.toBandStr();
	}

	QString toTechStr() const {
		return cfLow_.toTechStr();
	}

	QString toRadioTypeStr() const {
		return cfLow_.toRadioTypeStr();
	}

signals:
	void channelFreqLowChanged();
	void channelFreqHighChanged();
	void infoChanged();

	void channelsChanged();
	void freqsChanged();
	void techBandChanged();

private:
	ChannelFreq cfLow_;
	ChannelFreq cfHigh_;
};

//}}


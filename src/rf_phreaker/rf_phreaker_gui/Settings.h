#pragma once
#include <QSettings>
#include <QList>
#include <QString>
#include "rf_phreaker/rf_phreaker_gui/Serialization.h"

//namespace rf_phreaker { namespace gui { 

static const QString api_output_key("api_output");

class Settings {
public:
	bool api_output_;
};

class SettingsIO {
public:
	SettingsIO() 
		: qs_(QSettings::IniFormat, QSettings::UserScope, "rf_phreaker", "gui") {}

	void readSettings(Settings &settings) {
		settings.api_output_ = qs_.value("api_output", false).toBool();
	}
	QList<CollectionInfo*> readScanList() {
		QList<CollectionInfo*> list;
		readCollectionInfoList(list, "scan_list");
		return list;
	}
	void readCollectionInfoList(QList<CollectionInfo*> &list, const QString &descrip) {
		auto size = qs_.beginReadArray(descrip);
		for(auto i = 0; i < size; ++i) {
			qs_.setArrayIndex(i);
			auto low = qs_.value("channel_freq_low").value<rf_phreaker::channel_freq>();
			auto high = qs_.value("channel_freq_high").value<rf_phreaker::channel_freq>();
			auto tech = (ApiTypes::Tech)qs_.value("tech").value<::rp_technology>();
			list.append(new CollectionInfo(low, high, tech));
		}
		qs_.endArray();
	}
	void writeSettings(const Settings &settings) {
		qs_.setValue("api_output", settings.api_output_);

	}
	void writeScanList(const QList<CollectionInfo*> &list) {
		writeCollectionInfoList(list, "scan_list");
	}
	void writeCollectionInfoList(const QList<CollectionInfo*> &list, const QString &descrip) {
		qs_.beginWriteArray(descrip);
		int i = 0;
		for(const auto &j : list) {
			qs_.setArrayIndex(i++);
			qs_.setValue("channel_freq_low", QVariant::fromValue(j->channelFreqLow()->channelFreq()));
			qs_.setValue("channel_freq_high", QVariant::fromValue(j->channelFreqHigh()->channelFreq()));
			qs_.setValue("tech", QVariant::fromValue((::rp_technology)j->channelFreqLow()->tech()));
		}
		qs_.endArray();

	}

private:
	QSettings qs_;
};



//}}

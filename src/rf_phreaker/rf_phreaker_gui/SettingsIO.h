#pragma once
#include <mutex>
#include <QMutex>
#include <QSettings>
#include <QList>
#include <QString>
#include <QDebug>
#include <QFile>
#include "rf_phreaker/rf_phreaker_gui/Serialization.h"
#include "rf_phreaker/rf_phreaker_gui/CollectionInfo.h"
#include "rf_phreaker/common/settings.h"
#include "rf_phreaker/qt_specific/settings_io.h"
#include "rf_phreaker/qt_specific/qt_utility.h"
#include "marble/geodata/data/GeoDataCoordinates.h"

//namespace rf_phreaker { namespace gui {

static const QString apiOutputKey("api_output");
static const QString last_known_coordinates_key("last_known_coordinates");
static const QString rpfTrackMinDistanceKey("rpf_track_min_distance");
static const QString themePrimaryColorKey("theme_primary_color");
static const QString themeAccentColorkey("theme_accent_color");
static const QString themeTabHighlightColorKey("theme_tab_highlight_color");
static const QString measurementRemovalTimeKey("measurement_removal_time");
static const QString convertRfpToAsciiKey("convert_rfp_to_ascii");
static const QString spectrumBinSizeKey("spectrum_bin_size");
static const QString spectrumDwellTimeKey("spectrum_dwell_time");
static const QString cwBinSizeKey("cw_bin_size");
static const QString cwSpanKey("cw_span");
static const QString cwDwellTimeKey("cw_dwell_time");
static const QString cwOffsetKey("cw_offset");
static const QString iqBandwidthKey("iq_bandwidth");
static const QString iqSamplingRateKey("iq_sampling_rate");
static const QString iqDwellTimeKey("iq_dwell_time");


class Settings;

class SettingsIO {
public:
	SettingsIO()
		: qs_(QSettings::IniFormat, QSettings::UserScope, "rf_phreaker", "gui") {
		if(!QFile(qs_.fileName()).exists())
			qWarning() << "Unable to access or find the configuration file!  Settings will be set to default.";
	}

	void readSettings(Settings &settings);

	void writeSettings(const Settings &settings);

	QString fileName() const { return qs_.fileName(); }

	Marble::GeoDataCoordinates readLastKnownCoordinate() {
		bool success = false;
		Marble::GeoDataCoordinates coordinate;
		auto s = qs_.value(last_known_coordinates_key, "").toString();
		coordinate = Marble::GeoDataCoordinates::fromString(s, success);
		if(!success) {
			coordinate.set(74.0059, 40.7128, 0);
		}
		return coordinate;
	}

	QList<CollectionInfo*> readScanList(QObject *parent) {
		QList<CollectionInfo*> list;
		readCollectionInfoList(list, "scan_list", parent);
		return list;
	}

	void readCollectionInfoList(QList<CollectionInfo*> &list, const QString &descrip, QObject *parent) {
		auto size = qs_.beginReadArray(descrip);
		for(auto i = 0; i < size; ++i) {
			qs_.setArrayIndex(i);
			auto low = qs_.value("channel_freq_low").value<rf_phreaker::channel_freq>();
			auto high = qs_.value("channel_freq_high").value<rf_phreaker::channel_freq>();
			auto tech = (ApiTypes::Tech)qs_.value("tech").value<ApiTypes::Tech>();
			list.append(new CollectionInfo(low, high, tech, parent));
		}
		qs_.endArray();
	}

	QStringList readMarbleLayers() {
		return qs_.value("previous_marble_layers").toStringList();
	}

	void writeLastKnownCoordinate(const Marble::GeoDataCoordinates &coordinate) {
		auto s = coordinate.toString(Marble::GeoDataCoordinates::Notation::Decimal);
		qs_.setValue(last_known_coordinates_key, s);
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
			qs_.setValue("tech", QVariant::fromValue(j->channelFreqLow()->tech()));
		}
		qs_.endArray();

	}

	void writeMarbleLayers(const QStringList &list) {
		qs_.setValue("previous_marble_layers", list);
	}

private:
	QSettings qs_;
};

//}}
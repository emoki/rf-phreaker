#include "rf_phreaker/rf_phreaker_gui/Settings.h"
#include "rf_phreaker/rf_phreaker_gui/SettingsIO.h"
#include "rf_phreaker/qt_specific/settings_io.h"
#include "rf_phreaker/qt_specific/qt_utility.h"

Settings *Settings::instance_ = nullptr;
QMutex Settings::instance_mutex_;

// To used with SettingsSingletonTypeProvider so that the pointer is owned by the qml engine.
Settings* Settings::instance() {
	if(instance_ == nullptr) {
		QMutexLocker lock(&instance_mutex_);
		if(instance_ == nullptr) {
			instance_ = new Settings;
		}
	}
	return instance_;
}

void Settings::loadSettings() {
	SettingsIO sio;
	sio.readSettings(*this);
	auto rp_s = readRpSettings();
	logLevelAppVerbosity_ = rp_s.log_level_;
	logLevelHardwareVerbosity_ = rp_s.blade_settings_.log_level_;
	loggingGps_ = rp_s.log_gps_general_ && rp_s.log_gps_parsing_;
	loggingCollection_ = rp_s.log_collection_;
	loggingPackets_ = rp_s.packet_output_.gps_ && rp_s.packet_output_.gsm_layer_3_ && rp_s.packet_output_.gsm_sweep_
		&& rp_s.packet_output_.lte_layer_3_ && rp_s.packet_output_.lte_sweep_ && rp_s.packet_output_.scanner_
		&& rp_s.packet_output_.sweep_ && rp_s.packet_output_.umts_layer_3_ && rp_s.packet_output_.umts_sweep_;
	emitSignals();
}

void Settings::saveSettings() {
	SettingsIO sio;
	sio.writeSettings(*this);
	auto rp_s = readRpSettings();
	rp_s.log_level_ = logLevelAppVerbosity_;
	rp_s.blade_settings_.log_level_ = logLevelHardwareVerbosity_;
	rp_s.log_gps_parsing_ = loggingGps_;
	rp_s.log_gps_general_ = loggingGps_;
	rp_s.log_collection_ = loggingCollection_;
	rp_s.packet_output_.gsm_layer_3_ = loggingPackets_;
	rp_s.packet_output_.gsm_sweep_ = loggingPackets_;
	rp_s.packet_output_.lte_layer_3_ = loggingPackets_;
	rp_s.packet_output_.lte_sweep_ = loggingPackets_;
	rp_s.packet_output_.scanner_ = loggingPackets_;
	rp_s.packet_output_.sweep_ = loggingPackets_;
	rp_s.packet_output_.umts_layer_3_ = loggingPackets_;
	rp_s.packet_output_.umts_sweep_ = loggingPackets_;
	writeRpSettings(rp_s);
}

bool Settings::shouldReinitializeApi() {
	auto rp_s = readRpSettings();
	return 	rp_s.log_level_ != logLevelAppVerbosity_ ||
		rp_s.blade_settings_.log_level_ != logLevelHardwareVerbosity_ ||
		rp_s.log_gps_parsing_ != loggingGps_ ||
		rp_s.log_gps_general_ != loggingGps_ ||
		rp_s.log_collection_ != loggingCollection_ ||
		rp_s.packet_output_.gsm_layer_3_ != loggingPackets_ ||
		rp_s.packet_output_.gsm_sweep_ != loggingPackets_ ||
		rp_s.packet_output_.lte_layer_3_ != loggingPackets_ ||
		rp_s.packet_output_.lte_sweep_ != loggingPackets_ ||
		rp_s.packet_output_.scanner_ != loggingPackets_ ||
		rp_s.packet_output_.sweep_ != loggingPackets_ ||
		rp_s.packet_output_.umts_layer_3_ != loggingPackets_ ||
		rp_s.packet_output_.umts_sweep_ != loggingPackets_;

}

rf_phreaker::settings Settings::readRpSettings() {
	rf_phreaker::settings s;
	rf_phreaker::settings_io io("rf_phreaker_api", rf_phreaker::qt_utility::app_name());
	if(!io.does_exist()) {
		qCritical() << "The INI file (\"" << io.filename().c_str() <<
			"\") was not found.  This may adversely affect API functionality.";
	}
	io.read(s);
	return s;
}

void Settings::writeRpSettings(rf_phreaker::settings &s) {
	rf_phreaker::settings_io io("rf_phreaker_api", rf_phreaker::qt_utility::app_name());
	io.write(s);
}

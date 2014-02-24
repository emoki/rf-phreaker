#include "rf_phreaker/qt_specific/settings_io.h"
#include "rf_phreaker/common/common_utility.h"
#include "QtCore\qsettings.h"

using namespace rf_phreaker;

settings_io::settings_io(const std::string &application_name, const std::string &organization)
: qsettings_(new QSettings(QSettings::IniFormat, QSettings::UserScope, organization.c_str(), application_name.c_str()))
{
}

void settings_io::populate_settings(settings &settings)
{
	settings.output_raw_packets_ = qsettings_->value("output_raw_packets", false).toBool();
	settings.log_level_	= qsettings_->value("log_level", 1).toInt();

	read_collection_settings(settings.umts_sweep_collection_, "umts_sweep_collection");
	read_collection_settings(settings.umts_layer_3_collection_, "umts_layer_3_collection");
	read_collection_settings(settings.lte_sweep_collection_, "lte_sweep_collection");
	read_collection_settings(settings.lte_layer_3_collection_, "lte_layer_3_collection");

	read_layer_3_settings(settings.umts_decode_layer_3_, "umts_decode_thresholds");
	read_layer_3_settings(settings.lte_decode_layer_3_, "lte_decode_thresholds");

	read_umts_general_settings(settings.umts_sweep_general_, "umts_sweep_general");
	read_umts_general_settings(settings.umts_layer_3_general_, "umts_layer_3_general");
}

void settings_io::read_collection_settings(collection_settings &settings, const std::string &group_key)
{
	qsettings_->beginGroup(group_key.c_str());
	settings.sampling_rate_ = qsettings_->value("sampling_rate", 4875000).toLongLong();
	settings.bandwidth_ = qsettings_->value("bandwidth", 5000000).toLongLong();
	settings.collection_time_ = qsettings_->value("collection_time", milli_to_nano(50)).toLongLong();
	qsettings_->endGroup();
}

void settings_io::read_layer_3_settings(layer_3_settings &settings, const std::string &group_key)
{
	qsettings_->beginGroup(group_key.c_str());
	settings.max_update_threshold_ = qsettings_->value("max_update_threshold", 150).toInt();
	settings.decode_threshold_ = qsettings_->value("decode_threshold", -13).toDouble();
	settings.decode_minimum_threshold_ = qsettings_->value("min_decode_threshold", -25).toDouble();
	qsettings_->endGroup();
}

void settings_io::read_umts_general_settings(umts_general &settings, const std::string &group_key)
{
	qsettings_->beginGroup(group_key.c_str());
	settings.sensitivity_ = qsettings_->value("sensitivity", -28.6).toDouble();
	settings.full_scan_interval_ = qsettings_->value("full_scan_interval", 150).toInt();
	qsettings_->endGroup();
}

#include "rf_phreaker/qt_specific/settings_io.h"
#include "rf_phreaker/common/common_utility.h"
#include "QtCore\qsettings.h"

using namespace rf_phreaker;

settings_io::settings_io(const std::string &application_name, const std::string &organization)
: qsettings_(new QSettings(QSettings::IniFormat, QSettings::UserScope, organization.c_str(), application_name.c_str()))
{
}

settings_io::~settings_io()
{}

void settings_io::read(settings &settings)
{
	settings.output_raw_packets_ = qsettings_->value(output_raw_packets_key.c_str(), settings_output_raw_packets_default).toBool();
	settings.log_level_ = qsettings_->value(log_level_key.c_str(), settings_log_level_default).toInt();

	read(settings.umts_sweep_collection_, umts_sweep_collection_group_key);
	read(settings.umts_layer_3_collection_, umts_layer_3_collection_group_key);
	read(settings.lte_sweep_collection_, lte_sweep_collection_group_key);
	read(settings.lte_layer_3_collection_, lte_layer_3_collection_group_key);

	read(settings.umts_decode_layer_3_, umts_decode_thresholds_group_key);
	read(settings.lte_decode_layer_3_, lte_decode_thresholds_group_key);

	read(settings.umts_sweep_general_, umts_sweep_general_group_key);
	read(settings.umts_layer_3_general_, umte_layer_3_general_group_key);
}

void settings_io::read(collection_settings &settings, const std::string &group_key)
{
	qsettings_->beginGroup(group_key.c_str());
	settings.sampling_rate_ = qsettings_->value(sampling_rate_key.c_str(), settings_sampling_rate_default).toLongLong();
	settings.bandwidth_ = qsettings_->value(bandwidth_key.c_str(), settings_bandwidth_default).toLongLong();
	settings.collection_time_ = qsettings_->value(collection_time_key.c_str(), settings_collection_time_default).toLongLong();
	qsettings_->endGroup();
}

void settings_io::read(layer_3_settings &settings, const std::string &group_key)
{
	qsettings_->beginGroup(group_key.c_str());
	settings.max_update_threshold_ = qsettings_->value(max_update_threshold_key.c_str(), settings_layer_3_max_update_threshold_default).toInt();
	settings.decode_threshold_ = qsettings_->value(decode_threshold_key.c_str(), settings_layer_3_decode_threshold_default).toDouble();
	settings.decode_minimum_threshold_ = qsettings_->value(min_decode_threshold_key.c_str(), settings_layer_3_min_decode_threshold_default).toDouble();
	qsettings_->endGroup();
}

void settings_io::read(umts_general_settings &settings, const std::string &group_key)
{
	qsettings_->beginGroup(group_key.c_str());
	settings.sensitivity_ = qsettings_->value(sensitivity_key.c_str(), settings_umts_general_sensitivity_default).toDouble();
	settings.full_scan_interval_ = qsettings_->value(full_scan_interval_key.c_str(), settings_umts_general_full_scan_interval_default).toInt();
	qsettings_->endGroup();
}

void settings_io::write(settings &settings)
{
	qsettings_->setValue(output_raw_packets_key.c_str(), settings.output_raw_packets_);
	qsettings_->setValue(log_level_key.c_str(), settings.log_level_);

	write(settings.umts_sweep_collection_, umts_sweep_collection_group_key);
	write(settings.umts_layer_3_collection_, umts_layer_3_collection_group_key);
	write(settings.lte_sweep_collection_, lte_sweep_collection_group_key);
	write(settings.lte_layer_3_collection_, lte_layer_3_collection_group_key);

	write(settings.umts_decode_layer_3_, umts_decode_thresholds_group_key);
	write(settings.lte_decode_layer_3_, lte_decode_thresholds_group_key);

	write(settings.umts_sweep_general_, umts_sweep_general_group_key);
	write(settings.umts_layer_3_general_, umte_layer_3_general_group_key);
}

void settings_io::write(collection_settings &settings, const std::string &group_key)
{
	qsettings_->beginGroup(group_key.c_str());
	qsettings_->setValue(sampling_rate_key.c_str(), settings.sampling_rate_);
	qsettings_->setValue(bandwidth_key.c_str(), settings.bandwidth_);
	qsettings_->setValue(collection_time_key.c_str(), settings.collection_time_);
	qsettings_->endGroup();
}

void settings_io::write(layer_3_settings &settings, const std::string &group_key)
{
	qsettings_->beginGroup(group_key.c_str());
	qsettings_->setValue(max_update_threshold_key.c_str(), settings.max_update_threshold_);
	qsettings_->setValue(decode_threshold_key.c_str(), settings.decode_threshold_);
	qsettings_->setValue(min_decode_threshold_key.c_str(), settings.decode_minimum_threshold_);
	qsettings_->endGroup();
}

void settings_io::write(umts_general_settings &settings, const std::string &group_key)
{
	qsettings_->beginGroup(group_key.c_str());
	qsettings_->setValue(sensitivity_key.c_str(), settings.sensitivity_);
	qsettings_->setValue(full_scan_interval_key.c_str(), settings.full_scan_interval_);
	qsettings_->endGroup();
}

void settings_io::clear()
{ 
	qsettings_->clear(); 
}



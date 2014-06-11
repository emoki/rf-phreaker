#include "rf_phreaker/qt_specific/settings_io.h"
#include "rf_phreaker/common/common_utility.h"
#include "QtCore\qsettings.h"

using namespace rf_phreaker;

settings_io::settings_io(const std::string &application_name, const std::string &organization)
: qsettings_(new QSettings(QSettings::IniFormat, QSettings::UserScope, organization.c_str(), application_name.c_str()))
{}

settings_io::settings_io(const std::string &filename)
: qsettings_(new QSettings(filename.c_str(), QSettings::IniFormat))
{}

settings_io::~settings_io()
{}

void settings_io::read(settings &settings)
{
	settings.log_level_ = qsettings_->value(log_level_key.c_str(), settings_log_level_default).toInt();
	settings.gps_collection_period_ms_ = qsettings_->value(gps_collection_period_ms_key.c_str(), gps_collection_period_ms_default).toInt();
	settings.num_items_in_flight_ = qsettings_->value(num_items_in_flight_key.c_str(), num_items_in_flight_default).toInt();
	settings.use_rf_board_adjustment_ = qsettings_->value(use_rf_board_adjustment_key.c_str(), use_rf_board_adjustment_default).toBool();

	read(settings.standard_output_, standard_output_group_key);
	read(settings.signal_slots_, signal_slot_output_group_key);
	read(settings.packet_output_, packet_output_group_key);

	read(settings.umts_sweep_collection_, umts_sweep_collection_group_key);
	read(settings.umts_layer_3_collection_, umts_layer_3_collection_group_key);
	read(settings.lte_sweep_collection_, lte_sweep_collection_group_key);
	read(settings.lte_layer_3_collection_, lte_layer_3_collection_group_key);

	read(settings.umts_decode_layer_3_, umts_decode_thresholds_group_key);
	read(settings.lte_decode_layer_3_, lte_decode_thresholds_group_key);

	read(settings.umts_sweep_general_, umts_sweep_general_group_key);
	read(settings.umts_layer_3_general_, umts_layer_3_general_group_key);

	read(settings.frequency_correction_settings_, frequency_correction_group_key);
}

void settings_io::read(output_settings &settings, const std::string &group_key)
{
	qsettings_->beginGroup(group_key.c_str());
	settings.scanner_ = qsettings_->value(scanner_output_key.c_str(), settings_output_default).toBool();
	settings.gps_ = qsettings_->value(scanner_output_key.c_str(), settings_output_default).toBool();
	settings.umts_sweep_ = qsettings_->value(umts_sweep_output_key.c_str(), settings_output_default).toBool();
	settings.umts_layer_3_ = qsettings_->value(umts_layer_3_output_key.c_str(), settings_output_default).toBool();
	settings.lte_sweep_ = qsettings_->value(lte_sweep_output_key.c_str(), settings_output_default).toBool();
	settings.lte_layer_3_ = qsettings_->value(lte_layer_3_output_key.c_str(), settings_output_default).toBool();
	qsettings_->endGroup();

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
	settings.minimum_collection_round_ = qsettings_->value(min_collection_round_key.c_str(), settings_layer_3_min_collection_round_default).toInt();
	settings.decode_threshold_ = qsettings_->value(decode_threshold_key.c_str(), settings_layer_3_decode_threshold_default).toDouble();
	settings.decode_minimum_threshold_ = qsettings_->value(min_decode_threshold_key.c_str(), settings_layer_3_min_decode_threshold_default).toDouble();
	qsettings_->endGroup();
}

void settings_io::read(umts_general_settings &settings, const std::string &group_key)
{
	qsettings_->beginGroup(group_key.c_str());
	settings.sensitivity_ = qsettings_->value(sensitivity_key.c_str(), settings_umts_general_sensitivity_default).toDouble();
	settings.full_scan_interval_ = qsettings_->value(full_scan_interval_key.c_str(), settings_umts_general_full_scan_interval_default).toInt();
	settings.num_coherent_slots_ = qsettings_->value(num_coherent_slots_key.c_str(), settings_umts_general_num_coherent_slots_default).toInt();
	qsettings_->endGroup();
}

void settings_io::read(frequency_correction_settings &settings, const std::string &group_key)
{
	qsettings_->beginGroup(group_key.c_str());
	settings.frequency_correction_range_start_ = qsettings_->value(frequency_correction_offset_start_key.c_str(), frequency_correction_offset_start_default).toDouble();
	settings.frequency_correction_range_end_ = qsettings_->value(frequency_correction_offset_end_key.c_str(), frequency_correction_offset_end_default).toInt();
	qsettings_->endGroup();
	read(settings.general_settings_, group_key);
}



void settings_io::write(const settings &settings)
{
	qsettings_->setValue(log_level_key.c_str(), settings.log_level_);
	qsettings_->setValue(gps_collection_period_ms_key.c_str(), settings.gps_collection_period_ms_);
	qsettings_->setValue(num_items_in_flight_key.c_str(), settings.num_items_in_flight_);
	qsettings_->setValue(use_rf_board_adjustment_key.c_str(), settings.use_rf_board_adjustment_);

	write(settings.standard_output_, standard_output_group_key);
	write(settings.signal_slots_, signal_slot_output_group_key);
	write(settings.packet_output_, packet_output_group_key);

	write(settings.umts_sweep_collection_, umts_sweep_collection_group_key);
	write(settings.umts_layer_3_collection_, umts_layer_3_collection_group_key);
	write(settings.lte_sweep_collection_, lte_sweep_collection_group_key);
	write(settings.lte_layer_3_collection_, lte_layer_3_collection_group_key);

	write(settings.umts_decode_layer_3_, umts_decode_thresholds_group_key);
	write(settings.lte_decode_layer_3_, lte_decode_thresholds_group_key);

	write(settings.umts_sweep_general_, umts_sweep_general_group_key);
	write(settings.umts_layer_3_general_, umts_layer_3_general_group_key);

	write(settings.frequency_correction_settings_, frequency_correction_group_key);
}

void settings_io::write(const output_settings &settings, const std::string &group_key)
{
	qsettings_->beginGroup(group_key.c_str());
	qsettings_->setValue(scanner_output_key.c_str(), settings.scanner_);
	qsettings_->setValue(gps_output_key.c_str(), settings.gps_);
	qsettings_->setValue(umts_sweep_output_key.c_str(), settings.umts_sweep_);
	qsettings_->setValue(umts_layer_3_output_key.c_str(), settings.umts_layer_3_);
	qsettings_->setValue(lte_sweep_output_key.c_str(), settings.lte_sweep_);
	qsettings_->setValue(lte_layer_3_output_key.c_str(), settings.lte_layer_3_);
	qsettings_->endGroup();
}

void settings_io::write(const collection_settings &settings, const std::string &group_key)
{
	qsettings_->beginGroup(group_key.c_str());
	qsettings_->setValue(sampling_rate_key.c_str(), settings.sampling_rate_);
	qsettings_->setValue(bandwidth_key.c_str(), settings.bandwidth_);
	qsettings_->setValue(collection_time_key.c_str(), settings.collection_time_);
	qsettings_->endGroup();
}

void settings_io::write(const layer_3_settings &settings, const std::string &group_key)
{
	qsettings_->beginGroup(group_key.c_str());
	qsettings_->setValue(max_update_threshold_key.c_str(), settings.max_update_threshold_);
	qsettings_->setValue(min_collection_round_key.c_str(), settings.minimum_collection_round_);
	qsettings_->setValue(decode_threshold_key.c_str(), settings.decode_threshold_);
	qsettings_->setValue(min_decode_threshold_key.c_str(), settings.decode_minimum_threshold_);
	qsettings_->endGroup();
}

void settings_io::write(const umts_general_settings &settings, const std::string &group_key)
{
	qsettings_->beginGroup(group_key.c_str());
	qsettings_->setValue(sensitivity_key.c_str(), settings.sensitivity_);
	qsettings_->setValue(full_scan_interval_key.c_str(), settings.full_scan_interval_);
	qsettings_->setValue(num_coherent_slots_key.c_str(), settings.num_coherent_slots_);
	qsettings_->endGroup();
}

void settings_io::write(const frequency_correction_settings &settings, const std::string &group_key)
{
	qsettings_->beginGroup(group_key.c_str());
	qsettings_->setValue(frequency_correction_offset_start_key.c_str(), settings.frequency_correction_range_start_);
	qsettings_->setValue(frequency_correction_offset_end_key.c_str(), settings.frequency_correction_range_end_);
	qsettings_->endGroup();
	write(settings.general_settings_, group_key);
}

void settings_io::clear()
{ 
	qsettings_->clear(); 
}



#include "rf_phreaker/qt_specific/settings_io.h"
#include "qtcore/qsettings.h"
#include "qtcore/qfile.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/qt_specific/file_path_validation.h"
#include "rf_phreaker/common/log.h"
#include "rf_phreaker/common/exception_types.h"
#include "rf_phreaker/layer_3_common/layer_3_utility.h"

using namespace rf_phreaker;

settings_io::settings_io(const std::string &application_name, const std::string &organization)
	: qsettings_(new QSettings(QSettings::IniFormat, QSettings::UserScope, organization.c_str(), application_name.c_str())) {}

settings_io::settings_io(const std::string &filename)
	: qsettings_(new QSettings(filename.c_str(), QSettings::IniFormat)) {}

settings_io::~settings_io() {}

bool settings_io::does_exist() const {
	QFile file(qsettings_->fileName());
	return file.exists();
}

std::string settings_io::filename() const {
	return qsettings_->fileName().toStdString();
}

void settings_io::read(settings &settings) {
	settings.log_level_ = qsettings_->value(log_level_key.c_str(), settings_log_level_default).toInt();
	settings.gps_collection_period_ms_ = qsettings_->value(gps_collection_period_ms_key.c_str(), gps_collection_period_ms_default).toInt();
	settings.num_items_in_flight_ = qsettings_->value(num_items_in_flight_key.c_str(), num_items_in_flight_default).toInt();
	settings.use_rf_board_adjustment_ = qsettings_->value(use_rf_board_adjustment_key.c_str(), use_rf_board_adjustment_default).toBool();

	settings.output_directory_ = qsettings_->value(output_directory_key.c_str(), output_directory_default.c_str()).toString().toStdString();
	if(settings.output_directory_.size()) {
		auto it = settings.output_directory_.rbegin();
		if(*it != '\\' && *it != '/')
			settings.output_directory_ += "/";
	}
	if(!file_path_validation::is_path_valid(settings.output_directory_)) {
		settings.output_directory_ = file_path_validation::get_writable_file_path();
		//LOG(LVERBOSE) << "Output directory is not valid.  Switching to " << settings.output_directory_ << ".";
	}

	settings.output_in_binary_ = qsettings_->value(output_in_binary_key.c_str(), output_in_binary_default).toBool();
	settings.simultaneous_collection_ = qsettings_->value(simultaneous_collection_key.c_str(), simultaneous_collection_default).toBool();
	settings.eeprom_update_period_for_1pps_calibration_minutes_ = qsettings_->value(eeprom_update_period_for_1pps_calibration_minutes_key.c_str(),
		eeprom_update_period_for_1pps_calibration_minutes_default).toInt();
	settings.scheduling_algorithm_ = (scheduling_algorithm_type)qsettings_->value(scheduling_algorithm_key.c_str(), scheduling_algorithm_default).toInt();

	settings.log_gps_general_ = qsettings_->value(log_gps_general_key.c_str(), log_gps_general_default).toBool();
	settings.log_gps_parsing_ = qsettings_->value(log_gps_parsing_key.c_str(), log_gps_parsing_default).toBool();
	settings.log_collection_ = qsettings_->value(log_collection_key.c_str(), log_collection_default).toBool();

	settings.power_spectrum_priority_ = qsettings_->value(power_spectrum_priority_key.c_str(), settings_power_spectrum_priority_default).toInt();
	settings.iq_data_priority_ = qsettings_->value(iq_data_priority_key.c_str(), settings_iq_data_priority_default).toInt();

	read(settings.standard_output_, standard_output_group_key);
	read(settings.signal_slots_, signal_slot_output_group_key);
	read(settings.packet_output_, packet_output_group_key);
	read(settings.file_output_, file_output_group_key);

	read(settings.output_intervals_, output_interval_group_key);

	read(settings.gsm_sweep_collection_, gsm_sweep_collection_group_key);
	read(settings.gsm_layer_3_collection_, gsm_layer_3_collection_group_key);
	read(settings.umts_sweep_collection_, umts_sweep_collection_group_key);
	read(settings.umts_layer_3_collection_, umts_layer_3_collection_group_key);
	read(settings.lte_sweep_collection_, lte_sweep_collection_group_key);
	read(settings.lte_layer_3_collection_, lte_layer_3_collection_group_key);
	read(settings.sweep_collection_, sweep_collection_group_key);

	read(settings.gsm_layer_3_decode_, gsm_decode_thresholds_group_key);
	read(settings.umts_layer_3_decode_, umts_decode_thresholds_group_key);
	read(settings.lte_layer_3_decode_, lte_decode_thresholds_group_key);

	read(settings.gsm_sweep_general_, gsm_sweep_general_group_key);
	read(settings.gsm_layer_3_general_, gsm_layer_3_general_group_key);

	read(settings.umts_sweep_general_, umts_sweep_general_group_key);
	read(settings.umts_layer_3_general_, umts_layer_3_general_group_key);

	read(settings.lte_sweep_general_, lte_sweep_general_group_key);
	read(settings.lte_layer_3_general_, lte_layer_3_general_group_key);

	read(settings.frequency_correction_settings_, frequency_correction_group_key);

	read(settings.blade_settings_);
}

void settings_io::read(output_settings &settings, const std::string &group_key) {
	qsettings_->beginGroup(group_key.c_str());
	settings.scanner_ = qsettings_->value(scanner_output_key.c_str(), settings_output_default).toBool();
	settings.gps_ = qsettings_->value(gps_output_key.c_str(), settings_output_default).toBool();
	settings.gsm_sweep_ = qsettings_->value(gsm_sweep_output_key.c_str(), settings_output_default).toBool();
	settings.gsm_layer_3_ = qsettings_->value(gsm_layer_3_output_key.c_str(), settings_output_default).toBool();
	settings.umts_sweep_ = qsettings_->value(umts_sweep_output_key.c_str(), settings_output_default).toBool();
	settings.umts_layer_3_ = qsettings_->value(umts_layer_3_output_key.c_str(), settings_output_default).toBool();
	settings.lte_sweep_ = qsettings_->value(lte_sweep_output_key.c_str(), settings_output_default).toBool();
	settings.lte_layer_3_ = qsettings_->value(lte_layer_3_output_key.c_str(), settings_output_default).toBool();
	settings.sweep_ = qsettings_->value(sweep_output_key.c_str(), settings_output_default).toBool();
	settings.power_spectrum_ = qsettings_->value(power_spectrum_output_key.c_str(), settings_output_default).toBool();
	settings.iq_data_ = qsettings_->value(iq_data_output_key.c_str(), settings_output_default).toBool();
	qsettings_->endGroup();

}

void settings_io::read(collection_settings &settings, const std::string &group_key) {
	qsettings_->beginGroup(group_key.c_str());
	settings.sampling_rate_ = qsettings_->value(sampling_rate_key.c_str(), settings_sampling_rate_default).toLongLong();
	settings.bandwidth_ = qsettings_->value(bandwidth_key.c_str(), settings_bandwidth_default).toLongLong();
	settings.collection_time_ = qsettings_->value(collection_time_key.c_str(), settings_collection_time_default).toLongLong();
	settings.is_streaming_ = qsettings_->value(is_streaming_key.c_str(), settings_is_streaming_default).toBool();
	settings.overlap_time_ = qsettings_->value(overlap_time_key.c_str(), settings_overlap_time_default).toLongLong();
	settings.priority_ = qsettings_->value(priority_key.c_str(), settings_priority_default).toInt();
	settings.low_intermediate_frequency_ = qsettings_->value(low_intermediate_frequency_key.c_str(), settings_low_intermediate_frequency_default).toLongLong();
	settings.high_intermediate_frequency_ = qsettings_->value(high_intermediate_frequency_key.c_str(), settings_high_intermediate_frequency_default).toLongLong();
	settings.step_size_ = qsettings_->value(step_size_key.c_str(), settings_step_size_default).toLongLong();
	qsettings_->endGroup();
}

void settings_io::read(layer_3_settings &settings, const std::string &group_key) {
	qsettings_->beginGroup(group_key.c_str());
	settings.max_update_threshold_ = qsettings_->value(max_update_threshold_key.c_str(), settings_layer_3_max_update_threshold_default).toInt();
	settings.minimum_collection_round_ = qsettings_->value(min_collection_round_key.c_str(), settings_layer_3_min_collection_round_default).toInt();
	settings.decode_threshold_ = qsettings_->value(decode_threshold_key.c_str(), settings_layer_3_decode_threshold_default).toDouble();
	settings.decode_minimum_threshold_ = qsettings_->value(min_decode_threshold_key.c_str(), settings_layer_3_min_decode_threshold_default).toDouble();
	settings.should_prioritize_layer_3_ = qsettings_->value(should_prioritize_layer_3_key.c_str(), settings_layer_3_should_prioritize_layer_3_default).toBool();
	settings.minimum_decode_count_ = qsettings_->value(minimum_decode_count_key.c_str(), settings_layer_3_minimum_decode_count_default).toDouble();
	settings.complete_decode_interval_ = qsettings_->value(complete_decode_interval_key.c_str(), settings_layer_3_complete_decode_interval_default).toDouble();
	auto list = qsettings_->value(layer_3_wanted_key.c_str());
	auto string_list = list.toStringList();
	settings.wanted_layer_3_.clear();
	if(group_key == gsm_decode_thresholds_group_key) {
		for(auto i : string_list) {
			if(i.size())
				settings.wanted_layer_3_.push_back(convert_gsm_si(i.toStdString()));
		}
	}
	else if(group_key == umts_decode_thresholds_group_key) {
		for(auto i : string_list) {
			if(i.size())
				settings.wanted_layer_3_.push_back(convert_umts_sib(i.toStdString()));
		}
	}
	else if(group_key == lte_decode_thresholds_group_key) {
		for(auto i : string_list) {
			if(i.size())
				settings.wanted_layer_3_.push_back(convert_lte_sib(i.toStdString()));
		}
	}
	else {
		for(auto i : string_list) {
			if(i.size())
				settings.wanted_layer_3_.push_back(i.toInt());
		}
	}
	qsettings_->endGroup();
}

void settings_io::read(gsm_general_settings &settings, const std::string &group_key) {
	qsettings_->beginGroup(group_key.c_str());
	settings.side_power_threshold_ = qsettings_->value(gsm_side_power_threshold_key.c_str(), settings_gsm_general_side_power_threshold_default).toDouble();
	settings.band_power_threshold_ = qsettings_->value(gsm_band_power_threshold_key.c_str(), settings_gsm_general_band_power_threshold_default).toDouble();
	settings.perform_sync_correlations_ = qsettings_->value(gsm_perform_sync_correlations_key.c_str(), settings_gsm_general_perform_sync_correlations_default).toBool();
	settings.c_i_ratio_confidence_threshold_ = qsettings_->value(gsm_c_i_ratio_confidence_threshold_key.c_str(), settings_gsm_general_c_i_ratio_confidence_threshold_default).toDouble();
	qsettings_->endGroup();
}

void settings_io::read(umts_general_settings &settings, const std::string &group_key) {
	qsettings_->beginGroup(group_key.c_str());
	settings.sensitivity_ = qsettings_->value(sensitivity_key.c_str(), settings_umts_general_sensitivity_default).toDouble();
	settings.full_scan_interval_ = qsettings_->value(full_scan_interval_key.c_str(), settings_umts_general_full_scan_interval_default).toInt();
	settings.num_coherent_slots_ = qsettings_->value(num_coherent_slots_key.c_str(), settings_umts_general_num_coherent_slots_default).toInt();
	qsettings_->endGroup();
}

void settings_io::read(lte_general_settings &settings, const std::string &group_key) {
	qsettings_->beginGroup(group_key.c_str());
	settings.sync_quality_confidence_threshold_ = qsettings_->value(sync_quality_confidence_threshold_key.c_str(), settings_lte_general_sync_quality_confidence_threshold_default).toDouble();
	settings.full_scan_interval_ = qsettings_->value(full_scan_interval_key.c_str(), settings_lte_general_full_scan_interval_default).toInt();
	settings.pbch_decoding_threshold_ = qsettings_->value(pbch_decoding_threshold_key.c_str(), settings_lte_general_pbch_decoding_threshold_default).toDouble();
	settings.minimum_relative_peak_threshold_= qsettings_->value(minimum_relative_peak_threshold_key.c_str(), settings_lte_general_minimum_relative_peak_threshold_default).toDouble();
	qsettings_->endGroup();
}

void settings_io::read(frequency_correction_settings &settings, const std::string &group_key) {
	qsettings_->beginGroup(group_key.c_str());
	settings.initial_frequency_correction_range_start_ = qsettings_->value(initial_frequency_correction_offset_start_key.c_str(), initial_frequency_correction_offset_start_default).toDouble();
	settings.initial_frequency_correction_range_end_ = qsettings_->value(initial_frequency_correction_offset_end_key.c_str(), initial_frequency_correction_offset_end_default).toInt();
	qsettings_->endGroup();
	read(settings.general_settings_, group_key);
}

void settings_io::read(blade_settings &settings) {
	qsettings_->beginGroup(nr_general_group_key.c_str());
	settings.log_level_ = qsettings_->value(blade_log_level_key.c_str(), blade_log_level_default).toInt();
	qsettings_->endGroup();
	read(settings.intermittent_streaming_rx_, nr_intermittent_streaming_group_key);
	read(settings.full_streaming_rx_, nr_full_streaming_group_key);
}

void settings_io::read(blade_rx_settings &settings, const std::string &group_key) {
	qsettings_->beginGroup(group_key.c_str());
	settings.rx_sync_num_buffers_ = qsettings_->value(blade_rx_sync_num_buffers_key.c_str(), blade_rx_sync_num_buffers_default).toInt();
	settings.rx_sync_buffer_size_ = qsettings_->value(blade_rx_sync_buffer_size_key.c_str(), blade_rx_sync_buffer_size_default).toInt();
	settings.rx_sync_num_transfers_ = qsettings_->value(blade_rx_sync_num_transfers_key.c_str(), blade_rx_sync_num_transfers_default).toInt();
	settings.rx_sync_timeout_ = qsettings_->value(blade_rx_sync_timeout_key.c_str(), blade_rx_sync_timeout_default).toInt();
	qsettings_->endGroup();
}

void settings_io::read(output_interval_settings &settings, const std::string &group_key) {
	qsettings_->beginGroup(group_key.c_str());
	//settings.scanner_ = qsettings_->value(scanner_output_key.c_str(), settings_output_default).toBool();
	//settings.gps_ = qsettings_->value(gps_output_key.c_str(), settings_output_default).toBool();
	//settings.gsm_sweep_ = qsettings_->value(gsm_sweep_output_key.c_str(), settings_output_default).toBool();
	settings.gsm_layer_3_ = qsettings_->value(gsm_layer_3_output_key.c_str(), settings_output_interval_default).toInt();
	//settings.umts_sweep_ = qsettings_->value(umts_sweep_output_key.c_str(), settings_output_default).toBool();
	//settings.umts_layer_3_ = qsettings_->value(umts_layer_3_output_key.c_str(), settings_output_default).toBool();
	//settings.lte_sweep_ = qsettings_->value(lte_sweep_output_key.c_str(), settings_output_default).toBool();
	//settings.lte_layer_3_ = qsettings_->value(lte_layer_3_output_key.c_str(), settings_output_default).toBool();
	//settings.sweep_ = qsettings_->value(sweep_output_key.c_str(), settings_output_default).toBool();
	qsettings_->endGroup();

}



void settings_io::write(const settings &settings) {
	qsettings_->setValue(log_level_key.c_str(), settings.log_level_);
	qsettings_->setValue(gps_collection_period_ms_key.c_str(), settings.gps_collection_period_ms_);
	qsettings_->setValue(num_items_in_flight_key.c_str(), settings.num_items_in_flight_);
	qsettings_->setValue(use_rf_board_adjustment_key.c_str(), settings.use_rf_board_adjustment_);
	qsettings_->setValue(output_directory_key.c_str(), settings.output_directory_.c_str());
	qsettings_->setValue(output_in_binary_key.c_str(), settings.output_in_binary_);
	qsettings_->setValue(simultaneous_collection_key.c_str(), settings.simultaneous_collection_);
	qsettings_->setValue(eeprom_update_period_for_1pps_calibration_minutes_key.c_str(), settings.eeprom_update_period_for_1pps_calibration_minutes_);
	qsettings_->setValue(scheduling_algorithm_key.c_str(), settings.scheduling_algorithm_);

	qsettings_->setValue(log_gps_general_key.c_str(), settings.log_gps_general_);
	qsettings_->setValue(log_gps_parsing_key.c_str(), settings.log_gps_parsing_);
	qsettings_->setValue(log_collection_key.c_str(), settings.log_collection_);

	qsettings_->setValue(power_spectrum_priority_key.c_str(), settings.power_spectrum_priority_);
	qsettings_->setValue(iq_data_priority_key.c_str(), settings.iq_data_priority_);

	write(settings.standard_output_, standard_output_group_key);
	write(settings.signal_slots_, signal_slot_output_group_key);
	write(settings.packet_output_, packet_output_group_key);
	write(settings.file_output_, file_output_group_key);

	write(settings.output_intervals_, output_interval_group_key);

	write(settings.gsm_sweep_collection_, gsm_sweep_collection_group_key);
	write(settings.gsm_layer_3_collection_, gsm_layer_3_collection_group_key);
	write(settings.umts_sweep_collection_, umts_sweep_collection_group_key);
	write(settings.umts_layer_3_collection_, umts_layer_3_collection_group_key);
	write(settings.lte_sweep_collection_, lte_sweep_collection_group_key);
	write(settings.lte_layer_3_collection_, lte_layer_3_collection_group_key);
	write(settings.sweep_collection_, sweep_collection_group_key);

	write(settings.gsm_layer_3_decode_, gsm_decode_thresholds_group_key);
	write(settings.umts_layer_3_decode_, umts_decode_thresholds_group_key);
	write(settings.lte_layer_3_decode_, lte_decode_thresholds_group_key);

	write(settings.gsm_sweep_general_, gsm_sweep_general_group_key);
	write(settings.gsm_layer_3_general_, gsm_layer_3_general_group_key);

	write(settings.umts_sweep_general_, umts_sweep_general_group_key);
	write(settings.umts_layer_3_general_, umts_layer_3_general_group_key);

	write(settings.lte_sweep_general_, lte_sweep_general_group_key);
	write(settings.lte_layer_3_general_, lte_layer_3_general_group_key);

	write(settings.frequency_correction_settings_, frequency_correction_group_key);

	write(settings.blade_settings_);
}

void settings_io::write(const output_settings &settings, const std::string &group_key) {
	qsettings_->beginGroup(group_key.c_str());
	qsettings_->setValue(scanner_output_key.c_str(), settings.scanner_);
	qsettings_->setValue(gps_output_key.c_str(), settings.gps_);
	qsettings_->setValue(gsm_sweep_output_key.c_str(), settings.gsm_sweep_);
	qsettings_->setValue(gsm_layer_3_output_key.c_str(), settings.gsm_layer_3_);
	qsettings_->setValue(umts_sweep_output_key.c_str(), settings.umts_sweep_);
	qsettings_->setValue(umts_layer_3_output_key.c_str(), settings.umts_layer_3_);
	qsettings_->setValue(lte_sweep_output_key.c_str(), settings.lte_sweep_);
	qsettings_->setValue(lte_layer_3_output_key.c_str(), settings.lte_layer_3_);
	qsettings_->setValue(sweep_output_key.c_str(), settings.sweep_);
	qsettings_->setValue(power_spectrum_output_key.c_str(), settings.sweep_);
	qsettings_->setValue(iq_data_output_key.c_str(), settings.sweep_);
	qsettings_->endGroup();
}

void settings_io::write(const collection_settings &settings, const std::string &group_key) {
	qsettings_->beginGroup(group_key.c_str());
	qsettings_->setValue(sampling_rate_key.c_str(), settings.sampling_rate_);
	qsettings_->setValue(bandwidth_key.c_str(), settings.bandwidth_);
	qsettings_->setValue(collection_time_key.c_str(), settings.collection_time_);
	qsettings_->setValue(is_streaming_key.c_str(), settings.is_streaming_);
	qsettings_->setValue(overlap_time_key.c_str(), settings.overlap_time_);
	qsettings_->setValue(priority_key.c_str(), settings.priority_);
	qsettings_->setValue(low_intermediate_frequency_key.c_str(), settings.low_intermediate_frequency_);
	qsettings_->setValue(high_intermediate_frequency_key.c_str(), settings.high_intermediate_frequency_);
	qsettings_->setValue(step_size_key.c_str(), settings.step_size_);
	qsettings_->endGroup();
}

void settings_io::write(const layer_3_settings &settings, const std::string &group_key) {
	qsettings_->beginGroup(group_key.c_str());
	qsettings_->setValue(max_update_threshold_key.c_str(), settings.max_update_threshold_);
	qsettings_->setValue(min_collection_round_key.c_str(), settings.minimum_collection_round_);
	qsettings_->setValue(decode_threshold_key.c_str(), settings.decode_threshold_);
	qsettings_->setValue(min_decode_threshold_key.c_str(), settings.decode_minimum_threshold_);
	qsettings_->setValue(should_prioritize_layer_3_key.c_str(), settings.should_prioritize_layer_3_);
	qsettings_->setValue(minimum_decode_count_key.c_str(), settings.minimum_decode_count_);
	qsettings_->setValue(complete_decode_interval_key.c_str(), settings.complete_decode_interval_);
	QStringList list;
	if(group_key == gsm_decode_thresholds_group_key) {
		for(auto i : settings.wanted_layer_3_)
			list.append(QString(convert_gsm_si(i).c_str()));
	}
	else if(group_key == umts_decode_thresholds_group_key) {
		for(auto i : settings.wanted_layer_3_)
			list.append(QString(convert_umts_sib(i).c_str()));
	}
	else if(group_key == lte_decode_thresholds_group_key) {
		for(auto i : settings.wanted_layer_3_)
			list.append(QString(convert_lte_sib(i).c_str()));
	}
	else {
		for(auto i : settings.wanted_layer_3_)
			list.append(QString::number((int)i));
	}
	qsettings_->setValue(layer_3_wanted_key.c_str(), list);
	qsettings_->endGroup();
}

void settings_io::write(const gsm_general_settings &settings, const std::string &group_key) {
	qsettings_->beginGroup(group_key.c_str());
	qsettings_->setValue(gsm_side_power_threshold_key.c_str(), settings.side_power_threshold_);
	qsettings_->setValue(gsm_band_power_threshold_key.c_str(), settings.band_power_threshold_);
	qsettings_->setValue(gsm_perform_sync_correlations_key.c_str(), settings.perform_sync_correlations_);
	qsettings_->setValue(gsm_c_i_ratio_confidence_threshold_key.c_str(), settings.c_i_ratio_confidence_threshold_);
	qsettings_->endGroup();
}

void settings_io::write(const umts_general_settings &settings, const std::string &group_key) {
	qsettings_->beginGroup(group_key.c_str());
	qsettings_->setValue(sensitivity_key.c_str(), settings.sensitivity_);
	qsettings_->setValue(full_scan_interval_key.c_str(), settings.full_scan_interval_);
	qsettings_->setValue(num_coherent_slots_key.c_str(), settings.num_coherent_slots_);
	qsettings_->endGroup();
}

void settings_io::write(const lte_general_settings &settings, const std::string &group_key) {
	qsettings_->beginGroup(group_key.c_str());
	qsettings_->setValue(sync_quality_confidence_threshold_key.c_str(), settings.sync_quality_confidence_threshold_);
	qsettings_->setValue(full_scan_interval_key.c_str(), settings.full_scan_interval_);
	qsettings_->setValue(pbch_decoding_threshold_key.c_str(), settings.pbch_decoding_threshold_);
	qsettings_->setValue(minimum_relative_peak_threshold_key.c_str(), settings.minimum_relative_peak_threshold_);
	qsettings_->endGroup();
}

void settings_io::write(const frequency_correction_settings &settings, const std::string &group_key) {
	qsettings_->beginGroup(group_key.c_str());
	qsettings_->setValue(initial_frequency_correction_offset_start_key.c_str(), settings.initial_frequency_correction_range_start_);
	qsettings_->setValue(initial_frequency_correction_offset_end_key.c_str(), settings.initial_frequency_correction_range_end_);
	qsettings_->endGroup();
	write(settings.general_settings_, group_key);
}

void settings_io::write(const blade_settings &settings) {
	qsettings_->beginGroup(nr_general_group_key.c_str());
	qsettings_->setValue(blade_log_level_key.c_str(), settings.log_level_);
	qsettings_->endGroup();
	write(settings.intermittent_streaming_rx_, nr_intermittent_streaming_group_key);
	write(settings.full_streaming_rx_, nr_full_streaming_group_key);
}

void settings_io::write(const blade_rx_settings &settings, const std::string &group_key) {
	qsettings_->beginGroup(group_key.c_str());
	qsettings_->setValue(blade_rx_sync_num_buffers_key.c_str(), settings.rx_sync_num_buffers_);
	qsettings_->setValue(blade_rx_sync_buffer_size_key.c_str(), settings.rx_sync_buffer_size_);
	qsettings_->setValue(blade_rx_sync_num_transfers_key.c_str(), settings.rx_sync_num_transfers_);
	qsettings_->setValue(blade_rx_sync_timeout_key.c_str(), settings.rx_sync_timeout_);
	qsettings_->endGroup();

}

void settings_io::write(const output_interval_settings &settings, const std::string &group_key) {
	qsettings_->beginGroup(group_key.c_str());
	//qsettings_->setValue(scanner_output_key.c_str(), settings.scanner_);
	//qsettings_->setValue(gps_output_key.c_str(), settings.gps_);
	//qsettings_->setValue(gsm_sweep_output_key.c_str(), settings.gsm_sweep_);
	qsettings_->setValue(gsm_layer_3_output_key.c_str(), settings.gsm_layer_3_);
	//qsettings_->setValue(umts_sweep_output_key.c_str(), settings.umts_sweep_);
	//qsettings_->setValue(umts_layer_3_output_key.c_str(), settings.umts_layer_3_);
	//qsettings_->setValue(lte_sweep_output_key.c_str(), settings.lte_sweep_);
	//qsettings_->setValue(lte_layer_3_output_key.c_str(), settings.lte_layer_3_);
	//qsettings_->setValue(sweep_output_key.c_str(), settings.sweep_);
	qsettings_->endGroup();
}

void settings_io::clear() {
	qsettings_->clear();
}


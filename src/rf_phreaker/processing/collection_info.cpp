#include "rf_phreaker/processing/collection_info.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/exception_types.h"

using namespace rf_phreaker::processing;


rf_phreaker::time_type sweep_collection_info::time_ns__ = milli_to_nano(31);
rf_phreaker::time_type sweep_collection_info::overlap_time_ns__ = milli_to_nano(5);
rf_phreaker::bandwidth_type sweep_collection_info::bandwidth__ = mhz(5);
rf_phreaker::frequency_type sweep_collection_info::sampling_rate__ = khz(4875);

rf_phreaker::time_type gsm_sweep_collection_info::time_ns__ = milli_to_nano(31);
rf_phreaker::time_type gsm_sweep_collection_info::overlap_time_ns__ = milli_to_nano(5);
rf_phreaker::bandwidth_type gsm_sweep_collection_info::bandwidth__ = mhz(5);
rf_phreaker::frequency_type gsm_sweep_collection_info::sampling_rate__ = khz(4875);

rf_phreaker::time_type gsm_layer_3_collection_info::time_ns__ = milli_to_nano(60);
rf_phreaker::time_type gsm_layer_3_collection_info::overlap_time_ns__ = milli_to_nano(5);
rf_phreaker::bandwidth_type gsm_layer_3_collection_info::bandwidth__ = mhz(5);
rf_phreaker::frequency_type gsm_layer_3_collection_info::sampling_rate__ = khz(4875);

rf_phreaker::time_type umts_sweep_collection_info::time_ns__ = milli_to_nano(31);
rf_phreaker::time_type umts_sweep_collection_info::overlap_time_ns__ = milli_to_nano(5);
rf_phreaker::bandwidth_type umts_sweep_collection_info::bandwidth__ = mhz(5);
rf_phreaker::frequency_type umts_sweep_collection_info::sampling_rate__ = khz(4875);

rf_phreaker::time_type umts_layer_3_collection_info::time_ns__ = milli_to_nano(160);
rf_phreaker::time_type umts_layer_3_collection_info::overlap_time_ns__ = milli_to_nano(5);
rf_phreaker::bandwidth_type umts_layer_3_collection_info::bandwidth__ = mhz(5);
rf_phreaker::frequency_type umts_layer_3_collection_info::sampling_rate__ = khz(4875);

rf_phreaker::time_type lte_sweep_collection_info::time_ns__ = milli_to_nano(30);
rf_phreaker::time_type lte_sweep_collection_info::overlap_time_ns__ = milli_to_nano(5);
rf_phreaker::bandwidth_type lte_sweep_collection_info::bandwidth__ = mhz(5);
rf_phreaker::frequency_type lte_sweep_collection_info::sampling_rate__ = khz(3840); //khz(3840);

rf_phreaker::time_type lte_layer_3_collection_info::time_ns__ = milli_to_nano(40);
rf_phreaker::time_type lte_layer_3_collection_info::overlap_time_ns__ = milli_to_nano(5);
rf_phreaker::bandwidth_type lte_layer_3_collection_info::bandwidth__ = mhz(5);
rf_phreaker::frequency_type lte_layer_3_collection_info::sampling_rate__ = khz(3840); //khz(3840);

void rf_phreaker::processing::initialize_collection_info_defaults(const rf_phreaker::settings &config) {
	sweep_collection_info::bandwidth__ = config.sweep_collection_.bandwidth_;
	sweep_collection_info::sampling_rate__ = config.sweep_collection_.sampling_rate_;
	sweep_collection_info::time_ns__ = config.sweep_collection_.collection_time_;
	sweep_collection_info::overlap_time_ns__ = config.sweep_collection_.overlap_time_;

	gsm_sweep_collection_info::bandwidth__ = config.gsm_sweep_collection_.bandwidth_;
	gsm_sweep_collection_info::sampling_rate__ = config.gsm_sweep_collection_.sampling_rate_;
	gsm_sweep_collection_info::time_ns__ = config.gsm_sweep_collection_.collection_time_;
	gsm_sweep_collection_info::overlap_time_ns__ = config.gsm_sweep_collection_.overlap_time_;

	gsm_layer_3_collection_info::bandwidth__ = config.gsm_layer_3_collection_.bandwidth_;
	gsm_layer_3_collection_info::sampling_rate__ = config.gsm_layer_3_collection_.sampling_rate_;
	gsm_layer_3_collection_info::time_ns__ = config.gsm_layer_3_collection_.collection_time_;
	gsm_layer_3_collection_info::overlap_time_ns__ = config.gsm_layer_3_collection_.overlap_time_;

	umts_sweep_collection_info::bandwidth__ = config.umts_sweep_collection_.bandwidth_;
	umts_sweep_collection_info::sampling_rate__ = config.umts_sweep_collection_.sampling_rate_;
	umts_sweep_collection_info::time_ns__ = config.umts_sweep_collection_.collection_time_;
	umts_sweep_collection_info::overlap_time_ns__ = config.umts_sweep_collection_.overlap_time_;

	umts_layer_3_collection_info::bandwidth__ = config.umts_layer_3_collection_.bandwidth_;
	umts_layer_3_collection_info::sampling_rate__ = config.umts_layer_3_collection_.sampling_rate_;
	umts_layer_3_collection_info::time_ns__ = config.umts_layer_3_collection_.collection_time_;
	umts_layer_3_collection_info::overlap_time_ns__ = config.umts_layer_3_collection_.overlap_time_;

	lte_sweep_collection_info::bandwidth__ = config.lte_sweep_collection_.bandwidth_;
	lte_sweep_collection_info::sampling_rate__ = config.lte_sweep_collection_.sampling_rate_;
	lte_sweep_collection_info::time_ns__ = config.lte_sweep_collection_.collection_time_;
	lte_sweep_collection_info::overlap_time_ns__ = config.lte_sweep_collection_.overlap_time_;

	lte_layer_3_collection_info::bandwidth__ = config.lte_layer_3_collection_.bandwidth_;
	lte_layer_3_collection_info::sampling_rate__ = config.lte_layer_3_collection_.sampling_rate_;
	lte_layer_3_collection_info::time_ns__ = config.lte_layer_3_collection_.collection_time_;
	lte_layer_3_collection_info::overlap_time_ns__ = config.lte_layer_3_collection_.overlap_time_;
}

collection_info rf_phreaker::processing::create_tech_collection_info(rf_phreaker::specifier tech, rf_phreaker::frequency_type freq, rf_phreaker::operating_band band, bool can_remove) {
	using namespace rf_phreaker;
	switch(tech) {
	case GSM_SWEEP: {
		gsm_sweep_collection_info a(freq);
		a.operating_bands_ = band;
		a.can_remove_ = can_remove;
		return a;
	}
	case GSM_LAYER_3_DECODE: {
		gsm_layer_3_collection_info a(freq);
		a.operating_bands_ = band;
		a.can_remove_ = can_remove;
		return a;
	}
	//case CDMA_SWEEP:
	//	collection_info a(freq);
	//	a.operating_band_ = band;
	//a.can_remove_ = can_remove;
	//	return a;
	//case CDMA_LAYER_3_DECODE:
	//	collection_info a(freq);
	//	a.operating_band_ = band;
	//a.can_remove_ = can_remove;
	//	return a;
	case UMTS_SWEEP: {
		umts_sweep_collection_info a(freq);
		a.operating_bands_ = band;
		a.can_remove_ = can_remove;
		return a;
	}
	case UMTS_LAYER_3_DECODE: {
		umts_layer_3_collection_info a(freq);
		a.operating_bands_ = band;
		a.can_remove_ = can_remove;
		return a;
	}
	case LTE_SWEEP: {
		lte_sweep_collection_info a(freq);
		a.operating_bands_ = band;
		a.can_remove_ = can_remove;
		return a;
	}
	case LTE_LAYER_3_DECODE: {
		lte_layer_3_collection_info a(freq);
		a.operating_bands_ = band;
		a.can_remove_ = can_remove;
		return a;
	}
    //case RAW_DATA:
	//	collection_info a(freq);
	//	a.operating_band_ = band;
	//	return a;
	default:
		throw misc_error("Unknown tech specifier.");
	}
}

collection_info rf_phreaker::processing::create_sweep_collection_info(rf_phreaker::specifiers specs, rf_phreaker::frequency_type freq, operating_bands bands, bool can_remove) {
	sweep_collection_info a(freq, specs, bands, can_remove);
	return a;
}
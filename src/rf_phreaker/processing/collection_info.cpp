#include "rf_phreaker/processing/collection_info.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/exception_types.h"

using namespace rf_phreaker::processing;


rf_phreaker::time_type sweep_collection_info::time_ns__ = milli_to_nano(31);
rf_phreaker::bandwidth_type sweep_collection_info::bandwidth__ = mhz(5);
rf_phreaker::frequency_type sweep_collection_info::sampling_rate__ = khz(3840);

rf_phreaker::time_type umts_sweep_collection_info::time_ns__ = milli_to_nano(31);
rf_phreaker::bandwidth_type umts_sweep_collection_info::bandwidth__ = mhz(5);
rf_phreaker::frequency_type umts_sweep_collection_info::sampling_rate__ = khz(3840);

rf_phreaker::time_type umts_layer_3_collection_info::time_ns__ = milli_to_nano(160);
rf_phreaker::bandwidth_type umts_layer_3_collection_info::bandwidth__ = mhz(5);
rf_phreaker::frequency_type umts_layer_3_collection_info::sampling_rate__ = khz(3840);

rf_phreaker::time_type lte_sweep_collection_info::time_ns__ = milli_to_nano(30);
rf_phreaker::bandwidth_type lte_sweep_collection_info::bandwidth__ = mhz(5);
rf_phreaker::frequency_type lte_sweep_collection_info::sampling_rate__ = khz(3840); //khz(3840);

rf_phreaker::time_type lte_layer_3_collection_info::time_ns__ = milli_to_nano(40);
rf_phreaker::bandwidth_type lte_layer_3_collection_info::bandwidth__ = mhz(5);
rf_phreaker::frequency_type lte_layer_3_collection_info::sampling_rate__ = khz(3840); //khz(3840);

void rf_phreaker::processing::initialize_collection_info_defaults(const rf_phreaker::settings &config) {
	umts_sweep_collection_info::bandwidth__ = config.umts_sweep_collection_.bandwidth_;
	umts_sweep_collection_info::sampling_rate__ = config.umts_sweep_collection_.sampling_rate_;
	umts_sweep_collection_info::time_ns__ = config.umts_sweep_collection_.collection_time_;

	umts_layer_3_collection_info::bandwidth__ = config.umts_layer_3_collection_.bandwidth_;
	umts_layer_3_collection_info::sampling_rate__ = config.umts_layer_3_collection_.sampling_rate_;
	umts_layer_3_collection_info::time_ns__ = config.umts_layer_3_collection_.collection_time_;

	lte_sweep_collection_info::bandwidth__ = config.lte_sweep_collection_.bandwidth_;
	lte_sweep_collection_info::sampling_rate__ = config.lte_sweep_collection_.sampling_rate_;
	lte_sweep_collection_info::time_ns__ = config.lte_sweep_collection_.collection_time_;

	lte_layer_3_collection_info::bandwidth__ = config.lte_layer_3_collection_.bandwidth_;
	lte_layer_3_collection_info::sampling_rate__ = config.lte_layer_3_collection_.sampling_rate_;
	lte_layer_3_collection_info::time_ns__ = config.lte_layer_3_collection_.collection_time_;
}

collection_info rf_phreaker::processing::create_tech_collection_info(rf_phreaker::specifier tech, rf_phreaker::frequency_type freq, rf_phreaker::operating_band band) {
	using namespace rf_phreaker;
	switch(tech) {
	//case GSM_SWEEP:
	//	collection_info a(freq);
	//	a.operating_band_ = band;
	//	return a;
	//case GSM_LAYER_3_DECODE:
	//	collection_info a(freq);
	//	a.operating_band_ = band;
	//	return a;
	//case CDMA_SWEEP:
	//	collection_info a(freq);
	//	a.operating_band_ = band;
	//	return a;
	//case CDMA_LAYER_3_DECODE:
	//	collection_info a(freq);
	//	a.operating_band_ = band;
	//	return a;
	case UMTS_SWEEP: {
		umts_sweep_collection_info a(freq);
		a.operating_band_ = band;
		return a; 
	}
	case UMTS_LAYER_3_DECODE: {
		umts_layer_3_collection_info a(freq);
		a.operating_band_ = band;
		return a;
	}
	case LTE_SWEEP: {
		lte_sweep_collection_info a(freq);
		a.operating_band_ = band;
		return a;
	}
	case LTE_LAYER_3_DECODE: {
		lte_layer_3_collection_info a(freq);
		a.operating_band_ = band;
		return a;
	}
	//case RAW_IQ:
	//	collection_info a(freq);
	//	a.operating_band_ = band;
	//	return a;
	default:
		throw misc_error("Unknown tech specifier.");
	}
}
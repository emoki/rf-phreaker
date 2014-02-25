#include "rf_phreaker/processing/collection_info.h"
#include "rf_phreaker/common/common_utility.h"

using namespace rf_phreaker::processing;


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

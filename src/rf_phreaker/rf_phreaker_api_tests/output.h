#include <iostream>
#include <functional>
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/protobuf_specific/rf_phreaker.pb.h"

void RP_CALLCONV rp_update(const int8_t *bytes, int32_t size) {
	rf_phreaker::protobuf::rp_update u;
	u.ParseFromArray(bytes, size);
	u.PrintDebugString();
	std::cout << "\n\n\n";
	switch(u.update_case()) {
	case rf_phreaker::protobuf::rp_update::UpdateCase::kLog:
		std::cout << u.log().msg().c_str() << std::endl;
		break;
	case rf_phreaker::protobuf::rp_update::UpdateCase::kDevice:
		std::cout << u.device().serial() << "\t" << u.device().device_communication() << std::endl;
		break;
	case rf_phreaker::protobuf::rp_update::UpdateCase::kGps:
		std::cout << u.gps().lock() << "\t" << u.gps().latitude() << "\t" << u.gps().longitude() << "\t" << std::endl;
		break;
	}
}


void RP_CALLCONV rp_log_update(const char *message) {
	std::cout << message << std::endl;
}

void RP_CALLCONV rp_message_update(rp_status status, const char *message) {
	std::cout << rp_status_message(status) << " " << message << std::endl;
}

void RP_CALLCONV rp_device_info_update(const rp_device_info *info) {}

void RP_CALLCONV rp_gps_update(const rp_gps *gps) {
	std::cout << "gps" << std::endl;
}

void RP_CALLCONV rp_gsm_update(const rp_base *base, const rp_gsm *gsm, int num_gsm) {}

void RP_CALLCONV rp_wcdma_update(const rp_base *base, const rp_wcdma *umts, int num_umts) {}

void RP_CALLCONV rp_lte_update(const rp_base *base, const rp_lte *lte, int num_lte) {}

void RP_CALLCONV rp_gsm_sweep_update(const rp_base *base, const rp_gsm *gsm, int num_gsm) {}

void RP_CALLCONV rp_wcdma_sweep_update(const rp_base *base, const rp_wcdma *wcdma, int num_wcdma) {}

void RP_CALLCONV rp_lte_sweep_update(const rp_base *base, const rp_lte *lte, int num_lte) {}

void RP_CALLCONV rp_raw_data_update(const rp_raw_data, int num_raw_data) {}

class api_output {
public:
	api_output() {
		cbs_.rp_update = &rp_update;
		cbs_.rp_log_update = &rp_log_update;
		cbs_.rp_message_update = &rp_message_update;
		cbs_.rp_device_info_update = &rp_device_info_update;
		cbs_.rp_gps_update = &rp_gps_update;
		cbs_.rp_gsm_full_scan_update = &rp_gsm_update;
		cbs_.rp_wcdma_full_scan_update = &rp_wcdma_update;
		cbs_.rp_lte_full_scan_update = &rp_lte_update;
		cbs_.rp_gsm_sweep_update = &rp_gsm_sweep_update;
		cbs_.rp_wcdma_sweep_update = &rp_wcdma_sweep_update;
		cbs_.rp_lte_sweep_update = &rp_lte_sweep_update;
		cbs_.rp_raw_data_update = &rp_raw_data_update;
	}
	rp_callbacks cbs_;
};	

#include <iostream>
#include <functional>
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"

void RP_CALLCONV rp_log_update(const char *message) {
	std::cout << message << std::endl;
}

void RP_CALLCONV rp_message_update(rp_status status, const char *message) {
	std::cout << rp_status_message(status) << " " << message << std::endl;
}

void RP_CALLCONV rp_device_info_update(const rp_device_info *info) {}

void RP_CALLCONV rp_gps_update(const rp_gps *gps) {}

void RP_CALLCONV rp_gsm_update(const rp_base *base, const rp_gsm *gsm, int num_gsm) {}

void RP_CALLCONV rp_umts_update(const rp_base *base, const rp_umts *umts, int num_umts) {}

void RP_CALLCONV rp_lte_update(const rp_base *base, const rp_lte *lte, int num_lte) {}

void RP_CALLCONV rp_sweep_update(const rp_base *base, const rp_gsm *gsm, int num_gsm, const rp_umts *umts, int num_umts, const rp_lte *lte, int num_lte) {}

class api_output {
public:
	api_output() {
		cbs_.rp_log_update = &rp_log_update;
		cbs_.rp_message_update = &rp_message_update;
		cbs_.rp_device_info_update = &rp_device_info_update;
		cbs_.rp_gps_update = &rp_gps_update;
		cbs_.rp_gsm_update = &rp_gsm_update;
		cbs_.rp_umts_update = &rp_umts_update;
		cbs_.rp_lte_update = &rp_lte_update;
		cbs_.rp_sweep_update = &rp_sweep_update;
	}
	rp_callbacks cbs_;
};	

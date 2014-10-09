#include "rf_phreaker\rf_phreaker_api\rf_phreaker_api.h"
#include "rf_phreaker\common\exception_types.h"

namespace rf_phreaker { namespace api { 

static rp_status to_rp_status(const rf_phreaker_error &err) {
	char *s = 0;

	switch(err.error_type_) {
	case comm_error_type: 
		break;
	case scanner_init_error_type:
		break;
	case hardware_error_type:
		break;
	case misc_error_type:
		break;
	case file_error_type:
		break;
	case blade_rf_error_type:
		break;
	case ipp_error_type:
		break;
	case filter_error_type:
		break;
	case gsm_analysis_error_type:
		break;
	case umts_analysis_error_type:
		break;
	case lte_analysis_error_type:
		break;
	case processing_error_type:
		break;
	case matlab_interface_error_type:
		break;
	case cappeen_api_error_type:
		break;
	case gps_comm_error_type:
		break;
	case rf_phreaker_api_error_type:
		break;
	default:
		;
	}
	return RP_STATUS_OK;
}

class rf_phreaker_api_converter {
	//rp_device_info* to_

};
}}
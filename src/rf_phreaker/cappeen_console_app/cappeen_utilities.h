#pragma once

#include "rf_phreaker/cappeen_console_app/helper_structs.h"

namespace cappeen_scanner {


const uint16_t NOT_DECODED_16 = 0xFFFF;
const uint32_t NOT_DECODED_32 = 0xFFFFFFFF;



class cappeen_utilities
{
public:
	static void convert_and_add_gsm_bands(std::vector<beagle_api::TECHNOLOGIES_AND_BANDS> &tech_bands, const std::vector<int> &bands);

	static void convert_and_add_umts_bands(std::vector<beagle_api::TECHNOLOGIES_AND_BANDS> &tech_bands, const std::vector<int> &bands);

	static void convert_and_add_lte_bands(std::vector<beagle_api::TECHNOLOGIES_AND_BANDS> &tech_bands, const std::vector<int> &bands);

	static void set_thread_name(char* szThreadName,  uint32_t dwThreadID = -1);

	static std::string create_time_stamp();

};


}
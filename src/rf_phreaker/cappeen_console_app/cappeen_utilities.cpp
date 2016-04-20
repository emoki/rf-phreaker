#include "rf_phreaker/cappeen_console_app/cappeen_utilities.h"

#include <boost/date_time.hpp>
#include <Windows.h>

using namespace beagle_api;

namespace cappeen_scanner {

	void cappeen_utilities::convert_and_add_gsm_bands(std::vector<beagle_api::TECHNOLOGIES_AND_BANDS> &tech_bands, const std::vector<int> &bands) {
		for(auto it = bands.begin(); it != bands.end(); ++it) {
			switch(*it) {
			case 850:
				tech_bands.push_back(GSM_BAND_850);
				break;
			case 900:
				tech_bands.push_back(GSM_BAND_900);
				break;
			case 1800:
				tech_bands.push_back(GSM_BAND_1800);
				break;
			case 1900:
				tech_bands.push_back(GSM_BAND_1900);
				break;
			default:
				throw std::runtime_error("Unknown GSM band.");
			}
		}
	}

	void cappeen_utilities::convert_and_add_umts_bands(std::vector<beagle_api::TECHNOLOGIES_AND_BANDS> &tech_bands, const std::vector<int> &bands) {
		for(auto it = bands.begin(); it != bands.end(); ++it) {
			switch(*it) {
			case 850:
				tech_bands.push_back(WCDMA_BAND_850);
				break;
			case 900:
				tech_bands.push_back(WCDMA_BAND_900);
				break;
			case 1800:
				tech_bands.push_back(WCDMA_BAND_1800);
				break;
			case 1900:
				tech_bands.push_back(WCDMA_BAND_1900);
				break;
			case 2100:
				tech_bands.push_back(WCDMA_BAND_2100);
				break;
			default:
				throw std::runtime_error("Unknown WCDMA band.");
			}
		}
	}

	void cappeen_utilities::convert_and_add_lte_bands(std::vector<beagle_api::TECHNOLOGIES_AND_BANDS> &tech_bands, const std::vector<int> &bands)
{
	for(auto it = bands.begin(); it != bands.end(); ++it)
	{
		switch(*it)
		{
			case 12:
				tech_bands.push_back(LTE_BAND_12);
				break;
			case 20:
				tech_bands.push_back(LTE_BAND_20);
				break;
			case 5:
				tech_bands.push_back(LTE_BAND_5);
				break;
			case 3:
				tech_bands.push_back(LTE_BAND_3);
				break;
			case 2:
				tech_bands.push_back(LTE_BAND_2);
				break;
			case 4:
				tech_bands.push_back(LTE_BAND_4);
				break;
			case 1:
				tech_bands.push_back(LTE_BAND_1);
				break;
			case 8:
				tech_bands.push_back(LTE_BAND_8);
				break;
			case 7:
				tech_bands.push_back(LTE_BAND_7);
				break;
			default:
				throw std::runtime_error("Unknown LTE band.");
		}
	}
}

typedef struct tagTHREADNAME_INFO
{
	DWORD dwType; // must be 0x1000
	LPCSTR szName; // pointer to name (in user addr space)
	DWORD dwThreadID; // thread ID (-1=caller thread)
	DWORD dwFlags; // reserved for future use, must be zero
} THREADNAME_INFO;

void cappeen_utilities::set_thread_name(char* szThreadName,  uint32_t dwThreadID)
{
	THREADNAME_INFO info;
	info.dwType = 0x1000;
	info.szName = szThreadName;
	info.dwThreadID = dwThreadID;
	info.dwFlags = 0;

	__try
	{
		RaiseException( 0x406D1388, 0, sizeof(info)/sizeof(DWORD), (DWORD*)&info );
	}
	__except(EXCEPTION_CONTINUE_EXECUTION)
	{
	}
}

std::string cappeen_utilities::create_time_stamp()
{
	return boost::posix_time::to_simple_string(boost::posix_time::second_clock::local_time());
}



}
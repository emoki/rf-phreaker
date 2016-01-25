#include "rf_phreaker/cappeen_console_app/cappeen_io.h"
#include "rf_phreaker/cappeen_console_app/simple_logger.h"

namespace cappeen_scanner {


static std::string beagle_filename = "_beagle_info.txt";
static std::string gps_filename = "_gps.txt";
static std::string gsm_sector_filename = "_gsm_sector.txt";
static std::string gsm_sweep_filename = "_gsm_sweep.txt";
static std::string umts_sector_filename = "_umts_sector.txt";
static std::string umts_sweep_filename = "_umts_sweep.txt";
static std::string lte_sector_filename = "_lte_sector.txt";
static std::string lte_sweep_filename = "_lte_sweep.txt";
static std::string api_string_filename = "_api_string.txt";


cappeen_io::cappeen_io(void)
{
	file_suffixes_[BEAGLE_OUTPUT] = beagle_filename;
	file_suffixes_[GPS_OUTPUT] = gps_filename;
	file_suffixes_[GSM_SECTOR_OUTPUT] = gsm_sector_filename;
	file_suffixes_[GSM_SWEEP_OUTPUT] = gsm_sweep_filename;
	file_suffixes_[UMTS_SECTOR_OUTPUT] = umts_sector_filename;
	file_suffixes_[UMTS_SWEEP_OUTPUT] = umts_sweep_filename;
	file_suffixes_[LTE_SECTOR_OUTPUT] = lte_sector_filename;
	file_suffixes_[LTE_SWEEP_OUTPUT] = lte_sweep_filename;
	file_suffixes_[API_STRING_OUTPUT] = api_string_filename;
}

cappeen_io::~cappeen_io(void)
{
}

void cappeen_io::configure_output_filename(const std::string &base_filename)
{
	base_filename_ = base_filename;
}

void cappeen_io::log_to_stdout(bool log)
{
	log_to_stdout_ = log;
}

std::string cappeen_io::output_common_header()
{
	return std::string("time") + beagle_delimiter;
}

template<> beagle_output_type cappeen_io::find_beagle_output_type<beagle_info_wrapper>() { return BEAGLE_OUTPUT; }
template<> beagle_output_type cappeen_io::find_beagle_output_type<gps_info_wrapper>() { return GPS_OUTPUT; }
template<> beagle_output_type cappeen_io::find_beagle_output_type<gsm_sector_info_wrapper>() { return GSM_SECTOR_OUTPUT; }
template<> beagle_output_type cappeen_io::find_beagle_output_type<gsm_sweep_info_wrapper>() { return GSM_SWEEP_OUTPUT; }
template<> beagle_output_type cappeen_io::find_beagle_output_type<umts_sector_info_wrapper>() { return UMTS_SECTOR_OUTPUT; }
template<> beagle_output_type cappeen_io::find_beagle_output_type<umts_sweep_info_wrapper>() { return UMTS_SWEEP_OUTPUT; }
template<> beagle_output_type cappeen_io::find_beagle_output_type<lte_sector_info_wrapper>() { return LTE_SECTOR_OUTPUT; }
template<> beagle_output_type cappeen_io::find_beagle_output_type<lte_sweep_info_wrapper>() { return LTE_SWEEP_OUTPUT; }
template<> beagle_output_type cappeen_io::find_beagle_output_type<api_string>() { return API_STRING_OUTPUT; }

}
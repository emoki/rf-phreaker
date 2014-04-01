#pragma once

#include "rf_phreaker/cappeen/beagle_defines.h"
#include "rf_phreaker/cappeen/cappeen_delegate.h"
#include "rf_phreaker/scanner/blade_rf_controller_async.h"
#include "rf_phreaker/processing/processing_graph.h"
#include "rf_phreaker/processing/gps_graph.h"
#include "rf_phreaker/common/settings.h"
#include "rf_phreaker/common/operating_band_range_specifier.h"
#include <memory>
#include <string>
#include <mutex>

namespace rf_phreaker { namespace cappeen_api {

class cappeen_impl
{
public:
	cappeen_impl();

	~cappeen_impl();

	long initialize(beagle_api::beagle_delegate *del);
	long clean_up();
	long list_available_units(char *list, unsigned int buf_size);
	long open_unit(const char *serial, unsigned int buf_size);
	long close_unit(const char *serial, unsigned int buf_size);
	long stop_collection();
	long start_collection(const beagle_api::collection_info &collection);
	long input_new_license(const char *serial, uint32_t serial_buf_size, const char *new_license_filename, uint32_t license_buf_size);
	const char* api_version() const;

private:

	void verify_init();
	void read_settings();
	rf_phreaker::processing::collection_info_containers create_collection_info_containers(const beagle_api::collection_info &collection);

	bool is_initialized_;

	rf_phreaker::settings config_;

	std::unique_ptr<rf_phreaker::scanner::blade_rf_controller_async> scanner_;

	std::unique_ptr<rf_phreaker::processing::data_output_async> data_output_;

	std::unique_ptr<rf_phreaker::processing::processing_graph> processing_graph_;

	std::unique_ptr<rf_phreaker::processing::gps_graph> gps_graph_;

	operating_band_range_specifier operating_bands_;

	std::unique_ptr<cappeen_delegate> delegate_;

	std::unique_ptr<init_log> logger_;

	std::mutex mutex_;
};


}}
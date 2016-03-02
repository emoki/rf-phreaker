#pragma once

#include "rf_phreaker/cappeen/beagle_defines.h"

#include <boost/scoped_ptr.hpp>
#include <boost/lexical_cast.hpp>

namespace cappeen_scanner
{
	class cappeen_interface
	{
	public:
		virtual ~cappeen_interface() {}
		virtual long list_available_beagle_units(char *beagle_list, unsigned int buf_size) = 0;
		virtual long open_beagle_unit(const char *beagle_serial, unsigned int buf_size) = 0;
		virtual long close_beagle_unit(const char *beagle_serial, unsigned int buf_size) = 0;
		virtual long stop_collection() = 0;
		virtual long start_collection(const beagle_api::collection_info &collection, bool perform_quick_scan) = 0;
		virtual long input_new_license(const char *beagle_serial, uint32_t serial_buf_size, const char *new_license_filename, uint32_t license_buf_size) = 0;
		virtual const char* api_version() = 0;
	};
}

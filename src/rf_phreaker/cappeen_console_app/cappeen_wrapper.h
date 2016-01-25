#pragma once

#include "rf_phreaker/cappeen_console_app/cappeen_interface.h"
#include "rf_phreaker/cappeen/cappeen.h"
#include <boost/scoped_ptr.hpp>
#include <boost/lexical_cast.hpp>

namespace cappeen_scanner
{

	class cappeen_wrapper : public cappeen_interface
	{
	public:
		cappeen_wrapper(beagle_api::beagle_delegate *del)
		{
			long error = cappeen_initialize(del);
			if(error)
				throw std::runtime_error("Error initializing cappeen.  Error code: " + boost::lexical_cast<std::string>(error));
		}

		virtual ~cappeen_wrapper()
		{
			cappeen_clean_up();
		}

		virtual long list_available_beagle_units(char *beagle_list, unsigned int buf_size)
		{
			return cappeen_list_available_units(beagle_list, buf_size);
		}

		virtual long open_beagle_unit(const char *beagle_serial, unsigned int buf_size)
		{
			return cappeen_open_unit(beagle_serial, buf_size);
		}

		virtual long close_beagle_unit(const char *beagle_serial, unsigned int buf_size)
		{
			return cappeen_close_unit(beagle_serial, buf_size);
		}

		virtual long stop_collection()
		{
			return cappeen_stop_collection();
		}

		virtual long start_collection(const beagle_api::collection_info &collection)
		{
			return cappeen_start_collection(collection);
		}

		virtual long input_new_license(const char *beagle_serial, uint32_t serial_buf_size, const char *new_license_filename, uint32_t license_buf_size)
		{
			return cappeen_input_new_license(beagle_serial, serial_buf_size, new_license_filename, license_buf_size);
		}

		virtual const char* api_version()
		{
			return cappeen_api_version();
		}
	};

}

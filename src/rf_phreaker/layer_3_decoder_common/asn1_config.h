#pragma once

#include "stdafx.h"
#include <stdint.h>
#include <math.h>
#include <boost/assert.hpp>
#include "rf_phreaker/common/config_file.h"


static const bool output_segments_default = false;
static const bool output_combined_segments_default = false;

static std::string asn1_config_filename = "asn1.config";
static std::string output_segments_key = "output_segments";
static std::string output_combined_segments_key = "output_combined_segments";

class asn1_config
{
public:
	asn1_config(std::string asn1_config_filename_tmp = asn1_config_filename) 
	{
		load_config_file(asn1_config_filename_tmp);
	}

	void load_config_file(std::string file)
	{
		try
		{
			std::string path_and_filename = create_path_and_filename(file);
			ConfigFile config(path_and_filename);

			output_segments_ = config.read<bool>(output_segments_key, output_segments_default);

			output_combined_segments_ = config.read<bool>(output_combined_segments_key, output_combined_segments_default);
		}
		catch(ConfigFile::file_not_found)
		{
			load_defaults();
		}
		catch(ConfigFile::key_not_found)
		{
			load_defaults();
		}
	}

	void load_defaults()
	{
		output_segments_ = output_segments_default;
		output_combined_segments_ = output_combined_segments_default;
	}

	bool output_segments() const { return output_segments_; }

	bool output_combined_segments() const { return output_combined_segments_; }

private:
	std::string create_path_and_filename(const std::string &filename)
	{
		char module_filename_char[MAX_PATH] = "";

		DWORD success = ::GetModuleFileName(0, module_filename_char, sizeof(module_filename_char) - 1);

		module_filename_char[MAX_PATH -1 ] = '\0';

		std::string module_filename(module_filename_char);
		
		std::string path_and_filename = module_filename.substr(0, module_filename.rfind("\\"));

		return path_and_filename.append("\\").append(filename);
	}

	bool output_segments_;

	bool output_combined_segments_;
};




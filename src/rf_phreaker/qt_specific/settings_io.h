#pragma once

#include "rf_phreaker/common/settings.h"
#include <memory>
#include <string>

class QSettings;

namespace rf_phreaker
{


class settings_io
{
public:
	settings_io(const std::string &application_name, const std::string &organization);

	void populate_settings(settings &settings);

	void read_collection_settings(collection_settings &settings, const std::string &group_key);

	void read_layer_3_settings(layer_3_settings &settings, const std::string &group_key);

	void read_umts_general_settings(umts_general &settings, const std::string &group_key);

private:
	std::unique_ptr<QSettings> qsettings_;
};


} 
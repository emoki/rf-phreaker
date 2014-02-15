#pragma once

#include "rf_phreaker/common/settings.h"
#include <memory>

class QSettings;

namespace rf_phreaker
{


class settings_io
{
public:
	settings_io(const std::string &application_name, const std::string &organization);

	void populate_settings(settings &settings);

	std::unique_ptr<QSettings> qsettings_;
};


}
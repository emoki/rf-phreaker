#include "rf_phreaker\qt_specific\settings_io.h"
#include "QtCore\qsettings.h"

using namespace rf_phreaker;

settings_io::settings_io(const std::string &application_name, const std::string &organization)
: qsettings_(new QSettings(organization.c_str(), application_name.c_str()))
{
}

void settings_io::populate_settings(settings &settings)
{
}

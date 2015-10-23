#include "rf_phreaker/qt_specific/file_path_validation.h"
#include "qtcore/qstandardpaths.h"
#include "qtcore/qfileinfo.h"
#include "qtcore/qdir.h"
#include "rf_phreaker/common/exception_types.h"
#include "rf_phreaker/qt_specific/qt_init.h"

namespace rf_phreaker {

std::string file_path_validation::get_writable_file_path() {
	qt_init::init();
	auto paths = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);
	if(paths.empty()) {
		throw rf_phreaker::file_io_error("Unable to find writable path.");
	}
	auto path = paths.first().toStdString();
	auto it = path.rbegin();
	if(*it != '\\' && *it != '/')
		path += "/";

	return path;
}

bool file_path_validation::is_path_valid(const std::string &path) {
	qt_init::init();
	QFileInfo info(path.c_str());
	return info.exists() && info.isWritable() && info.isReadable();
}

void file_path_validation::make_path(const std::string &path) {
	qt_init::init();
	QDir info;
	if(!info.mkpath(path.c_str()))
		throw rf_phreaker::file_io_error("Unable to make path.");
}

}
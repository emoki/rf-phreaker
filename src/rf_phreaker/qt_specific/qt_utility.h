#pragma once

#include "QtCore/qcoreapplication.h"
#include "rf_phreaker/qt_specific/qt_init.h"

namespace rf_phreaker {

class qt_utility {
public:
	static std::string app_name() {
		qt_init::init();
		return QCoreApplication::applicationName().toStdString();
	}
};

}
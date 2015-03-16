#pragma once

#include "QtCore/qcoreapplication.h"

namespace rf_phreaker {

class qt_init
{
public:
	static void init() {
		if(QCoreApplication::instance() == nullptr) {
			int argc = 1;
			char* argv = "dummy_qt_core";
			static QCoreApplication dummy_qt_core(argc, &argv);
		}
	}
};

}
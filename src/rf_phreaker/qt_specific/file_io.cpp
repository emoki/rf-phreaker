#include "rf_phreaker/qt_specific/file_io.h"
#include <io.h>
#include <QtCore/QTemporaryFile>
#include "rf_phreaker/qt_specific/qt_init.h"

using namespace rf_phreaker;

temp_file::temp_file() 
: file_descriptor_(nullptr) {
	qt_init::init(); 
	file_ = std::make_unique<QTemporaryFile>();
	if(file_->open()) {
		file_descriptor_ = _fdopen(_dup(file_->handle()), "w+");
	}
}

temp_file::~temp_file() {
	if(file_descriptor_) {
		fclose(file_descriptor_);
		file_descriptor_ = nullptr;
	}
}

FILE* temp_file::get_file_descriptor() {
	return file_descriptor_;
}

void temp_file::flush() {
	if(file_descriptor_) {
		fflush(file_descriptor_);
	}
}

std::string temp_file::read_entire_file() {
	flush();
	if(!file_->isOpen())
		file_->open();
	else
		file_->reset();
	return file_->readAll().toStdString();
}

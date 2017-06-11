#pragma once
#include <memory>
#include <string>

class QTemporaryFile;

namespace rf_phreaker {

class temp_file
{
public:
	temp_file();

	~temp_file();

	FILE* get_file_descriptor();

	void flush();

	std::string read_entire_file();

private:
	std::unique_ptr<QTemporaryFile> file_;
	FILE *file_descriptor_;
};

}

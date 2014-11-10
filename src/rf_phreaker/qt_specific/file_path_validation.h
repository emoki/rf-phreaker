#pragma once

#include <string>

namespace rf_phreaker {

class file_path_validation
{
public:
	static std::string get_writable_file_path();

	static bool is_path_valid(const std::string &path);

	static void make_path(const std::string &path);
};

}
#pragma once

#include "rf_phreaker/scanner/blade_rf_controller.h"

namespace rf_phreaker { namespace matlab_interface {

	
enum matlab_interface_errors
{
	matlab_interface_no_error = 0,
	matlab_interface_error_general = -1000,
	matlab_interface_error_insufficient_buf_size,
	matlab_interface_error_null_detected,
	matlab_interface_error_invalid_parameter
};

rf_phreaker::scanner::blade_rf_controller controller;

std::string last_error_;

void check_buf_size(int buf_size, const std::string &str, const std::string &desc)
{
	if(buf_size < 0)
		throw matlab_interface_error("Invalid paramter.  " + desc + " buf size is negative.", matlab_interface_error_insufficient_buf_size);

	auto str_size = str.size() + 1;
	if((unsigned int)buf_size < str_size)
		throw matlab_interface_error(desc + " buffer size is insufficient.  Buf size needs to be at least " +
		boost::lexical_cast<std::string>(str_size)+" bytes.", matlab_interface_error_insufficient_buf_size);
}

void check_null(char *ptr)
{
	if(ptr == nullptr)
		throw matlab_interface_error("Invalid parameter.  char ptr is NULL.", matlab_interface_error_null_detected);
}

void check_null(int *ptr)
{
	if(ptr == nullptr)
		throw matlab_interface_error("Invalid parameter.  int ptr is NULL.", matlab_interface_error_null_detected);
}

void check_null(uint32_t *ptr)
{
	if(ptr == nullptr)
		throw matlab_interface_error("Invalid parameter.  uint32_t ptr is NULL.", matlab_interface_error_null_detected);
}

void check_null(uint16_t *ptr)
{
	if(ptr == nullptr)
		throw matlab_interface_error("Invalid parameter.  uint32_t ptr is NULL.", matlab_interface_error_null_detected);
}

void check_null(float *ptr)
{
	if(ptr == nullptr)
		throw matlab_interface_error("Invalid parameter.  float ptr is NULL.", matlab_interface_error_null_detected);
}


}}
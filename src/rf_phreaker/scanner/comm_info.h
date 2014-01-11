#pragma once

#include "rf_phreaker/scanner/scanner_types.h"

#include <string>
#include <memory>

namespace rf_phreaker { namespace scanner {

enum comm_type
{
	AUTO,
	USB_FTDI_DEVICE,
	FAKE_USB_FTDI_DEVICE,
	USB_BLADE_RF,
	FAKE_USB_BLADE_RF
};


class comm_info;
typedef ::std::shared_ptr<comm_info> comm_info_ptr;

class comm_info
{
public:
	comm_info(/*scanner_id_type id, const std::string &description, bool is_open*/)
		//: id_(id)
		//, description_(description)
		//, is_open_(is_open)
	{}

	virtual scanner_id_type id() const = 0;//{ return id_; } 

	virtual std::string description() const = 0; //{ return description_; }

	virtual bool is_open() const = 0; //{ return is_open_; }

	virtual comm_type type() const = 0;
//private:
//	scanner_id_type id_;
//	std::string description_;
//	bool is_open_;
//
};

}}
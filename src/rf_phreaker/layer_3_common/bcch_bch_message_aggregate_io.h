#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "rf_phreaker/layer_3_common/bcch_bch_message_aggregate.h"

namespace layer_3_information
{

static std::string main_delim = "\t";
static std::string begin_delim = "[";
static std::string end_delim = "]";
static std::string spacer = " | ";
static std::string spacer2 = " : ";
static std::string spacer3 = " ";

inline std::ostream& operator << (std::ostream &os, const bcch_bch_message_aggregate &t)
{
	os << t.mcc_ << main_delim
		<< t.mnc_ << main_delim
		<< t.lac_ << main_delim
		<< t.cid_;
	return os;
}

inline std::ostream& operator << (std::ostream &os, const plmn &t)
{
	os << t.mcc_ << spacer3 << t.mnc_;
	return os;
}

inline std::ostream& operator << (std::ostream &os, const multiple_plmn_type &t)
{
	for(auto i : t) {
		os << begin_delim << i << end_delim << spacer3;
	}
	return os;
}

}
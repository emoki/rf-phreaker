#pragma once

#include "rf_phreaker/common/common_types.h"

#define khz(x) (static_cast<rf_phreaker::frequency_type>(x)*1000)             /**< Convenience for kHz */
#define mhz(x) (static_cast<rf_phreaker::frequency_type>(x)*1000000)          /**< Convenience for MHz */
#define ghz(x) (static_cast<rf_phreaker::frequency_type>(x)*1000000000)       /**< Convenience for GHz */
#define milli_to_nano(x) (static_cast<rf_phreaker::time_type>(x)*1000000)       /**< Convenience for nano */


namespace rf_phreaker {

//template<frequency_type N>
//struct khz_ {
//	enum { v = N * 1000 };
//};
//
//template<frequency_type N>
//struct mhz {
//	enum { v = N * 1000000 };
//};
//
//template<frequency_type N>
//struct hz {
//	enum { v = N * 1000000000 };
//};
//
//template<time_type N>
//struct nano
//{
//	enum {v = N * 1000000000};
//};
//
//template<time_type N>
//struct micro
//{
//	enum { v = N * 1000000 };
//};
//
//template<time_type N>
//struct milli
//{
//	enum { v = N * 1000 };
//};


inline int16_t sign_extend_12_bits(int16_t &var)
{
	if(var & 0x0800) 
		var |= 0xF000;
	else
		var &= 0x0FFF;

	return var;
}

}
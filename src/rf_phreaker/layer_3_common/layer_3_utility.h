#pragma once
#include <string>
#include "rf_phreaker/common/exception_types.h"

namespace rf_phreaker {

inline int convert_gsm_si(const std::string &s) {
	if(s == "gsm_si_1")
		return 0;
	else if(s == "gsm_si_2")
		return 1;
	else if(s == "gsm_si_2bis")
		return 2;
	else if(s == "gsm_si_2ter")
		return 3;
	else if(s == "gsm_si_2quater")
		return 4;
	else if(s == "gsm_si_3")
		return 5;
	else if(s == "gsm_si_4")
		return 6;
	else if(s == "gsm_si_7")
		return 7;
	else if(s == "gsm_si_8")
		return 8;
	else if(s == "gsm_si_23")
		return 9;
	else
		throw rf_phreaker_error("Unknown gsm system information specifier.");
}

inline std::string convert_gsm_si(int s) {
	switch(s) {
	case 0:
		return "gsm_si_1";
	case 1:
		return "gsm_si_2";
	case 2:
		return "gsm_si_2bis";
	case 3:
		return "gsm_si_2ter";
	case 4:
		return "gsm_si_2quater";
	case 5:
		return "gsm_si_3";
	case 6:
		return "gsm_si_4";
	case 7:
		return "gsm_si_7";
	case 8:
		return "gsm_si_8";
	case 9:
		return "gsm_si_23";
	default:
		throw rf_phreaker_error("Unknown gsm system information specifier.");
	}
}

inline int convert_umts_sib(const std::string &s) {
	if(s == "umts_mib")
		return 0;
	else if(s == "umts_sib1")
		return 1;
	else if(s == "umts_sib3_4")
		return 2;
	else if(s == "umts_sib11_11bis")
		return 3;
	else
		throw rf_phreaker_error("Unknown umts system information block specifier.");
}

inline std::string convert_umts_sib(int s) {
	switch(s) {
	case 0:
		return "umts_mib";
	case 1:
		return "umts_sib1";
	case 2:
		return "umts_sib3_4";
	case 3:
		return "umts_sib11_11bis";
	default:
		throw rf_phreaker_error("Unknown umts system information block specifier.");
	}
}

inline int convert_lte_sib(const std::string &s) {
	if(s == "lte_sib_1")
		return 0;
	else if(s == "lte_sib_2")
		return 1;
	else if(s == "lte_sib_3")
		return 2;
	else if(s == "lte_sib_4")
		return 3;
	else if(s == "lte_sib_5")
		return 4;
	else if(s == "lte_sib_6")
		return 5;
	else if(s == "lte_sib_7")
		return 6;
	else if(s == "lte_sib_8")
		return 7;
	else if(s == "lte_sib_9")
		return 8;
	else if(s == "lte_sib_10")
		return 9;
	else if(s == "lte_sib_11")
		return 10;
	else if(s == "lte_sib_12_v920")
		return 11;
	else if(s == "lte_sib_13_v920")
		return 12;
	else if(s == "lte_sib_14_v1130")
		return 13;
	else if(s == "lte_sib_15_v1130")
		return 14;
	else if(s == "lte_sib_16_v1130")
		return 15;
	else
		throw rf_phreaker_error("Unknown lte system information block specifier.");
}

inline std::string convert_lte_sib(int s) {
	switch(s) {
	case 0:
		return "lte_sib_1";
	case 1:
		return "lte_sib_2";
	case 2:
		return "lte_sib_3";
	case 3:
		return "lte_sib_4";
	case 4:
		return "lte_sib_5";
	case 5:
		return "lte_sib_6";
	case 6:
		return "lte_sib_7";
	case 7:
		return "lte_sib_8";
	case 8:
		return "lte_sib_9";
	case 9:
		return "lte_sib_10";
	case 10:
		return "lte_sib_11";
	case 11:
		return "lte_sib_12_v920";
	case 12:
		return "lte_sib_13_v920";
	case 13:
		return "lte_sib_14_v1130";
	case 14:
		return "lte_sib_15_v1130";
	case 15:
		return "lte_sib_16_v1130";
	default:
		throw rf_phreaker_error("Unknown lte system information block specifier.");
	}
}

}
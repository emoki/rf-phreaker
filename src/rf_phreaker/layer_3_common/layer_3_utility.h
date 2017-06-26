#pragma once
#include <string>
#include "rf_phreaker/common/exception_types.h"
#include "rf_phreaker/layer_3_common/pdu_element_types.h"

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
	using namespace layer_3_information;
	if(s == "umts_bcch_bch")
		return umts_bcch_bch;
	else if(s == "umts_mib")
		return umts_mib;
	else if(s == "umts_sib1")
		return umts_sib1;
	else if(s == "umts_sib2")
		return umts_sib2;
	else if(s == "umts_sib3")
		return umts_sib3;
	else if(s == "umts_sib4")
		return umts_sib4;
	else if(s == "umts_sib5")
		return umts_sib5;
	else if(s == "umts_sib5bis")
		return umts_sib5bis;
	else if(s == "umts_sib6")
		return umts_sib6;
	else if(s == "umts_sib7")
		return umts_sib7;
	else if(s == "umts_sib11")
		return umts_sib11;
	else if(s == "umts_sib11_bis")
		return umts_sib11_bis;
	else if(s == "umts_sib12")
		return umts_sib12;
	else if(s == "umts_sib13")
		return umts_sib13;
	else if(s == "umts_sib13_1")
		return umts_sib13_1;
	else if(s == "umts_sib13_2")
		return umts_sib13_2;
	else if(s == "umts_sib13_3")
		return umts_sib13_3;
	else if(s == "umts_sib13_4")
		return umts_sib13_4;
	else if(s == "umts_sib14")
		return umts_sib14;
	else if(s == "umts_sib15")
		return umts_sib15;
	else if(s == "umts_sib15bis")
		return umts_sib15bis;
	else if(s == "umts_sib15_1")
		return umts_sib15_1;
	else if(s == "umts_sib15_1bis")
		return umts_sib15_1bis;
	else if(s == "umts_sib15_2")
		return umts_sib15_2;
	else if(s == "umts_sib15_2bis")
		return umts_sib15_2bis;
	else if(s == "umts_sib15_2ter")
		return umts_sib15_2ter;
	else if(s == "umts_sib15_3")
		return umts_sib15_3;
	else if(s == "umts_sib15_3bis")
		return umts_sib15_3bis;
	else if(s == "umts_sib15_4")
		return umts_sib15_4;
	else if(s == "umts_sib15_5")
		return umts_sib15_5;
	else if(s == "umts_sib15_6")
		return umts_sib15_6;
	else if(s == "umts_sib15_7")
		return umts_sib15_7;
	else if(s == "umts_sib15_8")
		return umts_sib15_8;
	else if(s == "umts_sib16")
		return umts_sib16;
	else if(s == "umts_sib17")
		return umts_sib17;
	else if(s == "umts_sib18")
		return umts_sib18;
	else if(s == "umts_sib19")
		return umts_sib19;
	else if(s == "umts_sib20")
		return umts_sib20;
	else if(s == "umts_scheduling_block1")
		return umts_scheduling_block1;
	else if(s == "umts_scheduling_block2")
		return umts_scheduling_block2;
	else
		throw rf_phreaker_error("Unknown umts system information block specifier.");
}

inline std::string convert_umts_sib(int s) {
	using namespace layer_3_information;
	switch(s) {
	case umts_bcch_bch:
		return "umts_bcch_bch";
	case umts_mib:
		return "umts_mib";
	case umts_sib1:
		return "umts_sib1";
	case umts_sib2:
		return "umts_sib2";
	case umts_sib3:
		return "umts_sib3";
	case umts_sib4:
		return "umts_sib4";
	case umts_sib5:
		return "umts_sib5";
	case umts_sib5bis:
		return "umts_sib5bis";
	case umts_sib6:
		return "umts_sib6";
	case umts_sib7:
		return "umts_sib7";
	case umts_sib11:
		return "umts_sib11";
	case umts_sib11_bis:
		return "umts_sib11_bis";
	case umts_sib12:
		return "umts_sib12";
	case umts_sib13:
		return "umts_sib13";
	case umts_sib13_1:
		return "umts_sib13_1";
	case umts_sib13_2:
		return "umts_sib13_2";
	case umts_sib13_3:
		return "umts_sib13_3";
	case umts_sib13_4:
		return "umts_sib13_4";
	case umts_sib14:
		return "umts_sib14";
	case umts_sib15:
		return "umts_sib15";
	case umts_sib15bis:
		return "umts_sib15bis";
	case umts_sib15_1:
		return "umts_sib15_1";
	case umts_sib15_1bis:
		return "umts_sib15_1bis";
	case umts_sib15_2:
		return "umts_sib15_2";
	case umts_sib15_2bis:
		return "umts_sib15_2bis";
	case umts_sib15_2ter:
		return "umts_sib15_2ter";
	case umts_sib15_3:
		return "umts_sib15_3";
	case umts_sib15_3bis:
		return "umts_sib15_3bis";
	case umts_sib15_4:
		return "umts_sib15_4";
	case umts_sib15_5:
		return "umts_sib15_5";
	case umts_sib15_6:
		return "umts_sib15_6";
	case umts_sib15_7:
		return "umts_sib15_7";
	case umts_sib15_8:
		return "umts_sib15_8";
	case umts_sib16:
		return "umts_sib16";
	case umts_sib17:
		return "umts_sib17";
	case umts_sib18:
		return "umts_sib18";
	case umts_sib19:
		return "umts_sib19";
	case umts_sib20:
		return "umts_sib20";
	case umts_scheduling_block1:
		return "umts_scheduling_block1";
	case umts_scheduling_block2:
		return "umts_scheduling_block2";
	default:
		throw rf_phreaker_error("Unknown umts system information block specifier.");
	}
}

inline int convert_lte_sib(const std::string &s) {
	// This matches up with lte_sib_type which is the same as the asn1 compiler enum.
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
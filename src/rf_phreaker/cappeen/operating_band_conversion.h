#pragma once

#include "rf_phreaker/cappeen/beagle_defines.h"
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/processing/collection_info_container.h"
#include "rf_phreaker/common/exception_types.h"

namespace rf_phreaker {	namespace cappeen_api {


static rf_phreaker::operating_band convert_band(beagle_api::TECHNOLOGIES_AND_BANDS band) {
	using namespace beagle_api;

	rf_phreaker::operating_band b;

	switch(band) {
	case WCDMA_BAND_850:
		b = rf_phreaker::UMTS_OPERATING_BAND_5;
		break;
	case WCDMA_BAND_900:
		b = rf_phreaker::UMTS_OPERATING_BAND_8;
		break;
	case WCDMA_BAND_1800:
		b = rf_phreaker::UMTS_OPERATING_BAND_3;
		break;
	case WCDMA_BAND_1900:
		b = rf_phreaker::UMTS_OPERATING_BAND_2;
		break;
	// Comply with beagle_api behavior.  The 2100 band is considered UMTS band 1 except for freqs xxxx.5 
	// which are only valid in UMTS band 4. 
	case WCDMA_BAND_2100:
		b = rf_phreaker::UMTS_OPERATING_BAND_1;
		break;
	case LTE_BAND_1:
		b = rf_phreaker::LTE_OPERATING_BAND_1;
		break;
	case LTE_BAND_2:
		b = rf_phreaker::LTE_OPERATING_BAND_2;
		break;
	case LTE_BAND_3:
		b = rf_phreaker::LTE_OPERATING_BAND_3;
		break;
	case LTE_BAND_4:
		b = rf_phreaker::LTE_OPERATING_BAND_4;
		break;
	case LTE_BAND_5:
		b = rf_phreaker::LTE_OPERATING_BAND_5;
		break;
	case LTE_BAND_6:
		b = rf_phreaker::LTE_OPERATING_BAND_6;
		break;
	case LTE_BAND_7:
		b = rf_phreaker::LTE_OPERATING_BAND_7;
		break;
	case LTE_BAND_8:
		b = rf_phreaker::LTE_OPERATING_BAND_8;
		break;
	case LTE_BAND_9:
		b = rf_phreaker::LTE_OPERATING_BAND_9;
		break;
	case LTE_BAND_10:
		b = rf_phreaker::LTE_OPERATING_BAND_10;
		break;
	case LTE_BAND_11:
		b = rf_phreaker::LTE_OPERATING_BAND_11;
		break;
	case LTE_BAND_12:
		b = rf_phreaker::LTE_OPERATING_BAND_12;
		break;
	case LTE_BAND_13:
		b = rf_phreaker::LTE_OPERATING_BAND_13;
		break;
	case LTE_BAND_14:
		b = rf_phreaker::LTE_OPERATING_BAND_14;
		break;
	case LTE_BAND_17:
		b = rf_phreaker::LTE_OPERATING_BAND_17;
		break;
	case LTE_BAND_18:
		b = rf_phreaker::LTE_OPERATING_BAND_18;
		break;
	case LTE_BAND_19:
		b = rf_phreaker::LTE_OPERATING_BAND_19;
		break;
	case LTE_BAND_20:
		b = rf_phreaker::LTE_OPERATING_BAND_20;
		break;
	case LTE_BAND_21:
		b = rf_phreaker::LTE_OPERATING_BAND_21;
		break;
	case LTE_BAND_22:
		b = rf_phreaker::LTE_OPERATING_BAND_22;
		break;
	case LTE_BAND_23:
		b = rf_phreaker::LTE_OPERATING_BAND_23;
		break;
	case LTE_BAND_24:
		b = rf_phreaker::LTE_OPERATING_BAND_24;
		break;
	case LTE_BAND_25:
		b = rf_phreaker::LTE_OPERATING_BAND_25;
		break;
	case LTE_BAND_26:
		b = rf_phreaker::LTE_OPERATING_BAND_26;
		break;
	case LTE_BAND_27:
		b = rf_phreaker::LTE_OPERATING_BAND_27;
		break;
	case LTE_BAND_28:
		b = rf_phreaker::LTE_OPERATING_BAND_28;
		break;
	case LTE_BAND_29:
		b = rf_phreaker::LTE_OPERATING_BAND_29;
		break;
	case LTE_BAND_30:
		b = rf_phreaker::LTE_OPERATING_BAND_30;
		break;
	case LTE_BAND_33:
		b = rf_phreaker::LTE_OPERATING_BAND_33;
		break;
	case LTE_BAND_34:
		b = rf_phreaker::LTE_OPERATING_BAND_34;
		break;
	case LTE_BAND_35:
		b = rf_phreaker::LTE_OPERATING_BAND_35;
		break;
	case LTE_BAND_36:
		b = rf_phreaker::LTE_OPERATING_BAND_36;
		break;
	case LTE_BAND_37:
		b = rf_phreaker::LTE_OPERATING_BAND_37;
		break;
	case LTE_BAND_38:
		b = rf_phreaker::LTE_OPERATING_BAND_38;
		break;
	case LTE_BAND_39:
		b = rf_phreaker::LTE_OPERATING_BAND_39;
		break;
	case LTE_BAND_40:
		b = rf_phreaker::LTE_OPERATING_BAND_40;
		break;
	case LTE_BAND_41:
		b = rf_phreaker::LTE_OPERATING_BAND_41;
		break;
	case LTE_BAND_42:
		b = rf_phreaker::LTE_OPERATING_BAND_42;
		break;
	case LTE_BAND_43:
		b = rf_phreaker::LTE_OPERATING_BAND_43;
		break;
	case LTE_BAND_44:
		b = rf_phreaker::LTE_OPERATING_BAND_44;
		break;
	default:
		throw rf_phreaker::cappeen_api_error("Unknown technology_and_band type.", GENERAL_ERROR);
	}
	return b;
}

static std::string tech_band_to_string(beagle_api::TECHNOLOGIES_AND_BANDS band) {
	using namespace beagle_api;
	
	std::string s;

	switch(band) {
	case WCDMA_BAND_850:
		s = "WCDMA_BAND_850";
		break;
	case WCDMA_BAND_900:
		s = "WCDMA_BAND_900";
		break;
	case WCDMA_BAND_1800:
		s = "WCDMA_BAND_1800";
		break;
	case WCDMA_BAND_1900:
		s = "WCDMA_BAND_1900";
		break;
		// Comply with beagle_api behavior.  The 2100 band is considered UMTS band 1 except for freqs xxxx.5 
		// which are only valid in UMTS band 4. 
	case WCDMA_BAND_2100:
		s = "WCDMA_BAND_2100";
		break;
	case LTE_BAND_1:
		s = "LTE_BAND_1";
		break;
	case LTE_BAND_2:
		s = "LTE_BAND_2";
		break;
	case LTE_BAND_3:
		s = "LTE_BAND_3";
		break;
	case LTE_BAND_4:
		s = "LTE_BAND_4";
		break;
	case LTE_BAND_5:
		s = "LTE_BAND_5";
		break;
	case LTE_BAND_6:
		s = "LTE_BAND_6";
		break;
	case LTE_BAND_7:
		s = "LTE_BAND_7";
		break;
	case LTE_BAND_8:
		s = "LTE_BAND_8";
		break;
	case LTE_BAND_9:
		s = "LTE_BAND_9";
		break;
	case LTE_BAND_10:
		s = "LTE_BAND_10";
		break;
	case LTE_BAND_11:
		s = "LTE_BAND_11";
		break;
	case LTE_BAND_12:
		s = "LTE_BAND_12";
		break;
	case LTE_BAND_13:
		s = "LTE_BAND_13";
		break;
	case LTE_BAND_14:
		s = "LTE_BAND_14";
		break;
	case LTE_BAND_17:
		s = "LTE_BAND_17";
		break;
	case LTE_BAND_18:
		s = "LTE_BAND_18";
		break;
	case LTE_BAND_19:
		s = "LTE_BAND_19";
		break;
	case LTE_BAND_20:
		s = "LTE_BAND_20";
		break;
	case LTE_BAND_21:
		s = "LTE_BAND_21";
		break;
	case LTE_BAND_22:
		s = "LTE_BAND_22";
		break;
	case LTE_BAND_23:
		s = "LTE_BAND_23";
		break;
	case LTE_BAND_24:
		s = "LTE_BAND_24";
		break;
	case LTE_BAND_25:
		s = "LTE_BAND_25";
		break;
	case LTE_BAND_26:
		s = "LTE_BAND_26";
		break;
	case LTE_BAND_27:
		s = "LTE_BAND_27";
		break;
	case LTE_BAND_28:
		s = "LTE_BAND_28";
		break;
	case LTE_BAND_29:
		s = "LTE_BAND_29";
		break;
	case LTE_BAND_30:
		s = "LTE_BAND_30";
		break;
	case LTE_BAND_33:
		s = "LTE_BAND_33";
		break;
	case LTE_BAND_34:
		s = "LTE_BAND_34";
		break;
	case LTE_BAND_35:
		s = "LTE_BAND_35";
		break;
	case LTE_BAND_36:
		s = "LTE_BAND_36";
		break;
	case LTE_BAND_37:
		s = "LTE_BAND_37";
		break;
	case LTE_BAND_38:
		s = "LTE_BAND_38";
		break;
	case LTE_BAND_39:
		s = "LTE_BAND_39";
		break;
	case LTE_BAND_40:
		s = "LTE_BAND_40";
		break;
	case LTE_BAND_41:
		s = "LTE_BAND_41";
		break;
	case LTE_BAND_42:
		s = "LTE_BAND_42";
		break;
	case LTE_BAND_43:
		s = "LTE_BAND_43";
		break;
	case LTE_BAND_44:
		s = "LTE_BAND_44";
		break;
	default:
		throw rf_phreaker::cappeen_api_error("Unknown technology_and_band type.", GENERAL_ERROR);
	}
	return s;
}

static beagle_api::TECHNOLOGIES_AND_BANDS convert_band_to_tech_band(rf_phreaker::operating_band band) {
	using namespace beagle_api;

	beagle_api::TECHNOLOGIES_AND_BANDS b;

	switch(band) {
	case rf_phreaker::UMTS_OPERATING_BAND_5:
		b = WCDMA_BAND_850;
		break;
	case rf_phreaker::UMTS_OPERATING_BAND_8:
		b = WCDMA_BAND_900;
		break;
	case rf_phreaker::UMTS_OPERATING_BAND_3:
		b = WCDMA_BAND_1800;
		break;
	case rf_phreaker::UMTS_OPERATING_BAND_2:
		b = WCDMA_BAND_1900;
		break;
	case rf_phreaker::UMTS_OPERATING_BAND_1:
	case rf_phreaker::UMTS_OPERATING_BAND_4:
		b = WCDMA_BAND_2100;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_1:
		b = LTE_BAND_1;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_2:
		b = LTE_BAND_2;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_3:
		b = LTE_BAND_3;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_4:
		b = LTE_BAND_4;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_5:
		b = LTE_BAND_5;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_6:
		b = LTE_BAND_6;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_7:
		b = LTE_BAND_7;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_8:
		b = LTE_BAND_8;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_9:
		b = LTE_BAND_9;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_10:
		b = LTE_BAND_10;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_11:
		b = LTE_BAND_11;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_12:
		b = LTE_BAND_12;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_13:
		b = LTE_BAND_13;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_14:
		b = LTE_BAND_14;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_17:
		b = LTE_BAND_17;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_18:
		b = LTE_BAND_18;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_19:
		b = LTE_BAND_19;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_20:
		b = LTE_BAND_20;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_21:
		b = LTE_BAND_21;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_22:
		b = LTE_BAND_22;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_23:
		b = LTE_BAND_23;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_24:
		b = LTE_BAND_24;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_25:
		b = LTE_BAND_25;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_26:
		b = LTE_BAND_26;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_27:
		b = LTE_BAND_27;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_28:
		b = LTE_BAND_28;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_29:
		b = LTE_BAND_29;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_30:
		b = LTE_BAND_30;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_33:
		b = LTE_BAND_33;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_34:
		b = LTE_BAND_34;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_35:
		b = LTE_BAND_35;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_36:
		b = LTE_BAND_36;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_37:
		b = LTE_BAND_37;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_38:
		b = LTE_BAND_38;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_39:
		b = LTE_BAND_39;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_40:
		b = LTE_BAND_40;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_41:
		b = LTE_BAND_41;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_42:
		b = LTE_BAND_42;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_43:
		b = LTE_BAND_43;
		break;
	case rf_phreaker::LTE_OPERATING_BAND_44:
		b = LTE_BAND_44;
		break;
	default:
		throw rf_phreaker::cappeen_api_error("Unknown technology_and_band type.", GENERAL_ERROR);
	}
	return b;
}

static beagle_api::BANDS convert_band_to_hw_band(rf_phreaker::operating_band band) {
	using namespace beagle_api;

	beagle_api::BANDS b;

	switch(band) {
	case rf_phreaker::UMTS_OPERATING_BAND_5:
		b = BAND_850;
		break;
	case rf_phreaker::UMTS_OPERATING_BAND_8:
		b = BAND_900;
		break;
	case rf_phreaker::UMTS_OPERATING_BAND_3:
		b = BAND_1800;
		break;
	case rf_phreaker::UMTS_OPERATING_BAND_2:
		b = BAND_1900;
		break;
	case rf_phreaker::UMTS_OPERATING_BAND_1:
	case rf_phreaker::UMTS_OPERATING_BAND_4:
		b = BAND_2100;
		break;
		//case LTE_BAND_1:
		//	b = rf_phreaker::LTE_OPERATING_BAND_1;
		//	break;
		//case LTE_BAND_2:
		//	b = rf_phreaker::LTE_OPERATING_BAND_2;
		//	break;
		//case LTE_BAND_3:
		//	b = rf_phreaker::LTE_OPERATING_BAND_3;
		//	break;
		//case LTE_BAND_4:
		//	b = rf_phreaker::LTE_OPERATING_BAND_4;
		//	break;
		//case LTE_BAND_5:
		//	b = rf_phreaker::LTE_OPERATING_BAND_5;
		//	break;
		//case LTE_BAND_6:
		//	b = rf_phreaker::LTE_OPERATING_BAND_6;
		//	break;
		//case LTE_BAND_7:
		//	b = rf_phreaker::LTE_OPERATING_BAND_7;
		//	break;
		//case LTE_BAND_8:
		//	b = rf_phreaker::LTE_OPERATING_BAND_8;
		//	break;
		//case LTE_BAND_9:
		//	b = rf_phreaker::LTE_OPERATING_BAND_9;
		//	break;
		//case LTE_BAND_10:
		//	b = rf_phreaker::LTE_OPERATING_BAND_10;
		//	break;
		//case LTE_BAND_11:
		//	b = rf_phreaker::LTE_OPERATING_BAND_11;
		//	break;
		//case LTE_BAND_12:
		//	b = rf_phreaker::LTE_OPERATING_BAND_12;
		//	break;
		//case LTE_BAND_13:
		//	b = rf_phreaker::LTE_OPERATING_BAND_13;
		//	break;
		//case LTE_BAND_14:
		//	b = rf_phreaker::LTE_OPERATING_BAND_14;
		//	break;
		//case LTE_BAND_17:
		//	b = rf_phreaker::LTE_OPERATING_BAND_17;
		//	break;
		//case LTE_BAND_18:
		//	b = rf_phreaker::LTE_OPERATING_BAND_18;
		//	break;
		//case LTE_BAND_19:
		//	b = rf_phreaker::LTE_OPERATING_BAND_19;
		//	break;
		//case LTE_BAND_20:
		//	b = rf_phreaker::LTE_OPERATING_BAND_20;
		//	break;
		//case LTE_BAND_21:
		//	b = rf_phreaker::LTE_OPERATING_BAND_21;
		//	break;
		//case LTE_BAND_22:
		//	b = rf_phreaker::LTE_OPERATING_BAND_22;
		//	break;
		//case LTE_BAND_23:
		//	b = rf_phreaker::LTE_OPERATING_BAND_23;
		//	break;
		//case LTE_BAND_24:
		//	b = rf_phreaker::LTE_OPERATING_BAND_24;
		//	break;
		//case LTE_BAND_25:
		//	b = rf_phreaker::LTE_OPERATING_BAND_25;
		//	break;
		//case LTE_BAND_26:
		//	b = rf_phreaker::LTE_OPERATING_BAND_26;
		//	break;
		//case LTE_BAND_27:
		//	b = rf_phreaker::LTE_OPERATING_BAND_27;
		//	break;
		//case LTE_BAND_28:
		//	b = rf_phreaker::LTE_OPERATING_BAND_28;
		//	break;
		//case LTE_BAND_29:
		//	b = rf_phreaker::LTE_OPERATING_BAND_29;
		//	break;
		//case LTE_BAND_30:
		//	b = rf_phreaker::LTE_OPERATING_BAND_30;
		//	break;
		//case LTE_BAND_33:
		//	b = rf_phreaker::LTE_OPERATING_BAND_33;
		//	break;
		//case LTE_BAND_34:
		//	b = rf_phreaker::LTE_OPERATING_BAND_34;
		//	break;
		//case LTE_BAND_35:
		//	b = rf_phreaker::LTE_OPERATING_BAND_35;
		//	break;
		//case LTE_BAND_36:
		//	b = rf_phreaker::LTE_OPERATING_BAND_36;
		//	break;
		//case LTE_BAND_37:
		//	b = rf_phreaker::LTE_OPERATING_BAND_37;
		//	break;
		//case LTE_BAND_38:
		//	b = rf_phreaker::LTE_OPERATING_BAND_38;
		//	break;
		//case LTE_BAND_39:
		//	b = rf_phreaker::LTE_OPERATING_BAND_39;
		//	break;
		//case LTE_BAND_40:
		//	b = rf_phreaker::LTE_OPERATING_BAND_40;
		//	break;
		//case LTE_BAND_41:
		//	b = rf_phreaker::LTE_OPERATING_BAND_41;
		//	break;
		//case LTE_BAND_42:
		//	b = rf_phreaker::LTE_OPERATING_BAND_42;
		//	break;
		//case LTE_BAND_43:
		//	b = rf_phreaker::LTE_OPERATING_BAND_43;
		//	break;
		//case LTE_BAND_44:
		//	b = rf_phreaker::LTE_OPERATING_BAND_44;
		//	break;
	default:
		throw rf_phreaker::cappeen_api_error("Unknown technology_and_band type.", GENERAL_ERROR);
	}
	return b;
}

static std::string hw_band_to_string(beagle_api::BANDS band) {
	using namespace beagle_api;

	std::string s;

	switch(band) {
	case BAND_700:
		s = "BAND_700";
		break;
	case BAND_850:
		s = "BAND_850";
		break;
	case BAND_900:
		s = "BAND_900";
		break;
	case BAND_1700:
		s = "BAND_1700";
		break;
	case BAND_1800:
		s = "BAND_1800";
		break;
	case BAND_1900:
		s = "BAND_1900";
		break;
	case BAND_2100:
		s = "BAND_2100";
		break;
	case BAND_2300:
		s = "BAND_2300";
		break;
	case BAND_2600:
		s = "BAND_2600";
		break;
	default:
		throw rf_phreaker::cappeen_api_error("Unknown band type.", GENERAL_ERROR);
	}
	return s;
}

}}

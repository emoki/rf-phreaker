#include "rf_phreaker/cappeen_api/beagle_defines.h"
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/processing/collection_info_container.h"
#include "rf_phreaker/common/exception_types.h"

namespace rf_phreaker {	namespace cappeen_api {


rf_phreaker::operating_band convert_band(beagle_api::technologies_and_band_group band)
{
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
	case WCDMA_BAND_2100:
		b = rf_phreaker::UMTS_OPERATING_BAND_4;
		break;
	case WCDMA_BAND_850:
		b = rf_phreaker::UMTS_OPERATING_BAND_5;
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
		throw rf_phreaker::cappeen_api_error("Unknown technology_and_band type.");
	}
	return b;
}


}}

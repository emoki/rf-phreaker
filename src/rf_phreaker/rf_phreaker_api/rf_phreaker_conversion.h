#pragma once

#include "rf_phreaker\rf_phreaker_api\rf_phreaker_api.h"
#include "rf_phreaker\common\exception_types.h"
#include "rf_phreaker\common\measurements.h"

namespace rf_phreaker { namespace api { 

inline rp_status to_rp_status(const rf_phreaker_error &err) {
	switch(err.error_type_) {
	case no_error_type:
		return RP_STATUS_OK;
	case generic_error_type:
		return RP_STATUS_GENERIC_ERROR;
	case comm_error_type: 
		return RP_STATUS_COMMUNICATION_ERROR;
	case scanner_init_error_type:
		return RP_STATUS_SCANNER_INIT_ERROR;
	case hardware_info_error_type:
		return RP_STATUS_HARDWARE_INFO_ERROR;
	case misc_error_type:
		return RP_STATUS_MISC_ERROR;
	case file_io_error_type:
		return RP_STATUS_FILE_IO_ERROR;
	case blade_rf_error_type:
		return RP_STATUS_BLADE_RF_ERROR;
	case ipp_error_type:
		return RP_STATUS_IPP_ERROR;
	case filter_error_type:
		return RP_STATUS_FILTER_ERROR;
	case gsm_analysis_error_type:
		return RP_STATUS_GSM_ANALYSIS_ERROR;
	case umts_analysis_error_type:
		return RP_STATUS_UMTS_ANALYSIS_ERROR;
	case lte_analysis_error_type:
		return RP_STATUS_LTE_ANALYSIS_ERROR;
	case processing_error_type:
		return RP_STATUS_PROCESSING_ERROR;
	case gps_comm_error_type:
		return RP_STATUS_GPS_COMMUNICATION_ERROR;
	case rf_phreaker_api_error_type:
		return RP_STATUS_RF_PHREAKER_API_ERROR;
	default:
		return RP_STATUS_UNKNOWN_ERROR;
	}
}

inline rf_phreaker::specifier to_sweep_specifier(rp_technology tech) {
	switch(tech) {
	case GSM:
		return GSM_SWEEP;
    case WCDMA:
		return UMTS_SWEEP;
	case LTE:
		return LTE_SWEEP;
	case CDMA:
		return CDMA_SWEEP;
	case RAW_DATA:
        return RAW_DATA;
	default:
		throw rf_phreaker_api_error("sweep specifier not supported.");
	}
}

inline rf_phreaker::specifier to_layer_3_specifier(rp_technology tech) {
	switch(tech) {
	case GSM:
		return GSM_LAYER_3_DECODE;
    case WCDMA:
		return UMTS_LAYER_3_DECODE;
	case LTE:
		return LTE_LAYER_3_DECODE;
	case CDMA:
		return CDMA_LAYER_3_DECODE;
	case RAW_DATA:
        return RAW_DATA;
	default:
		throw rf_phreaker_api_error("sweep specifier not supported.");
	}
}

inline rp_device_communication to_api_device_communication(device_communication t) {
	switch(t) {
	case USB_HI_SPEED:
		return rp_device_communication::USB_HI_SPEED;
	case USB_SUPER_SPEED:
		return rp_device_communication::USB_SUPER_SPEED;
	case UNKNOWN_SPEED:
	default:
		return rp_device_communication::UNKNOWN_DEVICE_COMMUNICATION;
	}
}

inline rp_operating_band to_api_operating_band(rf_phreaker::operating_band t) {
	switch(t) {
	case GSM_T_380: //	380	380.2–389.8	390.2–399.8	dynamic
		return rp_operating_band::GSM_T_380;
	case GSM_T_410:
		return rp_operating_band::GSM_T_410; //	410	410.2–419.8	420.2–429.8	dynamic
	case GSM_450:
		return rp_operating_band::GSM_450; //	450	450.6–457.6	460.6–467.6	259–293
	case GSM_480:
		return rp_operating_band::GSM_480; //	480	479.0–486.0	489.0–496.0	306–340
	case GSM_710:
		return rp_operating_band::GSM_710; //	710	698.2–716.2	728.2–746.2	dynamic
	case GSM_750:
		return rp_operating_band::GSM_750; //	750	747.2–762.2	777.2–792.2	438–511
	case GSM_T_810:
		return rp_operating_band::GSM_T_810; //	810	806.2–821.2	851.2–866.2	dynamic
	case GSM_850:
		return rp_operating_band::GSM_850; //	850	824.2–849.2	869.2–894.2	128–251
	case GSM_P_900:
		return rp_operating_band::GSM_P_900; //	900	890.0–915.0	935.0–960.0	1–124
	case GSM_E_900:
		return rp_operating_band::GSM_E_900; //	900	880.0–915.0	925.0–960.0	975–1023, 0-124
	case GSM_R_900:
		return rp_operating_band::GSM_R_900; //	900	876.0–915.0	921.0–960.0	955–1023, 0-124
	case GSM_T_900:
		return rp_operating_band::GSM_T_900; //	900	870.4–876.0	915.4–921.0	dynamic^
	case GSM_DCS_1800:
		return rp_operating_band::GSM_DCS_1800; //	1800 1,710.2–1,784.8	1,805.2–1,879.8	512–885	
	case GSM_PCS_1900:
		return rp_operating_band::GSM_PCS_1900; //	1900 1,850.2–1,909.8	1,930.2–1,989.8	512–810	

	case UMTS_OPERATING_BAND_1:
		return rp_operating_band::UMTS_OPERATING_BAND_1;	//  2100	IMT	1920 - 1980	2110 – 2170
	case UMTS_OPERATING_BAND_2:
		return rp_operating_band::UMTS_OPERATING_BAND_2;	//  1900	PCS A-F	1850 – 1910	1930 – 1990
	case UMTS_OPERATING_BAND_3:
		return rp_operating_band::UMTS_OPERATING_BAND_3;	//	1800	DCS	1710 – 1785	1805 – 1880
	case UMTS_OPERATING_BAND_4:
		return rp_operating_band::UMTS_OPERATING_BAND_4;	//	1700	AWS A-F	1710 – 1755	2110 – 2155			
	case UMTS_OPERATING_BAND_5:
		return rp_operating_band::UMTS_OPERATING_BAND_5;	//	850	CLR	824 – 849	869 – 894				
	case UMTS_OPERATING_BAND_6:
		return rp_operating_band::UMTS_OPERATING_BAND_6;	//	800		830 – 840	875 – 885				
	case UMTS_OPERATING_BAND_7:
		return rp_operating_band::UMTS_OPERATING_BAND_7;	//	2600	IMT-E	2500 – 2570	2620 – 2690
	case UMTS_OPERATING_BAND_8:
		return rp_operating_band::UMTS_OPERATING_BAND_8;	//	900	E-GSM	880 – 915	925 – 960
	case UMTS_OPERATING_BAND_9:
		return rp_operating_band::UMTS_OPERATING_BAND_9;	//	1700		1749.9 – 1784.9	1844.9 – 1879.9
	case UMTS_OPERATING_BAND_10:
		return rp_operating_band::UMTS_OPERATING_BAND_10;	//	1700	EAWS A-G	1710 – 1770	2110 – 2170
	case UMTS_OPERATING_BAND_11:
		return rp_operating_band::UMTS_OPERATING_BAND_11;	//	1500	LPDC	1427.9 – 1447.9	1475.9 – 1495.9
	case UMTS_OPERATING_BAND_12:
		return rp_operating_band::UMTS_OPERATING_BAND_12;	//	700	LSMH A/B/C	699 – 716	729 – 746
	case UMTS_OPERATING_BAND_13:
		return rp_operating_band::UMTS_OPERATING_BAND_13;	//	700	USMH C	777 – 787	746 – 756
	case UMTS_OPERATING_BAND_14:
		return rp_operating_band::UMTS_OPERATING_BAND_14;	//	700	USMH D	788 – 798	758 – 768
	case UMTS_OPERATING_BAND_19:
		return rp_operating_band::UMTS_OPERATING_BAND_19;	//	800		832.4 – 842.6	877.4 – 887.6
	case UMTS_OPERATING_BAND_20:
		return rp_operating_band::UMTS_OPERATING_BAND_20;	//	800	EUDD	832 – 862	791 – 821
	case UMTS_OPERATING_BAND_21:
		return rp_operating_band::UMTS_OPERATING_BAND_21;	//	1500	UPDC	1447.9 – 1462.9	1495.9 – 1510.9
	case UMTS_OPERATING_BAND_22:
		return rp_operating_band::UMTS_OPERATING_BAND_22;	//	3500		3410 – 3490	3510 – 3590
	case UMTS_OPERATING_BAND_25:
		return rp_operating_band::UMTS_OPERATING_BAND_25;	//	1900	EPCS A-G	1850 – 1915	1930 – 1995
	case UMTS_OPERATING_BAND_26:
		return rp_operating_band::UMTS_OPERATING_BAND_26;	//	850	ECLR	814 – 849	859 – 894

	case LTE_OPERATING_BAND_1:
		return rp_operating_band::LTE_OPERATING_BAND_1;	//	1920 - 1980	2110 - 2170	FDD
	case LTE_OPERATING_BAND_2:
		return rp_operating_band::LTE_OPERATING_BAND_2;	//	1850 - 1910	1930 - 1990	FDD
	case LTE_OPERATING_BAND_3:
		return rp_operating_band::LTE_OPERATING_BAND_3;	//	1710 - 1785	1805 - 1880	FDD
	case LTE_OPERATING_BAND_4:
		return rp_operating_band::LTE_OPERATING_BAND_4;	//	1710 - 1755	2110 - 2155	FDD
	case LTE_OPERATING_BAND_5:
		return rp_operating_band::LTE_OPERATING_BAND_5;	//	824 - 849	869 - 894	FDD
	case LTE_OPERATING_BAND_6:
		return rp_operating_band::LTE_OPERATING_BAND_6;	//	830 - 840	875 - 885	FDD			
	case LTE_OPERATING_BAND_7:
		return rp_operating_band::LTE_OPERATING_BAND_7;	//	2500 - 2570	2620 - 2690	FDD
	case LTE_OPERATING_BAND_8:
		return rp_operating_band::LTE_OPERATING_BAND_8;	//	880 - 915	925 - 960	FDD
	case LTE_OPERATING_BAND_9:
		return rp_operating_band::LTE_OPERATING_BAND_9;	//	1749.9 - 1784.9	1844.9 - 1879.9	FDD
	case LTE_OPERATING_BAND_10:
		return rp_operating_band::LTE_OPERATING_BAND_10;	//	1710 - 1770	2110 - 2170	FDD			
	case LTE_OPERATING_BAND_11:
		return rp_operating_band::LTE_OPERATING_BAND_11;	//	1427.9 - 1447.9	1475.9 - 1495.9	FDD
	case LTE_OPERATING_BAND_12:
		return rp_operating_band::LTE_OPERATING_BAND_12;	//	699 - 716	729 - 746	FDD
	case LTE_OPERATING_BAND_13:
		return rp_operating_band::LTE_OPERATING_BAND_13;	//	777 - 787	746 - 756	FDD
	case LTE_OPERATING_BAND_14:
		return rp_operating_band::LTE_OPERATING_BAND_14;	//	788 - 798	758 - 768	FDD
	case LTE_OPERATING_BAND_17:
		return rp_operating_band::LTE_OPERATING_BAND_17;	//	704 - 716	734 - 746	FDD			
	case LTE_OPERATING_BAND_18:
		return rp_operating_band::LTE_OPERATING_BAND_18;	//	815 - 830	860 - 875	FDD
	case LTE_OPERATING_BAND_19:
		return rp_operating_band::LTE_OPERATING_BAND_19;	//	830 - 845	875 - 890	FDD			
	case LTE_OPERATING_BAND_20:
		return rp_operating_band::LTE_OPERATING_BAND_20;	//	832 - 862	791 - 821	FDD
	case LTE_OPERATING_BAND_21:
		return rp_operating_band::LTE_OPERATING_BAND_21;	//	1447.9 - 1462.9	1495.9 - 1510.9	FDD
	case LTE_OPERATING_BAND_22:
		return rp_operating_band::LTE_OPERATING_BAND_22;	//	3410 - 3490	3510 - 3590	FDD
	case LTE_OPERATING_BAND_23:
		return rp_operating_band::LTE_OPERATING_BAND_23;	//	2000 - 2020	2180 - 2200	FDD			
	case LTE_OPERATING_BAND_24:
		return rp_operating_band::LTE_OPERATING_BAND_24;	//	1626.5 - 1660.5	1525 - 1559	FDD
	case LTE_OPERATING_BAND_25:
		return rp_operating_band::LTE_OPERATING_BAND_25;	//	1850 - 1915	1930 - 1995	FDD			
	case LTE_OPERATING_BAND_26:
		return rp_operating_band::LTE_OPERATING_BAND_26;	//	814 - 849	859 - 894	FDD			
	case LTE_OPERATING_BAND_27:
		return rp_operating_band::LTE_OPERATING_BAND_27;	//	807 - 824	852 - 869	FDD
	case LTE_OPERATING_BAND_28:
		return rp_operating_band::LTE_OPERATING_BAND_28;	//	703 - 748	758 - 803	FDD
	case LTE_OPERATING_BAND_29:
		return rp_operating_band::LTE_OPERATING_BAND_29;	//	N/A	716 - 728	FDD	
	case LTE_OPERATING_BAND_30:
		return rp_operating_band::LTE_OPERATING_BAND_30;	//	2305 - 2315	 2350 - 2360 FDD
	case LTE_OPERATING_BAND_33:
		return rp_operating_band::LTE_OPERATING_BAND_33;	//	1900 - 1920		TDD
	case LTE_OPERATING_BAND_34:
		return rp_operating_band::LTE_OPERATING_BAND_34;	//	2010 - 2025		TDD
	case LTE_OPERATING_BAND_35:
		return rp_operating_band::LTE_OPERATING_BAND_35;	//	1850 - 1910		TDD
	case LTE_OPERATING_BAND_36:
		return rp_operating_band::LTE_OPERATING_BAND_36;	//	1930 - 1990		TDD
	case LTE_OPERATING_BAND_37:
		return rp_operating_band::LTE_OPERATING_BAND_37;	//	1910 - 1930		TDD
	case LTE_OPERATING_BAND_38:
		return rp_operating_band::LTE_OPERATING_BAND_38;	//	2570 - 2620		TDD
	case LTE_OPERATING_BAND_39:
		return rp_operating_band::LTE_OPERATING_BAND_39;	//	1880 - 1920		TDD
	case LTE_OPERATING_BAND_40:
		return rp_operating_band::LTE_OPERATING_BAND_40;	//	2300 - 2400		TDD
	case LTE_OPERATING_BAND_41:
		return rp_operating_band::LTE_OPERATING_BAND_41;	//	2496 - 2690		TDD
	case LTE_OPERATING_BAND_42:
		return rp_operating_band::LTE_OPERATING_BAND_42;	//	3400 - 3600		TDD
	case LTE_OPERATING_BAND_43:
		return rp_operating_band::LTE_OPERATING_BAND_43;	//	3600 - 3800		TDD
	case LTE_OPERATING_BAND_44:
		return rp_operating_band::LTE_OPERATING_BAND_44;	//	703 - 803		TDD

	case OPERATING_BAND_UNKNOWN:
	default:
		return rp_operating_band::OPERATING_BAND_UNKNOWN;
	}
}

inline rf_phreaker::operating_band to_operating_band(rp_operating_band t) {
	switch(t) {
	case rp_operating_band::GSM_T_380: //	380	380.2–389.8	390.2–399.8	dynamic
		return operating_band::GSM_T_380;
	case rp_operating_band::GSM_T_410:
		return operating_band::GSM_T_410; //	410	410.2–419.8	420.2–429.8	dynamic
	case rp_operating_band::GSM_450:
		return operating_band::GSM_450; //	450	450.6–457.6	460.6–467.6	259–293
	case rp_operating_band::GSM_480:
		return operating_band::GSM_480; //	480	479.0–486.0	489.0–496.0	306–340
	case rp_operating_band::GSM_710:
		return operating_band::GSM_710; //	710	698.2–716.2	728.2–746.2	dynamic
	case rp_operating_band::GSM_750:
		return operating_band::GSM_750; //	750	747.2–762.2	777.2–792.2	438–511
	case rp_operating_band::GSM_T_810:
		return operating_band::GSM_T_810; //	810	806.2–821.2	851.2–866.2	dynamic
	case rp_operating_band::GSM_850:
		return operating_band::GSM_850; //	850	824.2–849.2	869.2–894.2	128–251
	case rp_operating_band::GSM_P_900:
		return operating_band::GSM_P_900; //	900	890.0–915.0	935.0–960.0	1–124
	case rp_operating_band::GSM_E_900:
		return operating_band::GSM_E_900; //	900	880.0–915.0	925.0–960.0	975–1023, 0-124
	case rp_operating_band::GSM_R_900:
		return operating_band::GSM_R_900; //	900	876.0–915.0	921.0–960.0	955–1023, 0-124
	case rp_operating_band::GSM_T_900:
		return operating_band::GSM_T_900; //	900	870.4–876.0	915.4–921.0	dynamic^
	case rp_operating_band::GSM_DCS_1800:
		return operating_band::GSM_DCS_1800; //	1800 1,710.2–1,784.8	1,805.2–1,879.8	512–885	
	case rp_operating_band::GSM_PCS_1900:
		return operating_band::GSM_PCS_1900; //	1900 1,850.2–1,909.8	1,930.2–1,989.8	512–810	

	case rp_operating_band::UMTS_OPERATING_BAND_1:
		return operating_band::UMTS_OPERATING_BAND_1;	//  2100	IMT	1920 - 1980	2110 – 2170
	case rp_operating_band::UMTS_OPERATING_BAND_2:
		return operating_band::UMTS_OPERATING_BAND_2;	//  1900	PCS A-F	1850 – 1910	1930 – 1990
	case rp_operating_band::UMTS_OPERATING_BAND_3:
		return operating_band::UMTS_OPERATING_BAND_3;	//	1800	DCS	1710 – 1785	1805 – 1880
	case rp_operating_band::UMTS_OPERATING_BAND_4:
		return operating_band::UMTS_OPERATING_BAND_4;	//	1700	AWS A-F	1710 – 1755	2110 – 2155			
	case rp_operating_band::UMTS_OPERATING_BAND_5:
		return operating_band::UMTS_OPERATING_BAND_5;	//	850	CLR	824 – 849	869 – 894				
	case rp_operating_band::UMTS_OPERATING_BAND_6:
		return operating_band::UMTS_OPERATING_BAND_6;	//	800		830 – 840	875 – 885				
	case rp_operating_band::UMTS_OPERATING_BAND_7:
		return operating_band::UMTS_OPERATING_BAND_7;	//	2600	IMT-E	2500 – 2570	2620 – 2690
	case rp_operating_band::UMTS_OPERATING_BAND_8:
		return operating_band::UMTS_OPERATING_BAND_8;	//	900	E-GSM	880 – 915	925 – 960
	case rp_operating_band::UMTS_OPERATING_BAND_9:
		return operating_band::UMTS_OPERATING_BAND_9;	//	1700		1749.9 – 1784.9	1844.9 – 1879.9
	case rp_operating_band::UMTS_OPERATING_BAND_10:
		return operating_band::UMTS_OPERATING_BAND_10;	//	1700	EAWS A-G	1710 – 1770	2110 – 2170
	case rp_operating_band::UMTS_OPERATING_BAND_11:
		return operating_band::UMTS_OPERATING_BAND_11;	//	1500	LPDC	1427.9 – 1447.9	1475.9 – 1495.9
	case rp_operating_band::UMTS_OPERATING_BAND_12:
		return operating_band::UMTS_OPERATING_BAND_12;	//	700	LSMH A/B/C	699 – 716	729 – 746
	case rp_operating_band::UMTS_OPERATING_BAND_13:
		return operating_band::UMTS_OPERATING_BAND_13;	//	700	USMH C	777 – 787	746 – 756
	case rp_operating_band::UMTS_OPERATING_BAND_14:
		return operating_band::UMTS_OPERATING_BAND_14;	//	700	USMH D	788 – 798	758 – 768
	case rp_operating_band::UMTS_OPERATING_BAND_19:
		return operating_band::UMTS_OPERATING_BAND_19;	//	800		832.4 – 842.6	877.4 – 887.6
	case rp_operating_band::UMTS_OPERATING_BAND_20:
		return operating_band::UMTS_OPERATING_BAND_20;	//	800	EUDD	832 – 862	791 – 821
	case rp_operating_band::UMTS_OPERATING_BAND_21:
		return operating_band::UMTS_OPERATING_BAND_21;	//	1500	UPDC	1447.9 – 1462.9	1495.9 – 1510.9
	case rp_operating_band::UMTS_OPERATING_BAND_22:
		return operating_band::UMTS_OPERATING_BAND_22;	//	3500		3410 – 3490	3510 – 3590
	case rp_operating_band::UMTS_OPERATING_BAND_25:
		return operating_band::UMTS_OPERATING_BAND_25;	//	1900	EPCS A-G	1850 – 1915	1930 – 1995
	case rp_operating_band::UMTS_OPERATING_BAND_26:
		return operating_band::UMTS_OPERATING_BAND_26;	//	850	ECLR	814 – 849	859 – 894

	case rp_operating_band::LTE_OPERATING_BAND_1:
		return operating_band::LTE_OPERATING_BAND_1;	//	1920 - 1980	2110 - 2170	FDD
	case rp_operating_band::LTE_OPERATING_BAND_2:
		return operating_band::LTE_OPERATING_BAND_2;	//	1850 - 1910	1930 - 1990	FDD
	case rp_operating_band::LTE_OPERATING_BAND_3:
		return operating_band::LTE_OPERATING_BAND_3;	//	1710 - 1785	1805 - 1880	FDD
	case rp_operating_band::LTE_OPERATING_BAND_4:
		return operating_band::LTE_OPERATING_BAND_4;	//	1710 - 1755	2110 - 2155	FDD
	case rp_operating_band::LTE_OPERATING_BAND_5:
		return operating_band::LTE_OPERATING_BAND_5;	//	824 - 849	869 - 894	FDD
	case rp_operating_band::LTE_OPERATING_BAND_6:
		return operating_band::LTE_OPERATING_BAND_6;	//	830 - 840	875 - 885	FDD			
	case rp_operating_band::LTE_OPERATING_BAND_7:
		return operating_band::LTE_OPERATING_BAND_7;	//	2500 - 2570	2620 - 2690	FDD
	case rp_operating_band::LTE_OPERATING_BAND_8:
		return operating_band::LTE_OPERATING_BAND_8;	//	880 - 915	925 - 960	FDD
	case rp_operating_band::LTE_OPERATING_BAND_9:
		return operating_band::LTE_OPERATING_BAND_9;	//	1749.9 - 1784.9	1844.9 - 1879.9	FDD
	case rp_operating_band::LTE_OPERATING_BAND_10:
		return operating_band::LTE_OPERATING_BAND_10;	//	1710 - 1770	2110 - 2170	FDD			
	case rp_operating_band::LTE_OPERATING_BAND_11:
		return operating_band::LTE_OPERATING_BAND_11;	//	1427.9 - 1447.9	1475.9 - 1495.9	FDD
	case rp_operating_band::LTE_OPERATING_BAND_12:
		return operating_band::LTE_OPERATING_BAND_12;	//	699 - 716	729 - 746	FDD
	case rp_operating_band::LTE_OPERATING_BAND_13:
		return operating_band::LTE_OPERATING_BAND_13;	//	777 - 787	746 - 756	FDD
	case rp_operating_band::LTE_OPERATING_BAND_14:
		return operating_band::LTE_OPERATING_BAND_14;	//	788 - 798	758 - 768	FDD
	case rp_operating_band::LTE_OPERATING_BAND_17:
		return operating_band::LTE_OPERATING_BAND_17;	//	704 - 716	734 - 746	FDD			
	case rp_operating_band::LTE_OPERATING_BAND_18:
		return operating_band::LTE_OPERATING_BAND_18;	//	815 - 830	860 - 875	FDD
	case rp_operating_band::LTE_OPERATING_BAND_19:
		return operating_band::LTE_OPERATING_BAND_19;	//	830 - 845	875 - 890	FDD			
	case rp_operating_band::LTE_OPERATING_BAND_20:
		return operating_band::LTE_OPERATING_BAND_20;	//	832 - 862	791 - 821	FDD
	case rp_operating_band::LTE_OPERATING_BAND_21:
		return operating_band::LTE_OPERATING_BAND_21;	//	1447.9 - 1462.9	1495.9 - 1510.9	FDD
	case rp_operating_band::LTE_OPERATING_BAND_22:
		return operating_band::LTE_OPERATING_BAND_22;	//	3410 - 3490	3510 - 3590	FDD
	case rp_operating_band::LTE_OPERATING_BAND_23:
		return operating_band::LTE_OPERATING_BAND_23;	//	2000 - 2020	2180 - 2200	FDD			
	case rp_operating_band::LTE_OPERATING_BAND_24:
		return operating_band::LTE_OPERATING_BAND_24;	//	1626.5 - 1660.5	1525 - 1559	FDD
	case rp_operating_band::LTE_OPERATING_BAND_25:
		return operating_band::LTE_OPERATING_BAND_25;	//	1850 - 1915	1930 - 1995	FDD			
	case rp_operating_band::LTE_OPERATING_BAND_26:
		return operating_band::LTE_OPERATING_BAND_26;	//	814 - 849	859 - 894	FDD			
	case rp_operating_band::LTE_OPERATING_BAND_27:
		return operating_band::LTE_OPERATING_BAND_27;	//	807 - 824	852 - 869	FDD
	case rp_operating_band::LTE_OPERATING_BAND_28:
		return operating_band::LTE_OPERATING_BAND_28;	//	703 - 748	758 - 803	FDD
	case rp_operating_band::LTE_OPERATING_BAND_29:
		return operating_band::LTE_OPERATING_BAND_29;	//	N/A	716 - 728	FDD	
	case rp_operating_band::LTE_OPERATING_BAND_30:
		return operating_band::LTE_OPERATING_BAND_30;	//	2305 - 2315	 2350 - 2360 FDD
	case rp_operating_band::LTE_OPERATING_BAND_33:
		return operating_band::LTE_OPERATING_BAND_33;	//	1900 - 1920		TDD
	case rp_operating_band::LTE_OPERATING_BAND_34:
		return operating_band::LTE_OPERATING_BAND_34;	//	2010 - 2025		TDD
	case rp_operating_band::LTE_OPERATING_BAND_35:
		return operating_band::LTE_OPERATING_BAND_35;	//	1850 - 1910		TDD
	case rp_operating_band::LTE_OPERATING_BAND_36:
		return operating_band::LTE_OPERATING_BAND_36;	//	1930 - 1990		TDD
	case rp_operating_band::LTE_OPERATING_BAND_37:
		return operating_band::LTE_OPERATING_BAND_37;	//	1910 - 1930		TDD
	case rp_operating_band::LTE_OPERATING_BAND_38:
		return operating_band::LTE_OPERATING_BAND_38;	//	2570 - 2620		TDD
	case rp_operating_band::LTE_OPERATING_BAND_39:
		return operating_band::LTE_OPERATING_BAND_39;	//	1880 - 1920		TDD
	case rp_operating_band::LTE_OPERATING_BAND_40:
		return operating_band::LTE_OPERATING_BAND_40;	//	2300 - 2400		TDD
	case rp_operating_band::LTE_OPERATING_BAND_41:
		return operating_band::LTE_OPERATING_BAND_41;	//	2496 - 2690		TDD
	case rp_operating_band::LTE_OPERATING_BAND_42:
		return operating_band::LTE_OPERATING_BAND_42;	//	3400 - 3600		TDD
	case rp_operating_band::LTE_OPERATING_BAND_43:
		return operating_band::LTE_OPERATING_BAND_43;	//	3600 - 3800		TDD
	case rp_operating_band::LTE_OPERATING_BAND_44:
		return operating_band::LTE_OPERATING_BAND_44;	//	703 - 803		TDD

	case OPERATING_BAND_UNKNOWN:
	default:
		return operating_band::OPERATING_BAND_UNKNOWN;
	}
}

inline rp_band_indicator to_api_band_indicator(layer_3_information::band_indicator_type t) {
	switch(t) {
	case layer_3_information::dcs_1800_was_used:
		return dcs_1800_was_used;
	case layer_3_information::pcs_1900_was_used:
		return pcs_1900_was_used;
	case layer_3_information::unknown_band_was_used:
	default:
		return unknown_band_was_used;
	}
}

inline void populate_plmn(rp_plmn &a, const layer_3_information::plmn &t) {
	memset(a.mcc_, 0, PLMN_STRING_SIZE);
	memcpy(a.mcc_, t.mcc_.to_string(), t.mcc_.num_characters());
	memset(a.mnc_, 0, PLMN_STRING_SIZE);
	memcpy(a.mnc_, t.mnc_.to_string(), t.mnc_.num_characters());
}

inline void populate_plmns(std::vector<rp_plmn> &a, const std::vector<layer_3_information::plmn> &t) {
	a.reserve(t.size());
	auto i = 0;
	for(auto &j : t) {
		populate_plmn(a[i], j);
		++i;
	}
}

inline void populate_raw_layer_3(std::vector<rp_raw_layer_3> &a, const std::vector<layer_3_information::bit_stream> &t) {
	a.reserve(t.size());
	auto i = 0;
	for(auto &j : t) {
		a[i].num_bytes_ = j.bytes_.size();
		memset(a[i].bytes_, 0, MAX_RAW_LAYER_3_BYTE_SIZE);
		memcpy(a[i].bytes_, j.bytes_.data(), std::min(MAX_RAW_LAYER_3_BYTE_SIZE, (int32_t)j.bytes_.size()));
		a[i].unused_bits_ = j.unused_bits_;
		++i;
	}
}

class rf_phreaker_api_converter {
	//rp_device_info* to_

};

}}

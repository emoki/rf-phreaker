#pragma once
#include <QObject>
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/common/common_types.h"

//namespace rf_phreaker { namespace gui {

class ApiTypes : public QObject {
	Q_OBJECT
	Q_ENUMS(ConnectionStatus)
	Q_ENUMS(DeviceStatus)
	Q_ENUMS(Tech)
	Q_ENUMS(OperatingBand)

public:
	enum ConnectionStatus {
		DISCONNECTED,
		CONNECTING,
		CONNECTED
	};

	enum DeviceStatus {
		OFF,
		IDLE,
		BACKGROUND_SCANNING,
		SCANNING,
		RECORDING,
		UPDATING_LICENSE,
		WORKBENCH,
		ERROR
	};

	enum DeviceCommunication {
		USB_HI_SPEED,
		USB_SUPER_SPEED,
		UNKNOWN_DEVICE_COMMUNICATION
	};

	enum Tech {
		UNKNOWN_TECH,
		GSM_FULL_SCAN = ::rf_phreaker::GSM_LAYER_3_DECODE,
		CDMA_FULL_SCAN = ::rf_phreaker::CDMA_LAYER_3_DECODE,
		WCDMA_FULL_SCAN = ::rf_phreaker::UMTS_LAYER_3_DECODE,
		LTE_FULL_SCAN = ::rf_phreaker::LTE_LAYER_3_DECODE,
		GSM_SWEEP = ::rf_phreaker::GSM_SWEEP,
		CDMA_SWEEP = ::rf_phreaker::CDMA_SWEEP,
		WCDMA_SWEEP = ::rf_phreaker::UMTS_SWEEP,
		LTE_SWEEP = ::rf_phreaker::LTE_SWEEP,
		RAW_DATA = ::rf_phreaker::RAW_DATA,
	};

	enum OperatingBand {
		OPERATING_BAND_UNKNOWN = ::rp_operating_band::OPERATING_BAND_UNKNOWN,

		GSM_T_380 = ::rp_operating_band::GSM_T_380, //	380	380.2�389.8	390.2�399.8	dynamic
		GSM_T_410 = ::rp_operating_band::GSM_T_410, //	410	410.2�419.8	420.2�429.8	dynamic
		GSM_450 = ::rp_operating_band::GSM_450, //	450	450.6�457.6	460.6�467.6	259�293
		GSM_480 = ::rp_operating_band::GSM_480, //	480	479.0�486.0	489.0�496.0	306�340
		GSM_710 = ::rp_operating_band::GSM_710, //	710	698.2�716.2	728.2�746.2	dynamic
		GSM_750 = ::rp_operating_band::GSM_750, //	750	747.2�762.2	777.2�792.2	438�511
		GSM_T_810 = ::rp_operating_band::GSM_T_810, //	810	806.2�821.2	851.2�866.2	dynamic
		GSM_850 = ::rp_operating_band::GSM_850, //	850	824.2�849.2	869.2�894.2	128�251
		GSM_P_900 = ::rp_operating_band::GSM_P_900, //	900	890.0�915.0	935.0�960.0	1�124
		GSM_E_900 = ::rp_operating_band::GSM_E_900, //	900	880.0�915.0	925.0�960.0	975�1023, 0-124
		GSM_R_900 = ::rp_operating_band::GSM_R_900, //	900	876.0�915.0	921.0�960.0	955�1023, 0-124
		GSM_ER_900 = ::rp_operating_band::GSM_ER_900, //	900	873.0–915.0	918.0–960.0	945–1023, 0-124
		GSM_T_900 = ::rp_operating_band::GSM_T_900, //	900	870.4�876.0	915.4�921.0	dynamic^
		GSM_DCS_1800 = ::rp_operating_band::GSM_DCS_1800, //	1800	1,710.2�1,784.8	1,805.2�1,879.8	512�885
		GSM_PCS_1900 = ::rp_operating_band::GSM_PCS_1900, //	1900	1,850.2�1,909.8	1,930.2�1,989.8	512�810

		WCDMA_OPERATING_BAND_1 = ::rp_operating_band::UMTS_OPERATING_BAND_1,	//  2100	IMT	1920 - 1980	2110 � 2170
		WCDMA_OPERATING_BAND_2 = ::rp_operating_band::UMTS_OPERATING_BAND_2,	//  1900	PCS�A-F	1850 � 1910	1930 � 1990
		WCDMA_OPERATING_BAND_3 = ::rp_operating_band::UMTS_OPERATING_BAND_3,	//	1800	DCS	1710 � 1785	1805 � 1880
		WCDMA_OPERATING_BAND_4 = ::rp_operating_band::UMTS_OPERATING_BAND_4,	//	1700	AWS�A-F	1710 � 1755	2110 � 2155
		WCDMA_OPERATING_BAND_5 = ::rp_operating_band::UMTS_OPERATING_BAND_5,	//	850	CLR	824 � 849	869 � 894
		WCDMA_OPERATING_BAND_6 = ::rp_operating_band::UMTS_OPERATING_BAND_6,	//	800		830 � 840	875 � 885
		WCDMA_OPERATING_BAND_7 = ::rp_operating_band::UMTS_OPERATING_BAND_7,	//	2600	IMT-E	2500 � 2570	2620 � 2690
		WCDMA_OPERATING_BAND_8 = ::rp_operating_band::UMTS_OPERATING_BAND_8,	//	900	E-GSM	880 � 915	925 � 960
		WCDMA_OPERATING_BAND_9 = ::rp_operating_band::UMTS_OPERATING_BAND_9,	//	1700		1749.9 � 1784.9	1844.9 � 1879.9
		WCDMA_OPERATING_BAND_10 = ::rp_operating_band::UMTS_OPERATING_BAND_10,	//	1700	EAWS A-G	1710 � 1770	2110 � 2170
		WCDMA_OPERATING_BAND_11 = ::rp_operating_band::UMTS_OPERATING_BAND_11,	//	1500	LPDC	1427.9 � 1447.9	1475.9 � 1495.9
		WCDMA_OPERATING_BAND_12 = ::rp_operating_band::UMTS_OPERATING_BAND_12,	//	700	LSMH A/B/C	699 � 716	729 � 746
		WCDMA_OPERATING_BAND_13 = ::rp_operating_band::UMTS_OPERATING_BAND_13,	//	700	USMH C	777 � 787	746 � 756
		WCDMA_OPERATING_BAND_14 = ::rp_operating_band::UMTS_OPERATING_BAND_14,	//	700	USMH D	788 � 798	758 � 768
		WCDMA_OPERATING_BAND_19 = ::rp_operating_band::UMTS_OPERATING_BAND_19,	//	800		832.4 � 842.6	877.4 � 887.6
		WCDMA_OPERATING_BAND_20 = ::rp_operating_band::UMTS_OPERATING_BAND_20,	//	800	EUDD	832 � 862	791 � 821
		WCDMA_OPERATING_BAND_21 = ::rp_operating_band::UMTS_OPERATING_BAND_21,	//	1500	UPDC	1447.9 � 1462.9	1495.9 � 1510.9
		WCDMA_OPERATING_BAND_22 = ::rp_operating_band::UMTS_OPERATING_BAND_22,	//	3500		3410 � 3490	3510 � 3590
		WCDMA_OPERATING_BAND_25 = ::rp_operating_band::UMTS_OPERATING_BAND_25,	//	1900	EPCS A-G	1850 � 1915	1930 � 1995
		WCDMA_OPERATING_BAND_26 = ::rp_operating_band::UMTS_OPERATING_BAND_26,	//	850	ECLR	814 � 849	859 � 894

		LTE_OPERATING_BAND_1 = ::rp_operating_band::LTE_OPERATING_BAND_1,	//	1920�- 1980	2110�- 2170	FDD
		LTE_OPERATING_BAND_2 = ::rp_operating_band::LTE_OPERATING_BAND_2,	//	1850�- 1910	1930�- 1990	FDD
		LTE_OPERATING_BAND_3 = ::rp_operating_band::LTE_OPERATING_BAND_3,	//	1710�- 1785	1805�- 1880	FDD
		LTE_OPERATING_BAND_4 = ::rp_operating_band::LTE_OPERATING_BAND_4,	//	1710�- 1755	2110�- 2155	FDD
		LTE_OPERATING_BAND_5 = ::rp_operating_band::LTE_OPERATING_BAND_5,	//	824�- 849	869�- 894	FDD
		LTE_OPERATING_BAND_6 = ::rp_operating_band::LTE_OPERATING_BAND_6,	//	830�- 840	875�- 885	FDD
		LTE_OPERATING_BAND_7 = ::rp_operating_band::LTE_OPERATING_BAND_7,	//	2500�- 2570	2620�- 2690	FDD
		LTE_OPERATING_BAND_8 = ::rp_operating_band::LTE_OPERATING_BAND_8,	//	880�- 915	925�- 960	FDD
		LTE_OPERATING_BAND_9 = ::rp_operating_band::LTE_OPERATING_BAND_9,	//	1749.9�- 1784.9	1844.9�- 1879.9	FDD
		LTE_OPERATING_BAND_10 = ::rp_operating_band::LTE_OPERATING_BAND_10,	//	1710�- 1770	2110�- 2170	FDD
		LTE_OPERATING_BAND_11 = ::rp_operating_band::LTE_OPERATING_BAND_11,	//	1427.9�- 1447.9	1475.9�- 1495.9	FDD
		LTE_OPERATING_BAND_12 = ::rp_operating_band::LTE_OPERATING_BAND_12,	//	699�- 716	729�- 746	FDD
		LTE_OPERATING_BAND_13 = ::rp_operating_band::LTE_OPERATING_BAND_13,	//	777�- 787	746�- 756	FDD
		LTE_OPERATING_BAND_14 = ::rp_operating_band::LTE_OPERATING_BAND_14,	//	788�- 798	758�- 768	FDD
		LTE_OPERATING_BAND_17 = ::rp_operating_band::LTE_OPERATING_BAND_17,	//	704�- 716	734�- 746	FDD
		LTE_OPERATING_BAND_18 = ::rp_operating_band::LTE_OPERATING_BAND_18,	//	815�- 830	860�- 875	FDD
		LTE_OPERATING_BAND_19 = ::rp_operating_band::LTE_OPERATING_BAND_19,	//	830�- 845	875�- 890	FDD
		LTE_OPERATING_BAND_20 = ::rp_operating_band::LTE_OPERATING_BAND_20,	//	832�- 862	791�- 821	FDD
		LTE_OPERATING_BAND_21 = ::rp_operating_band::LTE_OPERATING_BAND_21,	//	1447.9�- 1462.9	1495.9�- 1510.9	FDD
		LTE_OPERATING_BAND_22 = ::rp_operating_band::LTE_OPERATING_BAND_22,	//	3410�- 3490	3510�- 3590	FDD
		LTE_OPERATING_BAND_23 = ::rp_operating_band::LTE_OPERATING_BAND_23,	//	2000�- 2020	2180�- 2200	FDD
		LTE_OPERATING_BAND_24 = ::rp_operating_band::LTE_OPERATING_BAND_24,	//	1626.5�- 1660.5	1525�- 1559	FDD
		LTE_OPERATING_BAND_25 = ::rp_operating_band::LTE_OPERATING_BAND_25,	//	1850�- 1915	1930�- 1995	FDD
		LTE_OPERATING_BAND_26 = ::rp_operating_band::LTE_OPERATING_BAND_26,	//	814�- 849	859�- 894	FDD
		LTE_OPERATING_BAND_27 = ::rp_operating_band::LTE_OPERATING_BAND_27,	//	807�- 824	852�- 869	FDD
		LTE_OPERATING_BAND_28 = ::rp_operating_band::LTE_OPERATING_BAND_28,	//	703�- 748	758�- 803	FDD
		LTE_OPERATING_BAND_29 = ::rp_operating_band::LTE_OPERATING_BAND_29,	//	N/A	716�- 728	FDD
		LTE_OPERATING_BAND_30 = ::rp_operating_band::LTE_OPERATING_BAND_30,	//	2305 - 2315	 2350 - 2360 FDD
		LTE_OPERATING_BAND_33 = ::rp_operating_band::LTE_OPERATING_BAND_33,	//	1900�- 1920		TDD
		LTE_OPERATING_BAND_34 = ::rp_operating_band::LTE_OPERATING_BAND_34,	//	2010�- 2025		TDD
		LTE_OPERATING_BAND_35 = ::rp_operating_band::LTE_OPERATING_BAND_35,	//	1850�- 1910		TDD
		LTE_OPERATING_BAND_36 = ::rp_operating_band::LTE_OPERATING_BAND_36,	//	1930�- 1990		TDD
		LTE_OPERATING_BAND_37 = ::rp_operating_band::LTE_OPERATING_BAND_37,	//	1910�- 1930		TDD
		LTE_OPERATING_BAND_38 = ::rp_operating_band::LTE_OPERATING_BAND_38,	//	2570�- 2620		TDD
		LTE_OPERATING_BAND_39 = ::rp_operating_band::LTE_OPERATING_BAND_39,	//	1880�- 1920		TDD
		LTE_OPERATING_BAND_40 = ::rp_operating_band::LTE_OPERATING_BAND_40,	//	2300�- 2400		TDD
		LTE_OPERATING_BAND_41 = ::rp_operating_band::LTE_OPERATING_BAND_41,	//	2496�- 2690		TDD
		LTE_OPERATING_BAND_42 = ::rp_operating_band::LTE_OPERATING_BAND_42,	//	3400�- 3600		TDD
		LTE_OPERATING_BAND_43 = ::rp_operating_band::LTE_OPERATING_BAND_43,	//	3600�- 3800		TDD
		LTE_OPERATING_BAND_44 = ::rp_operating_band::LTE_OPERATING_BAND_44,	//	703�- 803		TDD

		FIRST_GSM_OPERATING_BAND = GSM_T_380,
		LAST_GSM_OPERATING_BAND = GSM_PCS_1900,
		FIRST_UMTS_OPERATING_BAND = UMTS_OPERATING_BAND_1,
		LAST_UMTS_OPERATING_BAND = UMTS_OPERATING_BAND_26,
		FIRST_LTE_OPERATING_BAND = LTE_OPERATING_BAND_1,
		LAST_LTE_OPERATING_BAND = LTE_OPERATING_BAND_44
	};

	const static int serialLength = 6;

	Q_INVOKABLE static rf_phreaker::specifier toSpecifier(Tech s) {
		switch(s) {
		case GSM_FULL_SCAN:
			return rf_phreaker::GSM_LAYER_3_DECODE;
		case CDMA_FULL_SCAN:
			return rf_phreaker::CDMA_LAYER_3_DECODE;
		case WCDMA_FULL_SCAN:
			return rf_phreaker::UMTS_LAYER_3_DECODE;
		case LTE_FULL_SCAN:
			return rf_phreaker::LTE_LAYER_3_DECODE;
		case GSM_SWEEP:
			return rf_phreaker::GSM_SWEEP;
		case CDMA_SWEEP:
			return rf_phreaker::CDMA_SWEEP;
		case WCDMA_SWEEP:
			return rf_phreaker::UMTS_SWEEP;
		case LTE_SWEEP:
			return rf_phreaker::LTE_SWEEP;
		case RAW_DATA:
			return rf_phreaker::RAW_DATA;
		default:
			return rf_phreaker::UNKOWN_SPECIFIER;

		}
	}

	Q_INVOKABLE static Tech toTech(QString s) {
		if(s == "GSM FULL SCAN")
			return GSM_FULL_SCAN;
		else if(s == "CDMA FULL SCAN")
			return CDMA_FULL_SCAN;
		else if(s == "WCDMA FULL SCAN")
			return WCDMA_FULL_SCAN;
		else if(s == "LTE FULL SCAN")
			return LTE_FULL_SCAN;
		else if(s == "GSM SWEEP")
			return GSM_SWEEP;
		else if(s == "CDMA SWEEP")
			return CDMA_SWEEP;
		else if(s == "WCDMA SWEEP")
			return WCDMA_SWEEP;
		else if(s == "LTE SWEEP")
			return LTE_SWEEP;
		else if(s == "RAW DATA")
			return RAW_DATA;
		else
			return UNKNOWN_TECH;
	}

	Q_INVOKABLE static QString toQString(Tech s) {
		switch(s) {
		case GSM_FULL_SCAN:
			return "GSM FULL SCAN";
		case CDMA_FULL_SCAN:
			return "CDMA FULL SCAN";
		case WCDMA_FULL_SCAN:
			return "WCDMA FULL SCAN";
		case LTE_FULL_SCAN:
			return "LTE FULL SCAN";
		case GSM_SWEEP:
			return "GSM SWEEP";
		case CDMA_SWEEP:
			return "CDMA SWEEP";
		case WCDMA_SWEEP:
			return "WCDMA SWEEP";
		case LTE_SWEEP:
			return "LTE SWEEP";
		case RAW_DATA:
			return "RAW DATA";
		default:
			return "UNKNOWN";
		}
	}

	Q_INVOKABLE static OperatingBand toOperatingBand(QString t) {
		if(t == "GSM T 380") //	380	380.2�389.8	390.2�399.8	dynamic
			return GSM_T_380;
		else if(t == "GSM T 410")
			return GSM_T_410; //	410	410.2�419.8	420.2�429.8	dynamic
		else if(t == "GSM 450")
				return GSM_450; //	450	450.6�457.6	460.6�467.6	259�293
		else if(t == "GSM 480")
				return GSM_480; //	480	479.0�486.0	489.0�496.0	306�340
		else if(t == "GSM 710")
				return GSM_710; //	710	698.2�716.2	728.2�746.2	dynamic
		else if(t == "GSM 750")
				return GSM_750; //	750	747.2�762.2	777.2�792.2	438�511
		else if(t == "GSM T 810")
				return GSM_T_810; //	810	806.2�821.2	851.2�866.2	dynamic
		else if(t == "GSM 850")
				return GSM_850; //	850	824.2�849.2	869.2�894.2	128�251
		else if(t == "GSM P 900")
				return GSM_P_900; //	900	890.0�915.0	935.0�960.0	1�124
		else if(t == "GSM E 900")
				return GSM_E_900; //	900	880.0�915.0	925.0�960.0	975�1023, 0-124
		else if(t == "GSM R 900")
				return GSM_R_900; //	900	876.0�915.0	921.0�960.0	955�1023, 0-124
		else if(t == "GSM ER 900")
				return GSM_ER_900; //	900	876.0ï¿½915.0	921.0ï¿½960.0	955ï¿½1023, 0-124
		else if(t == "GSM T 900")
				return GSM_T_900; //	900	870.4�876.0	915.4�921.0	dynamic^
		else if(t == "GSM DCS 1800")
				return GSM_DCS_1800; //	1800 1,710.2�1,784.8	1,805.2�1,879.8	512�885
		else if(t == "GSM PCS 1900")
				return GSM_PCS_1900; //	1900 1,850.2�1,909.8	1,930.2�1,989.8	512�810

		else if(t == "WCDMA BAND 1")
				return WCDMA_OPERATING_BAND_1;	//  2100	IMT	1920 - 1980	2110 � 2170
		else if(t == "WCDMA BAND 2")
				return WCDMA_OPERATING_BAND_2;	//  1900	PCS�A-F	1850 � 1910	1930 � 1990
		else if(t == "WCDMA BAND 3")
				return WCDMA_OPERATING_BAND_3;	//	1800	DCS	1710 � 1785	1805 � 1880
		else if(t == "WCDMA BAND 4")
				return WCDMA_OPERATING_BAND_4;	//	1700	AWS�A-F	1710 � 1755	2110 � 2155
		else if(t == "WCDMA BAND 5")
				return WCDMA_OPERATING_BAND_5;	//	850	CLR	824 � 849	869 � 894
		else if(t == "WCDMA BAND 6")
				return WCDMA_OPERATING_BAND_6;	//	800		830 � 840	875 � 885
		else if(t == "WCDMA BAND 7")
				return WCDMA_OPERATING_BAND_7;	//	2600	IMT-E	2500 � 2570	2620 � 2690
		else if(t == "WCDMA BAND 8")
				return WCDMA_OPERATING_BAND_8;	//	900	E-GSM	880 � 915	925 � 960
		else if(t == "WCDMA BAND 9")
				return WCDMA_OPERATING_BAND_9;	//	1700		1749.9 � 1784.9	1844.9 � 1879.9
		else if(t == "WCDMA BAND 10")
				return WCDMA_OPERATING_BAND_10;	//	1700	EAWS A-G	1710 � 1770	2110 � 2170
		else if(t == "WCDMA BAND 11")
				return WCDMA_OPERATING_BAND_11;	//	1500	LPDC	1427.9 � 1447.9	1475.9 � 1495.9
		else if(t == "WCDMA BAND 12")
				return WCDMA_OPERATING_BAND_12;	//	700	LSMH A/B/C	699 � 716	729 � 746
		else if(t == "WCDMA BAND 13")
				return WCDMA_OPERATING_BAND_13;	//	700	USMH C	777 � 787	746 � 756
		else if(t == "WCDMA BAND 14")
				return WCDMA_OPERATING_BAND_14;	//	700	USMH D	788 � 798	758 � 768
		else if(t == "WCDMA BAND 19")
				return WCDMA_OPERATING_BAND_19;	//	800		832.4 � 842.6	877.4 � 887.6
		else if(t == "WCDMA BAND 20")
				return WCDMA_OPERATING_BAND_20;	//	800	EUDD	832 � 862	791 � 821
		else if(t == "WCDMA BAND 21")
				return WCDMA_OPERATING_BAND_21;	//	1500	UPDC	1447.9 � 1462.9	1495.9 � 1510.9
		else if(t == "WCDMA BAND 22")
				return WCDMA_OPERATING_BAND_22;	//	3500		3410 � 3490	3510 � 3590
		else if(t == "WCDMA BAND 25")
				return WCDMA_OPERATING_BAND_25;	//	1900	EPCS A-G	1850 � 1915	1930 � 1995
		else if(t == "WCDMA BAND 26")
				return WCDMA_OPERATING_BAND_26;	//	850	ECLR	814 � 849	859 � 894

		else if(t == "LTE BAND 1")
				return LTE_OPERATING_BAND_1;	//	1920�- 1980	2110�- 2170	FDD
		else if(t == "LTE BAND 2")
				return LTE_OPERATING_BAND_2;	//	1850�- 1910	1930�- 1990	FDD
		else if(t == "LTE BAND 3")
				return LTE_OPERATING_BAND_3;	//	1710�- 1785	1805�- 1880	FDD
		else if(t == "LTE BAND 4")
				return LTE_OPERATING_BAND_4;	//	1710�- 1755	2110�- 2155	FDD
		else if(t == "LTE BAND 5")
				return LTE_OPERATING_BAND_5;	//	824�- 849	869�- 894	FDD
		else if(t == "LTE BAND 6")
				return LTE_OPERATING_BAND_6;	//	830�- 840	875�- 885	FDD
		else if(t == "LTE BAND 7")
				return LTE_OPERATING_BAND_7;	//	2500�- 2570	2620�- 2690	FDD
		else if(t == "LTE BAND 8")
				return LTE_OPERATING_BAND_8;	//	880�- 915	925�- 960	FDD
		else if(t == "LTE BAND 9")
				return LTE_OPERATING_BAND_9;	//	1749.9�- 1784.9	1844.9�- 1879.9	FDD
		else if(t == "LTE BAND 10")
				return LTE_OPERATING_BAND_10;	//	1710�- 1770	2110�- 2170	FDD
		else if(t == "LTE BAND 11")
				return LTE_OPERATING_BAND_11;	//	1427.9�- 1447.9	1475.9�- 1495.9	FDD
		else if(t == "LTE BAND 12")
				return LTE_OPERATING_BAND_12;	//	699�- 716	729�- 746	FDD
		else if(t == "LTE BAND 13")
				return LTE_OPERATING_BAND_13;	//	777�- 787	746�- 756	FDD
		else if(t == "LTE BAND 14")
				return LTE_OPERATING_BAND_14;	//	788�- 798	758�- 768	FDD
		else if(t == "LTE BAND 17")
				return LTE_OPERATING_BAND_17;	//	704�- 716	734�- 746	FDD
		else if(t == "LTE BAND 18")
				return LTE_OPERATING_BAND_18;	//	815�- 830	860�- 875	FDD
		else if(t == "LTE BAND 19")
				return LTE_OPERATING_BAND_19;	//	830�- 845	875�- 890	FDD
		else if(t == "LTE BAND 20")
				return LTE_OPERATING_BAND_20;	//	832�- 862	791�- 821	FDD
		else if(t == "LTE BAND 21")
				return LTE_OPERATING_BAND_21;	//	1447.9�- 1462.9	1495.9�- 1510.9	FDD
		else if(t == "LTE BAND 22")
				return LTE_OPERATING_BAND_22;	//	3410�- 3490	3510�- 3590	FDD
		else if(t == "LTE BAND 23")
				return LTE_OPERATING_BAND_23;	//	2000�- 2020	2180�- 2200	FDD
		else if(t == "LTE BAND 24")
				return LTE_OPERATING_BAND_24;	//	1626.5�- 1660.5	1525�- 1559	FDD
		else if(t == "LTE BAND 25")
				return LTE_OPERATING_BAND_25;	//	1850�- 1915	1930�- 1995	FDD
		else if(t == "LTE BAND 26")
				return LTE_OPERATING_BAND_26;	//	814�- 849	859�- 894	FDD
		else if(t == "LTE BAND 27")
				return LTE_OPERATING_BAND_27;	//	807�- 824	852�- 869	FDD
		else if(t == "LTE BAND 28")
				return LTE_OPERATING_BAND_28;	//	703�- 748	758�- 803	FDD
		else if(t == "LTE BAND 29")
				return LTE_OPERATING_BAND_29;	//	N/A	716�- 728	FDD
		else if(t == "LTE BAND 30")
				return LTE_OPERATING_BAND_30;	//	2305 - 2315	 2350 - 2360 FDD
		else if(t == "LTE BAND 33")
				return LTE_OPERATING_BAND_33;	//	1900�- 1920		TDD
		else if(t == "LTE BAND 34")
				return LTE_OPERATING_BAND_34;	//	2010�- 2025		TDD
		else if(t == "LTE BAND 35")
				return LTE_OPERATING_BAND_35;	//	1850�- 1910		TDD
		else if(t == "LTE BAND 36")
				return LTE_OPERATING_BAND_36;	//	1930�- 1990		TDD
		else if(t == "LTE BAND 37")
				return LTE_OPERATING_BAND_37;	//	1910�- 1930		TDD
		else if(t == "LTE BAND 38")
				return LTE_OPERATING_BAND_38;	//	2570�- 2620		TDD
		else if(t == "LTE BAND 39")
				return LTE_OPERATING_BAND_39;	//	1880�- 1920		TDD
		else if(t == "LTE BAND 40")
				return LTE_OPERATING_BAND_40;	//	2300�- 2400		TDD
		else if(t == "LTE BAND 41")
				return LTE_OPERATING_BAND_41;	//	2496�- 2690		TDD
		else if(t == "LTE BAND 42")
				return LTE_OPERATING_BAND_42;	//	3400�- 3600		TDD
		else if(t == "LTE BAND 43")
				return LTE_OPERATING_BAND_43;	//	3600�- 3800		TDD
		else if(t == "LTE BAND 44")
				return LTE_OPERATING_BAND_44;	//	703�- 803		TDD

		else
			return OPERATING_BAND_UNKNOWN;

	}

	Q_INVOKABLE static QString toQString(ConnectionStatus s) {
		switch(s) {
		case DISCONNECTED:
			return "Disconnected";
		case CONNECTING:
			return "Connecting";
		case CONNECTED:
			return "Connected";
		default:
			return "Uknown";
		}
	}

	Q_INVOKABLE static QString toQString(DeviceStatus s) {
		switch(s) {
		case OFF:
			return "Off";
		case IDLE:
			return "Idle";
		case BACKGROUND_SCANNING:
			return "Background Scanning";
		case SCANNING:
			return "Scanning";
		case RECORDING:
			return "Recording";
		case UPDATING_LICENSE:
			return "Updating License";
		case ERROR:
			return "Error";
		default:
			return "Unknown";
		}
	}

	Q_INVOKABLE static QString toQString(OperatingBand t) {
		switch(t) {
		case GSM_T_380: //	380	380.2�389.8	390.2�399.8	dynamic
			return "GSM T 380";
		case GSM_T_410:
			return "GSM T 410"; //	410	410.2�419.8	420.2�429.8	dynamic
		case GSM_450:
			return "GSM 450"; //	450	450.6�457.6	460.6�467.6	259�293
		case GSM_480:
			return "GSM 480"; //	480	479.0�486.0	489.0�496.0	306�340
		case GSM_710:
			return "GSM 710"; //	710	698.2�716.2	728.2�746.2	dynamic
		case GSM_750:
			return "GSM 750"; //	750	747.2�762.2	777.2�792.2	438�511
		case GSM_T_810:
			return "GSM T 810"; //	810	806.2�821.2	851.2�866.2	dynamic
		case GSM_850:
			return "GSM 850"; //	850	824.2�849.2	869.2�894.2	128�251
		case GSM_P_900:
			return "GSM P 900"; //	900	890.0�915.0	935.0�960.0	1�124
		case GSM_E_900:
			return "GSM E 900"; //	900	880.0�915.0	925.0�960.0	975�1023, 0-124
		case GSM_R_900:
			return "GSM R 900"; //	900	876.0�915.0	921.0�960.0	955�1023, 0-124
		case GSM_ER_900:
			return "GSM ER 900"; //	900	876.0ï¿½915.0	921.0ï¿½960.0	955ï¿½1023, 0-124
		case GSM_T_900:
			return "GSM T 900"; //	900	870.4�876.0	915.4�921.0	dynamic^
		case GSM_DCS_1800:
			return "GSM DCS 1800"; //	1800 1,710.2�1,784.8	1,805.2�1,879.8	512�885
		case GSM_PCS_1900:
			return "GSM PCS 1900"; //	1900 1,850.2�1,909.8	1,930.2�1,989.8	512�810

		case WCDMA_OPERATING_BAND_1:
			return "WCDMA BAND 1";	//  2100	IMT	1920 - 1980	2110 � 2170
		case WCDMA_OPERATING_BAND_2:
			return "WCDMA BAND 2";	//  1900	PCS�A-F	1850 � 1910	1930 � 1990
		case WCDMA_OPERATING_BAND_3:
			return "WCDMA BAND 3";	//	1800	DCS	1710 � 1785	1805 � 1880
		case WCDMA_OPERATING_BAND_4:
			return "WCDMA BAND 4";	//	1700	AWS�A-F	1710 � 1755	2110 � 2155
		case WCDMA_OPERATING_BAND_5:
			return "WCDMA BAND 5";	//	850	CLR	824 � 849	869 � 894
		case WCDMA_OPERATING_BAND_6:
			return "WCDMA BAND 6";	//	800		830 � 840	875 � 885
		case WCDMA_OPERATING_BAND_7:
			return "WCDMA BAND 7";	//	2600	IMT-E	2500 � 2570	2620 � 2690
		case WCDMA_OPERATING_BAND_8:
			return "WCDMA BAND 8";	//	900	E-GSM	880 � 915	925 � 960
		case WCDMA_OPERATING_BAND_9:
			return "WCDMA BAND 9";	//	1700		1749.9 � 1784.9	1844.9 � 1879.9
		case WCDMA_OPERATING_BAND_10:
			return "WCDMA BAND 10";	//	1700	EAWS A-G	1710 � 1770	2110 � 2170
		case WCDMA_OPERATING_BAND_11:
			return "WCDMA BAND 11";	//	1500	LPDC	1427.9 � 1447.9	1475.9 � 1495.9
		case WCDMA_OPERATING_BAND_12:
			return "WCDMA BAND 12";	//	700	LSMH A/B/C	699 � 716	729 � 746
		case WCDMA_OPERATING_BAND_13:
			return "WCDMA BAND 13";	//	700	USMH C	777 � 787	746 � 756
		case WCDMA_OPERATING_BAND_14:
			return "WCDMA BAND 14";	//	700	USMH D	788 � 798	758 � 768
		case WCDMA_OPERATING_BAND_19:
			return "WCDMA BAND 19";	//	800		832.4 � 842.6	877.4 � 887.6
		case WCDMA_OPERATING_BAND_20:
			return "WCDMA BAND 20";	//	800	EUDD	832 � 862	791 � 821
		case WCDMA_OPERATING_BAND_21:
			return "WCDMA BAND 21";	//	1500	UPDC	1447.9 � 1462.9	1495.9 � 1510.9
		case WCDMA_OPERATING_BAND_22:
			return "WCDMA BAND 22";	//	3500		3410 � 3490	3510 � 3590
		case WCDMA_OPERATING_BAND_25:
			return "WCDMA BAND 25";	//	1900	EPCS A-G	1850 � 1915	1930 � 1995
		case WCDMA_OPERATING_BAND_26:
			return "WCDMA BAND 26";	//	850	ECLR	814 � 849	859 � 894

		case LTE_OPERATING_BAND_1:
			return "LTE BAND 1";	//	1920�- 1980	2110�- 2170	FDD
		case LTE_OPERATING_BAND_2:
			return "LTE BAND 2";	//	1850�- 1910	1930�- 1990	FDD
		case LTE_OPERATING_BAND_3:
			return "LTE BAND 3";	//	1710�- 1785	1805�- 1880	FDD
		case LTE_OPERATING_BAND_4:
			return "LTE BAND 4";	//	1710�- 1755	2110�- 2155	FDD
		case LTE_OPERATING_BAND_5:
			return "LTE BAND 5";	//	824�- 849	869�- 894	FDD
		case LTE_OPERATING_BAND_6:
			return "LTE BAND 6";	//	830�- 840	875�- 885	FDD
		case LTE_OPERATING_BAND_7:
			return "LTE BAND 7";	//	2500�- 2570	2620�- 2690	FDD
		case LTE_OPERATING_BAND_8:
			return "LTE BAND 8";	//	880�- 915	925�- 960	FDD
		case LTE_OPERATING_BAND_9:
			return "LTE BAND 9";	//	1749.9�- 1784.9	1844.9�- 1879.9	FDD
		case LTE_OPERATING_BAND_10:
			return "LTE BAND 10";	//	1710�- 1770	2110�- 2170	FDD
		case LTE_OPERATING_BAND_11:
			return "LTE BAND 11";	//	1427.9�- 1447.9	1475.9�- 1495.9	FDD
		case LTE_OPERATING_BAND_12:
			return "LTE BAND 12";	//	699�- 716	729�- 746	FDD
		case LTE_OPERATING_BAND_13:
			return "LTE BAND 13";	//	777�- 787	746�- 756	FDD
		case LTE_OPERATING_BAND_14:
			return "LTE BAND 14";	//	788�- 798	758�- 768	FDD
		case LTE_OPERATING_BAND_17:
			return "LTE BAND 17";	//	704�- 716	734�- 746	FDD
		case LTE_OPERATING_BAND_18:
			return "LTE BAND 18";	//	815�- 830	860�- 875	FDD
		case LTE_OPERATING_BAND_19:
			return "LTE BAND 19";	//	830�- 845	875�- 890	FDD
		case LTE_OPERATING_BAND_20:
			return "LTE BAND 20";	//	832�- 862	791�- 821	FDD
		case LTE_OPERATING_BAND_21:
			return "LTE BAND 21";	//	1447.9�- 1462.9	1495.9�- 1510.9	FDD
		case LTE_OPERATING_BAND_22:
			return "LTE BAND 22";	//	3410�- 3490	3510�- 3590	FDD
		case LTE_OPERATING_BAND_23:
			return "LTE BAND 23";	//	2000�- 2020	2180�- 2200	FDD
		case LTE_OPERATING_BAND_24:
			return "LTE BAND 24";	//	1626.5�- 1660.5	1525�- 1559	FDD
		case LTE_OPERATING_BAND_25:
			return "LTE BAND 25";	//	1850�- 1915	1930�- 1995	FDD
		case LTE_OPERATING_BAND_26:
			return "LTE BAND 26";	//	814�- 849	859�- 894	FDD
		case LTE_OPERATING_BAND_27:
			return "LTE BAND 27";	//	807�- 824	852�- 869	FDD
		case LTE_OPERATING_BAND_28:
			return "LTE BAND 28";	//	703�- 748	758�- 803	FDD
		case LTE_OPERATING_BAND_29:
			return "LTE BAND 29";	//	N/A	716�- 728	FDD
		case LTE_OPERATING_BAND_30:
			return "LTE BAND 30";	//	2305 - 2315	 2350 - 2360 FDD
		case LTE_OPERATING_BAND_33:
			return "LTE BAND 33";	//	1900�- 1920		TDD
		case LTE_OPERATING_BAND_34:
			return "LTE BAND 34";	//	2010�- 2025		TDD
		case LTE_OPERATING_BAND_35:
			return "LTE BAND 35";	//	1850�- 1910		TDD
		case LTE_OPERATING_BAND_36:
			return "LTE BAND 36";	//	1930�- 1990		TDD
		case LTE_OPERATING_BAND_37:
			return "LTE BAND 37";	//	1910�- 1930		TDD
		case LTE_OPERATING_BAND_38:
			return "LTE BAND 38";	//	2570�- 2620		TDD
		case LTE_OPERATING_BAND_39:
			return "LTE BAND 39";	//	1880�- 1920		TDD
		case LTE_OPERATING_BAND_40:
			return "LTE BAND 40";	//	2300�- 2400		TDD
		case LTE_OPERATING_BAND_41:
			return "LTE BAND 41";	//	2496�- 2690		TDD
		case LTE_OPERATING_BAND_42:
			return "LTE BAND 42";	//	3400�- 3600		TDD
		case LTE_OPERATING_BAND_43:
			return "LTE BAND 43";	//	3600�- 3800		TDD
		case LTE_OPERATING_BAND_44:
			return "LTE BAND 44";	//	703�- 803		TDD

		case OPERATING_BAND_UNKNOWN:
		default:
			return "BAND UNKNOWN";
		}
	}

	Q_INVOKABLE static QString toQString(rf_phreaker::operating_band t) {
		return toQString((OperatingBand)t);
	}

	Q_INVOKABLE static QString toQString(rp_operating_band t) {
		return toQString((OperatingBand)t);
	}

	Q_INVOKABLE static QString toQStringShort(const rp_serial &serial) {
		QString s(serial.serial_);
		return s.left(serialLength);
	}

	Q_INVOKABLE static QString toQStringShort(const rf_phreaker::scanner_serial_type &serial) {
		QString s(serial.c_str());
		return s.left(serialLength);
	}

	Q_INVOKABLE static QString toQString(const rp_serial &serial) {
		QString s(serial.serial_);
		return s;
	}

	Q_INVOKABLE static bool statusOk(rp_status status) {
		return status == RP_STATUS_OK;
	}

	Q_INVOKABLE static rp_operating_band toRpOperatingBand(rf_phreaker::operating_band t) {
		return static_cast<rp_operating_band>(t);
	}

	Q_INVOKABLE static OperatingBand toOperatingBand(rf_phreaker::operating_band t) {
		return static_cast<OperatingBand>(t);
	}

	Q_INVOKABLE static rf_phreaker::operating_band toOperatingBand(OperatingBand t) {
		return static_cast<rf_phreaker::operating_band>(t);
	}

	Q_INVOKABLE static QString toQString(const rp_device_communication &comm) {
		switch(comm) {
		case USB_HI_SPEED:
			return "Hi-Speed USB";
		case USB_SUPER_SPEED:
			return "Super-Speed USB";
		case UNKNOWN_DEVICE_COMMUNICATION:
		default:
			return "Unknown Device Communication";
		}
	}

	Q_INVOKABLE static QString toQString(const rf_phreaker::device_communication &comm) {
		switch(comm) {
		case USB_HI_SPEED:
			return "Hi-Speed USB";
		case USB_SUPER_SPEED:
			return "Super-Speed USB";
		case UNKNOWN_DEVICE_COMMUNICATION:
		default:
			return "Unknown Device Communication";
		}
	}
};

//}}

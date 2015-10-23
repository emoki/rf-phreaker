#ifndef RF_PHREAKER_API
#define RF_PHREAKER_API

#ifdef __cplusplus
extern "C" {
#endif

#ifndef RP_CALLCONV
#ifdef _WIN32
#define RP_CALLCONV __stdcall
#else
#define RP_CALLCONV
#endif
#endif

#ifdef BUILDING_DLL
#ifdef _WIN32
#define RP_LIBEXPORT(x) __declspec(dllexport) x __stdcall
#else
#define RP_LIBEXPORT(x) __declspec(dllexport) x
#endif
#else
#ifdef _WIN32
#define RP_LIBEXPORT(x) __declspec(dllimport) x __stdcall
#else
#define RP_LIBEXPORT(x) __declspec(dllimport) x
#endif
#endif

#include <stdint.h>

#define RF_PHREAKER_API_VERSION 1

struct rp_device;

const int RP_SERIAL_LENGTH = 33;
const int RP_FREQUENCY_PATH_SIZE = 100;

typedef int64_t rp_frequency_type;

typedef int32_t rp_channel_type;

typedef int32_t rp_bandwidth_type;

typedef int64_t rp_time_type;

typedef enum rp_status {
	RP_STATUS_OK = 0,
	RP_STATUS_NOT_INITIALIZED,
	RP_STATUS_INVALID_PARAMETER,
	RP_STATUS_COMMUNICATION_ERROR,
	RP_STATUS_SCANNER_INIT_ERROR,
	RP_STATUS_HARDWARE_INFO_ERROR,
	RP_STATUS_MISC_ERROR,
	RP_STATUS_FILE_IO_ERROR,
	RP_STATUS_BLADE_RF_ERROR,
	RP_STATUS_IPP_ERROR,
	RP_STATUS_FILTER_ERROR,
	RP_STATUS_GSM_ANALYSIS_ERROR,
	RP_STATUS_UMTS_ANALYSIS_ERROR,
	RP_STATUS_LTE_ANALYSIS_ERROR,
	RP_STATUS_PROCESSING_ERROR,
	RP_STATUS_GPS_COMMUNICATION_ERROR,
	RP_STATUS_RF_PHREAKER_API_ERROR,
	RP_STATUS_GENERIC_ERROR,
	RP_STATUS_UNKNOWN_ERROR
} rp_status;

typedef enum rp_technology {
	GSM,
	CDMA,
	WCDMA,
	LTE,
	RAW_DATA
} rp_technology;

typedef enum rp_operating_band {
	OPERATING_BAND_UNKNOWN,

	GSM_T_380, //	380	380.2–389.8	390.2–399.8	dynamic
	GSM_T_410, //	410	410.2–419.8	420.2–429.8	dynamic
	GSM_450, //	450	450.6–457.6	460.6–467.6	259–293
	GSM_480, //	480	479.0–486.0	489.0–496.0	306–340
	GSM_710, //	710	698.2–716.2	728.2–746.2	dynamic
	GSM_750, //	750	747.2–762.2	777.2–792.2	438–511
	GSM_T_810, //	810	806.2–821.2	851.2–866.2	dynamic
	GSM_850, //	850	824.2–849.2	869.2–894.2	128–251
	GSM_P_900, //	900	890.0–915.0	935.0–960.0	1–124
	GSM_E_900, //	900	880.0–915.0	925.0–960.0	975–1023, 0-124
	GSM_R_900, //	900	876.0–915.0	921.0–960.0	955–1023, 0-124
	GSM_ER_900, //	900	873.0–915.0	918.0–960.0	945–1023, 0-124
	GSM_T_900, //	900	870.4–876.0	915.4–921.0	dynamic^
	GSM_DCS_1800, //	1800	1,710.2–1,784.8	1,805.2–1,879.8	512–885
	GSM_PCS_1900, //	1900	1,850.2–1,909.8	1,930.2–1,989.8	512–810

	UMTS_OPERATING_BAND_1,	//  2100	IMT	1920 - 1980	2110 – 2170
	UMTS_OPERATING_BAND_2,	//  1900	PCS A-F	1850 – 1910	1930 – 1990
	UMTS_OPERATING_BAND_3,	//	1800	DCS	1710 – 1785	1805 – 1880
	UMTS_OPERATING_BAND_4,	//	1700	AWS A-F	1710 – 1755	2110 – 2155
	UMTS_OPERATING_BAND_5,	//	850	CLR	824 – 849	869 – 894
	UMTS_OPERATING_BAND_6,	//	800		830 – 840	875 – 885
	UMTS_OPERATING_BAND_7,	//	2600	IMT-E	2500 – 2570	2620 – 2690
	UMTS_OPERATING_BAND_8,	//	900	E-GSM	880 – 915	925 – 960
	UMTS_OPERATING_BAND_9,	//	1700		1749.9 – 1784.9	1844.9 – 1879.9
	UMTS_OPERATING_BAND_10,	//	1700	EAWS A-G	1710 – 1770	2110 – 2170
	UMTS_OPERATING_BAND_11,	//	1500	LPDC	1427.9 – 1447.9	1475.9 – 1495.9
	UMTS_OPERATING_BAND_12,	//	700	LSMH A/B/C	699 – 716	729 – 746
	UMTS_OPERATING_BAND_13,	//	700	USMH C	777 – 787	746 – 756
	UMTS_OPERATING_BAND_14,	//	700	USMH D	788 – 798	758 – 768
	UMTS_OPERATING_BAND_19,	//	800		832.4 – 842.6	877.4 – 887.6
	UMTS_OPERATING_BAND_20,	//	800	EUDD	832 – 862	791 – 821
	UMTS_OPERATING_BAND_21,	//	1500	UPDC	1447.9 – 1462.9	1495.9 – 1510.9
	UMTS_OPERATING_BAND_22,	//	3500		3410 – 3490	3510 – 3590
	UMTS_OPERATING_BAND_25,	//	1900	EPCS A-G	1850 – 1915	1930 – 1995
	UMTS_OPERATING_BAND_26,	//	850	ECLR	814 – 849	859 – 894

	LTE_OPERATING_BAND_1,	//	1920 - 1980	2110 - 2170	FDD
	LTE_OPERATING_BAND_2,	//	1850 - 1910	1930 - 1990	FDD
	LTE_OPERATING_BAND_3,	//	1710 - 1785	1805 - 1880	FDD
	LTE_OPERATING_BAND_4,	//	1710 - 1755	2110 - 2155	FDD
	LTE_OPERATING_BAND_5,	//	824 - 849	869 - 894	FDD
	LTE_OPERATING_BAND_6,	//	830 - 840	875 - 885	FDD
	LTE_OPERATING_BAND_7,	//	2500 - 2570	2620 - 2690	FDD
	LTE_OPERATING_BAND_8,	//	880 - 915	925 - 960	FDD
	LTE_OPERATING_BAND_9,	//	1749.9 - 1784.9	1844.9 - 1879.9	FDD
	LTE_OPERATING_BAND_10,	//	1710 - 1770	2110 - 2170	FDD
	LTE_OPERATING_BAND_11,	//	1427.9 - 1447.9	1475.9 - 1495.9	FDD
	LTE_OPERATING_BAND_12,	//	699 - 716	729 - 746	FDD
	LTE_OPERATING_BAND_13,	//	777 - 787	746 - 756	FDD
	LTE_OPERATING_BAND_14,	//	788 - 798	758 - 768	FDD
	LTE_OPERATING_BAND_17,	//	704 - 716	734 - 746	FDD
	LTE_OPERATING_BAND_18,	//	815 - 830	860 - 875	FDD
	LTE_OPERATING_BAND_19,	//	830 - 845	875 - 890	FDD
	LTE_OPERATING_BAND_20,	//	832 - 862	791 - 821	FDD
	LTE_OPERATING_BAND_21,	//	1447.9 - 1462.9	1495.9 - 1510.9	FDD
	LTE_OPERATING_BAND_22,	//	3410 - 3490	3510 - 3590	FDD
	LTE_OPERATING_BAND_23,	//	2000 - 2020	2180 - 2200	FDD
	LTE_OPERATING_BAND_24,	//	1626.5 - 1660.5	1525 - 1559	FDD
	LTE_OPERATING_BAND_25,	//	1850 - 1915	1930 - 1995	FDD
	LTE_OPERATING_BAND_26,	//	814 - 849	859 - 894	FDD
	LTE_OPERATING_BAND_27,	//	807 - 824	852 - 869	FDD
	LTE_OPERATING_BAND_28,	//	703 - 748	758 - 803	FDD
	LTE_OPERATING_BAND_29,	//	N/A	716 - 728	FDD
	LTE_OPERATING_BAND_30,	//	2305 - 2315	 2350 - 2360 FDD
	LTE_OPERATING_BAND_33,	//	1900 - 1920		TDD
	LTE_OPERATING_BAND_34,	//	2010 - 2025		TDD
	LTE_OPERATING_BAND_35,	//	1850 - 1910		TDD
	LTE_OPERATING_BAND_36,	//	1930 - 1990		TDD
	LTE_OPERATING_BAND_37,	//	1910 - 1930		TDD
	LTE_OPERATING_BAND_38,	//	2570 - 2620		TDD
	LTE_OPERATING_BAND_39,	//	1880 - 1920		TDD
	LTE_OPERATING_BAND_40,	//	2300 - 2400		TDD
	LTE_OPERATING_BAND_41,	//	2496 - 2690		TDD
	LTE_OPERATING_BAND_42,	//	3400 - 3600		TDD
	LTE_OPERATING_BAND_43,	//	3600 - 3800		TDD
	LTE_OPERATING_BAND_44,	//	703 - 803		TDD

	FIRST_GSM_OPERATING_BAND = GSM_T_380,
	LAST_GSM_OPERATING_BAND = GSM_PCS_1900,
	FIRST_UMTS_OPERATING_BAND = UMTS_OPERATING_BAND_1,
	LAST_UMTS_OPERATING_BAND = UMTS_OPERATING_BAND_26,
	FIRST_LTE_OPERATING_BAND = LTE_OPERATING_BAND_1,
	LAST_LTE_OPERATING_BAND = LTE_OPERATING_BAND_44,
} rp_operating_band;

typedef enum rp_device_communication {
	USB_HI_SPEED,
	USB_SUPER_SPEED,
	UNKNOWN_DEVICE_COMMUNICATION
} rp_device_communication;

typedef struct rp_serial {
	char serial_[RP_SERIAL_LENGTH]; // Includes NULL terminator.
} rp_serial;

typedef struct rp_frequency_path {
	rp_frequency_type low_freq_;
	rp_frequency_type high_freq_;
} rp_frequency_path;

typedef struct rp_frequency_band {
	rp_frequency_type freq_;
	rp_operating_band band_;
} rp_frequency_band;

typedef struct rp_frequency_group {
	rp_frequency_type *e_;
	int32_t size_;
} rp_frequency_group;

typedef struct rp_operating_band_group {
	rp_operating_band *e_;
	int32_t size_;
} rp_operating_band_group;

typedef struct rp_frequency_band_group {
	rp_frequency_band *e_;
	int32_t size_;
} rp_frequency_band_group;

typedef struct rp_collection_info {
	rp_frequency_band_group gsm_;
	rp_frequency_band_group wcdma_;
	rp_frequency_band_group lte_;
	rp_frequency_group raw_data_;
	rp_operating_band_group sweep_;
} rp_collection_info;

typedef struct rp_device_info {
	rp_serial serial_;
	rp_device_communication device_communication_;
	int64_t frequency_correction_calibration_date_;
	int64_t rf_calibration_date_;
	int num_frequency_paths_;
	rp_frequency_path frequency_paths_[RP_FREQUENCY_PATH_SIZE];
	int num_licenses_;
	// TODO - expose license.
} rp_device_info;

typedef struct rp_gps {
	rp_serial serial_;
	bool lock_;
	rp_time_type coordinated_universal_time_;
	int32_t visible_satellites_;
	int32_t tracking_satellites_;
	double latitude_;
	double longitude_;
	int32_t speed_;
	int64_t raw_status_;
} rp_gps;

typedef struct rp_base {
	rp_serial serial_;
	int64_t collection_round_;
	rp_frequency_type carrier_frequency_;
	rp_bandwidth_type carrier_bandwidth_;
	double carrier_signal_level_;
	rp_time_type time_;
	int32_t status_flags_;
} rp_base;

typedef struct rp_gsm {
	rp_base base_;
	rp_channel_type arfcn_;
	int32_t bsic_;
	// TODO - expose layer 3
} rp_gsm;

typedef struct rp_wcdma {
	rp_base base_;
	rp_channel_type uarfcn_;
	rp_operating_band operating_band_;
	int32_t cpich_;
	double ecio_;
	double rscp_;
	// TODO - expose layer 3
} rp_wcdma;

typedef struct rp_lte {
	rp_base base_;
	rp_channel_type earfcn_;
	rp_operating_band operating_band_;
	int32_t physical_cell_id_;
	double rsrp_;
	double rsrq_;
	double rssi_;
	int32_t psch_id_;
	double psch_quality_;
	int32_t ssch_id_;
	double ssch_quality_;
	double sync_quality_;
	int32_t cyclic_prefix_;
	int32_t num_antenna_ports_;
	int32_t downlink_bandwidth_;
	int32_t frame_number_;
	// TODO - expose layer 3
} rp_lte;

typedef enum rp_sample_format {
	LITTLE_ENDIAN_FLOAT_REAL_IMAGINARY
} rp_sample_format;

typedef struct rp_raw_data {
	rp_base base_;
	double power_adjustment_;
	rp_sample_format sample_format_;
	int64_t num_samples_;
	void *samples_;
} rp_raw_data;

typedef struct rp_callbacks {
	void (RP_CALLCONV *rp_log_update)(const char *message);

	void (RP_CALLCONV *rp_message_update)(rp_status status, const char *message);

	void (RP_CALLCONV *rp_device_info_update)(const rp_device_info *info);

	void (RP_CALLCONV *rp_gps_update)(const rp_gps *gps);

	void (RP_CALLCONV *rp_gsm_update)(const rp_base *base, const rp_gsm *gsm, int num_gsm);

	void (RP_CALLCONV *rp_wcdma_update)(const rp_base *base, const rp_wcdma *wcdma, int num_wcdma);

	void (RP_CALLCONV *rp_lte_update)(const rp_base *base, const rp_lte *lte, int num_lte);

	void (RP_CALLCONV *rp_sweep_update)(const rp_base *base, const rp_gsm *gsm, int num_gsm, const rp_wcdma *umts, int num_umts, const rp_lte *lte, int num_lte);

	void (RP_CALLCONV *rp_raw_data_update)(const rp_raw_data, int num_raw_data);
} rp_callbacks;

RP_LIBEXPORT(rp_status) rp_initialize(rp_callbacks *callbacks);

RP_LIBEXPORT(rp_status) rp_clean_up();

RP_LIBEXPORT(rp_status) rp_list_devices(rp_serial *serials, int *num_serials);

RP_LIBEXPORT(rp_status) rp_connect_device(rp_serial serial, rp_device **device);

RP_LIBEXPORT(rp_status) rp_disconnect_device(rp_device *device);

RP_LIBEXPORT(bool) rp_is_device_open(rp_device *device);

RP_LIBEXPORT(rp_status) rp_get_device_info(rp_device *device, rp_device_info *device_info);

//RP_LIBEXPORT(rp_status) rp_add_collection_frequency(rp_device *device, rp_technology data, rp_frequency_type freq, rp_operating_band band);
//
////RP_LIBEXPORT(rp_status) rp_add_collection_channel(rp_device *device, rp_technology data, rp_channel_type channel);
//
//RP_LIBEXPORT(rp_status) rp_remove_collection_frequency(rp_device *device, rp_technology data, rp_frequency_type freq, rp_operating_band band);
//
//RP_LIBEXPORT(rp_status) rp_add_sweep_operating_band(rp_device *device, rp_operating_band band);
//
//RP_LIBEXPORT(rp_status) rp_remove_sweep_operating_band(rp_device *device, rp_operating_band band);
//
//RP_LIBEXPORT(rp_status) rp_remove_collection_frequencies_and_bands(rp_device *device);

RP_LIBEXPORT(rp_status) rp_start_collection(rp_device *device, const rp_collection_info *info);

RP_LIBEXPORT(rp_status) rp_stop_collection(rp_device *device);

RP_LIBEXPORT(rp_status) rp_get_gps_data(rp_device *device, rp_gps gps);

RP_LIBEXPORT(rp_status) rp_get_iq_data_using_auto_gain(rp_device *device, rp_frequency_type frequency, rp_time_type time_ns, rp_bandwidth_type bandwidth, rp_frequency_type sampling_rate, rp_raw_data *raw_data);

RP_LIBEXPORT(rp_status) rp_get_iq_data(rp_device *device, rp_frequency_type frequency, rp_time_type time_ns, rp_bandwidth_type bandwidth, rp_frequency_type sampling_rate, int32_t gain_db, rp_raw_data *raw_data);

RP_LIBEXPORT(rp_status) rp_update_license(rp_device *device, const char *filename);

RP_LIBEXPORT(const char*) rp_status_message(rp_status status);

RP_LIBEXPORT(const char*) rp_build_version();





#ifdef __cplusplus
}
#endif

#endif

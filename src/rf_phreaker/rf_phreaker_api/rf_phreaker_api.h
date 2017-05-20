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

const int32_t RP_SERIAL_LENGTH = 33;
const int32_t RP_FREQUENCY_PATH_SIZE = 100;
const int32_t PLMN_STRING_SIZE = 4;
const int32_t MAX_RAW_LAYER_3_BYTE_SIZE = 512;

typedef int64_t rp_frequency_type;

typedef int32_t rp_channel_type;

typedef int32_t rp_bandwidth_type;

typedef int64_t rp_time_type;

typedef enum rp_status {
	RP_STATUS_OK = 0,
	RP_STATUS_FREQUENCY_CORRECTION_SUCCESSFUL,
	RP_STATUS_FREQUENCY_CORRECTION_FAILED,
	RP_STATUS_FREQUENCY_CORRECTION_VALUE_INVALID,
	RP_STATUS_NOT_INITIALIZED,
	RP_STATUS_INVALID_PARAMETER,
	RP_STATUS_CALIBRATION_ERROR,
	RP_STATUS_EEPROM_ERROR,
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
	RP_STATUS_LICENSE_ERROR,
	RP_STATUS_CONFIGURATION_FILE_NOT_FOUND,
	RP_STATUS_CONVERSION_ERROR,
	RP_STATUS_COLLECTION_FINISHED,
	RP_STATUS_GENERIC_ERROR,
	RP_STATUS_UNKNOWN_ERROR
} rp_status;

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

typedef struct rp_power_spectrum_spec {
	rp_frequency_type start_frequency_;
	rp_frequency_type span_;
	rp_frequency_type bin_size_;
	rp_time_type dwell_time_;
} rp_power_spectrum_spec;

typedef struct rp_power_spectrum_spec_group {
	rp_power_spectrum_spec *e_;
	int32_t size_;
} rp_power_spectrum_spec_group;

typedef struct rp_iq_data_spec {
	rp_frequency_type center_frequency_;
	rp_bandwidth_type bandwidth_;
	rp_frequency_type sampling_rate_;
	rp_time_type dwell_time_;
} rp_iq_data_spec;

typedef struct rp_iq_spec_group {
	rp_iq_data_spec *e_;
	int32_t size_;
} rp_iq_data_spec_group;

typedef struct rp_collection_info {
	rp_frequency_band_group gsm_;
	rp_frequency_band_group wcdma_;
	rp_frequency_band_group lte_;
	rp_power_spectrum_spec_group power_spectrum_spec_;
	rp_iq_spec_group iq_data_;
	rp_operating_band_group sweep_;
} rp_collection_info;

typedef struct rp_device_info {
	rp_serial serial_;
	rp_device_communication device_communication_;
	int64_t frequency_correction_calibration_date_;
	int64_t rf_calibration_date_;
	int32_t num_frequency_paths_;
	rp_frequency_path frequency_paths_[RP_FREQUENCY_PATH_SIZE];
	int32_t num_licenses_;
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
	double altitude_;
	double angle_;
	double speed_;
	double dilution_of_precision_;
	double horizontal_accuracy_meters_;
	double vertical_accuracy_meters_;
	int64_t raw_status_;
} rp_gps;

typedef struct rp_base {
	rp_serial serial_;
	int64_t collection_round_;
	rp_frequency_type measurement_frequency_;
	rp_bandwidth_type measurement_bandwidth_;
	double measurement_signal_level_;
	rp_time_type time_;
	int32_t status_flags_;
} rp_base;

typedef struct rp_plmn {
	uint8_t mcc_[PLMN_STRING_SIZE];
	uint8_t mnc_[PLMN_STRING_SIZE];
} rp_plmn;

typedef struct rp_raw_layer_3 {
	uint8_t bytes_[MAX_RAW_LAYER_3_BYTE_SIZE];
	int32_t num_bytes_;
	int32_t unused_bits_;
} rp_raw_layer_3;

typedef enum rp_band_indicator_type {
	dcs_1800_was_used,
	pcs_1900_was_used,
	unknown_band_was_used
} rp_band_indicator_type;

typedef enum rp_duplex_type {
	fdd,
	tdd
} rp_duplex_type;

typedef enum rp_utran_bandwidth_type {
	utran_3_84_mcps,
	utran_1_24_mcps,
	utran_2_mcps,
	utran_3_mcps,
	utran_4_mcps,
	utran_5_mcps,
	utran_6_mcps,
	utran_7_mcps,
	utran_default_mcps = utran_3_84_mcps
} rp_utran_bandwidth_type;

typedef struct rp_gsm_utran_neighbor {
	rp_duplex_type duplexing_;
	int32_t arfcn_;
	rp_utran_bandwidth_type bandwidth_;
	int32_t num_scrambling_codes_;
	int32_t *scrambling_codes_;
} rp_gsm_utran_neighbor;


typedef enum rp_eutran_bandwidth_type {
	num_resource_blocks_6,
	num_resource_blocks_15,
	num_resource_blocks_25,
	num_resource_blocks_50,
	num_resource_blocks_75,
	num_resource_blocks_100
} rp_eutran_bandwidth_type;

typedef struct rp_pcid_group {
	int32_t num_pcids_;
	int32_t *pcids_;
} rp_pcid_group;

typedef struct rp_gsm_eutran_neighbor {
	int32_t earfcn_;
	rp_eutran_bandwidth_type bandwidth_;
	int32_t priority_;
	int32_t threshold_high_db_;
	int32_t threshold_low_db_;
	int32_t qrxlevmin_db_;
	rp_pcid_group pcids_allowed_;
	rp_pcid_group pcids_not_allowed_;
	int32_t num_pcids_same_tracking_area_;
	rp_pcid_group *pcids_same_tracking_area_;
	int32_t num_pcids_different_tracking_area_;
	rp_pcid_group *pcids_different_tracking_area_;
} rp_gsm_eutran_neighbor;

typedef struct rp_gsm_si1 {
	bool is_decoded_;
	rp_band_indicator_type band_indicator_;
} rp_gsm_si1;

typedef struct rp_gsm_si2 {
	bool is_decoded_;
	int32_t num_bcch_neighbors_;
	int32_t *bcch_neighbors_;
	bool extension_indication_;
	int32_t bcch_allocation_indication_;
} rp_gsm_si2;

typedef struct rp_gsm_si2_bis {
	bool is_decoded_;
	int32_t num_bcch_neighbors_;
	int32_t *bcch_neighbors_;
	bool extension_indication_;
	int32_t bcch_allocation_indication_;
	int32_t rest_octet_index_;
	int32_t rest_octet_count_;
} rp_gsm_si2_bis;

typedef struct rp_gsm_si2_ter {
	bool is_decoded_;
	int32_t num_extended_bcch_neighbors_;
	int32_t *extended_bcch_neighbors_;
	int32_t gsm_bcch_allocation_indication_;
	int32_t bcch_neighbors_multiband_reporting_;
	int32_t num_utran_neighbors_;
	rp_gsm_utran_neighbor *utran_neighbors_;
	int32_t rest_octet_index_;
	int32_t rest_octet_count_;
} rp_gsm_si2_ter;

typedef struct rp_gsm_si2_quater {
	bool is_decoded_;
	int32_t gsm_bcch_allocation_indication_;
	int32_t p3g_bcch_allocation_indication_;
	int32_t utran_neighbor_cell_index_start_3g_;
	int32_t utran_neighbor_cell_absolute_index_start_emr_;
	int32_t num_utran_neighbors_;
	rp_gsm_utran_neighbor *utran_neighbors_;
	int32_t num_eutran_neighbors_;
	rp_gsm_eutran_neighbor *eutran_neighbors_;
	int32_t rest_octet_index_;
	int32_t rest_octet_count_;
} rp_gsm_si2_quater;

typedef struct rp_gsm_selection_parameters {
	int32_t cbq_;
	int32_t cell_reselect_offset_db_; // actual range = 0-63 (0, 2, 4,...,126db)
	int32_t temporary_offset_db_; // actual range = 0-7 (0, 10, 20,...,60db, infinity)
	int32_t penalty_time_seconds_; // actual range = 0-31 (20, 40, 60,...,620 seconds)
	bool subtract_reselect_cell_offset_ignore_temp_offset_;
	bool apply_infinity_offset_;
} rp_gsm_selection_parameters;

typedef struct rp_gsm_si3 {
	bool is_decoded_;
	rp_plmn plmn_;
	int32_t location_area_code_;
	int32_t cell_id_;
	int32_t cell_reselect_hysteresis_db_;
	rp_gsm_selection_parameters selection_parameters_;
	int32_t bs_ag_blks_res_;
	bool is_2ter_present_;
	bool is_2quater_present_;
} rp_gsm_si3;

typedef struct rp_gsm_si4 {
	bool is_decoded_;
	rp_plmn plmn_;
	int32_t location_area_code_;
	int32_t cell_id_;
	int32_t cell_reselect_hysteresis_db_;
	rp_gsm_selection_parameters selection_parameters_;
	bool is_cbch_present_;
	bool have_additional_param_in_si7_si8_;
} rp_gsm_si4;

typedef struct rp_gsm_layer_3 {
	int32_t num_raw_layer_3_;
	rp_raw_layer_3 *raw_layer_3_;
	rp_gsm_si1 si1_;
	rp_gsm_si2 si2_;
	rp_gsm_si2_bis si2_bis_;
	rp_gsm_si2_ter si2_ter_;
	rp_gsm_si2_quater si2_quater_;
	rp_gsm_si3 si3_;
	rp_gsm_si4 si4_;
} rp_gsm_layer_3;

typedef struct rp_gsm {
	rp_base base_;
	rp_channel_type arfcn_;
	rp_operating_band operating_band_;
	int32_t bsic_;
	int32_t tdma_frame_number_;
	double bcch_signal_level_;
	double ctoi_;
	rp_gsm_layer_3 layer_3_;
} rp_gsm;


typedef struct rp_wcdma_utran_neighbor {
	int32_t uarfcn_;
	int32_t cpich_;
} rp_wcdma_neighbor_inter;

typedef struct rp_wcdma_gsm_neighbor {
	int32_t bsic_;
	rp_band_indicator_type band_indicator_;
	int32_t arfcn_;
	int32_t qrx_lev_min_;
} rp_wcdma_gsm_neighbor;

typedef struct rp_wcdma_mib {
	bool is_decoded_;
	rp_plmn plmn_;
	int32_t num_multiple_plmns_;
	rp_plmn *multiple_plmns_;
} rp_wcdma_mib;

typedef struct rp_wcdma_sib1 {
	bool is_decoded_;
	int32_t lac_;
} rp_wcdma_sib1;

typedef struct rp_wcdma_sib3 {
	bool is_decoded_;
	int32_t cid_;
} rp_wcdma_sib3;

typedef struct rp_wcdma_sib4 {
	bool is_decoded_;
	int32_t cid_;
} rp_wcdma_sib4;

typedef struct rp_wcdma_sib11 {
	bool is_decoded_;
	int32_t num_utran_intra_neighbor_cpichs_;
	int32_t *utran_intra_neighbor_cpichs_;
	int32_t num_utran_inter_neighbors_;
	rp_wcdma_utran_neighbor *utran_inter_neighbors_;
	int32_t num_gsm_inter_neighbors_;
	rp_wcdma_gsm_neighbor *gsm_inter_neighbors_;
} rp_wcdma_sib11;

typedef rp_wcdma_sib11 rp_wcdma_sib11_bis;

typedef struct rp_wcdma_layer_3 {
	int32_t num_raw_layer_3_;
	rp_raw_layer_3 *raw_layer_3_;
	rp_wcdma_mib mib_;
	rp_wcdma_sib1 sib1_;
	rp_wcdma_sib3 sib3_;
	rp_wcdma_sib4 sib4_;
	rp_wcdma_sib11 sib11_;
	rp_wcdma_sib11_bis sib11_bis_;
} rp_wcdma_layer_3;

typedef struct rp_wcdma {
	rp_base base_;
	rp_channel_type uarfcn_;
	rp_operating_band operating_band_;
	int32_t cpich_;
	double ecio_;
	double rscp_;
	rp_wcdma_layer_3 layer_3_;
} rp_wcdma;


typedef enum rp_lte_sib_type {
	LTE_SIB1,
	LTE_SIB2,
	LTE_SIB3,
	LTE_SIB4,
	LTE_SIB5,
	LTE_SIB6,
	LTE_SIB7,
	LTE_SIB8,
	LTE_SIB9,
	LTE_SIB10,
	LTE_SIB11,
	LTE_SIB12_V920,
	LTE_SIB13_V920,
	LTE_SIB14_V1130,
	LTE_SIB15_V1130,
	LTE_SIB16_V1130,
	LTE_SPARE2,
	LTE_SPARE1
} rp_lte_sib_type;

typedef struct rp_lte_scheduling_info {
	int32_t periodicity_in_frames_;
	int32_t num_sibs_;
	rp_lte_sib_type *sibs;
} rp_lte_scheduling_info;

typedef struct rp_lte_sib1 {
	bool is_decoded_;
	int32_t num_multiple_plmns_;
	rp_plmn *multiple_plmns_;
	int32_t tac_;
	int32_t cid_;
	int32_t num_scheduling_info_;
	rp_lte_scheduling_info *scheduling_info_;
	int32_t si_window_length_ms_;
} rp_lte_sib1;

typedef struct rp_lte_cell_reselection_serving_freq_info {
	int32_t s_non_intra_search_; // reselection_threshold
	int32_t threshold_serving_low_; // reselection_threshold
	int32_t cell_reselection_priority_;
} rp_lte_cell_reselection_serving_freq_info;

typedef struct rp_lte_s_search_v920 {
	int32_t p_; 
	int32_t q_; 
} rp_lte_s_search_v920;

typedef struct rp_lte_sib3 {
	bool is_decoded_;
	rp_lte_cell_reselection_serving_freq_info cell_reselection_serving_freq_info_;
	int32_t intra_freq_cell_reselection_info_s_intra_search_;
	rp_lte_s_search_v920 s_intra_search_v920_;
	rp_lte_s_search_v920 s_non_intra_search_v920_;
	int32_t threshold_serving_low_q_;
} rp_lte_sib3;

typedef struct rp_lte_physical_cellid_range {
	int32_t start_;
	int32_t range_;
} rp_lte_physical_cellid_range;

typedef struct rp_lte_neighbor_cell {
	int32_t physical_cell_id_;
	int32_t q_offset_cell_;
} rp_lte_neighbor_cell;

typedef struct rp_lte_sib4 {
	bool is_decoded_;
	int32_t num_intra_freq_neighbor_cell_list_;
	rp_lte_neighbor_cell *intra_freq_neighbor_cell_list_;
	int32_t num_intra_freq_black_cell_list_;
	rp_lte_physical_cellid_range *intra_freq_black_cell_list_;
	rp_lte_physical_cellid_range csg_physical_cellid_range_;
} rp_lte_sib4;

typedef struct rp_lte_inter_freq_carrier_freq_info {
	int32_t downlink_arfcn_value_eutra_;
	int32_t q_rx_lev_min_;
	int32_t q_offset_freq_;
	int32_t allowed_measurement_bandwidth_;
	bool presence_antenna_port_1_;
	int32_t threshold_x_high_;
	int32_t threshold_x_low_;
	int32_t threshold_x_high_q_r9_;
	int32_t threshold_x_low_q_r9_;
	int32_t cell_reselection_priority_;
	int32_t num_inter_freq_neighbor_cell_list_;
	rp_lte_neighbor_cell *inter_freq_neighbor_cell_list_;
	int32_t num_inter_freq_black_cell_list_;
	rp_lte_physical_cellid_range *inter_freq_black_cell_list_;
} rp_lte_inter_freq_carrier_freq_info;

typedef struct rp_lte_sib5 {
	bool is_decoded_;
	int32_t num_inter_freq_carrier_info_list_;
	rp_lte_inter_freq_carrier_freq_info *inter_freq_carrier_info_list_;
} rp_lte_sib5;

typedef struct rp_lte_carrier_freq_utra {
	int32_t arfcn_value_utra_;
	int32_t threshold_x_low_;
	int32_t threshold_x_high_;
	int32_t threshold_x_low_q_r9_;
	int32_t threshold_x_high_q_r9_;
	int32_t cell_reselection_priority_;
} rp_lte_carrier_freq_utra;

typedef struct rp_lte_sib6 {
	bool is_decoded_;
	int32_t num_carrier_freq_list_utra_fdd_;
	rp_lte_carrier_freq_utra *carrier_freq_list_utra_fdd_;
	int32_t num_carrier_freq_list_utra_tdd_;
	rp_lte_carrier_freq_utra *carrier_freq_list_utra_tdd_;
} rp_lte_sib6;

typedef struct rp_lte_carrier_freqs_geran{
	rp_band_indicator_type band_indicator_;
	int32_t num_arfcns_;
	int32_t *arfcns_;
} rp_lte_carrier_freqs_geran;

typedef struct rp_lte_geran_common_info {
	int32_t cell_reselection_priority_;
	int32_t threshold_x_high_;
	int32_t threshold_x_low_;
} rp_lte_geran_common_info;

typedef struct rp_lte_carrier_freqs_info_geran {
	rp_lte_carrier_freqs_geran carrier_freqs_;
	rp_lte_geran_common_info common_info_;
} rp_lte_carrier_freqs_info_geran;

typedef struct rp_lte_sib7 {
	bool is_decoded_;
	int32_t num_carrier_freqs_info_list_geran_;
	rp_lte_carrier_freqs_info_geran *carrier_freqs_info_list_geran_;
} rp_lte_sib7;

typedef struct rp_lte_neighbor_cells_per_band_class_cdma_2000 {
	int32_t arfcn_value_cmda_2000_;
	int32_t num_physical_cell_ids_;
	int32_t *physical_cell_ids_;
} rp_lte_neighbor_cells_per_band_class_cdma_2000;

typedef enum rp_lte_band_class_cmda_2000_type {
	bc0,
	bc1,
	bc2,
	bc3,
	bc4,
	bc5,
	bc6,
	bc7,
	bc8,
	bc9,
	bc10,
	bc11,
	bc12,
	bc13,
	bc14,
	bc15,
	bc16,
	bc17,
	bc18_v9a0,
	bc19_v9a0,
	bc20_v9a0,
	bc21_v9a0,
	spare10,
	spare9,
	spare8,
	spare7,
	spare6,
	spare5,
	spare4,
	spare3,
	spare2,
	spare1
} rp_lte_band_class_cmda_2000_type;

typedef struct rp_lte_neighbor_cell_cdma_2000{
	rp_lte_band_class_cmda_2000_type band_;
	int32_t num_neighbor_cells_per_freq_list_;
	rp_lte_neighbor_cells_per_band_class_cdma_2000 *neighbor_cells_per_freq_list_;
} rp_lte_neighbor_cell_cdma_2000;

typedef struct rp_lte_cell_reselection_parameters_cmda_2000 {
	int32_t num_neighbor_cell_list_;
	rp_lte_neighbor_cell_cdma_2000 *neighbor_cell_list_;
} rp_lte_cell_reselection_parameters_cmda_2000;

typedef struct rp_lte_sib8 {
	bool is_decoded_;
	rp_lte_cell_reselection_parameters_cmda_2000 parameters_hrpd_;
	rp_lte_cell_reselection_parameters_cmda_2000 parameters_1xrtt_;
} rp_lte_sib8;

typedef struct rp_lte_layer_3 {
	int32_t num_raw_layer_3_;
	rp_raw_layer_3 *raw_layer_3_;
	rp_lte_sib1 sib1_;
	rp_lte_sib1 sib2_;
	rp_lte_sib3 sib3_;
	rp_lte_sib4 sib4_;
	rp_lte_sib5 sib5_;
	rp_lte_sib6 sib6_;
	rp_lte_sib7 sib7_;
	rp_lte_sib8 sib8_;
} rp_lte_layer_3;

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
	rp_lte_layer_3 layer_3_;
} rp_lte;


typedef struct rp_power_spectrum {
	rp_base base_;
	rp_time_type dwell_time_;
	rp_frequency_type sampling_rate_;
	rp_frequency_type start_frequency_;
	rp_frequency_type end_frequency_;
	rp_frequency_type span_;
	int32_t window_length_;
	int32_t num_windows_;
	int32_t bin_size_;
	int32_t step_size_;
	int32_t num_power_;
	double *power_;
} rp_power_spectrum;


typedef enum rp_sample_format_type {
	LITTLE_ENDIAN_FLOAT_REAL_IMAGINARY,
	BIG_ENDIAN_FLOAT_REAL_IMAGINARY
} rp_sample_format_type;

typedef struct power_adjustment {
	rp_frequency_path path_;
	rp_frequency_type step_size_;
	int32_t num_power_;
	double *power_;
} rp_power_adjustment;

typedef struct rp_iq_data {
	rp_base base_;
	rp_time_type dwell_time_;
	rp_sample_format_type sample_format_;
	rp_frequency_type sampling_rate_;
	power_adjustment power_adjustment_;
	int32_t num_samples_;
	void *samples_;
} rp_iq_data;


typedef struct rp_callbacks {
	void (RP_CALLCONV *rp_update)(const int8_t *google_protocol_buffer_stream, int32_t size);

	void (RP_CALLCONV *rp_log_update)(const char *message);

	void (RP_CALLCONV *rp_message_update)(rp_status status, const char *message);

	void (RP_CALLCONV *rp_device_info_update)(const rp_device_info *info);

	void (RP_CALLCONV *rp_gps_update)(const rp_gps *gps);

	void (RP_CALLCONV *rp_gsm_sweep_update)(const rp_base *base, const rp_gsm *gsm, int32_t num_gsm);

	void (RP_CALLCONV *rp_gsm_full_scan_update)(const rp_base *base, const rp_gsm *gsm, int32_t num_gsm);

	void (RP_CALLCONV *rp_wcdma_sweep_update)(const rp_base *base, const rp_wcdma *umts, int32_t num_umts);

	void (RP_CALLCONV *rp_wcdma_full_scan_update)(const rp_base *base, const rp_wcdma *wcdma, int32_t num_wcdma);

	void (RP_CALLCONV *rp_lte_sweep_update)(const rp_base *base, const rp_lte *lte, int32_t num_lte);

	void (RP_CALLCONV *rp_lte_full_scan_update)(const rp_base *base, const rp_lte *lte, int32_t num_lte);

	void (RP_CALLCONV *rp_power_spectrum_update)(const rp_power_spectrum *spec);

	void (RP_CALLCONV *rp_iq_data_update)(const rp_iq_data *iq);
} rp_callbacks;

RP_LIBEXPORT(rp_status) rp_initialize(rp_callbacks *callbacks);

RP_LIBEXPORT(rp_status) rp_clean_up();

RP_LIBEXPORT(rp_status) rp_list_devices(rp_serial *serials, int32_t *num_serials);

RP_LIBEXPORT(rp_status) rp_connect_device(rp_serial serial, rp_device **device);

RP_LIBEXPORT(rp_status) rp_disconnect_device(rp_device *device);

RP_LIBEXPORT(bool) rp_is_device_open(rp_device *device);

RP_LIBEXPORT(rp_status) rp_get_device_info(rp_device *device, rp_device_info *device_info);

RP_LIBEXPORT(rp_status) rp_start_collection(rp_device *device, const rp_collection_info *info);

RP_LIBEXPORT(rp_status) rp_stop_collection(rp_device *device);

RP_LIBEXPORT(rp_status) rp_get_gps_data(rp_device *device, rp_gps gps);

RP_LIBEXPORT(rp_status) rp_get_iq_data(rp_device *device, rp_frequency_type frequency, rp_time_type dwell_time_ns, rp_bandwidth_type bandwidth, rp_frequency_type sampling_rate, int32_t gain_db, rp_iq_data *iq_data);

RP_LIBEXPORT(rp_status) rp_update_license(rp_device *device, const char *filename);

RP_LIBEXPORT(const char*) rp_status_message(rp_status status);

RP_LIBEXPORT(const char*) rp_last_error_message();

RP_LIBEXPORT(const char*) rp_build_version();





#ifdef __cplusplus
}
#endif

#endif

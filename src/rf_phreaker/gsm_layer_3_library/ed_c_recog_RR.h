/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.152
	GENERATOR: ed-c-recog
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __ed_c_recog_RR_h
#define __ed_c_recog_RR_h
#include "ed_c_RR.h"
#if ED_VERSION != 10152
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.152
#endif

#include "ed_user.h"
#define ED_MAXSIZE 600
#include "endec_configs_RR.h"

#ifdef __cplusplus
	extern "C" {
#endif

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group RRDownlink
--------------------------------------------------------------------*/
typedef enum {
	ID_RRDownlink_Unrecognized = 0,
	ID_RRDownlink_ADDITIONAL_ASSIGNMENT_DN,
	ID_RRDownlink_ASSIGNMENT_COMMAND_DN,
	ID_RRDownlink_CHANNEL_MODE_MODIFY_DN,
	ID_RRDownlink_CHANNEL_RELEASE_DN,
	ID_RRDownlink_CIPHERING_MODE_COMMAND_DN,
	ID_RRDownlink_CLASSMARK_ENQUIRY_DN,
	ID_RRDownlink_CONFIGURATION_CHANGE_COMMAND_DN,
	ID_RRDownlink_DTM_ASSIGNMENT_COMMAND_DN,
	ID_RRDownlink_DTM_INFORMATION_DN,
	ID_RRDownlink_DTM_REJECT_DN,
	ID_RRDownlink_FREQUENCY_REDEFINITION_DN,
	ID_RRDownlink_PDCH_ASSIGNMENT_COMMAND_DN,
	ID_RRDownlink_HANDOVER_COMMAND_DN,
	ID_RRDownlink_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN,
	ID_RRDownlink_INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN,
	ID_RRDownlink_HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN,
	ID_RRDownlink_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN,
	ID_RRDownlink_RR_CELL_CHANGE_ORDER_DN,
	ID_RRDownlink_PACKET_ASSIGNMENT_DN,
	ID_RRDownlink_PACKET_NOTIFICATION_DN,
	ID_RRDownlink_PARTIAL_RELEASE_DN,
	ID_RRDownlink_PHYSICAL_INFORMATION_DN,
	ID_RRDownlink_RR_STATUS,
	ID_RRDownlink_UPLINK_BUSY_DN,
	ID_RRDownlink_UPLINK_RELEASE,
	ID_RRDownlink_VGCS_DNLINK_GRANT_DN,
	ID_RRDownlink_APPLICATION_INFORMATION
} TRRDownlink_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group RRDownlink
--------------------------------------------------------------------*/
typedef struct {
	TRRDownlink_Type Type;
	int SkipIndicator;
	int ProtocolDiscriminator;
	int MessageType;
	union {
		c_ADDITIONAL_ASSIGNMENT_DN* fld_c_ADDITIONAL_ASSIGNMENT_DN;
		c_ASSIGNMENT_COMMAND_DN* fld_c_ASSIGNMENT_COMMAND_DN;
		c_CHANNEL_MODE_MODIFY_DN* fld_c_CHANNEL_MODE_MODIFY_DN;
		c_CHANNEL_RELEASE_DN* fld_c_CHANNEL_RELEASE_DN;
		c_CIPHERING_MODE_COMMAND_DN* fld_c_CIPHERING_MODE_COMMAND_DN;
		c_CLASSMARK_ENQUIRY_DN* fld_c_CLASSMARK_ENQUIRY_DN;
		c_CONFIGURATION_CHANGE_COMMAND_DN* fld_c_CONFIGURATION_CHANGE_COMMAND_DN;
		c_DTM_ASSIGNMENT_COMMAND_DN* fld_c_DTM_ASSIGNMENT_COMMAND_DN;
		c_DTM_INFORMATION_DN* fld_c_DTM_INFORMATION_DN;
		c_DTM_REJECT_DN* fld_c_DTM_REJECT_DN;
		c_FREQUENCY_REDEFINITION_DN* fld_c_FREQUENCY_REDEFINITION_DN;
		c_PDCH_ASSIGNMENT_COMMAND_DN* fld_c_PDCH_ASSIGNMENT_COMMAND_DN;
		c_HANDOVER_COMMAND_DN* fld_c_HANDOVER_COMMAND_DN;
		c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN* fld_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN;
		c_INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN* fld_c_INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN;
		c_HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN* fld_c_HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN;
		c_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN* fld_c_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN;
		c_RR_CELL_CHANGE_ORDER_DN* fld_c_RR_CELL_CHANGE_ORDER_DN;
		c_PACKET_ASSIGNMENT_DN* fld_c_PACKET_ASSIGNMENT_DN;
		c_PACKET_NOTIFICATION_DN* fld_c_PACKET_NOTIFICATION_DN;
		c_PARTIAL_RELEASE_DN* fld_c_PARTIAL_RELEASE_DN;
		c_PHYSICAL_INFORMATION_DN* fld_c_PHYSICAL_INFORMATION_DN;
		c_RR_STATUS* fld_c_RR_STATUS;
		c_UPLINK_BUSY_DN* fld_c_UPLINK_BUSY_DN;
		c_UPLINK_RELEASE* fld_c_UPLINK_RELEASE;
		c_VGCS_DNLINK_GRANT_DN* fld_c_VGCS_DNLINK_GRANT_DN;
		c_APPLICATION_INFORMATION* fld_c_APPLICATION_INFORMATION;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TRRDownlink_Data;
#define INIT_TRRDownlink_Data(sp) (ED_RESET_MEM ((sp), sizeof (TRRDownlink_Data)), (sp)->Type=ID_RRDownlink_Unrecognized)
void FREE_TRRDownlink_Data (TRRDownlink_Data* sp);

void SETPRESENT_TRRDownlink_Data(TRRDownlink_Data* sp, TRRDownlink_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group RRUplink
--------------------------------------------------------------------*/
typedef enum {
	ID_RRUplink_Unrecognized = 0,
	ID_RRUplink_ASSIGNMENT_COMPLETE_UP,
	ID_RRUplink_ASSIGNMENT_FAILURE_UP,
	ID_RRUplink_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP,
	ID_RRUplink_CIPHERING_MODE_COMPLETE_UP,
	ID_RRUplink_CLASSMARK_CHANGE_UP,
	ID_RRUplink_UTRAN_CLASSMARK_CHANGE_UP,
	ID_RRUplink_CDMA2000_CLASSMARK_CHANGE_UP,
	ID_RRUplink_GERAN_IU_MODE_CLASSMARK_CHANGE_UP,
	ID_RRUplink_CONFIGURATION_CHANGE_ACKNOWLEDGE_UP,
	ID_RRUplink_CONFIGURATION_CHANGE_REJECT_UP,
	ID_RRUplink_DTM_ASSIGNMENT_COMMAND_UP,
	ID_RRUplink_DTM_ASSIGNMENT_FAILURE_UP,
	ID_RRUplink_DTM_REQUEST_UP,
	ID_RRUplink_GPRS_SUSPENSION_REQUEST_UP,
	ID_RRUplink_HANDOVER_COMPLETE_UP,
	ID_RRUplink_HANDOVER_FAILURE_UP,
	ID_RRUplink_MEASUREMENT_REPORT_UP,
	ID_RRUplink_NOTIFICATION_RESPONSE_UP,
	ID_RRUplink_PAGING_RESPONSE_UP,
	ID_RRUplink_PARTIAL_RELEASE_COMPLETE_UP,
	ID_RRUplink_RR_INITIALISATION_REQUEST_UP,
	ID_RRUplink_RR_STATUS,
	ID_RRUplink_TALKER_INDICATION_UP,
	ID_RRUplink_PRIORITY_DNLINK_REQUEST,
	ID_RRUplink_DATA_INDICATION,
	ID_RRUplink_DATA_INDICATION_2,
	ID_RRUplink_UPLINK_RELEASE,
	ID_RRUplink_EXTENDED_MEASUREMENT_REPORT_UP,
	ID_RRUplink_APPLICATION_INFORMATION
} TRRUplink_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group RRUplink
--------------------------------------------------------------------*/
typedef struct {
	TRRUplink_Type Type;
	int SkipIndicator;
	int ProtocolDiscriminator;
	int MessageType;
	union {
		c_ASSIGNMENT_COMPLETE_UP* fld_c_ASSIGNMENT_COMPLETE_UP;
		c_ASSIGNMENT_FAILURE_UP* fld_c_ASSIGNMENT_FAILURE_UP;
		c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP* fld_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP;
		c_CIPHERING_MODE_COMPLETE_UP* fld_c_CIPHERING_MODE_COMPLETE_UP;
		c_CLASSMARK_CHANGE_UP* fld_c_CLASSMARK_CHANGE_UP;
		c_UTRAN_CLASSMARK_CHANGE_UP* fld_c_UTRAN_CLASSMARK_CHANGE_UP;
		c_CDMA2000_CLASSMARK_CHANGE_UP* fld_c_CDMA2000_CLASSMARK_CHANGE_UP;
		c_GERAN_IU_MODE_CLASSMARK_CHANGE_UP* fld_c_GERAN_IU_MODE_CLASSMARK_CHANGE_UP;
		c_CONFIGURATION_CHANGE_ACKNOWLEDGE_UP* fld_c_CONFIGURATION_CHANGE_ACKNOWLEDGE_UP;
		c_CONFIGURATION_CHANGE_REJECT_UP* fld_c_CONFIGURATION_CHANGE_REJECT_UP;
		c_DTM_ASSIGNMENT_COMMAND_UP* fld_c_DTM_ASSIGNMENT_COMMAND_UP;
		c_DTM_ASSIGNMENT_FAILURE_UP* fld_c_DTM_ASSIGNMENT_FAILURE_UP;
		c_DTM_REQUEST_UP* fld_c_DTM_REQUEST_UP;
		c_GPRS_SUSPENSION_REQUEST_UP* fld_c_GPRS_SUSPENSION_REQUEST_UP;
		c_HANDOVER_COMPLETE_UP* fld_c_HANDOVER_COMPLETE_UP;
		c_HANDOVER_FAILURE_UP* fld_c_HANDOVER_FAILURE_UP;
		c_MEASUREMENT_REPORT_UP* fld_c_MEASUREMENT_REPORT_UP;
		c_NOTIFICATION_RESPONSE_UP* fld_c_NOTIFICATION_RESPONSE_UP;
		c_PAGING_RESPONSE_UP* fld_c_PAGING_RESPONSE_UP;
		c_PARTIAL_RELEASE_COMPLETE_UP* fld_c_PARTIAL_RELEASE_COMPLETE_UP;
		c_RR_INITIALISATION_REQUEST_UP* fld_c_RR_INITIALISATION_REQUEST_UP;
		c_RR_STATUS* fld_c_RR_STATUS;
		c_TALKER_INDICATION_UP* fld_c_TALKER_INDICATION_UP;
		c_PRIORITY_DNLINK_REQUEST* fld_c_PRIORITY_DNLINK_REQUEST;
		c_DATA_INDICATION* fld_c_DATA_INDICATION;
		c_DATA_INDICATION_2* fld_c_DATA_INDICATION_2;
		c_UPLINK_RELEASE* fld_c_UPLINK_RELEASE;
		c_EXTENDED_MEASUREMENT_REPORT_UP* fld_c_EXTENDED_MEASUREMENT_REPORT_UP;
		c_APPLICATION_INFORMATION* fld_c_APPLICATION_INFORMATION;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TRRUplink_Data;
#define INIT_TRRUplink_Data(sp) (ED_RESET_MEM ((sp), sizeof (TRRUplink_Data)), (sp)->Type=ID_RRUplink_Unrecognized)
void FREE_TRRUplink_Data (TRRUplink_Data* sp);

void SETPRESENT_TRRUplink_Data(TRRUplink_Data* sp, TRRUplink_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group RRPLENDownlink
--------------------------------------------------------------------*/
typedef enum {
	ID_RRPLENDownlink_Unrecognized = 0,
	ID_RRPLENDownlink_IMMEDIATE_ASSIGNMENT_DN,
	ID_RRPLENDownlink_IMMEDIATE_PACKET_ASSIGNMENT_DN,
	ID_RRPLENDownlink_IMMEDIATE_ASSIGNMENT_EXTENDED_DN,
	ID_RRPLENDownlink_IMMEDIATE_ASSIGNMENT_REJECT_DN,
	ID_RRPLENDownlink_NOTIFICATION_NCH_DN,
	ID_RRPLENDownlink_PAGING_REQUEST_TYPE_1_DN,
	ID_RRPLENDownlink_PAGING_REQUEST_TYPE_2_DN,
	ID_RRPLENDownlink_PAGING_REQUEST_TYPE_3_DN,
	ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_1_DN,
	ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_2_DN,
	ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_2BIS_DN,
	ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_2TER_DN,
	ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_2QUATER_DN,
	ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_3_DN,
	ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_4_DN,
	ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_5_DN,
	ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_5BIS_DN,
	ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_5TER_DN,
	ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_6_DN,
	ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_7_DN,
	ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_8_DN,
	ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_9_DN,
	ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_13_DN,
	ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_16_DN,
	ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_17_DN,
	ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_19_DN,
	ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_18_DN,
	ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_20_DN,
	ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_14_DN,
	ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_15_DN,
	ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_13alt_DN,
	ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_21_DN,
	ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_22_DN,
	ID_RRPLENDownlink_SYSTEM_INFORMATION_TYPE_23_DN,
	ID_RRPLENDownlink_EXTENDED_MEASUREMENT_ORDER_DN
} TRRPLENDownlink_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group RRPLENDownlink
--------------------------------------------------------------------*/
typedef struct {
	TRRPLENDownlink_Type Type;
	int SkipIndicator;
	int ProtocolDiscriminator;
	int MessageType;
	union {
		c_IMMEDIATE_ASSIGNMENT_DN* fld_c_IMMEDIATE_ASSIGNMENT_DN;
		c_IMMEDIATE_PACKET_ASSIGNMENT_DN* fld_c_IMMEDIATE_PACKET_ASSIGNMENT_DN;
		c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN* fld_c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN;
		c_IMMEDIATE_ASSIGNMENT_REJECT_DN* fld_c_IMMEDIATE_ASSIGNMENT_REJECT_DN;
		c_NOTIFICATION_NCH_DN* fld_c_NOTIFICATION_NCH_DN;
		c_PAGING_REQUEST_TYPE_1_DN* fld_c_PAGING_REQUEST_TYPE_1_DN;
		c_PAGING_REQUEST_TYPE_2_DN* fld_c_PAGING_REQUEST_TYPE_2_DN;
		c_PAGING_REQUEST_TYPE_3_DN* fld_c_PAGING_REQUEST_TYPE_3_DN;
		c_SYSTEM_INFORMATION_TYPE_1_DN* fld_c_SYSTEM_INFORMATION_TYPE_1_DN;
		c_SYSTEM_INFORMATION_TYPE_2_DN* fld_c_SYSTEM_INFORMATION_TYPE_2_DN;
		c_SYSTEM_INFORMATION_TYPE_2BIS_DN* fld_c_SYSTEM_INFORMATION_TYPE_2BIS_DN;
		c_SYSTEM_INFORMATION_TYPE_2TER_DN* fld_c_SYSTEM_INFORMATION_TYPE_2TER_DN;
		c_SYSTEM_INFORMATION_TYPE_2QUATER_DN* fld_c_SYSTEM_INFORMATION_TYPE_2QUATER_DN;
		c_SYSTEM_INFORMATION_TYPE_3_DN* fld_c_SYSTEM_INFORMATION_TYPE_3_DN;
		c_SYSTEM_INFORMATION_TYPE_4_DN* fld_c_SYSTEM_INFORMATION_TYPE_4_DN;
		c_SYSTEM_INFORMATION_TYPE_5_DN* fld_c_SYSTEM_INFORMATION_TYPE_5_DN;
		c_SYSTEM_INFORMATION_TYPE_5BIS_DN* fld_c_SYSTEM_INFORMATION_TYPE_5BIS_DN;
		c_SYSTEM_INFORMATION_TYPE_5TER_DN* fld_c_SYSTEM_INFORMATION_TYPE_5TER_DN;
		c_SYSTEM_INFORMATION_TYPE_6_DN* fld_c_SYSTEM_INFORMATION_TYPE_6_DN;
		c_SYSTEM_INFORMATION_TYPE_7_DN* fld_c_SYSTEM_INFORMATION_TYPE_7_DN;
		c_SYSTEM_INFORMATION_TYPE_8_DN* fld_c_SYSTEM_INFORMATION_TYPE_8_DN;
		c_SYSTEM_INFORMATION_TYPE_9_DN* fld_c_SYSTEM_INFORMATION_TYPE_9_DN;
		c_SYSTEM_INFORMATION_TYPE_13_DN* fld_c_SYSTEM_INFORMATION_TYPE_13_DN;
		c_SYSTEM_INFORMATION_TYPE_16_DN* fld_c_SYSTEM_INFORMATION_TYPE_16_DN;
		c_SYSTEM_INFORMATION_TYPE_17_DN* fld_c_SYSTEM_INFORMATION_TYPE_17_DN;
		c_SYSTEM_INFORMATION_TYPE_19_DN* fld_c_SYSTEM_INFORMATION_TYPE_19_DN;
		c_SYSTEM_INFORMATION_TYPE_18_DN* fld_c_SYSTEM_INFORMATION_TYPE_18_DN;
		c_SYSTEM_INFORMATION_TYPE_20_DN* fld_c_SYSTEM_INFORMATION_TYPE_20_DN;
		c_SYSTEM_INFORMATION_TYPE_14_DN* fld_c_SYSTEM_INFORMATION_TYPE_14_DN;
		c_SYSTEM_INFORMATION_TYPE_15_DN* fld_c_SYSTEM_INFORMATION_TYPE_15_DN;
		c_SYSTEM_INFORMATION_TYPE_13alt_DN* fld_c_SYSTEM_INFORMATION_TYPE_13alt_DN;
		c_SYSTEM_INFORMATION_TYPE_21_DN* fld_c_SYSTEM_INFORMATION_TYPE_21_DN;
		c_SYSTEM_INFORMATION_TYPE_22_DN* fld_c_SYSTEM_INFORMATION_TYPE_22_DN;
		c_SYSTEM_INFORMATION_TYPE_23_DN* fld_c_SYSTEM_INFORMATION_TYPE_23_DN;
		c_EXTENDED_MEASUREMENT_ORDER_DN* fld_c_EXTENDED_MEASUREMENT_ORDER_DN;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TRRPLENDownlink_Data;
#define INIT_TRRPLENDownlink_Data(sp) (ED_RESET_MEM ((sp), sizeof (TRRPLENDownlink_Data)), (sp)->Type=ID_RRPLENDownlink_Unrecognized)
void FREE_TRRPLENDownlink_Data (TRRPLENDownlink_Data* sp);

void SETPRESENT_TRRPLENDownlink_Data(TRRPLENDownlink_Data* sp, TRRPLENDownlink_Type toBeSetPresent);

/*--------------------------------------------------------------------
	Enum representing a tag for every message in group RRShortPD
--------------------------------------------------------------------*/
typedef enum {
	ID_RRShortPD_Unrecognized = 0,
	ID_RRShortPD_NOTIFICATION_FACCH,
	ID_RRShortPD_VBS_VGCS_RECONFIGURE,
	ID_RRShortPD_VBS_VGCS_RECONFIGURE2,
	ID_RRShortPD_UPLINK_FREE,
	ID_RRShortPD_VGCS_ADDITIONAL_INFORMATION,
	ID_RRShortPD_VGCS_SMS_INFORMATION,
	ID_RRShortPD_SYSTEM_INFORMATION_TYPE_10_UP,
	ID_RRShortPD_SYSTEM_INFORMATION_TYPE_10bis_UP,
	ID_RRShortPD_SYSTEM_INFORMATION_TYPE_10ter_UP,
	ID_RRShortPD_MEASUREMENT_INFORMATION,
	ID_RRShortPD_ENHANCED_MEASUREMENT_REPORT,
	ID_RRShortPD_VGCS_NEIGHBOUR_CELL_INFORMATION,
	ID_RRShortPD_NOTIFY_APPLICATION_DATA
} TRRShortPD_Type;

/*--------------------------------------------------------------------
	Union containing data for every message in group RRShortPD
--------------------------------------------------------------------*/
typedef struct {
	TRRShortPD_Type Type;
	int MessageType;
	union {
		c_NOTIFICATION_FACCH* fld_c_NOTIFICATION_FACCH;
		c_VBS_VGCS_RECONFIGURE* fld_c_VBS_VGCS_RECONFIGURE;
		c_VBS_VGCS_RECONFIGURE2* fld_c_VBS_VGCS_RECONFIGURE2;
		c_UPLINK_FREE* fld_c_UPLINK_FREE;
		c_VGCS_ADDITIONAL_INFORMATION* fld_c_VGCS_ADDITIONAL_INFORMATION;
		c_VGCS_SMS_INFORMATION* fld_c_VGCS_SMS_INFORMATION;
		c_SYSTEM_INFORMATION_TYPE_10_UP* fld_c_SYSTEM_INFORMATION_TYPE_10_UP;
		c_SYSTEM_INFORMATION_TYPE_10bis_UP* fld_c_SYSTEM_INFORMATION_TYPE_10bis_UP;
		c_SYSTEM_INFORMATION_TYPE_10ter_UP* fld_c_SYSTEM_INFORMATION_TYPE_10ter_UP;
		c_MEASUREMENT_INFORMATION* fld_c_MEASUREMENT_INFORMATION;
		c_ENHANCED_MEASUREMENT_REPORT* fld_c_ENHANCED_MEASUREMENT_REPORT;
		c_VGCS_NEIGHBOUR_CELL_INFORMATION* fld_c_VGCS_NEIGHBOUR_CELL_INFORMATION;
		c_NOTIFY_APPLICATION_DATA* fld_c_NOTIFY_APPLICATION_DATA;
		char Dummy; /* Avoids empty unions! */
	} Data;
} TRRShortPD_Data;
#define INIT_TRRShortPD_Data(sp) (ED_RESET_MEM ((sp), sizeof (TRRShortPD_Data)), (sp)->Type=ID_RRShortPD_Unrecognized)
void FREE_TRRShortPD_Data (TRRShortPD_Data* sp);

void SETPRESENT_TRRShortPD_Data(TRRShortPD_Data* sp, TRRShortPD_Type toBeSetPresent);


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_RRDownlink (const char* buffer, TRRDownlink_Data* data, int bitLen);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RRDownlink (const char* buffer, int len, TRRDownlink_Data* data);
#endif


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_RRUplink (const char* buffer, TRRUplink_Data* data, int bitLen);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RRUplink (const char* buffer, int len, TRRUplink_Data* data);
#endif


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_RRPLENDownlink (const char* buffer, TRRPLENDownlink_Data* data, int bitLen);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RRPLENDownlink (const char* buffer, int len, TRRPLENDownlink_Data* data);
#endif


/*-------------------------------------------------------------------------------
	Returns number of consumed bits (>=0) if recognized. <0 otherwise.
	Parameter 'len' is expressed in octets, while 'bitLen' is in bits.

-------------------------------------------------------------------------------*/
int SetDecode_RRShortPD (const char* buffer, TRRShortPD_Data* data, int bitLen);

/* Maintains compatibility with Encodix 1.0.33 and before */
#ifndef ED_EXCLUDE_1_0_33_COMPATIBILITY
	int Decode_RRShortPD (const char* buffer, int len, TRRShortPD_Data* data);
#endif

#ifdef __cplusplus
	}
#endif
#endif


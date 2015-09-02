/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.152
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __RRUplink_RR_h
#define __RRUplink_RR_h
#include "ed_lib.h"
#include "ed_c_RR.h"
#include "ed_user.h"
#include "endec_configs_RR.h"
#if ED_VERSION != 10152
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.152
#endif


#ifdef __cplusplus
	extern "C" {
#endif

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "ASSIGNMENT_COMPLETE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_ASSIGNMENT_COMPLETE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ASSIGNMENT_COMPLETE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_ASSIGNMENT_COMPLETE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ASSIGNMENT_COMPLETE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "ASSIGNMENT_COMPLETE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_ASSIGNMENT_COMPLETE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ASSIGNMENT_COMPLETE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_ASSIGNMENT_COMPLETE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ASSIGNMENT_COMPLETE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "ASSIGNMENT_FAILURE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_ASSIGNMENT_FAILURE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ASSIGNMENT_FAILURE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_ASSIGNMENT_FAILURE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ASSIGNMENT_FAILURE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "ASSIGNMENT_FAILURE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_ASSIGNMENT_FAILURE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ASSIGNMENT_FAILURE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_ASSIGNMENT_FAILURE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ASSIGNMENT_FAILURE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CIPHERING_MODE_COMPLETE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CIPHERING_MODE_COMPLETE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CIPHERING_MODE_COMPLETE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CIPHERING_MODE_COMPLETE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CIPHERING_MODE_COMPLETE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CIPHERING_MODE_COMPLETE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CIPHERING_MODE_COMPLETE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CIPHERING_MODE_COMPLETE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CIPHERING_MODE_COMPLETE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CIPHERING_MODE_COMPLETE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CLASSMARK_CHANGE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CLASSMARK_CHANGE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CLASSMARK_CHANGE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CLASSMARK_CHANGE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CLASSMARK_CHANGE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CLASSMARK_CHANGE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CLASSMARK_CHANGE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CLASSMARK_CHANGE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CLASSMARK_CHANGE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CLASSMARK_CHANGE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "UTRAN_CLASSMARK_CHANGE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_UTRAN_CLASSMARK_CHANGE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_UTRAN_CLASSMARK_CHANGE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_UTRAN_CLASSMARK_CHANGE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_UTRAN_CLASSMARK_CHANGE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "UTRAN_CLASSMARK_CHANGE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_UTRAN_CLASSMARK_CHANGE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_UTRAN_CLASSMARK_CHANGE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_UTRAN_CLASSMARK_CHANGE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_UTRAN_CLASSMARK_CHANGE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CDMA2000_CLASSMARK_CHANGE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CDMA2000_CLASSMARK_CHANGE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CDMA2000_CLASSMARK_CHANGE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CDMA2000_CLASSMARK_CHANGE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CDMA2000_CLASSMARK_CHANGE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CDMA2000_CLASSMARK_CHANGE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CDMA2000_CLASSMARK_CHANGE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CDMA2000_CLASSMARK_CHANGE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CDMA2000_CLASSMARK_CHANGE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CDMA2000_CLASSMARK_CHANGE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "GERAN_IU_MODE_CLASSMARK_CHANGE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_GERAN_IU_MODE_CLASSMARK_CHANGE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GERAN_IU_MODE_CLASSMARK_CHANGE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_GERAN_IU_MODE_CLASSMARK_CHANGE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GERAN_IU_MODE_CLASSMARK_CHANGE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "GERAN_IU_MODE_CLASSMARK_CHANGE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_GERAN_IU_MODE_CLASSMARK_CHANGE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GERAN_IU_MODE_CLASSMARK_CHANGE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_GERAN_IU_MODE_CLASSMARK_CHANGE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GERAN_IU_MODE_CLASSMARK_CHANGE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CONFIGURATION_CHANGE_ACKNOWLEDGE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CONFIGURATION_CHANGE_ACKNOWLEDGE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONFIGURATION_CHANGE_ACKNOWLEDGE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CONFIGURATION_CHANGE_ACKNOWLEDGE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONFIGURATION_CHANGE_ACKNOWLEDGE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CONFIGURATION_CHANGE_ACKNOWLEDGE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CONFIGURATION_CHANGE_ACKNOWLEDGE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONFIGURATION_CHANGE_ACKNOWLEDGE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CONFIGURATION_CHANGE_ACKNOWLEDGE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONFIGURATION_CHANGE_ACKNOWLEDGE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CONFIGURATION_CHANGE_REJECT_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CONFIGURATION_CHANGE_REJECT_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONFIGURATION_CHANGE_REJECT_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CONFIGURATION_CHANGE_REJECT_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONFIGURATION_CHANGE_REJECT_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CONFIGURATION_CHANGE_REJECT_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CONFIGURATION_CHANGE_REJECT_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONFIGURATION_CHANGE_REJECT_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CONFIGURATION_CHANGE_REJECT_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONFIGURATION_CHANGE_REJECT_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "DTM_ASSIGNMENT_COMMAND_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_DTM_ASSIGNMENT_COMMAND_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DTM_ASSIGNMENT_COMMAND_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_DTM_ASSIGNMENT_COMMAND_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DTM_ASSIGNMENT_COMMAND_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "DTM_ASSIGNMENT_COMMAND_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_DTM_ASSIGNMENT_COMMAND_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DTM_ASSIGNMENT_COMMAND_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_DTM_ASSIGNMENT_COMMAND_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DTM_ASSIGNMENT_COMMAND_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "DTM_ASSIGNMENT_FAILURE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_DTM_ASSIGNMENT_FAILURE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DTM_ASSIGNMENT_FAILURE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_DTM_ASSIGNMENT_FAILURE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DTM_ASSIGNMENT_FAILURE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "DTM_ASSIGNMENT_FAILURE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_DTM_ASSIGNMENT_FAILURE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DTM_ASSIGNMENT_FAILURE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_DTM_ASSIGNMENT_FAILURE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DTM_ASSIGNMENT_FAILURE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "DTM_REQUEST_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_DTM_REQUEST_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DTM_REQUEST_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_DTM_REQUEST_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DTM_REQUEST_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "DTM_REQUEST_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_DTM_REQUEST_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DTM_REQUEST_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_DTM_REQUEST_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DTM_REQUEST_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "GPRS_SUSPENSION_REQUEST_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_GPRS_SUSPENSION_REQUEST_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GPRS_SUSPENSION_REQUEST_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_GPRS_SUSPENSION_REQUEST_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GPRS_SUSPENSION_REQUEST_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "GPRS_SUSPENSION_REQUEST_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_GPRS_SUSPENSION_REQUEST_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GPRS_SUSPENSION_REQUEST_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_GPRS_SUSPENSION_REQUEST_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GPRS_SUSPENSION_REQUEST_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "HANDOVER_COMPLETE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_HANDOVER_COMPLETE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_HANDOVER_COMPLETE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_HANDOVER_COMPLETE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_HANDOVER_COMPLETE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "HANDOVER_COMPLETE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_HANDOVER_COMPLETE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_HANDOVER_COMPLETE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_HANDOVER_COMPLETE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_HANDOVER_COMPLETE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "HANDOVER_FAILURE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_HANDOVER_FAILURE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_HANDOVER_FAILURE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_HANDOVER_FAILURE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_HANDOVER_FAILURE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "HANDOVER_FAILURE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_HANDOVER_FAILURE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_HANDOVER_FAILURE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_HANDOVER_FAILURE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_HANDOVER_FAILURE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MEASUREMENT_REPORT_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MEASUREMENT_REPORT_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MEASUREMENT_REPORT_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MEASUREMENT_REPORT_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MEASUREMENT_REPORT_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "MEASUREMENT_REPORT_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MEASUREMENT_REPORT_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MEASUREMENT_REPORT_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MEASUREMENT_REPORT_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MEASUREMENT_REPORT_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "NOTIFICATION_RESPONSE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_NOTIFICATION_RESPONSE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_NOTIFICATION_RESPONSE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_NOTIFICATION_RESPONSE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_NOTIFICATION_RESPONSE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "NOTIFICATION_RESPONSE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_NOTIFICATION_RESPONSE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_NOTIFICATION_RESPONSE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_NOTIFICATION_RESPONSE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_NOTIFICATION_RESPONSE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PAGING_RESPONSE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PAGING_RESPONSE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PAGING_RESPONSE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PAGING_RESPONSE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PAGING_RESPONSE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "PAGING_RESPONSE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_PAGING_RESPONSE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PAGING_RESPONSE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_PAGING_RESPONSE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PAGING_RESPONSE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PARTIAL_RELEASE_COMPLETE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PARTIAL_RELEASE_COMPLETE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PARTIAL_RELEASE_COMPLETE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PARTIAL_RELEASE_COMPLETE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PARTIAL_RELEASE_COMPLETE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "PARTIAL_RELEASE_COMPLETE_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_PARTIAL_RELEASE_COMPLETE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PARTIAL_RELEASE_COMPLETE_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_PARTIAL_RELEASE_COMPLETE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PARTIAL_RELEASE_COMPLETE_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RR_INITIALISATION_REQUEST_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RR_INITIALISATION_REQUEST_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RR_INITIALISATION_REQUEST_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RR_INITIALISATION_REQUEST_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RR_INITIALISATION_REQUEST_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RR_INITIALISATION_REQUEST_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RR_INITIALISATION_REQUEST_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RR_INITIALISATION_REQUEST_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RR_INITIALISATION_REQUEST_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RR_INITIALISATION_REQUEST_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RR_STATUS".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RR_STATUS (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RR_STATUS* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RR_STATUS (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RR_STATUS* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RR_STATUS".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RR_STATUS (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RR_STATUS* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RR_STATUS (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RR_STATUS* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "TALKER_INDICATION_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_TALKER_INDICATION_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_TALKER_INDICATION_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_TALKER_INDICATION_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_TALKER_INDICATION_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "TALKER_INDICATION_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_TALKER_INDICATION_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_TALKER_INDICATION_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_TALKER_INDICATION_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_TALKER_INDICATION_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PRIORITY_DNLINK_REQUEST".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PRIORITY_DNLINK_REQUEST (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PRIORITY_DNLINK_REQUEST* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PRIORITY_DNLINK_REQUEST (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PRIORITY_DNLINK_REQUEST* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "PRIORITY_DNLINK_REQUEST".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_PRIORITY_DNLINK_REQUEST (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PRIORITY_DNLINK_REQUEST* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_PRIORITY_DNLINK_REQUEST (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PRIORITY_DNLINK_REQUEST* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "DATA_INDICATION".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_DATA_INDICATION (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DATA_INDICATION* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_DATA_INDICATION (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DATA_INDICATION* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "DATA_INDICATION".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_DATA_INDICATION (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DATA_INDICATION* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_DATA_INDICATION (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DATA_INDICATION* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "DATA_INDICATION_2".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_DATA_INDICATION_2 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DATA_INDICATION_2* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_DATA_INDICATION_2 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DATA_INDICATION_2* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "DATA_INDICATION_2".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_DATA_INDICATION_2 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DATA_INDICATION_2* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_DATA_INDICATION_2 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DATA_INDICATION_2* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "UPLINK_RELEASE".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_UPLINK_RELEASE (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_UPLINK_RELEASE* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_UPLINK_RELEASE (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_UPLINK_RELEASE* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "UPLINK_RELEASE".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_UPLINK_RELEASE (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_UPLINK_RELEASE* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_UPLINK_RELEASE (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_UPLINK_RELEASE* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "EXTENDED_MEASUREMENT_REPORT_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EXTENDED_MEASUREMENT_REPORT_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EXTENDED_MEASUREMENT_REPORT_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EXTENDED_MEASUREMENT_REPORT_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EXTENDED_MEASUREMENT_REPORT_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "EXTENDED_MEASUREMENT_REPORT_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_EXTENDED_MEASUREMENT_REPORT_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EXTENDED_MEASUREMENT_REPORT_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_EXTENDED_MEASUREMENT_REPORT_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EXTENDED_MEASUREMENT_REPORT_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "APPLICATION_INFORMATION".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_APPLICATION_INFORMATION (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_APPLICATION_INFORMATION* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_APPLICATION_INFORMATION (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_APPLICATION_INFORMATION* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "APPLICATION_INFORMATION".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_APPLICATION_INFORMATION (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_APPLICATION_INFORMATION* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_APPLICATION_INFORMATION (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_APPLICATION_INFORMATION* ED_CONST Destin, ED_EXLONG Length));

int Match_c_ASSIGNMENT_COMPLETE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_ASSIGNMENT_FAILURE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_CIPHERING_MODE_COMPLETE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_CLASSMARK_CHANGE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_UTRAN_CLASSMARK_CHANGE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_CDMA2000_CLASSMARK_CHANGE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_GERAN_IU_MODE_CLASSMARK_CHANGE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_CONFIGURATION_CHANGE_ACKNOWLEDGE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_CONFIGURATION_CHANGE_REJECT_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_DTM_ASSIGNMENT_COMMAND_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_DTM_ASSIGNMENT_FAILURE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_DTM_REQUEST_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_GPRS_SUSPENSION_REQUEST_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_HANDOVER_COMPLETE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_HANDOVER_FAILURE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_MEASUREMENT_REPORT_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_NOTIFICATION_RESPONSE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_PAGING_RESPONSE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_PARTIAL_RELEASE_COMPLETE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_RR_INITIALISATION_REQUEST_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_RR_STATUS (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_TALKER_INDICATION_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_PRIORITY_DNLINK_REQUEST (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_DATA_INDICATION (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_DATA_INDICATION_2 (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_UPLINK_RELEASE (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_EXTENDED_MEASUREMENT_REPORT_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_APPLICATION_INFORMATION (const char* Buffer, ED_CONST ED_EXLONG BitOffset);

#ifdef __cplusplus
	}
#endif
#endif


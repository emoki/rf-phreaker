/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.152
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __RRDownlink_RR_h
#define __RRDownlink_RR_h
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
	Encoding/decoding functions for "ADDITIONAL_ASSIGNMENT_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_ADDITIONAL_ASSIGNMENT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ADDITIONAL_ASSIGNMENT_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_ADDITIONAL_ASSIGNMENT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ADDITIONAL_ASSIGNMENT_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "ADDITIONAL_ASSIGNMENT_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_ADDITIONAL_ASSIGNMENT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ADDITIONAL_ASSIGNMENT_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_ADDITIONAL_ASSIGNMENT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ADDITIONAL_ASSIGNMENT_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "ASSIGNMENT_COMMAND_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_ASSIGNMENT_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ASSIGNMENT_COMMAND_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_ASSIGNMENT_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ASSIGNMENT_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "ASSIGNMENT_COMMAND_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_ASSIGNMENT_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ASSIGNMENT_COMMAND_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_ASSIGNMENT_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ASSIGNMENT_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CHANNEL_MODE_MODIFY_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CHANNEL_MODE_MODIFY_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CHANNEL_MODE_MODIFY_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CHANNEL_MODE_MODIFY_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CHANNEL_MODE_MODIFY_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CHANNEL_MODE_MODIFY_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CHANNEL_MODE_MODIFY_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CHANNEL_MODE_MODIFY_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CHANNEL_MODE_MODIFY_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CHANNEL_MODE_MODIFY_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CHANNEL_RELEASE_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CHANNEL_RELEASE_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CHANNEL_RELEASE_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CHANNEL_RELEASE_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CHANNEL_RELEASE_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CHANNEL_RELEASE_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CHANNEL_RELEASE_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CHANNEL_RELEASE_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CHANNEL_RELEASE_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CHANNEL_RELEASE_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CIPHERING_MODE_COMMAND_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CIPHERING_MODE_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CIPHERING_MODE_COMMAND_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CIPHERING_MODE_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CIPHERING_MODE_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CIPHERING_MODE_COMMAND_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CIPHERING_MODE_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CIPHERING_MODE_COMMAND_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CIPHERING_MODE_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CIPHERING_MODE_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CLASSMARK_ENQUIRY_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CLASSMARK_ENQUIRY_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CLASSMARK_ENQUIRY_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CLASSMARK_ENQUIRY_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CLASSMARK_ENQUIRY_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CLASSMARK_ENQUIRY_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CLASSMARK_ENQUIRY_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CLASSMARK_ENQUIRY_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CLASSMARK_ENQUIRY_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CLASSMARK_ENQUIRY_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CONFIGURATION_CHANGE_COMMAND_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CONFIGURATION_CHANGE_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONFIGURATION_CHANGE_COMMAND_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CONFIGURATION_CHANGE_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONFIGURATION_CHANGE_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "CONFIGURATION_CHANGE_COMMAND_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CONFIGURATION_CHANGE_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONFIGURATION_CHANGE_COMMAND_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CONFIGURATION_CHANGE_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONFIGURATION_CHANGE_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "DTM_ASSIGNMENT_COMMAND_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_DTM_ASSIGNMENT_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DTM_ASSIGNMENT_COMMAND_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_DTM_ASSIGNMENT_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DTM_ASSIGNMENT_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "DTM_ASSIGNMENT_COMMAND_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_DTM_ASSIGNMENT_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DTM_ASSIGNMENT_COMMAND_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_DTM_ASSIGNMENT_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DTM_ASSIGNMENT_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "DTM_INFORMATION_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_DTM_INFORMATION_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DTM_INFORMATION_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_DTM_INFORMATION_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DTM_INFORMATION_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "DTM_INFORMATION_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_DTM_INFORMATION_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DTM_INFORMATION_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_DTM_INFORMATION_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DTM_INFORMATION_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "DTM_REJECT_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_DTM_REJECT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DTM_REJECT_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_DTM_REJECT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DTM_REJECT_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "DTM_REJECT_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_DTM_REJECT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DTM_REJECT_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_DTM_REJECT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DTM_REJECT_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FREQUENCY_REDEFINITION_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FREQUENCY_REDEFINITION_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FREQUENCY_REDEFINITION_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FREQUENCY_REDEFINITION_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FREQUENCY_REDEFINITION_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "FREQUENCY_REDEFINITION_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_FREQUENCY_REDEFINITION_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FREQUENCY_REDEFINITION_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_FREQUENCY_REDEFINITION_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FREQUENCY_REDEFINITION_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PDCH_ASSIGNMENT_COMMAND_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PDCH_ASSIGNMENT_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PDCH_ASSIGNMENT_COMMAND_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PDCH_ASSIGNMENT_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PDCH_ASSIGNMENT_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "PDCH_ASSIGNMENT_COMMAND_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_PDCH_ASSIGNMENT_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PDCH_ASSIGNMENT_COMMAND_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_PDCH_ASSIGNMENT_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PDCH_ASSIGNMENT_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "HANDOVER_COMMAND_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_HANDOVER_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_HANDOVER_COMMAND_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_HANDOVER_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_HANDOVER_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "HANDOVER_COMMAND_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_HANDOVER_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_HANDOVER_COMMAND_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_HANDOVER_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_HANDOVER_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RR_CELL_CHANGE_ORDER_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RR_CELL_CHANGE_ORDER_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RR_CELL_CHANGE_ORDER_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RR_CELL_CHANGE_ORDER_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RR_CELL_CHANGE_ORDER_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "RR_CELL_CHANGE_ORDER_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RR_CELL_CHANGE_ORDER_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RR_CELL_CHANGE_ORDER_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RR_CELL_CHANGE_ORDER_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RR_CELL_CHANGE_ORDER_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PACKET_ASSIGNMENT_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PACKET_ASSIGNMENT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PACKET_ASSIGNMENT_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PACKET_ASSIGNMENT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PACKET_ASSIGNMENT_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "PACKET_ASSIGNMENT_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_PACKET_ASSIGNMENT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PACKET_ASSIGNMENT_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_PACKET_ASSIGNMENT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PACKET_ASSIGNMENT_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PACKET_NOTIFICATION_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PACKET_NOTIFICATION_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PACKET_NOTIFICATION_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PACKET_NOTIFICATION_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PACKET_NOTIFICATION_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "PACKET_NOTIFICATION_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_PACKET_NOTIFICATION_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PACKET_NOTIFICATION_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_PACKET_NOTIFICATION_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PACKET_NOTIFICATION_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PARTIAL_RELEASE_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PARTIAL_RELEASE_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PARTIAL_RELEASE_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PARTIAL_RELEASE_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PARTIAL_RELEASE_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "PARTIAL_RELEASE_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_PARTIAL_RELEASE_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PARTIAL_RELEASE_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_PARTIAL_RELEASE_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PARTIAL_RELEASE_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PHYSICAL_INFORMATION_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PHYSICAL_INFORMATION_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PHYSICAL_INFORMATION_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PHYSICAL_INFORMATION_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PHYSICAL_INFORMATION_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "PHYSICAL_INFORMATION_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_PHYSICAL_INFORMATION_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PHYSICAL_INFORMATION_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_PHYSICAL_INFORMATION_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PHYSICAL_INFORMATION_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "UPLINK_BUSY_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_UPLINK_BUSY_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_UPLINK_BUSY_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_UPLINK_BUSY_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_UPLINK_BUSY_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "UPLINK_BUSY_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_UPLINK_BUSY_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_UPLINK_BUSY_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_UPLINK_BUSY_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_UPLINK_BUSY_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "VGCS_DNLINK_GRANT_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_VGCS_DNLINK_GRANT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VGCS_DNLINK_GRANT_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_VGCS_DNLINK_GRANT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VGCS_DNLINK_GRANT_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "VGCS_DNLINK_GRANT_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_VGCS_DNLINK_GRANT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VGCS_DNLINK_GRANT_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_VGCS_DNLINK_GRANT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VGCS_DNLINK_GRANT_DN* ED_CONST Destin, ED_EXLONG Length));

int Match_c_ADDITIONAL_ASSIGNMENT_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_ASSIGNMENT_COMMAND_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_CHANNEL_MODE_MODIFY_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_CHANNEL_RELEASE_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_CIPHERING_MODE_COMMAND_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_CLASSMARK_ENQUIRY_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_CONFIGURATION_CHANGE_COMMAND_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_DTM_ASSIGNMENT_COMMAND_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_DTM_INFORMATION_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_DTM_REJECT_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_FREQUENCY_REDEFINITION_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_PDCH_ASSIGNMENT_COMMAND_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_HANDOVER_COMMAND_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_RR_CELL_CHANGE_ORDER_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_PACKET_ASSIGNMENT_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_PACKET_NOTIFICATION_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_PARTIAL_RELEASE_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_PHYSICAL_INFORMATION_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_UPLINK_BUSY_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_VGCS_DNLINK_GRANT_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);

#ifdef __cplusplus
	}
#endif
#endif


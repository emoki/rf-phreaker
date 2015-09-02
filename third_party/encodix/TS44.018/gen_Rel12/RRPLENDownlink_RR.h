/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.152
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __RRPLENDownlink_RR_h
#define __RRPLENDownlink_RR_h
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
	Encoding/decoding functions for "IMMEDIATE_ASSIGNMENT_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_IMMEDIATE_ASSIGNMENT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_IMMEDIATE_ASSIGNMENT_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_IMMEDIATE_ASSIGNMENT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_IMMEDIATE_ASSIGNMENT_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "IMMEDIATE_ASSIGNMENT_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_IMMEDIATE_ASSIGNMENT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_IMMEDIATE_ASSIGNMENT_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_IMMEDIATE_ASSIGNMENT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_IMMEDIATE_ASSIGNMENT_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "IMMEDIATE_PACKET_ASSIGNMENT_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_IMMEDIATE_PACKET_ASSIGNMENT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_IMMEDIATE_PACKET_ASSIGNMENT_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_IMMEDIATE_PACKET_ASSIGNMENT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_IMMEDIATE_PACKET_ASSIGNMENT_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "IMMEDIATE_PACKET_ASSIGNMENT_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_IMMEDIATE_PACKET_ASSIGNMENT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_IMMEDIATE_PACKET_ASSIGNMENT_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_IMMEDIATE_PACKET_ASSIGNMENT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_IMMEDIATE_PACKET_ASSIGNMENT_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "IMMEDIATE_ASSIGNMENT_EXTENDED_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "IMMEDIATE_ASSIGNMENT_EXTENDED_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "IMMEDIATE_ASSIGNMENT_REJECT_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_IMMEDIATE_ASSIGNMENT_REJECT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_IMMEDIATE_ASSIGNMENT_REJECT_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_IMMEDIATE_ASSIGNMENT_REJECT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_IMMEDIATE_ASSIGNMENT_REJECT_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "IMMEDIATE_ASSIGNMENT_REJECT_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_IMMEDIATE_ASSIGNMENT_REJECT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_IMMEDIATE_ASSIGNMENT_REJECT_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_IMMEDIATE_ASSIGNMENT_REJECT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_IMMEDIATE_ASSIGNMENT_REJECT_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "NOTIFICATION_NCH_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_NOTIFICATION_NCH_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_NOTIFICATION_NCH_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_NOTIFICATION_NCH_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_NOTIFICATION_NCH_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "NOTIFICATION_NCH_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_NOTIFICATION_NCH_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_NOTIFICATION_NCH_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_NOTIFICATION_NCH_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_NOTIFICATION_NCH_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PAGING_REQUEST_TYPE_1_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PAGING_REQUEST_TYPE_1_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PAGING_REQUEST_TYPE_1_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PAGING_REQUEST_TYPE_1_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PAGING_REQUEST_TYPE_1_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "PAGING_REQUEST_TYPE_1_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_PAGING_REQUEST_TYPE_1_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PAGING_REQUEST_TYPE_1_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_PAGING_REQUEST_TYPE_1_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PAGING_REQUEST_TYPE_1_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PAGING_REQUEST_TYPE_2_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PAGING_REQUEST_TYPE_2_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PAGING_REQUEST_TYPE_2_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PAGING_REQUEST_TYPE_2_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PAGING_REQUEST_TYPE_2_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "PAGING_REQUEST_TYPE_2_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_PAGING_REQUEST_TYPE_2_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PAGING_REQUEST_TYPE_2_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_PAGING_REQUEST_TYPE_2_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PAGING_REQUEST_TYPE_2_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PAGING_REQUEST_TYPE_3_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PAGING_REQUEST_TYPE_3_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PAGING_REQUEST_TYPE_3_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PAGING_REQUEST_TYPE_3_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PAGING_REQUEST_TYPE_3_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "PAGING_REQUEST_TYPE_3_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_PAGING_REQUEST_TYPE_3_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PAGING_REQUEST_TYPE_3_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_PAGING_REQUEST_TYPE_3_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PAGING_REQUEST_TYPE_3_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_1_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_1_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_1_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_1_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_1_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_1_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_1_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_1_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_1_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_1_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_2_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_2_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_2_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_2_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_2_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_2_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_2_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_2_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_2_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_2_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_2BIS_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_2BIS_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_2BIS_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_2BIS_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_2BIS_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_2BIS_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_2BIS_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_2BIS_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_2BIS_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_2BIS_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_2TER_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_2TER_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_2TER_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_2TER_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_2TER_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_2TER_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_2TER_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_2TER_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_2TER_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_2TER_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_2QUATER_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_2QUATER_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_2QUATER_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_2QUATER_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_2QUATER_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_2QUATER_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_2QUATER_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_2QUATER_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_2QUATER_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_2QUATER_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_3_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_3_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_3_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_3_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_3_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_3_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_3_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_3_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_3_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_3_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_4_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_4_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_4_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_4_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_4_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_4_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_4_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_4_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_4_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_4_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_5_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_5_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_5_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_5_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_5_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_5_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_5_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_5_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_5_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_5_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_5BIS_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_5BIS_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_5BIS_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_5BIS_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_5BIS_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_5BIS_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_5BIS_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_5BIS_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_5BIS_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_5BIS_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_5TER_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_5TER_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_5TER_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_5TER_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_5TER_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_5TER_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_5TER_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_5TER_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_5TER_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_5TER_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_6_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_6_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_6_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_6_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_6_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_6_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_6_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_6_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_6_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_6_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_7_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_7_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_7_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_7_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_7_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_7_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_7_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_7_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_7_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_7_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_8_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_8_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_8_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_8_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_8_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_8_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_8_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_8_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_8_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_8_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_9_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_9_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_9_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_9_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_9_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_9_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_9_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_9_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_9_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_9_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_13_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_13_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_13_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_13_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_13_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_13_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_13_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_13_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_13_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_13_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_16_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_16_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_16_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_16_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_16_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_16_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_16_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_16_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_16_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_16_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_17_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_17_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_17_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_17_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_17_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_17_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_17_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_17_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_17_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_17_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_19_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_19_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_19_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_19_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_19_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_19_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_19_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_19_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_19_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_19_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_18_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_18_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_18_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_18_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_18_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_18_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_18_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_18_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_18_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_18_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_20_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_20_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_20_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_20_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_20_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_20_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_20_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_20_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_20_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_20_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_14_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_14_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_14_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_14_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_14_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_14_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_14_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_14_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_14_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_14_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_15_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_15_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_15_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_15_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_15_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_15_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_15_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_15_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_15_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_15_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_13alt_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_13alt_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_13alt_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_13alt_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_13alt_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_13alt_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_13alt_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_13alt_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_13alt_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_13alt_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_21_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_21_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_21_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_21_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_21_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_21_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_21_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_21_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_21_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_21_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_22_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_22_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_22_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_22_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_22_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_22_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_22_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_22_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_22_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_22_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_23_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_23_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_23_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_23_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_23_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_23_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_23_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_23_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_23_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_23_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "EXTENDED_MEASUREMENT_ORDER_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EXTENDED_MEASUREMENT_ORDER_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EXTENDED_MEASUREMENT_ORDER_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EXTENDED_MEASUREMENT_ORDER_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EXTENDED_MEASUREMENT_ORDER_DN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "EXTENDED_MEASUREMENT_ORDER_DN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_EXTENDED_MEASUREMENT_ORDER_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EXTENDED_MEASUREMENT_ORDER_DN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_EXTENDED_MEASUREMENT_ORDER_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EXTENDED_MEASUREMENT_ORDER_DN* ED_CONST Destin, ED_EXLONG Length));

int Match_c_IMMEDIATE_ASSIGNMENT_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_IMMEDIATE_PACKET_ASSIGNMENT_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_IMMEDIATE_ASSIGNMENT_REJECT_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_NOTIFICATION_NCH_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_PAGING_REQUEST_TYPE_1_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_PAGING_REQUEST_TYPE_2_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_PAGING_REQUEST_TYPE_3_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_1_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_2_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_2BIS_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_2TER_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_2QUATER_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_3_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_4_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_5_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_5BIS_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_5TER_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_6_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_7_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_8_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_9_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_13_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_16_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_17_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_19_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_18_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_20_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_14_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_15_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_13alt_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_21_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_22_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_23_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_EXTENDED_MEASUREMENT_ORDER_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset);

#ifdef __cplusplus
	}
#endif
#endif


/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.152
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __RRShortPD_RR_h
#define __RRShortPD_RR_h
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
	Encoding/decoding functions for "NOTIFICATION_FACCH".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_NOTIFICATION_FACCH (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_NOTIFICATION_FACCH* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_NOTIFICATION_FACCH (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_NOTIFICATION_FACCH* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "NOTIFICATION_FACCH".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_NOTIFICATION_FACCH (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_NOTIFICATION_FACCH* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_NOTIFICATION_FACCH (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_NOTIFICATION_FACCH* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "VBS_VGCS_RECONFIGURE".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_VBS_VGCS_RECONFIGURE (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VBS_VGCS_RECONFIGURE* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_VBS_VGCS_RECONFIGURE (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VBS_VGCS_RECONFIGURE* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "VBS_VGCS_RECONFIGURE".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_VBS_VGCS_RECONFIGURE (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VBS_VGCS_RECONFIGURE* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_VBS_VGCS_RECONFIGURE (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VBS_VGCS_RECONFIGURE* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "VBS_VGCS_RECONFIGURE2".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_VBS_VGCS_RECONFIGURE2 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VBS_VGCS_RECONFIGURE2* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_VBS_VGCS_RECONFIGURE2 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VBS_VGCS_RECONFIGURE2* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "VBS_VGCS_RECONFIGURE2".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_VBS_VGCS_RECONFIGURE2 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VBS_VGCS_RECONFIGURE2* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_VBS_VGCS_RECONFIGURE2 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VBS_VGCS_RECONFIGURE2* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "UPLINK_FREE".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_UPLINK_FREE (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_UPLINK_FREE* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_UPLINK_FREE (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_UPLINK_FREE* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "UPLINK_FREE".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_UPLINK_FREE (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_UPLINK_FREE* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_UPLINK_FREE (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_UPLINK_FREE* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "VGCS_ADDITIONAL_INFORMATION".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_VGCS_ADDITIONAL_INFORMATION (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VGCS_ADDITIONAL_INFORMATION* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_VGCS_ADDITIONAL_INFORMATION (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VGCS_ADDITIONAL_INFORMATION* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "VGCS_ADDITIONAL_INFORMATION".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_VGCS_ADDITIONAL_INFORMATION (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VGCS_ADDITIONAL_INFORMATION* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_VGCS_ADDITIONAL_INFORMATION (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VGCS_ADDITIONAL_INFORMATION* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "VGCS_SMS_INFORMATION".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_VGCS_SMS_INFORMATION (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VGCS_SMS_INFORMATION* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_VGCS_SMS_INFORMATION (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VGCS_SMS_INFORMATION* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "VGCS_SMS_INFORMATION".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_VGCS_SMS_INFORMATION (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VGCS_SMS_INFORMATION* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_VGCS_SMS_INFORMATION (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VGCS_SMS_INFORMATION* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_10_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_10_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_10_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_10_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_10_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_10_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_10_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_10_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_10_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_10_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_10bis_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_10bis_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_10bis_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_10bis_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_10bis_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_10bis_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_10bis_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_10bis_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_10bis_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_10bis_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_10ter_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_10ter_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_10ter_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_10ter_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_10ter_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "SYSTEM_INFORMATION_TYPE_10ter_UP".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_10ter_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_10ter_UP* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_10ter_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_10ter_UP* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MEASUREMENT_INFORMATION".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MEASUREMENT_INFORMATION (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MEASUREMENT_INFORMATION* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MEASUREMENT_INFORMATION (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MEASUREMENT_INFORMATION* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "MEASUREMENT_INFORMATION".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MEASUREMENT_INFORMATION (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MEASUREMENT_INFORMATION* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MEASUREMENT_INFORMATION (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MEASUREMENT_INFORMATION* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "ENHANCED_MEASUREMENT_REPORT".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_ENHANCED_MEASUREMENT_REPORT (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ENHANCED_MEASUREMENT_REPORT* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_ENHANCED_MEASUREMENT_REPORT (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ENHANCED_MEASUREMENT_REPORT* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "ENHANCED_MEASUREMENT_REPORT".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_ENHANCED_MEASUREMENT_REPORT (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ENHANCED_MEASUREMENT_REPORT* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_ENHANCED_MEASUREMENT_REPORT (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ENHANCED_MEASUREMENT_REPORT* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "VGCS_NEIGHBOUR_CELL_INFORMATION".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_VGCS_NEIGHBOUR_CELL_INFORMATION (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VGCS_NEIGHBOUR_CELL_INFORMATION* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_VGCS_NEIGHBOUR_CELL_INFORMATION (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VGCS_NEIGHBOUR_CELL_INFORMATION* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "VGCS_NEIGHBOUR_CELL_INFORMATION".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_VGCS_NEIGHBOUR_CELL_INFORMATION (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VGCS_NEIGHBOUR_CELL_INFORMATION* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_VGCS_NEIGHBOUR_CELL_INFORMATION (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VGCS_NEIGHBOUR_CELL_INFORMATION* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "NOTIFY_APPLICATION_DATA".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_NOTIFY_APPLICATION_DATA (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_NOTIFY_APPLICATION_DATA* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_NOTIFY_APPLICATION_DATA (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_NOTIFY_APPLICATION_DATA* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for body of "NOTIFY_APPLICATION_DATA".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_NOTIFY_APPLICATION_DATA (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_NOTIFY_APPLICATION_DATA* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_NOTIFY_APPLICATION_DATA (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_NOTIFY_APPLICATION_DATA* ED_CONST Destin, ED_EXLONG Length));

int Match_c_NOTIFICATION_FACCH (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_VBS_VGCS_RECONFIGURE (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_VBS_VGCS_RECONFIGURE2 (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_UPLINK_FREE (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_VGCS_ADDITIONAL_INFORMATION (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_VGCS_SMS_INFORMATION (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_10_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_10bis_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_SYSTEM_INFORMATION_TYPE_10ter_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_MEASUREMENT_INFORMATION (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_ENHANCED_MEASUREMENT_REPORT (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_VGCS_NEIGHBOUR_CELL_INFORMATION (const char* Buffer, ED_CONST ED_EXLONG BitOffset);
int Match_c_NOTIFY_APPLICATION_DATA (const char* Buffer, ED_CONST ED_EXLONG BitOffset);

#ifdef __cplusplus
	}
#endif
#endif


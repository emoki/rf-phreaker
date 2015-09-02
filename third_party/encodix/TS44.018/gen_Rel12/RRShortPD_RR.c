/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.152
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#include "RRShortPD_RR.h"
#include "ed_c_known_ie_RR.h"
#include "ed_tlv.h"
#include "CSN1DataTypes_RR.h"
#include "UserDefinedDataTypes_RR.h"
#if ED_VERSION != 10152
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.152
#endif


#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE NOTIFICATION_FACCH
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_NOTIFICATION_FACCH (char* Buffer, ED_EXLONG BitOffset, const c_NOTIFICATION_FACCH* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 1, 6);
		CurrOfs += 6;
		
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->contents> DOT=<.> */
		Len = ENCODE_c_NOTIFICATION_FACCH_BODY (Buffer, CurrOfs, (&(Source->contents)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1318> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE NOTIFICATION_FACCH
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_NOTIFICATION_FACCH (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_NOTIFICATION_FACCH* ED_CONST Source))
{
	return L3_ENCODE_c_NOTIFICATION_FACCH (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE NOTIFICATION_FACCH
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_NOTIFICATION_FACCH (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_NOTIFICATION_FACCH* ED_CONST Source))
{
	return L3_ENCODE_c_NOTIFICATION_FACCH (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE NOTIFICATION_FACCH
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_NOTIFICATION_FACCH (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_NOTIFICATION_FACCH* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_NOTIFICATION_FACCH (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;
	
	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE NOTIFICATION_FACCH
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_NOTIFICATION_FACCH (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_NOTIFICATION_FACCH* ED_CONST Destin, ED_EXLONG Length))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_NOTIFICATION_FACCH_BODY (Buffer, CurrOfs, (&(Destin->contents)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1319> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1319, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1320> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1319, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE VBS_VGCS_RECONFIGURE
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_VBS_VGCS_RECONFIGURE (char* Buffer, ED_EXLONG BitOffset, const c_VBS_VGCS_RECONFIGURE* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 6);
		CurrOfs += 6;
		
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->contents> DOT=<.> */
		Len = ENCODE_c_VBS_VGCS_RECONFIGURE_BODY (Buffer, CurrOfs, (&(Source->contents)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1321> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE VBS_VGCS_RECONFIGURE
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_VBS_VGCS_RECONFIGURE (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VBS_VGCS_RECONFIGURE* ED_CONST Source))
{
	return L3_ENCODE_c_VBS_VGCS_RECONFIGURE (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE VBS_VGCS_RECONFIGURE
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_VBS_VGCS_RECONFIGURE (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VBS_VGCS_RECONFIGURE* ED_CONST Source))
{
	return L3_ENCODE_c_VBS_VGCS_RECONFIGURE (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE VBS_VGCS_RECONFIGURE
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_VBS_VGCS_RECONFIGURE (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VBS_VGCS_RECONFIGURE* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_VBS_VGCS_RECONFIGURE (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;
	
	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE VBS_VGCS_RECONFIGURE
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_VBS_VGCS_RECONFIGURE (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VBS_VGCS_RECONFIGURE* ED_CONST Destin, ED_EXLONG Length))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_VBS_VGCS_RECONFIGURE_BODY (Buffer, CurrOfs, (&(Destin->contents)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1322> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1322, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1323> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1322, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE VBS_VGCS_RECONFIGURE2
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_VBS_VGCS_RECONFIGURE2 (char* Buffer, ED_EXLONG BitOffset, const c_VBS_VGCS_RECONFIGURE2* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 7, 6);
		CurrOfs += 6;
		
	}
	
	
	/* Code for CellChannelDescription */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->CellChannelDescription> DOT=<.> */
		Len = ENCODE_c_CellChannel (Buffer, CurrOfs, (&(Source->CellChannelDescription)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1324> Error encoding subfield CellChannelDescription\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for StartingTime */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->StartingTime> DOT=<.> */
		EDIntToBits (Buffer, (CurrOfs), (int)(Source->StartingTime), 16);
		Len = 16;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1325> Error encoding subfield StartingTime\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE VBS_VGCS_RECONFIGURE2
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_VBS_VGCS_RECONFIGURE2 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VBS_VGCS_RECONFIGURE2* ED_CONST Source))
{
	return L3_ENCODE_c_VBS_VGCS_RECONFIGURE2 (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE VBS_VGCS_RECONFIGURE2
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_VBS_VGCS_RECONFIGURE2 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VBS_VGCS_RECONFIGURE2* ED_CONST Source))
{
	return L3_ENCODE_c_VBS_VGCS_RECONFIGURE2 (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE VBS_VGCS_RECONFIGURE2
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_VBS_VGCS_RECONFIGURE2 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VBS_VGCS_RECONFIGURE2* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_VBS_VGCS_RECONFIGURE2 (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;
	
	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE VBS_VGCS_RECONFIGURE2
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_VBS_VGCS_RECONFIGURE2 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VBS_VGCS_RECONFIGURE2* ED_CONST Destin, ED_EXLONG Length))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE CellChannelDescription
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 128;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, (&(Destin->CellChannelDescription)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1326> Error decoding subfield CellChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1326, (Destin->CellChannelDescription))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1327> Message too short decoding subfield CellChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1326, (Destin->CellChannelDescription))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE StartingTime
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 16;
	/* Read value part LOCATOR_16 */
	Destin->StartingTime = (ED_SHORT)EDBitsToInt (Buffer, (CurrOfs), 16);
	/* LOCATOR SETTINGS LOCINT */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-53003=EDCore::TDMInteger) */Destin->StartingTime___LOCATOR), CurrOfs, 16);
	RetLen = 16;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1328> Error decoding subfield StartingTime\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1328, (Destin->StartingTime))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1329> Message too short decoding subfield StartingTime\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1328, (Destin->StartingTime))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE UPLINK_FREE
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_UPLINK_FREE (char* Buffer, ED_EXLONG BitOffset, const c_UPLINK_FREE* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 2, 6);
		CurrOfs += 6;
		
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->contents> DOT=<.> */
		Len = ENCODE_c_UPLINK_FREE_BODY (Buffer, CurrOfs, (&(Source->contents)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1330> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE UPLINK_FREE
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_UPLINK_FREE (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_UPLINK_FREE* ED_CONST Source))
{
	return L3_ENCODE_c_UPLINK_FREE (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE UPLINK_FREE
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_UPLINK_FREE (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_UPLINK_FREE* ED_CONST Source))
{
	return L3_ENCODE_c_UPLINK_FREE (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE UPLINK_FREE
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_UPLINK_FREE (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_UPLINK_FREE* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_UPLINK_FREE (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;
	
	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE UPLINK_FREE
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_UPLINK_FREE (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_UPLINK_FREE* ED_CONST Destin, ED_EXLONG Length))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_UPLINK_FREE_BODY (Buffer, CurrOfs, (&(Destin->contents)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1331> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1331, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1332> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1331, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE VGCS_ADDITIONAL_INFORMATION
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_VGCS_ADDITIONAL_INFORMATION (char* Buffer, ED_EXLONG BitOffset, const c_VGCS_ADDITIONAL_INFORMATION* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 8, 6);
		CurrOfs += 6;
		
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->contents> DOT=<.> */
		Len = ENCODE_c_VGCS_ADDITIONAL_INFORMATION_BODY (Buffer, CurrOfs, (&(Source->contents)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1333> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE VGCS_ADDITIONAL_INFORMATION
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_VGCS_ADDITIONAL_INFORMATION (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VGCS_ADDITIONAL_INFORMATION* ED_CONST Source))
{
	return L3_ENCODE_c_VGCS_ADDITIONAL_INFORMATION (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE VGCS_ADDITIONAL_INFORMATION
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_VGCS_ADDITIONAL_INFORMATION (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VGCS_ADDITIONAL_INFORMATION* ED_CONST Source))
{
	return L3_ENCODE_c_VGCS_ADDITIONAL_INFORMATION (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE VGCS_ADDITIONAL_INFORMATION
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_VGCS_ADDITIONAL_INFORMATION (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VGCS_ADDITIONAL_INFORMATION* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_VGCS_ADDITIONAL_INFORMATION (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;
	
	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE VGCS_ADDITIONAL_INFORMATION
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_VGCS_ADDITIONAL_INFORMATION (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VGCS_ADDITIONAL_INFORMATION* ED_CONST Destin, ED_EXLONG Length))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_VGCS_ADDITIONAL_INFORMATION_BODY (Buffer, CurrOfs, (&(Destin->contents)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1334> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1334, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1335> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1334, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE VGCS_SMS_INFORMATION
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_VGCS_SMS_INFORMATION (char* Buffer, ED_EXLONG BitOffset, const c_VGCS_SMS_INFORMATION* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 9, 6);
		CurrOfs += 6;
		
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->contents> DOT=<.> */
		Len = ENCODE_c_VGCS_SMS_INFORMATION_BODY (Buffer, CurrOfs, (&(Source->contents)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1336> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE VGCS_SMS_INFORMATION
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_VGCS_SMS_INFORMATION (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VGCS_SMS_INFORMATION* ED_CONST Source))
{
	return L3_ENCODE_c_VGCS_SMS_INFORMATION (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE VGCS_SMS_INFORMATION
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_VGCS_SMS_INFORMATION (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VGCS_SMS_INFORMATION* ED_CONST Source))
{
	return L3_ENCODE_c_VGCS_SMS_INFORMATION (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE VGCS_SMS_INFORMATION
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_VGCS_SMS_INFORMATION (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VGCS_SMS_INFORMATION* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_VGCS_SMS_INFORMATION (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;
	
	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE VGCS_SMS_INFORMATION
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_VGCS_SMS_INFORMATION (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VGCS_SMS_INFORMATION* ED_CONST Destin, ED_EXLONG Length))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_VGCS_SMS_INFORMATION_BODY (Buffer, CurrOfs, (&(Destin->contents)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1337> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1337, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1338> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1337, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_10_UP
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_10_UP (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_10_UP* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 0, 6);
		CurrOfs += 6;
		
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->contents> DOT=<.> */
		Len = ENCODE_c_SYSTEM_INFORMATION_TYPE_10_BODY (Buffer, CurrOfs, (&(Source->contents)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1339> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_10_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_10_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_10_UP* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_10_UP (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_10_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_10_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_10_UP* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_10_UP (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_10_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_10_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_10_UP* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_10_UP (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;
	
	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_10_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_10_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_10_UP* ED_CONST Destin, ED_EXLONG Length))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_SYSTEM_INFORMATION_TYPE_10_BODY (Buffer, CurrOfs, (&(Destin->contents)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1340> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1340, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1341> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1340, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_10bis_UP
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_10bis_UP (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_10bis_UP* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 10, 6);
		CurrOfs += 6;
		
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->contents> DOT=<.> */
		Len = ENCODE_c_SYSTEM_INFORMATION_TYPE_10bis_BODY (Buffer, CurrOfs, (&(Source->contents)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1342> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_10bis_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_10bis_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_10bis_UP* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_10bis_UP (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_10bis_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_10bis_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_10bis_UP* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_10bis_UP (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_10bis_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_10bis_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_10bis_UP* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_10bis_UP (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;
	
	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_10bis_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_10bis_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_10bis_UP* ED_CONST Destin, ED_EXLONG Length))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_SYSTEM_INFORMATION_TYPE_10bis_BODY (Buffer, CurrOfs, (&(Destin->contents)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1343> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1343, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1344> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1343, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_10ter_UP
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_10ter_UP (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_10ter_UP* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 11, 6);
		CurrOfs += 6;
		
	}
	
	
	/* Code for CellChannelDescription */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->CellChannelDescription> DOT=<.> */
		Len = ENCODE_c_CellChannel (Buffer, CurrOfs, (&(Source->CellChannelDescription)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1345> Error encoding subfield CellChannelDescription\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for contents */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->contents> DOT=<.> */
		Len = ENCODE_c_SYSTEM_INFORMATION_TYPE_10ter (Buffer, CurrOfs, (&(Source->contents)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1346> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_10ter_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_10ter_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_10ter_UP* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_10ter_UP (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_10ter_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_10ter_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_10ter_UP* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_10ter_UP (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_10ter_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_10ter_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_10ter_UP* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_10ter_UP (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;
	
	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_10ter_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_10ter_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_10ter_UP* ED_CONST Destin, ED_EXLONG Length))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE CellChannelDescription
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 128;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, (&(Destin->CellChannelDescription)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1347> Error decoding subfield CellChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1347, (Destin->CellChannelDescription))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1348> Message too short decoding subfield CellChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1347, (Destin->CellChannelDescription))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_SYSTEM_INFORMATION_TYPE_10ter (Buffer, CurrOfs, (&(Destin->contents)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1349> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1349, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1350> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1349, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE MEASUREMENT_INFORMATION
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_MEASUREMENT_INFORMATION (char* Buffer, ED_EXLONG BitOffset, const c_MEASUREMENT_INFORMATION* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 5, 6);
		CurrOfs += 6;
		
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->contents> DOT=<.> */
		Len = ENCODE_c_Measurement_information (Buffer, CurrOfs, (&(Source->contents)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1351> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE MEASUREMENT_INFORMATION
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MEASUREMENT_INFORMATION (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MEASUREMENT_INFORMATION* ED_CONST Source))
{
	return L3_ENCODE_c_MEASUREMENT_INFORMATION (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE MEASUREMENT_INFORMATION
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MEASUREMENT_INFORMATION (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MEASUREMENT_INFORMATION* ED_CONST Source))
{
	return L3_ENCODE_c_MEASUREMENT_INFORMATION (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE MEASUREMENT_INFORMATION
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MEASUREMENT_INFORMATION (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MEASUREMENT_INFORMATION* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_MEASUREMENT_INFORMATION (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;
	
	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE MEASUREMENT_INFORMATION
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MEASUREMENT_INFORMATION (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MEASUREMENT_INFORMATION* ED_CONST Destin, ED_EXLONG Length))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_Measurement_information (Buffer, CurrOfs, (&(Destin->contents)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1352> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1352, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1353> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1352, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE ENHANCED_MEASUREMENT_REPORT
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_ENHANCED_MEASUREMENT_REPORT (char* Buffer, ED_EXLONG BitOffset, const c_ENHANCED_MEASUREMENT_REPORT* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 4, 6);
		CurrOfs += 6;
		
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->contents> DOT=<.> */
		Len = ENCODE_c_Enhanced_Measurement_report (Buffer, CurrOfs, (&(Source->contents)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1354> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE ENHANCED_MEASUREMENT_REPORT
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_ENHANCED_MEASUREMENT_REPORT (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ENHANCED_MEASUREMENT_REPORT* ED_CONST Source))
{
	return L3_ENCODE_c_ENHANCED_MEASUREMENT_REPORT (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE ENHANCED_MEASUREMENT_REPORT
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_ENHANCED_MEASUREMENT_REPORT (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ENHANCED_MEASUREMENT_REPORT* ED_CONST Source))
{
	return L3_ENCODE_c_ENHANCED_MEASUREMENT_REPORT (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE ENHANCED_MEASUREMENT_REPORT
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_ENHANCED_MEASUREMENT_REPORT (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ENHANCED_MEASUREMENT_REPORT* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_ENHANCED_MEASUREMENT_REPORT (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;
	
	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE ENHANCED_MEASUREMENT_REPORT
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_ENHANCED_MEASUREMENT_REPORT (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ENHANCED_MEASUREMENT_REPORT* ED_CONST Destin, ED_EXLONG Length))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_Enhanced_Measurement_report (Buffer, CurrOfs, (&(Destin->contents)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1355> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1355, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1356> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1355, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE VGCS_NEIGHBOUR_CELL_INFORMATION
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_VGCS_NEIGHBOUR_CELL_INFORMATION (char* Buffer, ED_EXLONG BitOffset, const c_VGCS_NEIGHBOUR_CELL_INFORMATION* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 12, 6);
		CurrOfs += 6;
		
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->contents> DOT=<.> */
		Len = ENCODE_c_VGCS_NEIGHBOUR_CELL_INFORMATION_BODY (Buffer, CurrOfs, (&(Source->contents)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1357> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE VGCS_NEIGHBOUR_CELL_INFORMATION
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_VGCS_NEIGHBOUR_CELL_INFORMATION (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VGCS_NEIGHBOUR_CELL_INFORMATION* ED_CONST Source))
{
	return L3_ENCODE_c_VGCS_NEIGHBOUR_CELL_INFORMATION (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE VGCS_NEIGHBOUR_CELL_INFORMATION
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_VGCS_NEIGHBOUR_CELL_INFORMATION (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VGCS_NEIGHBOUR_CELL_INFORMATION* ED_CONST Source))
{
	return L3_ENCODE_c_VGCS_NEIGHBOUR_CELL_INFORMATION (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE VGCS_NEIGHBOUR_CELL_INFORMATION
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_VGCS_NEIGHBOUR_CELL_INFORMATION (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VGCS_NEIGHBOUR_CELL_INFORMATION* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_VGCS_NEIGHBOUR_CELL_INFORMATION (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;
	
	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE VGCS_NEIGHBOUR_CELL_INFORMATION
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_VGCS_NEIGHBOUR_CELL_INFORMATION (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VGCS_NEIGHBOUR_CELL_INFORMATION* ED_CONST Destin, ED_EXLONG Length))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_VGCS_NEIGHBOUR_CELL_INFORMATION_BODY (Buffer, CurrOfs, (&(Destin->contents)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1358> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1358, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1359> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1358, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE NOTIFY_APPLICATION_DATA
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_NOTIFY_APPLICATION_DATA (char* Buffer, ED_EXLONG BitOffset, const c_NOTIFY_APPLICATION_DATA* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 13, 6);
		CurrOfs += 6;
		
	}
	
	
	/* Code for contents */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->contents> DOT=<.> */
		Len = ENCODE_c_NOTIFY_APPLICATION_DATA_BODY (Buffer, CurrOfs, (&(Source->contents)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1360> Error encoding subfield contents\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE NOTIFY_APPLICATION_DATA
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_NOTIFY_APPLICATION_DATA (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_NOTIFY_APPLICATION_DATA* ED_CONST Source))
{
	return L3_ENCODE_c_NOTIFY_APPLICATION_DATA (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE NOTIFY_APPLICATION_DATA
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_NOTIFY_APPLICATION_DATA (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_NOTIFY_APPLICATION_DATA* ED_CONST Source))
{
	return L3_ENCODE_c_NOTIFY_APPLICATION_DATA (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE NOTIFY_APPLICATION_DATA
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_NOTIFY_APPLICATION_DATA (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_NOTIFY_APPLICATION_DATA* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_NOTIFY_APPLICATION_DATA (Buffer, (BitOffset+6), Destin, Length-(6));
	if (Len < 0) return Len;
	
	return Len+6;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE NOTIFY_APPLICATION_DATA
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_NOTIFY_APPLICATION_DATA (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_NOTIFY_APPLICATION_DATA* ED_CONST Destin, ED_EXLONG Length))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	
	/*----------------------------------------------------- 
		Code for IE contents
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_NOTIFY_APPLICATION_DATA_BODY (Buffer, CurrOfs, (&(Destin->contents)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1361> Error decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1361, (Destin->contents))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1362> Message too short decoding subfield contents\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1361, (Destin->contents))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
int Match_c_NOTIFICATION_FACCH (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 1) /* message type */
	);
}

int Match_c_VBS_VGCS_RECONFIGURE (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 6) /* message type */
	);
}

int Match_c_VBS_VGCS_RECONFIGURE2 (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 7) /* message type */
	);
}

int Match_c_UPLINK_FREE (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 2) /* message type */
	);
}

int Match_c_VGCS_ADDITIONAL_INFORMATION (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 8) /* message type */
	);
}

int Match_c_VGCS_SMS_INFORMATION (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 9) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_10_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 0) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_10bis_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 10) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_10ter_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 11) /* message type */
	);
}

int Match_c_MEASUREMENT_INFORMATION (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 5) /* message type */
	);
}

int Match_c_ENHANCED_MEASUREMENT_REPORT (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 4) /* message type */
	);
}

int Match_c_VGCS_NEIGHBOUR_CELL_INFORMATION (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 12) /* message type */
	);
}

int Match_c_NOTIFY_APPLICATION_DATA (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		((EDBitsToInt (Buffer, BitOffset, 8) & 0x3F) == 13) /* message type */
	);
}


/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.152
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#include "RRUplink_RR.h"
#include "ed_c_known_ie_RR.h"
#include "ed_tlv.h"
#include "UserDefinedDataTypes_RR.h"
#include "CSN1DataTypes_RR.h"
#if ED_VERSION != 10152
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.152
#endif


#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE ASSIGNMENT_COMPLETE_UP
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_ASSIGNMENT_COMPLETE_UP (char* Buffer, ED_EXLONG BitOffset, const c_ASSIGNMENT_COMPLETE_UP* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 41, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for RrCause */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->RrCause> DOT=<.> */
		Len = ENCODE_c_RRCause (Buffer, CurrOfs, (&(Source->RrCause)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:724> Error encoding subfield RrCause\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE ASSIGNMENT_COMPLETE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_ASSIGNMENT_COMPLETE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ASSIGNMENT_COMPLETE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_ASSIGNMENT_COMPLETE_UP (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE ASSIGNMENT_COMPLETE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_ASSIGNMENT_COMPLETE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ASSIGNMENT_COMPLETE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_ASSIGNMENT_COMPLETE_UP (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE ASSIGNMENT_COMPLETE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_ASSIGNMENT_COMPLETE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ASSIGNMENT_COMPLETE_UP* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_ASSIGNMENT_COMPLETE_UP (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE ASSIGNMENT_COMPLETE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_ASSIGNMENT_COMPLETE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ASSIGNMENT_COMPLETE_UP* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE RrCause
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RRCause (Buffer, CurrOfs, (&(Destin->RrCause)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:725> Error decoding subfield RrCause\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 725, (Destin->RrCause))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:726> Message too short decoding subfield RrCause\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 725, (Destin->RrCause))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE ASSIGNMENT_FAILURE_UP
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_ASSIGNMENT_FAILURE_UP (char* Buffer, ED_EXLONG BitOffset, const c_ASSIGNMENT_FAILURE_UP* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 47, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for RrCause */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->RrCause> DOT=<.> */
		Len = ENCODE_c_RRCause (Buffer, CurrOfs, (&(Source->RrCause)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:727> Error encoding subfield RrCause\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE ASSIGNMENT_FAILURE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_ASSIGNMENT_FAILURE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ASSIGNMENT_FAILURE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_ASSIGNMENT_FAILURE_UP (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE ASSIGNMENT_FAILURE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_ASSIGNMENT_FAILURE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ASSIGNMENT_FAILURE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_ASSIGNMENT_FAILURE_UP (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE ASSIGNMENT_FAILURE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_ASSIGNMENT_FAILURE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ASSIGNMENT_FAILURE_UP* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_ASSIGNMENT_FAILURE_UP (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE ASSIGNMENT_FAILURE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_ASSIGNMENT_FAILURE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ASSIGNMENT_FAILURE_UP* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE RrCause
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RRCause (Buffer, CurrOfs, (&(Destin->RrCause)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:728> Error decoding subfield RrCause\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 728, (Destin->RrCause))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:729> Message too short decoding subfield RrCause\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 728, (Destin->RrCause))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP (char* Buffer, ED_EXLONG BitOffset, const c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 23, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for ChannelDescription */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ChannelDescription> DOT=<.> */
		Len = ENCODE_c_TChDesc2 (Buffer, CurrOfs, (&(Source->ChannelDescription)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:730> Error encoding subfield ChannelDescription\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ChannelMode */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ChannelMode> DOT=<.> */
		Len = ENCODE_c_ChannelMode (Buffer, CurrOfs, (&(Source->ChannelMode)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:731> Error encoding subfield ChannelMode\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ExtendedTSCSet */
	{
		if (Source->ExtendedTSCSet_Present) {
			/* Append to buffer IEI tag 0x6D */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x6D), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ExtendedTSCSet> DOT=<->> */
			Len = ENCODE_c_ExtendedTSCSet (Buffer, CurrOfs, Source->ExtendedTSCSet);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:732> Error encoding subfield ExtendedTSCSet\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP* ED_CONST Destin, ED_EXLONG Length))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Table containing the expected sequence of IEIs */
	const TEDTLVSkipItem TLVSkipItems [] = {
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{109, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	ED_WARNING_REMOVER (TLVSkipItems);
	
	/*----------------------------------------------------- 
		Code for IE ChannelDescription
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_TChDesc2 (Buffer, CurrOfs, (&(Destin->ChannelDescription)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:733> Error decoding subfield ChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 733, (Destin->ChannelDescription))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:734> Message too short decoding subfield ChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 733, (Destin->ChannelDescription))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ChannelMode
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_ChannelMode (Buffer, CurrOfs, (&(Destin->ChannelMode)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:735> Error decoding subfield ChannelMode\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 735, (Destin->ChannelMode))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:736> Message too short decoding subfield ChannelMode\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 735, (Destin->ChannelMode))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ExtendedTSCSet
	------------------------------------------------------*/
	/* Detect IEI tag 0x6D */
	ED_EXPECT_OPTIONAL_IE (0x6D,  8, 737, 2, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x6D) {
		SETPRESENT_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP_ExtendedTSCSet (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ExtendedTSCSet (Buffer, CurrOfs, Destin->ExtendedTSCSet, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:738> Error decoding subfield ExtendedTSCSet\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP_ExtendedTSCSet (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x6D, 738, (Destin->ExtendedTSCSet))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:739> Message too short decoding subfield ExtendedTSCSet\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP_ExtendedTSCSet (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x6D, 738, (Destin->ExtendedTSCSet))
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CIPHERING_MODE_COMPLETE_UP
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_CIPHERING_MODE_COMPLETE_UP (char* Buffer, ED_EXLONG BitOffset, const c_CIPHERING_MODE_COMPLETE_UP* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 50, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for MobileEquipmentId */
	{
		int TLV_Base = CurrOfs;
		if (Source->MobileEquipmentId_Present) {
			/* Append to buffer IEI tag 0x17 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x17), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->MobileEquipmentId> DOT=<->> */
			Len = ENCODE_c_RRMobileId (Buffer, CurrOfs+8, Source->MobileEquipmentId);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:740> Error encoding subfield MobileEquipmentId\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CIPHERING_MODE_COMPLETE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CIPHERING_MODE_COMPLETE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CIPHERING_MODE_COMPLETE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_CIPHERING_MODE_COMPLETE_UP (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE CIPHERING_MODE_COMPLETE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CIPHERING_MODE_COMPLETE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CIPHERING_MODE_COMPLETE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_CIPHERING_MODE_COMPLETE_UP (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CIPHERING_MODE_COMPLETE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CIPHERING_MODE_COMPLETE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CIPHERING_MODE_COMPLETE_UP* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_CIPHERING_MODE_COMPLETE_UP (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CIPHERING_MODE_COMPLETE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CIPHERING_MODE_COMPLETE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CIPHERING_MODE_COMPLETE_UP* ED_CONST Destin, ED_EXLONG Length))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Table containing the expected sequence of IEIs */
	const TEDTLVSkipItem TLVSkipItems [] = {
		{23, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	ED_WARNING_REMOVER (TLVSkipItems);
	
	/*----------------------------------------------------- 
		Code for IE MobileEquipmentId
	------------------------------------------------------*/
	/* Detect IEI tag 0x17 */
	ED_EXPECT_OPTIONAL_IE (0x17,  8, 741, 0, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x17) {
		SETPRESENT_c_CIPHERING_MODE_COMPLETE_UP_MobileEquipmentId (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 72)) {
			ED_SIGNAL_ERROR ("<ERRID:742> Size error decoding IE MobileEquipmentId\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_CIPHERING_MODE_COMPLETE_UP_MobileEquipmentId (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x17, 742, (Destin->MobileEquipmentId))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_RRMobileId (Buffer, CurrOfs, Destin->MobileEquipmentId, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:743> Error decoding subfield MobileEquipmentId\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CIPHERING_MODE_COMPLETE_UP_MobileEquipmentId (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x17, 743, (Destin->MobileEquipmentId))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:744> Message too short decoding subfield MobileEquipmentId\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CIPHERING_MODE_COMPLETE_UP_MobileEquipmentId (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x17, 743, (Destin->MobileEquipmentId))
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CLASSMARK_CHANGE_UP
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_CLASSMARK_CHANGE_UP (char* Buffer, ED_EXLONG BitOffset, const c_CLASSMARK_CHANGE_UP* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 22, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for MobileStationClassmark */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->MobileStationClassmark> DOT=<.> */
		Len = ENCODE_c_RRMobileStationClassmark2 (Buffer, CurrOfs+8, (&(Source->MobileStationClassmark)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:745> Error encoding subfield MobileStationClassmark\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for AdditionalMobileStationClassmarkInfo */
	{
		int TLV_Base = CurrOfs;
		if (Source->AdditionalMobileStationClassmarkInfo_Present) {
			/* Append to buffer IEI tag 0x20 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x20), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->AdditionalMobileStationClassmarkInfo> DOT=<->> */
			Len = ENCODE_c_RRClassmark3Value (Buffer, CurrOfs+8, Source->AdditionalMobileStationClassmarkInfo);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:746> Error encoding subfield AdditionalMobileStationClassmarkInfo\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CLASSMARK_CHANGE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CLASSMARK_CHANGE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CLASSMARK_CHANGE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_CLASSMARK_CHANGE_UP (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE CLASSMARK_CHANGE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CLASSMARK_CHANGE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CLASSMARK_CHANGE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_CLASSMARK_CHANGE_UP (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CLASSMARK_CHANGE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CLASSMARK_CHANGE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CLASSMARK_CHANGE_UP* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_CLASSMARK_CHANGE_UP (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CLASSMARK_CHANGE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CLASSMARK_CHANGE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CLASSMARK_CHANGE_UP* ED_CONST Destin, ED_EXLONG Length))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Table containing the expected sequence of IEIs */
	const TEDTLVSkipItem TLVSkipItems [] = {
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{32, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	ED_WARNING_REMOVER (TLVSkipItems);
	
	/*----------------------------------------------------- 
		Code for IE MobileStationClassmark
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Len != 24) {
		ED_SIGNAL_ERROR ("<ERRID:747> Size error decoding IE MobileStationClassmark\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 747, (Destin->MobileStationClassmark))
	} 
#endif
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RRMobileStationClassmark2 (Buffer, CurrOfs, (&(Destin->MobileStationClassmark)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:748> Error decoding subfield MobileStationClassmark\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 748, (Destin->MobileStationClassmark))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:749> Message too short decoding subfield MobileStationClassmark\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 748, (Destin->MobileStationClassmark))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE AdditionalMobileStationClassmarkInfo
	------------------------------------------------------*/
	/* Detect IEI tag 0x20 */
	ED_EXPECT_OPTIONAL_IE (0x20,  8, 750, 1, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x20) {
		SETPRESENT_c_CLASSMARK_CHANGE_UP_AdditionalMobileStationClassmarkInfo (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 96)) {
			ED_SIGNAL_ERROR ("<ERRID:751> Size error decoding IE AdditionalMobileStationClassmarkInfo\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_CLASSMARK_CHANGE_UP_AdditionalMobileStationClassmarkInfo (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x20, 751, (Destin->AdditionalMobileStationClassmarkInfo))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_RRClassmark3Value (Buffer, CurrOfs, Destin->AdditionalMobileStationClassmarkInfo, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:752> Error decoding subfield AdditionalMobileStationClassmarkInfo\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CLASSMARK_CHANGE_UP_AdditionalMobileStationClassmarkInfo (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x20, 752, (Destin->AdditionalMobileStationClassmarkInfo))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:753> Message too short decoding subfield AdditionalMobileStationClassmarkInfo\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CLASSMARK_CHANGE_UP_AdditionalMobileStationClassmarkInfo (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x20, 752, (Destin->AdditionalMobileStationClassmarkInfo))
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE UTRAN_CLASSMARK_CHANGE_UP
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_UTRAN_CLASSMARK_CHANGE_UP (char* Buffer, ED_EXLONG BitOffset, const c_UTRAN_CLASSMARK_CHANGE_UP* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 96, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for UTRANClassmark */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->UTRANClassmark> DOT=<.> */
		EDCopyBits (Buffer, CurrOfs+8, Source->UTRANClassmark.value, 0, Source->UTRANClassmark.usedBits);
		Len = Source->UTRANClassmark.usedBits;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:754> Error encoding subfield UTRANClassmark\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE UTRAN_CLASSMARK_CHANGE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_UTRAN_CLASSMARK_CHANGE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_UTRAN_CLASSMARK_CHANGE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_UTRAN_CLASSMARK_CHANGE_UP (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE UTRAN_CLASSMARK_CHANGE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_UTRAN_CLASSMARK_CHANGE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_UTRAN_CLASSMARK_CHANGE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_UTRAN_CLASSMARK_CHANGE_UP (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE UTRAN_CLASSMARK_CHANGE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_UTRAN_CLASSMARK_CHANGE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_UTRAN_CLASSMARK_CHANGE_UP* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_UTRAN_CLASSMARK_CHANGE_UP (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE UTRAN_CLASSMARK_CHANGE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_UTRAN_CLASSMARK_CHANGE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_UTRAN_CLASSMARK_CHANGE_UP* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE UTRANClassmark
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if ((Len < 8) || (Len > 4792)) {
		ED_SIGNAL_ERROR ("<ERRID:755> Size error decoding IE UTRANClassmark\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 755, (Destin->UTRANClassmark))
	} 
#endif
	/* Read value part LOCATOR_16 */
	/* LOCATOR SETTINGS LOCBIN2 */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-51984=EDCore::TDMBinary) */Destin->UTRANClassmark___LOCATOR), CurrOfs, Len);
	if (Len > 0) {
		/* BINDEC02 */
		ALLOC_c_UTRAN_CLASSMARK_CHANGE_UP_UTRANClassmark (&(Destin->UTRANClassmark), Len);
	
		EDCopyBits (Destin->UTRANClassmark.value, 0, Buffer, CurrOfs, Len);
		Destin->UTRANClassmark.usedBits = Len;
	}
	
	RetLen = Len;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:756> Error decoding subfield UTRANClassmark\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 756, (Destin->UTRANClassmark))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:757> Message too short decoding subfield UTRANClassmark\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 756, (Destin->UTRANClassmark))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CDMA2000_CLASSMARK_CHANGE_UP
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_CDMA2000_CLASSMARK_CHANGE_UP (char* Buffer, ED_EXLONG BitOffset, const c_CDMA2000_CLASSMARK_CHANGE_UP* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 98, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for TerminalInformation */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->TerminalInformation> DOT=<.> */
		EDCopyBits (Buffer, CurrOfs+8, Source->TerminalInformation.value, 0, Source->TerminalInformation.usedBits);
		Len = Source->TerminalInformation.usedBits;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:758> Error encoding subfield TerminalInformation\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for SecurityStatus */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->SecurityStatus> DOT=<.> */
		EDCopyBits (Buffer, CurrOfs+8, Source->SecurityStatus.value, 0, Source->SecurityStatus.usedBits);
		Len = Source->SecurityStatus.usedBits;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:759> Error encoding subfield SecurityStatus\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for BandClassInformation */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->BandClassInformation> DOT=<.> */
		EDCopyBits (Buffer, CurrOfs+8, Source->BandClassInformation.value, 0, Source->BandClassInformation.usedBits);
		Len = Source->BandClassInformation.usedBits;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:760> Error encoding subfield BandClassInformation\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for PowerClassInformation */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->PowerClassInformation> DOT=<.> */
		EDCopyBits (Buffer, CurrOfs+8, Source->PowerClassInformation.value, 0, Source->PowerClassInformation.usedBits);
		Len = Source->PowerClassInformation.usedBits;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:761> Error encoding subfield PowerClassInformation\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for OperatingModeInformation */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->OperatingModeInformation> DOT=<.> */
		EDCopyBits (Buffer, CurrOfs+8, Source->OperatingModeInformation.value, 0, Source->OperatingModeInformation.usedBits);
		Len = Source->OperatingModeInformation.usedBits;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:762> Error encoding subfield OperatingModeInformation\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for ServiceOptionInformation */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->ServiceOptionInformation> DOT=<.> */
		EDCopyBits (Buffer, CurrOfs+8, Source->ServiceOptionInformation.value, 0, Source->ServiceOptionInformation.usedBits);
		Len = Source->ServiceOptionInformation.usedBits;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:763> Error encoding subfield ServiceOptionInformation\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for MultiplexOptionInformation */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->MultiplexOptionInformation> DOT=<.> */
		EDCopyBits (Buffer, CurrOfs+8, Source->MultiplexOptionInformation.value, 0, Source->MultiplexOptionInformation.usedBits);
		Len = Source->MultiplexOptionInformation.usedBits;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:764> Error encoding subfield MultiplexOptionInformation\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for PowerControlInformation */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->PowerControlInformation> DOT=<.> */
		EDCopyBits (Buffer, CurrOfs+8, Source->PowerControlInformation.value, 0, Source->PowerControlInformation.usedBits);
		Len = Source->PowerControlInformation.usedBits;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:765> Error encoding subfield PowerControlInformation\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for CapabilityInformation */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->CapabilityInformation> DOT=<.> */
		EDCopyBits (Buffer, CurrOfs+8, Source->CapabilityInformation.value, 0, Source->CapabilityInformation.usedBits);
		Len = Source->CapabilityInformation.usedBits;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:766> Error encoding subfield CapabilityInformation\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for ChannelConfigurationCapabilityInformation */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->ChannelConfigurationCapabilityInformation> DOT=<.> */
		EDCopyBits (Buffer, CurrOfs+8, Source->ChannelConfigurationCapabilityInformation.value, 0, Source->ChannelConfigurationCapabilityInformation.usedBits);
		Len = Source->ChannelConfigurationCapabilityInformation.usedBits;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:767> Error encoding subfield ChannelConfigurationCapabilityInformation\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for ExtendedMultiplexOptionInformation */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->ExtendedMultiplexOptionInformation> DOT=<.> */
		EDCopyBits (Buffer, CurrOfs+8, Source->ExtendedMultiplexOptionInformation.value, 0, Source->ExtendedMultiplexOptionInformation.usedBits);
		Len = Source->ExtendedMultiplexOptionInformation.usedBits;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:768> Error encoding subfield ExtendedMultiplexOptionInformation\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for BandSubclassInformation */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->BandSubclassInformation> DOT=<.> */
		EDCopyBits (Buffer, CurrOfs+8, Source->BandSubclassInformation.value, 0, Source->BandSubclassInformation.usedBits);
		Len = Source->BandSubclassInformation.usedBits;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:769> Error encoding subfield BandSubclassInformation\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for EncryptionCapability */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->EncryptionCapability> DOT=<.> */
		EDCopyBits (Buffer, CurrOfs+8, Source->EncryptionCapability.value, 0, Source->EncryptionCapability.usedBits);
		Len = Source->EncryptionCapability.usedBits;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:770> Error encoding subfield EncryptionCapability\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CDMA2000_CLASSMARK_CHANGE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CDMA2000_CLASSMARK_CHANGE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CDMA2000_CLASSMARK_CHANGE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_CDMA2000_CLASSMARK_CHANGE_UP (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE CDMA2000_CLASSMARK_CHANGE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CDMA2000_CLASSMARK_CHANGE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CDMA2000_CLASSMARK_CHANGE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_CDMA2000_CLASSMARK_CHANGE_UP (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CDMA2000_CLASSMARK_CHANGE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CDMA2000_CLASSMARK_CHANGE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CDMA2000_CLASSMARK_CHANGE_UP* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_CDMA2000_CLASSMARK_CHANGE_UP (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CDMA2000_CLASSMARK_CHANGE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CDMA2000_CLASSMARK_CHANGE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CDMA2000_CLASSMARK_CHANGE_UP* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE TerminalInformation
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Len > 4792) {
		ED_SIGNAL_ERROR ("<ERRID:771> Size error decoding IE TerminalInformation\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 771, (Destin->TerminalInformation))
	} 
#endif
	/* Read value part LOCATOR_16 */
	/* LOCATOR SETTINGS LOCBIN2 */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-51987=EDCore::TDMBinary) */Destin->TerminalInformation___LOCATOR), CurrOfs, Len);
	if (Len > 0) {
		/* BINDEC02 */
		ALLOC_c_CDMA2000_CLASSMARK_CHANGE_UP_TerminalInformation (&(Destin->TerminalInformation), Len);
	
		EDCopyBits (Destin->TerminalInformation.value, 0, Buffer, CurrOfs, Len);
		Destin->TerminalInformation.usedBits = Len;
	}
	
	RetLen = Len;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:772> Error decoding subfield TerminalInformation\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 772, (Destin->TerminalInformation))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:773> Message too short decoding subfield TerminalInformation\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 772, (Destin->TerminalInformation))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE SecurityStatus
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Len > 4792) {
		ED_SIGNAL_ERROR ("<ERRID:774> Size error decoding IE SecurityStatus\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 774, (Destin->SecurityStatus))
	} 
#endif
	/* Read value part LOCATOR_16 */
	/* LOCATOR SETTINGS LOCBIN2 */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-51989=EDCore::TDMBinary) */Destin->SecurityStatus___LOCATOR), CurrOfs, Len);
	if (Len > 0) {
		/* BINDEC02 */
		ALLOC_c_CDMA2000_CLASSMARK_CHANGE_UP_SecurityStatus (&(Destin->SecurityStatus), Len);
	
		EDCopyBits (Destin->SecurityStatus.value, 0, Buffer, CurrOfs, Len);
		Destin->SecurityStatus.usedBits = Len;
	}
	
	RetLen = Len;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:775> Error decoding subfield SecurityStatus\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 775, (Destin->SecurityStatus))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:776> Message too short decoding subfield SecurityStatus\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 775, (Destin->SecurityStatus))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE BandClassInformation
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Len > 4792) {
		ED_SIGNAL_ERROR ("<ERRID:777> Size error decoding IE BandClassInformation\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 777, (Destin->BandClassInformation))
	} 
#endif
	/* Read value part LOCATOR_16 */
	/* LOCATOR SETTINGS LOCBIN2 */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-51991=EDCore::TDMBinary) */Destin->BandClassInformation___LOCATOR), CurrOfs, Len);
	if (Len > 0) {
		/* BINDEC02 */
		ALLOC_c_CDMA2000_CLASSMARK_CHANGE_UP_BandClassInformation (&(Destin->BandClassInformation), Len);
	
		EDCopyBits (Destin->BandClassInformation.value, 0, Buffer, CurrOfs, Len);
		Destin->BandClassInformation.usedBits = Len;
	}
	
	RetLen = Len;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:778> Error decoding subfield BandClassInformation\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 778, (Destin->BandClassInformation))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:779> Message too short decoding subfield BandClassInformation\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 778, (Destin->BandClassInformation))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE PowerClassInformation
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Len > 4792) {
		ED_SIGNAL_ERROR ("<ERRID:780> Size error decoding IE PowerClassInformation\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 780, (Destin->PowerClassInformation))
	} 
#endif
	/* Read value part LOCATOR_16 */
	/* LOCATOR SETTINGS LOCBIN2 */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-51993=EDCore::TDMBinary) */Destin->PowerClassInformation___LOCATOR), CurrOfs, Len);
	if (Len > 0) {
		/* BINDEC02 */
		ALLOC_c_CDMA2000_CLASSMARK_CHANGE_UP_PowerClassInformation (&(Destin->PowerClassInformation), Len);
	
		EDCopyBits (Destin->PowerClassInformation.value, 0, Buffer, CurrOfs, Len);
		Destin->PowerClassInformation.usedBits = Len;
	}
	
	RetLen = Len;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:781> Error decoding subfield PowerClassInformation\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 781, (Destin->PowerClassInformation))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:782> Message too short decoding subfield PowerClassInformation\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 781, (Destin->PowerClassInformation))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE OperatingModeInformation
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Len > 4792) {
		ED_SIGNAL_ERROR ("<ERRID:783> Size error decoding IE OperatingModeInformation\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 783, (Destin->OperatingModeInformation))
	} 
#endif
	/* Read value part LOCATOR_16 */
	/* LOCATOR SETTINGS LOCBIN2 */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-51995=EDCore::TDMBinary) */Destin->OperatingModeInformation___LOCATOR), CurrOfs, Len);
	if (Len > 0) {
		/* BINDEC02 */
		ALLOC_c_CDMA2000_CLASSMARK_CHANGE_UP_OperatingModeInformation (&(Destin->OperatingModeInformation), Len);
	
		EDCopyBits (Destin->OperatingModeInformation.value, 0, Buffer, CurrOfs, Len);
		Destin->OperatingModeInformation.usedBits = Len;
	}
	
	RetLen = Len;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:784> Error decoding subfield OperatingModeInformation\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 784, (Destin->OperatingModeInformation))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:785> Message too short decoding subfield OperatingModeInformation\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 784, (Destin->OperatingModeInformation))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ServiceOptionInformation
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Len > 4792) {
		ED_SIGNAL_ERROR ("<ERRID:786> Size error decoding IE ServiceOptionInformation\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 786, (Destin->ServiceOptionInformation))
	} 
#endif
	/* Read value part LOCATOR_16 */
	/* LOCATOR SETTINGS LOCBIN2 */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-51997=EDCore::TDMBinary) */Destin->ServiceOptionInformation___LOCATOR), CurrOfs, Len);
	if (Len > 0) {
		/* BINDEC02 */
		ALLOC_c_CDMA2000_CLASSMARK_CHANGE_UP_ServiceOptionInformation (&(Destin->ServiceOptionInformation), Len);
	
		EDCopyBits (Destin->ServiceOptionInformation.value, 0, Buffer, CurrOfs, Len);
		Destin->ServiceOptionInformation.usedBits = Len;
	}
	
	RetLen = Len;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:787> Error decoding subfield ServiceOptionInformation\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 787, (Destin->ServiceOptionInformation))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:788> Message too short decoding subfield ServiceOptionInformation\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 787, (Destin->ServiceOptionInformation))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MultiplexOptionInformation
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Len > 4792) {
		ED_SIGNAL_ERROR ("<ERRID:789> Size error decoding IE MultiplexOptionInformation\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 789, (Destin->MultiplexOptionInformation))
	} 
#endif
	/* Read value part LOCATOR_16 */
	/* LOCATOR SETTINGS LOCBIN2 */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-51999=EDCore::TDMBinary) */Destin->MultiplexOptionInformation___LOCATOR), CurrOfs, Len);
	if (Len > 0) {
		/* BINDEC02 */
		ALLOC_c_CDMA2000_CLASSMARK_CHANGE_UP_MultiplexOptionInformation (&(Destin->MultiplexOptionInformation), Len);
	
		EDCopyBits (Destin->MultiplexOptionInformation.value, 0, Buffer, CurrOfs, Len);
		Destin->MultiplexOptionInformation.usedBits = Len;
	}
	
	RetLen = Len;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:790> Error decoding subfield MultiplexOptionInformation\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 790, (Destin->MultiplexOptionInformation))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:791> Message too short decoding subfield MultiplexOptionInformation\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 790, (Destin->MultiplexOptionInformation))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE PowerControlInformation
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Len > 4792) {
		ED_SIGNAL_ERROR ("<ERRID:792> Size error decoding IE PowerControlInformation\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 792, (Destin->PowerControlInformation))
	} 
#endif
	/* Read value part LOCATOR_16 */
	/* LOCATOR SETTINGS LOCBIN2 */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-52001=EDCore::TDMBinary) */Destin->PowerControlInformation___LOCATOR), CurrOfs, Len);
	if (Len > 0) {
		/* BINDEC02 */
		ALLOC_c_CDMA2000_CLASSMARK_CHANGE_UP_PowerControlInformation (&(Destin->PowerControlInformation), Len);
	
		EDCopyBits (Destin->PowerControlInformation.value, 0, Buffer, CurrOfs, Len);
		Destin->PowerControlInformation.usedBits = Len;
	}
	
	RetLen = Len;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:793> Error decoding subfield PowerControlInformation\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 793, (Destin->PowerControlInformation))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:794> Message too short decoding subfield PowerControlInformation\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 793, (Destin->PowerControlInformation))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE CapabilityInformation
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Len > 4792) {
		ED_SIGNAL_ERROR ("<ERRID:795> Size error decoding IE CapabilityInformation\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 795, (Destin->CapabilityInformation))
	} 
#endif
	/* Read value part LOCATOR_16 */
	/* LOCATOR SETTINGS LOCBIN2 */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-52003=EDCore::TDMBinary) */Destin->CapabilityInformation___LOCATOR), CurrOfs, Len);
	if (Len > 0) {
		/* BINDEC02 */
		ALLOC_c_CDMA2000_CLASSMARK_CHANGE_UP_CapabilityInformation (&(Destin->CapabilityInformation), Len);
	
		EDCopyBits (Destin->CapabilityInformation.value, 0, Buffer, CurrOfs, Len);
		Destin->CapabilityInformation.usedBits = Len;
	}
	
	RetLen = Len;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:796> Error decoding subfield CapabilityInformation\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 796, (Destin->CapabilityInformation))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:797> Message too short decoding subfield CapabilityInformation\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 796, (Destin->CapabilityInformation))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ChannelConfigurationCapabilityInformation
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Len > 4792) {
		ED_SIGNAL_ERROR ("<ERRID:798> Size error decoding IE ChannelConfigurationCapabilityInformation\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 798, (Destin->ChannelConfigurationCapabilityInformation))
	} 
#endif
	/* Read value part LOCATOR_16 */
	/* LOCATOR SETTINGS LOCBIN2 */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-52005=EDCore::TDMBinary) */Destin->ChannelConfigurationCapabilityInformation___LOCATOR), CurrOfs, Len);
	if (Len > 0) {
		/* BINDEC02 */
		ALLOC_c_CDMA2000_CLASSMARK_CHANGE_UP_ChannelConfigurationCapabilityInformation (&(Destin->ChannelConfigurationCapabilityInformation), Len);
	
		EDCopyBits (Destin->ChannelConfigurationCapabilityInformation.value, 0, Buffer, CurrOfs, Len);
		Destin->ChannelConfigurationCapabilityInformation.usedBits = Len;
	}
	
	RetLen = Len;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:799> Error decoding subfield ChannelConfigurationCapabilityInformation\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 799, (Destin->ChannelConfigurationCapabilityInformation))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:800> Message too short decoding subfield ChannelConfigurationCapabilityInformation\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 799, (Destin->ChannelConfigurationCapabilityInformation))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ExtendedMultiplexOptionInformation
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Len > 4792) {
		ED_SIGNAL_ERROR ("<ERRID:801> Size error decoding IE ExtendedMultiplexOptionInformation\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 801, (Destin->ExtendedMultiplexOptionInformation))
	} 
#endif
	/* Read value part LOCATOR_16 */
	/* LOCATOR SETTINGS LOCBIN2 */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-52007=EDCore::TDMBinary) */Destin->ExtendedMultiplexOptionInformation___LOCATOR), CurrOfs, Len);
	if (Len > 0) {
		/* BINDEC02 */
		ALLOC_c_CDMA2000_CLASSMARK_CHANGE_UP_ExtendedMultiplexOptionInformation (&(Destin->ExtendedMultiplexOptionInformation), Len);
	
		EDCopyBits (Destin->ExtendedMultiplexOptionInformation.value, 0, Buffer, CurrOfs, Len);
		Destin->ExtendedMultiplexOptionInformation.usedBits = Len;
	}
	
	RetLen = Len;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:802> Error decoding subfield ExtendedMultiplexOptionInformation\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 802, (Destin->ExtendedMultiplexOptionInformation))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:803> Message too short decoding subfield ExtendedMultiplexOptionInformation\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 802, (Destin->ExtendedMultiplexOptionInformation))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE BandSubclassInformation
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Len > 4792) {
		ED_SIGNAL_ERROR ("<ERRID:804> Size error decoding IE BandSubclassInformation\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 804, (Destin->BandSubclassInformation))
	} 
#endif
	/* Read value part LOCATOR_16 */
	/* LOCATOR SETTINGS LOCBIN2 */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-52009=EDCore::TDMBinary) */Destin->BandSubclassInformation___LOCATOR), CurrOfs, Len);
	if (Len > 0) {
		/* BINDEC02 */
		ALLOC_c_CDMA2000_CLASSMARK_CHANGE_UP_BandSubclassInformation (&(Destin->BandSubclassInformation), Len);
	
		EDCopyBits (Destin->BandSubclassInformation.value, 0, Buffer, CurrOfs, Len);
		Destin->BandSubclassInformation.usedBits = Len;
	}
	
	RetLen = Len;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:805> Error decoding subfield BandSubclassInformation\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 805, (Destin->BandSubclassInformation))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:806> Message too short decoding subfield BandSubclassInformation\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 805, (Destin->BandSubclassInformation))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE EncryptionCapability
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Len > 4792) {
		ED_SIGNAL_ERROR ("<ERRID:807> Size error decoding IE EncryptionCapability\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 807, (Destin->EncryptionCapability))
	} 
#endif
	/* Read value part LOCATOR_16 */
	/* LOCATOR SETTINGS LOCBIN2 */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-52011=EDCore::TDMBinary) */Destin->EncryptionCapability___LOCATOR), CurrOfs, Len);
	if (Len > 0) {
		/* BINDEC02 */
		ALLOC_c_CDMA2000_CLASSMARK_CHANGE_UP_EncryptionCapability (&(Destin->EncryptionCapability), Len);
	
		EDCopyBits (Destin->EncryptionCapability.value, 0, Buffer, CurrOfs, Len);
		Destin->EncryptionCapability.usedBits = Len;
	}
	
	RetLen = Len;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:808> Error decoding subfield EncryptionCapability\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 808, (Destin->EncryptionCapability))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:809> Message too short decoding subfield EncryptionCapability\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 808, (Destin->EncryptionCapability))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE GERAN_IU_MODE_CLASSMARK_CHANGE_UP
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_GERAN_IU_MODE_CLASSMARK_CHANGE_UP (char* Buffer, ED_EXLONG BitOffset, const c_GERAN_IU_MODE_CLASSMARK_CHANGE_UP* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 101, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for GERANIuModeClassmark */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->GERANIuModeClassmark> DOT=<.> */
		EDCopyBits (Buffer, CurrOfs+8, Source->GERANIuModeClassmark.value, 0, Source->GERANIuModeClassmark.usedBits);
		Len = Source->GERANIuModeClassmark.usedBits;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:810> Error encoding subfield GERANIuModeClassmark\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE GERAN_IU_MODE_CLASSMARK_CHANGE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_GERAN_IU_MODE_CLASSMARK_CHANGE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GERAN_IU_MODE_CLASSMARK_CHANGE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_GERAN_IU_MODE_CLASSMARK_CHANGE_UP (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE GERAN_IU_MODE_CLASSMARK_CHANGE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_GERAN_IU_MODE_CLASSMARK_CHANGE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GERAN_IU_MODE_CLASSMARK_CHANGE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_GERAN_IU_MODE_CLASSMARK_CHANGE_UP (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE GERAN_IU_MODE_CLASSMARK_CHANGE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_GERAN_IU_MODE_CLASSMARK_CHANGE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GERAN_IU_MODE_CLASSMARK_CHANGE_UP* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_GERAN_IU_MODE_CLASSMARK_CHANGE_UP (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE GERAN_IU_MODE_CLASSMARK_CHANGE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_GERAN_IU_MODE_CLASSMARK_CHANGE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GERAN_IU_MODE_CLASSMARK_CHANGE_UP* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE GERANIuModeClassmark
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if ((Len < 112) || (Len > 4792)) {
		ED_SIGNAL_ERROR ("<ERRID:811> Size error decoding IE GERANIuModeClassmark\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 811, (Destin->GERANIuModeClassmark))
	} 
#endif
	/* Read value part LOCATOR_16 */
	/* LOCATOR SETTINGS LOCBIN2 */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-52014=EDCore::TDMBinary) */Destin->GERANIuModeClassmark___LOCATOR), CurrOfs, Len);
	if (Len > 0) {
		/* BINDEC02 */
		ALLOC_c_GERAN_IU_MODE_CLASSMARK_CHANGE_UP_GERANIuModeClassmark (&(Destin->GERANIuModeClassmark), Len);
	
		EDCopyBits (Destin->GERANIuModeClassmark.value, 0, Buffer, CurrOfs, Len);
		Destin->GERANIuModeClassmark.usedBits = Len;
	}
	
	RetLen = Len;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:812> Error decoding subfield GERANIuModeClassmark\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 812, (Destin->GERANIuModeClassmark))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:813> Message too short decoding subfield GERANIuModeClassmark\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 812, (Destin->GERANIuModeClassmark))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CONFIGURATION_CHANGE_ACKNOWLEDGE_UP
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_CONFIGURATION_CHANGE_ACKNOWLEDGE_UP (char* Buffer, ED_EXLONG BitOffset, const c_CONFIGURATION_CHANGE_ACKNOWLEDGE_UP* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 49, 8);
		CurrOfs += 8;
		
	}
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CONFIGURATION_CHANGE_ACKNOWLEDGE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CONFIGURATION_CHANGE_ACKNOWLEDGE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONFIGURATION_CHANGE_ACKNOWLEDGE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_CONFIGURATION_CHANGE_ACKNOWLEDGE_UP (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE CONFIGURATION_CHANGE_ACKNOWLEDGE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CONFIGURATION_CHANGE_ACKNOWLEDGE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONFIGURATION_CHANGE_ACKNOWLEDGE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_CONFIGURATION_CHANGE_ACKNOWLEDGE_UP (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CONFIGURATION_CHANGE_ACKNOWLEDGE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CONFIGURATION_CHANGE_ACKNOWLEDGE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONFIGURATION_CHANGE_ACKNOWLEDGE_UP* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_CONFIGURATION_CHANGE_ACKNOWLEDGE_UP (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CONFIGURATION_CHANGE_ACKNOWLEDGE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CONFIGURATION_CHANGE_ACKNOWLEDGE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONFIGURATION_CHANGE_ACKNOWLEDGE_UP* ED_CONST Destin, ED_EXLONG Length))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CONFIGURATION_CHANGE_REJECT_UP
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_CONFIGURATION_CHANGE_REJECT_UP (char* Buffer, ED_EXLONG BitOffset, const c_CONFIGURATION_CHANGE_REJECT_UP* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 51, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for RrCause */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->RrCause> DOT=<.> */
		Len = ENCODE_c_RRCause (Buffer, CurrOfs, (&(Source->RrCause)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:814> Error encoding subfield RrCause\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CONFIGURATION_CHANGE_REJECT_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CONFIGURATION_CHANGE_REJECT_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONFIGURATION_CHANGE_REJECT_UP* ED_CONST Source))
{
	return L3_ENCODE_c_CONFIGURATION_CHANGE_REJECT_UP (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE CONFIGURATION_CHANGE_REJECT_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CONFIGURATION_CHANGE_REJECT_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONFIGURATION_CHANGE_REJECT_UP* ED_CONST Source))
{
	return L3_ENCODE_c_CONFIGURATION_CHANGE_REJECT_UP (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CONFIGURATION_CHANGE_REJECT_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CONFIGURATION_CHANGE_REJECT_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONFIGURATION_CHANGE_REJECT_UP* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_CONFIGURATION_CHANGE_REJECT_UP (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CONFIGURATION_CHANGE_REJECT_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CONFIGURATION_CHANGE_REJECT_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONFIGURATION_CHANGE_REJECT_UP* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE RrCause
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RRCause (Buffer, CurrOfs, (&(Destin->RrCause)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:815> Error decoding subfield RrCause\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 815, (Destin->RrCause))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:816> Message too short decoding subfield RrCause\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 815, (Destin->RrCause))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE DTM_ASSIGNMENT_COMMAND_UP
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_DTM_ASSIGNMENT_COMMAND_UP (char* Buffer, ED_EXLONG BitOffset, const c_DTM_ASSIGNMENT_COMMAND_UP* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 76, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for RrCause */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->RrCause> DOT=<.> */
		Len = ENCODE_c_RRCause (Buffer, CurrOfs, (&(Source->RrCause)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:817> Error encoding subfield RrCause\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE DTM_ASSIGNMENT_COMMAND_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_DTM_ASSIGNMENT_COMMAND_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DTM_ASSIGNMENT_COMMAND_UP* ED_CONST Source))
{
	return L3_ENCODE_c_DTM_ASSIGNMENT_COMMAND_UP (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE DTM_ASSIGNMENT_COMMAND_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_DTM_ASSIGNMENT_COMMAND_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DTM_ASSIGNMENT_COMMAND_UP* ED_CONST Source))
{
	return L3_ENCODE_c_DTM_ASSIGNMENT_COMMAND_UP (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE DTM_ASSIGNMENT_COMMAND_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_DTM_ASSIGNMENT_COMMAND_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DTM_ASSIGNMENT_COMMAND_UP* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_DTM_ASSIGNMENT_COMMAND_UP (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE DTM_ASSIGNMENT_COMMAND_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_DTM_ASSIGNMENT_COMMAND_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DTM_ASSIGNMENT_COMMAND_UP* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE RrCause
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RRCause (Buffer, CurrOfs, (&(Destin->RrCause)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:818> Error decoding subfield RrCause\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 818, (Destin->RrCause))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:819> Message too short decoding subfield RrCause\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 818, (Destin->RrCause))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE DTM_ASSIGNMENT_FAILURE_UP
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_DTM_ASSIGNMENT_FAILURE_UP (char* Buffer, ED_EXLONG BitOffset, const c_DTM_ASSIGNMENT_FAILURE_UP* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 72, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for RrCause */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->RrCause> DOT=<.> */
		Len = ENCODE_c_RRCause (Buffer, CurrOfs, (&(Source->RrCause)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:820> Error encoding subfield RrCause\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE DTM_ASSIGNMENT_FAILURE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_DTM_ASSIGNMENT_FAILURE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DTM_ASSIGNMENT_FAILURE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_DTM_ASSIGNMENT_FAILURE_UP (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE DTM_ASSIGNMENT_FAILURE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_DTM_ASSIGNMENT_FAILURE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DTM_ASSIGNMENT_FAILURE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_DTM_ASSIGNMENT_FAILURE_UP (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE DTM_ASSIGNMENT_FAILURE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_DTM_ASSIGNMENT_FAILURE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DTM_ASSIGNMENT_FAILURE_UP* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_DTM_ASSIGNMENT_FAILURE_UP (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE DTM_ASSIGNMENT_FAILURE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_DTM_ASSIGNMENT_FAILURE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DTM_ASSIGNMENT_FAILURE_UP* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE RrCause
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RRCause (Buffer, CurrOfs, (&(Destin->RrCause)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:821> Error decoding subfield RrCause\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 821, (Destin->RrCause))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:822> Message too short decoding subfield RrCause\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 821, (Destin->RrCause))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE DTM_REQUEST_UP
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_DTM_REQUEST_UP (char* Buffer, ED_EXLONG BitOffset, const c_DTM_REQUEST_UP* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 74, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for Tlli */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->Tlli> DOT=<.> */
		EDIntToBits (Buffer, (CurrOfs), (int)(Source->Tlli), 32);
		Len = 32;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:823> Error encoding subfield Tlli\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ChReqDesc */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->ChReqDesc> DOT=<.> */
		Len = ENCODE_c_ChReqDesc2 (Buffer, CurrOfs+8, (&(Source->ChReqDesc)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:824> Error encoding subfield ChReqDesc\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE DTM_REQUEST_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_DTM_REQUEST_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DTM_REQUEST_UP* ED_CONST Source))
{
	return L3_ENCODE_c_DTM_REQUEST_UP (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE DTM_REQUEST_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_DTM_REQUEST_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DTM_REQUEST_UP* ED_CONST Source))
{
	return L3_ENCODE_c_DTM_REQUEST_UP (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE DTM_REQUEST_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_DTM_REQUEST_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DTM_REQUEST_UP* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_DTM_REQUEST_UP (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE DTM_REQUEST_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_DTM_REQUEST_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DTM_REQUEST_UP* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE Tlli
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 32;
	/* Read value part LOCATOR_16 */
	Destin->Tlli = (ED_LONG)EDBitsToInt (Buffer, (CurrOfs), 32);
	/* LOCATOR SETTINGS LOCINT */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-52027=EDCore::TDMInteger) */Destin->Tlli___LOCATOR), CurrOfs, 32);
	RetLen = 32;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:825> Error decoding subfield Tlli\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 825, (Destin->Tlli))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:826> Message too short decoding subfield Tlli\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 825, (Destin->Tlli))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ChReqDesc
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if ((Len < 32) || (Len > 4792)) {
		ED_SIGNAL_ERROR ("<ERRID:827> Size error decoding IE ChReqDesc\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 827, (Destin->ChReqDesc))
	} 
#endif
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_ChReqDesc2 (Buffer, CurrOfs, (&(Destin->ChReqDesc)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:828> Error decoding subfield ChReqDesc\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 828, (Destin->ChReqDesc))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:829> Message too short decoding subfield ChReqDesc\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 828, (Destin->ChReqDesc))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE GPRS_SUSPENSION_REQUEST_UP
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_GPRS_SUSPENSION_REQUEST_UP (char* Buffer, ED_EXLONG BitOffset, const c_GPRS_SUSPENSION_REQUEST_UP* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 52, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for TemporaryLogicalLinkId */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->TemporaryLogicalLinkId> DOT=<.> */
		EDIntToBits (Buffer, (CurrOfs), (int)(Source->TemporaryLogicalLinkId), 32);
		Len = 32;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:830> Error encoding subfield TemporaryLogicalLinkId\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for RouteingAreaId */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->RouteingAreaId> DOT=<.> */
		Len = ENCODE_c_RoutingAreaIdentity (Buffer, CurrOfs, (&(Source->RouteingAreaId)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:831> Error encoding subfield RouteingAreaId\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for SuspensionCause */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->SuspensionCause> DOT=<.> */
		EDIntToBits (Buffer, (CurrOfs), (int)(Source->SuspensionCause), 8);
		Len = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:832> Error encoding subfield SuspensionCause\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ServiceSupport */
	{
		if (Source->ServiceSupport_Present) {
			/* Append to buffer IEI tag 0x01 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x01), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ServiceSupport> DOT=<->> */
			Len = ENCODE_c_ServiceSupport (Buffer, CurrOfs, Source->ServiceSupport);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:833> Error encoding subfield ServiceSupport\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE GPRS_SUSPENSION_REQUEST_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_GPRS_SUSPENSION_REQUEST_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GPRS_SUSPENSION_REQUEST_UP* ED_CONST Source))
{
	return L3_ENCODE_c_GPRS_SUSPENSION_REQUEST_UP (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE GPRS_SUSPENSION_REQUEST_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_GPRS_SUSPENSION_REQUEST_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GPRS_SUSPENSION_REQUEST_UP* ED_CONST Source))
{
	return L3_ENCODE_c_GPRS_SUSPENSION_REQUEST_UP (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE GPRS_SUSPENSION_REQUEST_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_GPRS_SUSPENSION_REQUEST_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GPRS_SUSPENSION_REQUEST_UP* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_GPRS_SUSPENSION_REQUEST_UP (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE GPRS_SUSPENSION_REQUEST_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_GPRS_SUSPENSION_REQUEST_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GPRS_SUSPENSION_REQUEST_UP* ED_CONST Destin, ED_EXLONG Length))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Table containing the expected sequence of IEIs */
	const TEDTLVSkipItem TLVSkipItems [] = {
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{1, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	ED_WARNING_REMOVER (TLVSkipItems);
	
	/*----------------------------------------------------- 
		Code for IE TemporaryLogicalLinkId
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 32;
	/* Read value part LOCATOR_16 */
	Destin->TemporaryLogicalLinkId = (ED_LONG)EDBitsToInt (Buffer, (CurrOfs), 32);
	/* LOCATOR SETTINGS LOCINT */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-52032=EDCore::TDMInteger) */Destin->TemporaryLogicalLinkId___LOCATOR), CurrOfs, 32);
	RetLen = 32;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:834> Error decoding subfield TemporaryLogicalLinkId\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 834, (Destin->TemporaryLogicalLinkId))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:835> Message too short decoding subfield TemporaryLogicalLinkId\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 834, (Destin->TemporaryLogicalLinkId))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE RouteingAreaId
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 48;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RoutingAreaIdentity (Buffer, CurrOfs, (&(Destin->RouteingAreaId)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:836> Error decoding subfield RouteingAreaId\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 836, (Destin->RouteingAreaId))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:837> Message too short decoding subfield RouteingAreaId\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 836, (Destin->RouteingAreaId))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE SuspensionCause
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	Destin->SuspensionCause = (ED_OCTET)EDBitsToInt (Buffer, (CurrOfs), 8);
	/* LOCATOR SETTINGS LOCINT */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-52036=EDCore::TDMInteger) */Destin->SuspensionCause___LOCATOR), CurrOfs, 8);
	RetLen = 8;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:838> Error decoding subfield SuspensionCause\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 838, (Destin->SuspensionCause))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:839> Message too short decoding subfield SuspensionCause\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 838, (Destin->SuspensionCause))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ServiceSupport
	------------------------------------------------------*/
	/* Detect IEI tag 0x01 */
	ED_EXPECT_OPTIONAL_IE (0x01,  8, 840, 3, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x01) {
		SETPRESENT_c_GPRS_SUSPENSION_REQUEST_UP_ServiceSupport (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ServiceSupport (Buffer, CurrOfs, Destin->ServiceSupport, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:841> Error decoding subfield ServiceSupport\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_GPRS_SUSPENSION_REQUEST_UP_ServiceSupport (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x01, 841, (Destin->ServiceSupport))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:842> Message too short decoding subfield ServiceSupport\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_GPRS_SUSPENSION_REQUEST_UP_ServiceSupport (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x01, 841, (Destin->ServiceSupport))
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_COMPLETE_UP
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_HANDOVER_COMPLETE_UP (char* Buffer, ED_EXLONG BitOffset, const c_HANDOVER_COMPLETE_UP* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 44, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for RrCause */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->RrCause> DOT=<.> */
		Len = ENCODE_c_RRCause (Buffer, CurrOfs, (&(Source->RrCause)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:843> Error encoding subfield RrCause\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for MobileObservedTimeDifference */
	{
		int TLV_Base = CurrOfs;
		if (Source->MobileObservedTimeDifference_Present) {
			/* Append to buffer IEI tag 0x77 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x77), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->MobileObservedTimeDifference> DOT=<->> */
			Len = ENCODE_c_MobileTimeDiff (Buffer, CurrOfs+8, Source->MobileObservedTimeDifference);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:844> Error encoding subfield MobileObservedTimeDifference\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for MobileObservedTimeDifferenceHyperframe */
	{
		int TLV_Base = CurrOfs;
		if (Source->MobileObservedTimeDifferenceHyperframe_Present) {
			/* Append to buffer IEI tag 0x67 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x67), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->MobileObservedTimeDifferenceHyperframe> DOT=<->> */
			Len = ENCODE_c_MobileTimeDiffHyperframe (Buffer, CurrOfs+8, Source->MobileObservedTimeDifferenceHyperframe);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:845> Error encoding subfield MobileObservedTimeDifferenceHyperframe\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_COMPLETE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_HANDOVER_COMPLETE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_HANDOVER_COMPLETE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_HANDOVER_COMPLETE_UP (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_COMPLETE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_HANDOVER_COMPLETE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_HANDOVER_COMPLETE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_HANDOVER_COMPLETE_UP (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_COMPLETE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_HANDOVER_COMPLETE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_HANDOVER_COMPLETE_UP* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_HANDOVER_COMPLETE_UP (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_COMPLETE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_HANDOVER_COMPLETE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_HANDOVER_COMPLETE_UP* ED_CONST Destin, ED_EXLONG Length))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Table containing the expected sequence of IEIs */
	const TEDTLVSkipItem TLVSkipItems [] = {
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{119, 255, ED_SKIPLIST_OPTIONAL},
		{103, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	ED_WARNING_REMOVER (TLVSkipItems);
	
	/*----------------------------------------------------- 
		Code for IE RrCause
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RRCause (Buffer, CurrOfs, (&(Destin->RrCause)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:846> Error decoding subfield RrCause\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 846, (Destin->RrCause))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:847> Message too short decoding subfield RrCause\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 846, (Destin->RrCause))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileObservedTimeDifference
	------------------------------------------------------*/
	/* Detect IEI tag 0x77 */
	ED_EXPECT_OPTIONAL_IE (0x77,  8, 848, 1, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x77) {
		SETPRESENT_c_HANDOVER_COMPLETE_UP_MobileObservedTimeDifference (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len != 24) {
			ED_SIGNAL_ERROR ("<ERRID:849> Size error decoding IE MobileObservedTimeDifference\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMPLETE_UP_MobileObservedTimeDifference (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x77, 849, (Destin->MobileObservedTimeDifference))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_MobileTimeDiff (Buffer, CurrOfs, Destin->MobileObservedTimeDifference, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:850> Error decoding subfield MobileObservedTimeDifference\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMPLETE_UP_MobileObservedTimeDifference (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x77, 850, (Destin->MobileObservedTimeDifference))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:851> Message too short decoding subfield MobileObservedTimeDifference\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMPLETE_UP_MobileObservedTimeDifference (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x77, 850, (Destin->MobileObservedTimeDifference))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE MobileObservedTimeDifferenceHyperframe
	------------------------------------------------------*/
	/* Detect IEI tag 0x67 */
	ED_EXPECT_OPTIONAL_IE (0x67,  8, 852, 2, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x67) {
		SETPRESENT_c_HANDOVER_COMPLETE_UP_MobileObservedTimeDifferenceHyperframe (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len != 40) {
			ED_SIGNAL_ERROR ("<ERRID:853> Size error decoding IE MobileObservedTimeDifferenceHyperframe\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMPLETE_UP_MobileObservedTimeDifferenceHyperframe (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x67, 853, (Destin->MobileObservedTimeDifferenceHyperframe))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_MobileTimeDiffHyperframe (Buffer, CurrOfs, Destin->MobileObservedTimeDifferenceHyperframe, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:854> Error decoding subfield MobileObservedTimeDifferenceHyperframe\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMPLETE_UP_MobileObservedTimeDifferenceHyperframe (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x67, 854, (Destin->MobileObservedTimeDifferenceHyperframe))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:855> Message too short decoding subfield MobileObservedTimeDifferenceHyperframe\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMPLETE_UP_MobileObservedTimeDifferenceHyperframe (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x67, 854, (Destin->MobileObservedTimeDifferenceHyperframe))
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_FAILURE_UP
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_HANDOVER_FAILURE_UP (char* Buffer, ED_EXLONG BitOffset, const c_HANDOVER_FAILURE_UP* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 40, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for RrCause */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->RrCause> DOT=<.> */
		Len = ENCODE_c_RRCause (Buffer, CurrOfs, (&(Source->RrCause)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:856> Error encoding subfield RrCause\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for PSCause */
	{
		if (Source->PSCause_Present) {
			/* Append to buffer IEI tag 0x09 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x09), 4);
			CurrOfs += 4;
			/* Append to buffer value part DEBUG FIELD=<Source->PSCause> DOT=<.> */
			EDIntToBits (Buffer, (CurrOfs), (int)(Source->PSCause), 4);
			Len = 4;
			
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:857> Error encoding subfield PSCause\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_FAILURE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_HANDOVER_FAILURE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_HANDOVER_FAILURE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_HANDOVER_FAILURE_UP (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_FAILURE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_HANDOVER_FAILURE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_HANDOVER_FAILURE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_HANDOVER_FAILURE_UP (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_FAILURE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_HANDOVER_FAILURE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_HANDOVER_FAILURE_UP* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_HANDOVER_FAILURE_UP (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_FAILURE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_HANDOVER_FAILURE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_HANDOVER_FAILURE_UP* ED_CONST Destin, ED_EXLONG Length))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Table containing the expected sequence of IEIs */
	const TEDTLVSkipItem TLVSkipItems [] = {
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{144, 240, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	ED_WARNING_REMOVER (TLVSkipItems);
	
	/*----------------------------------------------------- 
		Code for IE RrCause
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RRCause (Buffer, CurrOfs, (&(Destin->RrCause)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:858> Error decoding subfield RrCause\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 858, (Destin->RrCause))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:859> Message too short decoding subfield RrCause\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 858, (Destin->RrCause))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE PSCause
	------------------------------------------------------*/
	/* Detect IEI tag 0x09 */
	ED_EXPECT_OPTIONAL_IE (0x09,  4, 860, 1, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 4); */
	
	/* This is an optional field */
	if (Tag == 0x09) {
		SETPRESENT_c_HANDOVER_FAILURE_UP_PSCause (Destin, ED_TRUE);
		CurrOfs += 4;
		Len = 4;
		/* Read value part LOCATOR_16 */
		Destin->PSCause = (ED_OCTET)EDBitsToInt (Buffer, (CurrOfs), 4);
		/* LOCATOR SETTINGS LOCINT */;
		ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-52050=EDCore::TDMInteger) */Destin->PSCause___LOCATOR), CurrOfs, 4);
		RetLen = 4;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:861> Error decoding subfield PSCause\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_FAILURE_UP_PSCause (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x09, 861, (Destin->PSCause))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:862> Message too short decoding subfield PSCause\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_FAILURE_UP_PSCause (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x09, 861, (Destin->PSCause))
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE MEASUREMENT_REPORT_UP
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_MEASUREMENT_REPORT_UP (char* Buffer, ED_EXLONG BitOffset, const c_MEASUREMENT_REPORT_UP* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 21, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for MeasurementResults */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->MeasurementResults> DOT=<.> */
		Len = ENCODE_c_MeasurementResults (Buffer, CurrOfs, (&(Source->MeasurementResults)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:863> Error encoding subfield MeasurementResults\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE MEASUREMENT_REPORT_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MEASUREMENT_REPORT_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MEASUREMENT_REPORT_UP* ED_CONST Source))
{
	return L3_ENCODE_c_MEASUREMENT_REPORT_UP (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE MEASUREMENT_REPORT_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_MEASUREMENT_REPORT_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MEASUREMENT_REPORT_UP* ED_CONST Source))
{
	return L3_ENCODE_c_MEASUREMENT_REPORT_UP (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE MEASUREMENT_REPORT_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MEASUREMENT_REPORT_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MEASUREMENT_REPORT_UP* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_MEASUREMENT_REPORT_UP (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE MEASUREMENT_REPORT_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_MEASUREMENT_REPORT_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MEASUREMENT_REPORT_UP* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE MeasurementResults
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 128;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_MeasurementResults (Buffer, CurrOfs, (&(Destin->MeasurementResults)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:864> Error decoding subfield MeasurementResults\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 864, (Destin->MeasurementResults))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:865> Message too short decoding subfield MeasurementResults\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 864, (Destin->MeasurementResults))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE NOTIFICATION_RESPONSE_UP
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_NOTIFICATION_RESPONSE_UP (char* Buffer, ED_EXLONG BitOffset, const c_NOTIFICATION_RESPONSE_UP* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 38, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for MobileStationClassmark */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->MobileStationClassmark> DOT=<.> */
		Len = ENCODE_c_RRMobileStationClassmark2 (Buffer, CurrOfs+8, (&(Source->MobileStationClassmark)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:866> Error encoding subfield MobileStationClassmark\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for MobileId */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->MobileId> DOT=<.> */
		Len = ENCODE_c_RRMobileId (Buffer, CurrOfs+8, (&(Source->MobileId)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:867> Error encoding subfield MobileId\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for GroupOrBroadcastCallRef */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->GroupOrBroadcastCallRef> DOT=<.> */
		Len = ENCODE_c_DescGrpOrBcastCallRef (Buffer, CurrOfs, (&(Source->GroupOrBroadcastCallRef)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:868> Error encoding subfield GroupOrBroadcastCallRef\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE NOTIFICATION_RESPONSE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_NOTIFICATION_RESPONSE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_NOTIFICATION_RESPONSE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_NOTIFICATION_RESPONSE_UP (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE NOTIFICATION_RESPONSE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_NOTIFICATION_RESPONSE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_NOTIFICATION_RESPONSE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_NOTIFICATION_RESPONSE_UP (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE NOTIFICATION_RESPONSE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_NOTIFICATION_RESPONSE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_NOTIFICATION_RESPONSE_UP* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_NOTIFICATION_RESPONSE_UP (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE NOTIFICATION_RESPONSE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_NOTIFICATION_RESPONSE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_NOTIFICATION_RESPONSE_UP* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE MobileStationClassmark
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Len != 24) {
		ED_SIGNAL_ERROR ("<ERRID:869> Size error decoding IE MobileStationClassmark\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 869, (Destin->MobileStationClassmark))
	} 
#endif
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RRMobileStationClassmark2 (Buffer, CurrOfs, (&(Destin->MobileStationClassmark)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:870> Error decoding subfield MobileStationClassmark\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 870, (Destin->MobileStationClassmark))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:871> Message too short decoding subfield MobileStationClassmark\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 870, (Destin->MobileStationClassmark))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileId
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if ((Len < 8) || (Len > 64)) {
		ED_SIGNAL_ERROR ("<ERRID:872> Size error decoding IE MobileId\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 872, (Destin->MobileId))
	} 
#endif
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RRMobileId (Buffer, CurrOfs, (&(Destin->MobileId)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:873> Error decoding subfield MobileId\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 873, (Destin->MobileId))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:874> Message too short decoding subfield MobileId\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 873, (Destin->MobileId))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE GroupOrBroadcastCallRef
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 40;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_DescGrpOrBcastCallRef (Buffer, CurrOfs, (&(Destin->GroupOrBroadcastCallRef)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:875> Error decoding subfield GroupOrBroadcastCallRef\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 875, (Destin->GroupOrBroadcastCallRef))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:876> Message too short decoding subfield GroupOrBroadcastCallRef\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 875, (Destin->GroupOrBroadcastCallRef))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE PAGING_RESPONSE_UP
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_PAGING_RESPONSE_UP (char* Buffer, ED_EXLONG BitOffset, const c_PAGING_RESPONSE_UP* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 39, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for CiphKeySequenceNum */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->CiphKeySequenceNum> DOT=<.> */
		Len = ENCODE_c_CipheringKeySequenceNumber (Buffer, (CurrOfs+4), (&(Source->CiphKeySequenceNum)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:877> Error encoding subfield CiphKeySequenceNum\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for SpareHalfOctet */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->SpareHalfOctet> DOT=<.> */
		EDIntToBits (Buffer, (CurrOfs-4), 0, 4);Len = 4;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:878> Error encoding subfield SpareHalfOctet\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for MobileStationClassmark */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->MobileStationClassmark> DOT=<.> */
		Len = ENCODE_c_RRMobileStationClassmark2 (Buffer, CurrOfs+8, (&(Source->MobileStationClassmark)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:879> Error encoding subfield MobileStationClassmark\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for MobileId */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->MobileId> DOT=<.> */
		Len = ENCODE_c_RRMobileId (Buffer, CurrOfs+8, (&(Source->MobileId)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:880> Error encoding subfield MobileId\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for AdditionalUpdateParameters */
	{
		if (Source->AdditionalUpdateParameters_Present) {
			/* Append to buffer IEI tag 0x0C */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x0C), 4);
			CurrOfs += 4;
			/* Append to buffer value part DEBUG FIELD=<Source->AdditionalUpdateParameters> DOT=<->> */
			Len = ENCODE_c_AdditionalUpdateParameters (Buffer, CurrOfs, Source->AdditionalUpdateParameters);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:881> Error encoding subfield AdditionalUpdateParameters\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE PAGING_RESPONSE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PAGING_RESPONSE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PAGING_RESPONSE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_PAGING_RESPONSE_UP (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE PAGING_RESPONSE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_PAGING_RESPONSE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PAGING_RESPONSE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_PAGING_RESPONSE_UP (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PAGING_RESPONSE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PAGING_RESPONSE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PAGING_RESPONSE_UP* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_PAGING_RESPONSE_UP (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PAGING_RESPONSE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_PAGING_RESPONSE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PAGING_RESPONSE_UP* ED_CONST Destin, ED_EXLONG Length))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Table containing the expected sequence of IEIs */
	const TEDTLVSkipItem TLVSkipItems [] = {
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{192, 240, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	ED_WARNING_REMOVER (TLVSkipItems);
	
	/*----------------------------------------------------- 
		Code for IE CiphKeySequenceNum
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_CipheringKeySequenceNumber (Buffer, (CurrOfs+4), (&(Destin->CiphKeySequenceNum)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:882> Error decoding subfield CiphKeySequenceNum\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 882, (Destin->CiphKeySequenceNum))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:883> Message too short decoding subfield CiphKeySequenceNum\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 882, (Destin->CiphKeySequenceNum))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE SpareHalfOctet
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part LOCATOR_16 */
	RetLen = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:884> Error decoding subfield SpareHalfOctet\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 884, (Destin->SpareHalfOctet))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:885> Message too short decoding subfield SpareHalfOctet\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 884, (Destin->SpareHalfOctet))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileStationClassmark
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Len != 24) {
		ED_SIGNAL_ERROR ("<ERRID:886> Size error decoding IE MobileStationClassmark\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 886, (Destin->MobileStationClassmark))
	} 
#endif
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RRMobileStationClassmark2 (Buffer, CurrOfs, (&(Destin->MobileStationClassmark)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:887> Error decoding subfield MobileStationClassmark\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 887, (Destin->MobileStationClassmark))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:888> Message too short decoding subfield MobileStationClassmark\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 887, (Destin->MobileStationClassmark))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileId
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if ((Len < 8) || (Len > 64)) {
		ED_SIGNAL_ERROR ("<ERRID:889> Size error decoding IE MobileId\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 889, (Destin->MobileId))
	} 
#endif
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RRMobileId (Buffer, CurrOfs, (&(Destin->MobileId)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:890> Error decoding subfield MobileId\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 890, (Destin->MobileId))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:891> Message too short decoding subfield MobileId\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 890, (Destin->MobileId))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE AdditionalUpdateParameters
	------------------------------------------------------*/
	/* Detect IEI tag 0x0C */
	ED_EXPECT_OPTIONAL_IE (0x0C,  4, 892, 4, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 4); */
	
	/* This is an optional field */
	if (Tag == 0x0C) {
		SETPRESENT_c_PAGING_RESPONSE_UP_AdditionalUpdateParameters (Destin, ED_TRUE);
		CurrOfs += 4;
		Len = 4;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_AdditionalUpdateParameters (Buffer, CurrOfs, Destin->AdditionalUpdateParameters, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:893> Error decoding subfield AdditionalUpdateParameters\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_PAGING_RESPONSE_UP_AdditionalUpdateParameters (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x0C, 893, (Destin->AdditionalUpdateParameters))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:894> Message too short decoding subfield AdditionalUpdateParameters\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_PAGING_RESPONSE_UP_AdditionalUpdateParameters (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x0C, 893, (Destin->AdditionalUpdateParameters))
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE PARTIAL_RELEASE_COMPLETE_UP
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_PARTIAL_RELEASE_COMPLETE_UP (char* Buffer, ED_EXLONG BitOffset, const c_PARTIAL_RELEASE_COMPLETE_UP* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 15, 8);
		CurrOfs += 8;
		
	}
	

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE PARTIAL_RELEASE_COMPLETE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PARTIAL_RELEASE_COMPLETE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PARTIAL_RELEASE_COMPLETE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_PARTIAL_RELEASE_COMPLETE_UP (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE PARTIAL_RELEASE_COMPLETE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_PARTIAL_RELEASE_COMPLETE_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PARTIAL_RELEASE_COMPLETE_UP* ED_CONST Source))
{
	return L3_ENCODE_c_PARTIAL_RELEASE_COMPLETE_UP (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PARTIAL_RELEASE_COMPLETE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PARTIAL_RELEASE_COMPLETE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PARTIAL_RELEASE_COMPLETE_UP* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_PARTIAL_RELEASE_COMPLETE_UP (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PARTIAL_RELEASE_COMPLETE_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_PARTIAL_RELEASE_COMPLETE_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PARTIAL_RELEASE_COMPLETE_UP* ED_CONST Destin, ED_EXLONG Length))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE RR_INITIALISATION_REQUEST_UP
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_RR_INITIALISATION_REQUEST_UP (char* Buffer, ED_EXLONG BitOffset, const c_RR_INITIALISATION_REQUEST_UP* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 60, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for CiphKeySequenceNum */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->CiphKeySequenceNum> DOT=<.> */
		Len = ENCODE_c_CipheringKeySequenceNumber (Buffer, (CurrOfs+4), (&(Source->CiphKeySequenceNum)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:895> Error encoding subfield CiphKeySequenceNum\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for MacModeAndChannelCodingReq */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->MacModeAndChannelCodingReq> DOT=<.> */
		Len = ENCODE_c_MACModeAndChCodReq (Buffer, (CurrOfs-4), (&(Source->MacModeAndChannelCodingReq)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:896> Error encoding subfield MacModeAndChannelCodingReq\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for MobileStationClassmark */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->MobileStationClassmark> DOT=<.> */
		Len = ENCODE_c_RRMobileStationClassmark2 (Buffer, CurrOfs+8, (&(Source->MobileStationClassmark)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:897> Error encoding subfield MobileStationClassmark\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for Tlli */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->Tlli> DOT=<.> */
		EDIntToBits (Buffer, (CurrOfs), (int)(Source->Tlli), 32);
		Len = 32;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:898> Error encoding subfield Tlli\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ChannelReqDescription */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ChannelReqDescription> DOT=<.> */
		Len = ENCODE_c_ChannelRequestDesc (Buffer, CurrOfs, (&(Source->ChannelReqDescription)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:899> Error encoding subfield ChannelReqDescription\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for GprsMeasurementResults */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->GprsMeasurementResults> DOT=<.> */
		Len = ENCODE_c_GPRSMeasurementResult (Buffer, CurrOfs, (&(Source->GprsMeasurementResults)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:900> Error encoding subfield GprsMeasurementResults\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE RR_INITIALISATION_REQUEST_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RR_INITIALISATION_REQUEST_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RR_INITIALISATION_REQUEST_UP* ED_CONST Source))
{
	return L3_ENCODE_c_RR_INITIALISATION_REQUEST_UP (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE RR_INITIALISATION_REQUEST_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RR_INITIALISATION_REQUEST_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RR_INITIALISATION_REQUEST_UP* ED_CONST Source))
{
	return L3_ENCODE_c_RR_INITIALISATION_REQUEST_UP (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE RR_INITIALISATION_REQUEST_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RR_INITIALISATION_REQUEST_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RR_INITIALISATION_REQUEST_UP* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_RR_INITIALISATION_REQUEST_UP (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE RR_INITIALISATION_REQUEST_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RR_INITIALISATION_REQUEST_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RR_INITIALISATION_REQUEST_UP* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE CiphKeySequenceNum
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_CipheringKeySequenceNumber (Buffer, (CurrOfs+4), (&(Destin->CiphKeySequenceNum)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:901> Error decoding subfield CiphKeySequenceNum\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 901, (Destin->CiphKeySequenceNum))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:902> Message too short decoding subfield CiphKeySequenceNum\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 901, (Destin->CiphKeySequenceNum))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MacModeAndChannelCodingReq
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_MACModeAndChCodReq (Buffer, (CurrOfs-4), (&(Destin->MacModeAndChannelCodingReq)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:903> Error decoding subfield MacModeAndChannelCodingReq\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 903, (Destin->MacModeAndChannelCodingReq))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:904> Message too short decoding subfield MacModeAndChannelCodingReq\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 903, (Destin->MacModeAndChannelCodingReq))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileStationClassmark
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Len != 24) {
		ED_SIGNAL_ERROR ("<ERRID:905> Size error decoding IE MobileStationClassmark\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 905, (Destin->MobileStationClassmark))
	} 
#endif
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RRMobileStationClassmark2 (Buffer, CurrOfs, (&(Destin->MobileStationClassmark)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:906> Error decoding subfield MobileStationClassmark\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 906, (Destin->MobileStationClassmark))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:907> Message too short decoding subfield MobileStationClassmark\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 906, (Destin->MobileStationClassmark))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE Tlli
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 32;
	/* Read value part LOCATOR_16 */
	Destin->Tlli = (ED_LONG)EDBitsToInt (Buffer, (CurrOfs), 32);
	/* LOCATOR SETTINGS LOCINT */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-52081=EDCore::TDMInteger) */Destin->Tlli___LOCATOR), CurrOfs, 32);
	RetLen = 32;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:908> Error decoding subfield Tlli\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 908, (Destin->Tlli))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:909> Message too short decoding subfield Tlli\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 908, (Destin->Tlli))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ChannelReqDescription
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 40;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_ChannelRequestDesc (Buffer, CurrOfs, (&(Destin->ChannelReqDescription)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:910> Error decoding subfield ChannelReqDescription\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 910, (Destin->ChannelReqDescription))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:911> Message too short decoding subfield ChannelReqDescription\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 910, (Destin->ChannelReqDescription))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE GprsMeasurementResults
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 16;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_GPRSMeasurementResult (Buffer, CurrOfs, (&(Destin->GprsMeasurementResults)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:912> Error decoding subfield GprsMeasurementResults\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 912, (Destin->GprsMeasurementResults))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:913> Message too short decoding subfield GprsMeasurementResults\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 912, (Destin->GprsMeasurementResults))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE RR_STATUS
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_RR_STATUS (char* Buffer, ED_EXLONG BitOffset, const c_RR_STATUS* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 18, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for RrCause */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->RrCause> DOT=<.> */
		Len = ENCODE_c_RRCause (Buffer, CurrOfs, (&(Source->RrCause)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:914> Error encoding subfield RrCause\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE RR_STATUS
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RR_STATUS (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RR_STATUS* ED_CONST Source))
{
	return L3_ENCODE_c_RR_STATUS (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE RR_STATUS
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RR_STATUS (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RR_STATUS* ED_CONST Source))
{
	return L3_ENCODE_c_RR_STATUS (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE RR_STATUS
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RR_STATUS (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RR_STATUS* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_RR_STATUS (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE RR_STATUS
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RR_STATUS (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RR_STATUS* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE RrCause
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RRCause (Buffer, CurrOfs, (&(Destin->RrCause)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:915> Error decoding subfield RrCause\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 915, (Destin->RrCause))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:916> Message too short decoding subfield RrCause\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 915, (Destin->RrCause))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE TALKER_INDICATION_UP
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_TALKER_INDICATION_UP (char* Buffer, ED_EXLONG BitOffset, const c_TALKER_INDICATION_UP* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 17, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for MobileStationClassmark */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->MobileStationClassmark> DOT=<.> */
		Len = ENCODE_c_RRMobileStationClassmark2 (Buffer, CurrOfs+8, (&(Source->MobileStationClassmark)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:917> Error encoding subfield MobileStationClassmark\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for MobileId */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->MobileId> DOT=<.> */
		Len = ENCODE_c_RRMobileId (Buffer, CurrOfs+8, (&(Source->MobileId)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:918> Error encoding subfield MobileId\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for CipheringKeySequenceNumber */
	{
		if (Source->CipheringKeySequenceNumber_Present) {
			/* Append to buffer IEI tag 0x0B */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x0B), 4);
			CurrOfs += 4;
			/* Append to buffer value part DEBUG FIELD=<Source->CipheringKeySequenceNumber> DOT=<.> */
			EDIntToBits (Buffer, (CurrOfs), (int)(Source->CipheringKeySequenceNumber), 4);
			Len = 4;
			
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:919> Error encoding subfield CipheringKeySequenceNumber\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE TALKER_INDICATION_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_TALKER_INDICATION_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_TALKER_INDICATION_UP* ED_CONST Source))
{
	return L3_ENCODE_c_TALKER_INDICATION_UP (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE TALKER_INDICATION_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_TALKER_INDICATION_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_TALKER_INDICATION_UP* ED_CONST Source))
{
	return L3_ENCODE_c_TALKER_INDICATION_UP (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE TALKER_INDICATION_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_TALKER_INDICATION_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_TALKER_INDICATION_UP* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_TALKER_INDICATION_UP (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE TALKER_INDICATION_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_TALKER_INDICATION_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_TALKER_INDICATION_UP* ED_CONST Destin, ED_EXLONG Length))
{
	ED_EXLONG CurrOfs = BitOffset;
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Destin);
	ED_WARNING_REMOVER (Length);
	ED_EXTRAPARAMS_CODE

{
	/* Table containing the expected sequence of IEIs */
	const TEDTLVSkipItem TLVSkipItems [] = {
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{176, 240, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	ED_WARNING_REMOVER (TLVSkipItems);
	
	/*----------------------------------------------------- 
		Code for IE MobileStationClassmark
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Len != 24) {
		ED_SIGNAL_ERROR ("<ERRID:920> Size error decoding IE MobileStationClassmark\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 920, (Destin->MobileStationClassmark))
	} 
#endif
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RRMobileStationClassmark2 (Buffer, CurrOfs, (&(Destin->MobileStationClassmark)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:921> Error decoding subfield MobileStationClassmark\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 921, (Destin->MobileStationClassmark))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:922> Message too short decoding subfield MobileStationClassmark\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 921, (Destin->MobileStationClassmark))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileId
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if ((Len < 8) || (Len > 64)) {
		ED_SIGNAL_ERROR ("<ERRID:923> Size error decoding IE MobileId\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 923, (Destin->MobileId))
	} 
#endif
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RRMobileId (Buffer, CurrOfs, (&(Destin->MobileId)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:924> Error decoding subfield MobileId\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 924, (Destin->MobileId))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:925> Message too short decoding subfield MobileId\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 924, (Destin->MobileId))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE CipheringKeySequenceNumber
	------------------------------------------------------*/
	/* Detect IEI tag 0x0B */
	ED_EXPECT_OPTIONAL_IE (0x0B,  4, 926, 2, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 4); */
	
	/* This is an optional field */
	if (Tag == 0x0B) {
		SETPRESENT_c_TALKER_INDICATION_UP_CipheringKeySequenceNumber (Destin, ED_TRUE);
		CurrOfs += 4;
		Len = 4;
		/* Read value part LOCATOR_16 */
		Destin->CipheringKeySequenceNumber = (ED_OCTET)EDBitsToInt (Buffer, (CurrOfs), 4);
		/* LOCATOR SETTINGS LOCINT */;
		ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-52095=EDCore::TDMInteger) */Destin->CipheringKeySequenceNumber___LOCATOR), CurrOfs, 4);
		RetLen = 4;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:927> Error decoding subfield CipheringKeySequenceNumber\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_TALKER_INDICATION_UP_CipheringKeySequenceNumber (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x0B, 927, (Destin->CipheringKeySequenceNumber))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:928> Message too short decoding subfield CipheringKeySequenceNumber\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_TALKER_INDICATION_UP_CipheringKeySequenceNumber (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x0B, 927, (Destin->CipheringKeySequenceNumber))
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE PRIORITY_DNLINK_REQUEST
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_PRIORITY_DNLINK_REQUEST (char* Buffer, ED_EXLONG BitOffset, const c_PRIORITY_DNLINK_REQUEST* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 102, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for EstablishmentCauseRandomReference */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->EstablishmentCauseRandomReference> DOT=<.> */
		Len = ENCODE_c_EstablishmentCauseRandomReference (Buffer, CurrOfs, (&(Source->EstablishmentCauseRandomReference)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:929> Error encoding subfield EstablishmentCauseRandomReference\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for Token */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->Token> DOT=<.> */
		EDIntToBits (Buffer, (CurrOfs), (int)(Source->Token), 32);
		Len = 32;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:930> Error encoding subfield Token\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ReducedGroupCallReference */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ReducedGroupCallReference> DOT=<.> */
		Len = ENCODE_c_ReducedGroupCallReference (Buffer, CurrOfs, (&(Source->ReducedGroupCallReference)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:931> Error encoding subfield ReducedGroupCallReference\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for MobileIdentity */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->MobileIdentity> DOT=<.> */
		Len = ENCODE_c_RRMobileId (Buffer, CurrOfs+8, (&(Source->MobileIdentity)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:932> Error encoding subfield MobileIdentity\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE PRIORITY_DNLINK_REQUEST
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PRIORITY_DNLINK_REQUEST (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PRIORITY_DNLINK_REQUEST* ED_CONST Source))
{
	return L3_ENCODE_c_PRIORITY_DNLINK_REQUEST (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE PRIORITY_DNLINK_REQUEST
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_PRIORITY_DNLINK_REQUEST (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PRIORITY_DNLINK_REQUEST* ED_CONST Source))
{
	return L3_ENCODE_c_PRIORITY_DNLINK_REQUEST (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PRIORITY_DNLINK_REQUEST
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PRIORITY_DNLINK_REQUEST (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PRIORITY_DNLINK_REQUEST* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_PRIORITY_DNLINK_REQUEST (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PRIORITY_DNLINK_REQUEST
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_PRIORITY_DNLINK_REQUEST (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PRIORITY_DNLINK_REQUEST* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE EstablishmentCauseRandomReference
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_EstablishmentCauseRandomReference (Buffer, CurrOfs, (&(Destin->EstablishmentCauseRandomReference)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:933> Error decoding subfield EstablishmentCauseRandomReference\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 933, (Destin->EstablishmentCauseRandomReference))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:934> Message too short decoding subfield EstablishmentCauseRandomReference\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 933, (Destin->EstablishmentCauseRandomReference))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE Token
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 32;
	/* Read value part LOCATOR_16 */
	Destin->Token = (ED_LONG)EDBitsToInt (Buffer, (CurrOfs), 32);
	/* LOCATOR SETTINGS LOCINT */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-52100=EDCore::TDMInteger) */Destin->Token___LOCATOR), CurrOfs, 32);
	RetLen = 32;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:935> Error decoding subfield Token\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 935, (Destin->Token))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:936> Message too short decoding subfield Token\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 935, (Destin->Token))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ReducedGroupCallReference
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 32;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_ReducedGroupCallReference (Buffer, CurrOfs, (&(Destin->ReducedGroupCallReference)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:937> Error decoding subfield ReducedGroupCallReference\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 937, (Destin->ReducedGroupCallReference))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:938> Message too short decoding subfield ReducedGroupCallReference\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 937, (Destin->ReducedGroupCallReference))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileIdentity
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if ((Len < 8) || (Len > 64)) {
		ED_SIGNAL_ERROR ("<ERRID:939> Size error decoding IE MobileIdentity\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 939, (Destin->MobileIdentity))
	} 
#endif
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RRMobileId (Buffer, CurrOfs, (&(Destin->MobileIdentity)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:940> Error decoding subfield MobileIdentity\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 940, (Destin->MobileIdentity))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:941> Message too short decoding subfield MobileIdentity\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 940, (Destin->MobileIdentity))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE DATA_INDICATION
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_DATA_INDICATION (char* Buffer, ED_EXLONG BitOffset, const c_DATA_INDICATION* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 103, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for MobileIdentity */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->MobileIdentity> DOT=<.> */
		EDIntToBits (Buffer, (CurrOfs), (int)(Source->MobileIdentity), 32);
		Len = 32;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:942> Error encoding subfield MobileIdentity\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ApplicationData */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ApplicationData> DOT=<.> */
		EDCopyBits (Buffer, CurrOfs, (Source->ApplicationData), 0, 72);
		Len = 72;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:943> Error encoding subfield ApplicationData\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for DataIdentity */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->DataIdentity> DOT=<.> */
		Len = ENCODE_c_DataIdentity (Buffer, CurrOfs, (&(Source->DataIdentity)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:944> Error encoding subfield DataIdentity\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE DATA_INDICATION
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_DATA_INDICATION (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DATA_INDICATION* ED_CONST Source))
{
	return L3_ENCODE_c_DATA_INDICATION (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE DATA_INDICATION
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_DATA_INDICATION (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DATA_INDICATION* ED_CONST Source))
{
	return L3_ENCODE_c_DATA_INDICATION (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE DATA_INDICATION
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_DATA_INDICATION (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DATA_INDICATION* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_DATA_INDICATION (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE DATA_INDICATION
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_DATA_INDICATION (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DATA_INDICATION* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE MobileIdentity
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 32;
	/* Read value part LOCATOR_16 */
	Destin->MobileIdentity = (ED_LONG)EDBitsToInt (Buffer, (CurrOfs), 32);
	/* LOCATOR SETTINGS LOCINT */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-52107=EDCore::TDMInteger) */Destin->MobileIdentity___LOCATOR), CurrOfs, 32);
	RetLen = 32;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:945> Error decoding subfield MobileIdentity\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 945, (Destin->MobileIdentity))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:946> Message too short decoding subfield MobileIdentity\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 945, (Destin->MobileIdentity))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ApplicationData
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 72;
	/* Read value part LOCATOR_16 */
	EDCopyBits (Destin->ApplicationData, 0, Buffer, CurrOfs, 72);
	/* LOCATOR SETTINGS LOCBIN1 */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-52109=EDCore::TDMBinary) */Destin->ApplicationData___LOCATOR), CurrOfs, 72);
	RetLen = 72;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:947> Error decoding subfield ApplicationData\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 947, (Destin->ApplicationData))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:948> Message too short decoding subfield ApplicationData\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 947, (Destin->ApplicationData))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE DataIdentity
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_DataIdentity (Buffer, CurrOfs, (&(Destin->DataIdentity)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:949> Error decoding subfield DataIdentity\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 949, (Destin->DataIdentity))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:950> Message too short decoding subfield DataIdentity\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 949, (Destin->DataIdentity))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE DATA_INDICATION_2
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_DATA_INDICATION_2 (char* Buffer, ED_EXLONG BitOffset, const c_DATA_INDICATION_2* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 104, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for MobileIdentity */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->MobileIdentity> DOT=<.> */
		EDIntToBits (Buffer, (CurrOfs), (int)(Source->MobileIdentity), 32);
		Len = 32;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:951> Error encoding subfield MobileIdentity\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ReducedGroupCallReference */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ReducedGroupCallReference> DOT=<.> */
		Len = ENCODE_c_ReducedGroupCallReference (Buffer, CurrOfs, (&(Source->ReducedGroupCallReference)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:952> Error encoding subfield ReducedGroupCallReference\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ApplicationData */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ApplicationData> DOT=<.> */
		EDCopyBits (Buffer, CurrOfs, (Source->ApplicationData), 0, 72);
		Len = 72;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:953> Error encoding subfield ApplicationData\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for DataIdentity */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->DataIdentity> DOT=<.> */
		Len = ENCODE_c_DataIdentity (Buffer, CurrOfs, (&(Source->DataIdentity)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:954> Error encoding subfield DataIdentity\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE DATA_INDICATION_2
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_DATA_INDICATION_2 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DATA_INDICATION_2* ED_CONST Source))
{
	return L3_ENCODE_c_DATA_INDICATION_2 (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE DATA_INDICATION_2
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_DATA_INDICATION_2 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DATA_INDICATION_2* ED_CONST Source))
{
	return L3_ENCODE_c_DATA_INDICATION_2 (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE DATA_INDICATION_2
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_DATA_INDICATION_2 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DATA_INDICATION_2* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_DATA_INDICATION_2 (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE DATA_INDICATION_2
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_DATA_INDICATION_2 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DATA_INDICATION_2* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE MobileIdentity
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 32;
	/* Read value part LOCATOR_16 */
	Destin->MobileIdentity = (ED_LONG)EDBitsToInt (Buffer, (CurrOfs), 32);
	/* LOCATOR SETTINGS LOCINT */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-52114=EDCore::TDMInteger) */Destin->MobileIdentity___LOCATOR), CurrOfs, 32);
	RetLen = 32;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:955> Error decoding subfield MobileIdentity\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 955, (Destin->MobileIdentity))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:956> Message too short decoding subfield MobileIdentity\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 955, (Destin->MobileIdentity))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ReducedGroupCallReference
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 32;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_ReducedGroupCallReference (Buffer, CurrOfs, (&(Destin->ReducedGroupCallReference)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:957> Error decoding subfield ReducedGroupCallReference\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 957, (Destin->ReducedGroupCallReference))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:958> Message too short decoding subfield ReducedGroupCallReference\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 957, (Destin->ReducedGroupCallReference))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ApplicationData
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 72;
	/* Read value part LOCATOR_16 */
	EDCopyBits (Destin->ApplicationData, 0, Buffer, CurrOfs, 72);
	/* LOCATOR SETTINGS LOCBIN1 */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-52118=EDCore::TDMBinary) */Destin->ApplicationData___LOCATOR), CurrOfs, 72);
	RetLen = 72;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:959> Error decoding subfield ApplicationData\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 959, (Destin->ApplicationData))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:960> Message too short decoding subfield ApplicationData\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 959, (Destin->ApplicationData))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE DataIdentity
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_DataIdentity (Buffer, CurrOfs, (&(Destin->DataIdentity)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:961> Error decoding subfield DataIdentity\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 961, (Destin->DataIdentity))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:962> Message too short decoding subfield DataIdentity\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 961, (Destin->DataIdentity))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE UPLINK_RELEASE
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_UPLINK_RELEASE (char* Buffer, ED_EXLONG BitOffset, const c_UPLINK_RELEASE* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 14, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for RrCause */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->RrCause> DOT=<.> */
		Len = ENCODE_c_RRCause (Buffer, CurrOfs, (&(Source->RrCause)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:963> Error encoding subfield RrCause\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE UPLINK_RELEASE
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_UPLINK_RELEASE (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_UPLINK_RELEASE* ED_CONST Source))
{
	return L3_ENCODE_c_UPLINK_RELEASE (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE UPLINK_RELEASE
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_UPLINK_RELEASE (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_UPLINK_RELEASE* ED_CONST Source))
{
	return L3_ENCODE_c_UPLINK_RELEASE (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE UPLINK_RELEASE
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_UPLINK_RELEASE (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_UPLINK_RELEASE* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_UPLINK_RELEASE (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE UPLINK_RELEASE
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_UPLINK_RELEASE (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_UPLINK_RELEASE* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE RrCause
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RRCause (Buffer, CurrOfs, (&(Destin->RrCause)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:964> Error decoding subfield RrCause\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 964, (Destin->RrCause))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:965> Message too short decoding subfield RrCause\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 964, (Destin->RrCause))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE EXTENDED_MEASUREMENT_REPORT_UP
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_EXTENDED_MEASUREMENT_REPORT_UP (char* Buffer, ED_EXLONG BitOffset, const c_EXTENDED_MEASUREMENT_REPORT_UP* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 54, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for ExtendedMeasurementResults */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ExtendedMeasurementResults> DOT=<.> */
		Len = ENCODE_c_ExtMeasurementResults (Buffer, CurrOfs, (&(Source->ExtendedMeasurementResults)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:966> Error encoding subfield ExtendedMeasurementResults\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE EXTENDED_MEASUREMENT_REPORT_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EXTENDED_MEASUREMENT_REPORT_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EXTENDED_MEASUREMENT_REPORT_UP* ED_CONST Source))
{
	return L3_ENCODE_c_EXTENDED_MEASUREMENT_REPORT_UP (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE EXTENDED_MEASUREMENT_REPORT_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_EXTENDED_MEASUREMENT_REPORT_UP (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EXTENDED_MEASUREMENT_REPORT_UP* ED_CONST Source))
{
	return L3_ENCODE_c_EXTENDED_MEASUREMENT_REPORT_UP (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE EXTENDED_MEASUREMENT_REPORT_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EXTENDED_MEASUREMENT_REPORT_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EXTENDED_MEASUREMENT_REPORT_UP* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_EXTENDED_MEASUREMENT_REPORT_UP (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE EXTENDED_MEASUREMENT_REPORT_UP
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_EXTENDED_MEASUREMENT_REPORT_UP (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EXTENDED_MEASUREMENT_REPORT_UP* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE ExtendedMeasurementResults
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 128;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_ExtMeasurementResults (Buffer, CurrOfs, (&(Destin->ExtendedMeasurementResults)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:967> Error decoding subfield ExtendedMeasurementResults\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 967, (Destin->ExtendedMeasurementResults))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:968> Message too short decoding subfield ExtendedMeasurementResults\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 967, (Destin->ExtendedMeasurementResults))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE APPLICATION_INFORMATION
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_APPLICATION_INFORMATION (char* Buffer, ED_EXLONG BitOffset, const c_APPLICATION_INFORMATION* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 56, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for ApduId */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ApduId> DOT=<.> */
		EDIntToBits (Buffer, ((CurrOfs+4)), (int)(Source->ApduId), 4);
		Len = 4;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:969> Error encoding subfield ApduId\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ApduFlags */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ApduFlags> DOT=<.> */
		Len = ENCODE_c_APDUFlags (Buffer, (CurrOfs-4), (&(Source->ApduFlags)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:970> Error encoding subfield ApduFlags\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ApduData */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->ApduData> DOT=<.> */
		EDCopyBits (Buffer, CurrOfs+8, Source->ApduData.value, 0, Source->ApduData.usedBits);
		Len = Source->ApduData.usedBits;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:971> Error encoding subfield ApduData\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE APPLICATION_INFORMATION
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_APPLICATION_INFORMATION (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_APPLICATION_INFORMATION* ED_CONST Source))
{
	return L3_ENCODE_c_APPLICATION_INFORMATION (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE APPLICATION_INFORMATION
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_APPLICATION_INFORMATION (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_APPLICATION_INFORMATION* ED_CONST Source))
{
	return L3_ENCODE_c_APPLICATION_INFORMATION (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE APPLICATION_INFORMATION
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_APPLICATION_INFORMATION (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_APPLICATION_INFORMATION* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_APPLICATION_INFORMATION (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE APPLICATION_INFORMATION
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_APPLICATION_INFORMATION (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_APPLICATION_INFORMATION* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE ApduId
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part LOCATOR_16 */
	Destin->ApduId = (ED_OCTET)EDBitsToInt (Buffer, ((CurrOfs+4)), 4);
	/* LOCATOR SETTINGS LOCINT */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-52129=EDCore::TDMInteger) */Destin->ApduId___LOCATOR), (CurrOfs+4), 4);
	RetLen = 4;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:972> Error decoding subfield ApduId\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 972, (Destin->ApduId))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:973> Message too short decoding subfield ApduId\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 972, (Destin->ApduId))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ApduFlags
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_APDUFlags (Buffer, (CurrOfs-4), (&(Destin->ApduFlags)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:974> Error decoding subfield ApduFlags\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 974, (Destin->ApduFlags))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:975> Message too short decoding subfield ApduFlags\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 974, (Destin->ApduFlags))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ApduData
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if ((Len < 8) || (Len > 4792)) {
		ED_SIGNAL_ERROR ("<ERRID:976> Size error decoding IE ApduData\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 976, (Destin->ApduData))
	} 
#endif
	/* Read value part LOCATOR_16 */
	/* LOCATOR SETTINGS LOCBIN2 */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-52133=EDCore::TDMBinary) */Destin->ApduData___LOCATOR), CurrOfs, Len);
	if (Len > 0) {
		/* BINDEC02 */
		ALLOC_c_APPLICATION_INFORMATION_ApduData (&(Destin->ApduData), Len);
	
		EDCopyBits (Destin->ApduData.value, 0, Buffer, CurrOfs, Len);
		Destin->ApduData.usedBits = Len;
	}
	
	RetLen = Len;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:977> Error decoding subfield ApduData\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 977, (Destin->ApduData))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:978> Message too short decoding subfield ApduData\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 977, (Destin->ApduData))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
int Match_c_ASSIGNMENT_COMPLETE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 41) /* message type */
	);
}

int Match_c_ASSIGNMENT_FAILURE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 47) /* message type */
	);
}

int Match_c_CHANNEL_MODE_MODIFY_ACKNOWLEDGE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 23) /* message type */
	);
}

int Match_c_CIPHERING_MODE_COMPLETE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 50) /* message type */
	);
}

int Match_c_CLASSMARK_CHANGE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 22) /* message type */
	);
}

int Match_c_UTRAN_CLASSMARK_CHANGE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 96) /* message type */
	);
}

int Match_c_CDMA2000_CLASSMARK_CHANGE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 98) /* message type */
	);
}

int Match_c_GERAN_IU_MODE_CLASSMARK_CHANGE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 101) /* message type */
	);
}

int Match_c_CONFIGURATION_CHANGE_ACKNOWLEDGE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 49) /* message type */
	);
}

int Match_c_CONFIGURATION_CHANGE_REJECT_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 51) /* message type */
	);
}

int Match_c_DTM_ASSIGNMENT_COMMAND_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 76) /* message type */
	);
}

int Match_c_DTM_ASSIGNMENT_FAILURE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 72) /* message type */
	);
}

int Match_c_DTM_REQUEST_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 74) /* message type */
	);
}

int Match_c_GPRS_SUSPENSION_REQUEST_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 52) /* message type */
	);
}

int Match_c_HANDOVER_COMPLETE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 44) /* message type */
	);
}

int Match_c_HANDOVER_FAILURE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 40) /* message type */
	);
}

int Match_c_MEASUREMENT_REPORT_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 21) /* message type */
	);
}

int Match_c_NOTIFICATION_RESPONSE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 38) /* message type */
	);
}

int Match_c_PAGING_RESPONSE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 39) /* message type */
	);
}

int Match_c_PARTIAL_RELEASE_COMPLETE_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 15) /* message type */
	);
}

int Match_c_RR_INITIALISATION_REQUEST_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 60) /* message type */
	);
}

int Match_c_RR_STATUS (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 18) /* message type */
	);
}

int Match_c_TALKER_INDICATION_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 17) /* message type */
	);
}

int Match_c_PRIORITY_DNLINK_REQUEST (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 102) /* message type */
	);
}

int Match_c_DATA_INDICATION (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 103) /* message type */
	);
}

int Match_c_DATA_INDICATION_2 (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 104) /* message type */
	);
}

int Match_c_UPLINK_RELEASE (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 14) /* message type */
	);
}

int Match_c_EXTENDED_MEASUREMENT_REPORT_UP (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 54) /* message type */
	);
}

int Match_c_APPLICATION_INFORMATION (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 56) /* message type */
	);
}


/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.152
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#include "RRPLENDownlink_RR.h"
#include "ed_c_known_ie_RR.h"
#include "ed_tlv.h"
#include "UserDefinedDataTypes_RR.h"
#include "CSN1DataTypes_RR.h"
#if ED_VERSION != 10152
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.152
#endif


#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE IMMEDIATE_ASSIGNMENT_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_IMMEDIATE_ASSIGNMENT_DN (char* Buffer, ED_EXLONG BitOffset, const c_IMMEDIATE_ASSIGNMENT_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 63, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for PageMode */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->PageMode> DOT=<.> */
		Len = ENCODE_c_PageMode (Buffer, (CurrOfs+4), (&(Source->PageMode)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:979> Error encoding subfield PageMode\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for DedicatedModeOrTbf */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->DedicatedModeOrTbf> DOT=<.> */
		Len = ENCODE_c_DedicatedModeOrTBF4b (Buffer, (CurrOfs-4), (&(Source->DedicatedModeOrTbf)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:980> Error encoding subfield DedicatedModeOrTbf\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ChannelDescription */
	{
#undef DATA
#define DATA (*Source)
#define ED_IS_ENCODING
		if (!(DATA.DedicatedModeOrTbf.TD)) {
			/* Append to buffer value part DEBUG FIELD=<Source->ChannelDescription> DOT=<->> */
			Len = ENCODE_c_TChDesc (Buffer, CurrOfs, Source->ChannelDescription);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:981> Error encoding subfield ChannelDescription\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
#undef DATA
#undef ED_IS_ENCODING
	}
	
	/* Code for PacketChannelDescription */
	{
#undef DATA
#define DATA (*Source)
#define ED_IS_ENCODING
		if ((DATA.DedicatedModeOrTbf.TD)) {
			/* Append to buffer value part DEBUG FIELD=<Source->PacketChannelDescription> DOT=<->> */
			Len = ENCODE_c_PacketChannelDescription (Buffer, CurrOfs, Source->PacketChannelDescription);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:982> Error encoding subfield PacketChannelDescription\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
#undef DATA
#undef ED_IS_ENCODING
	}
	
	/* Code for ReqRef */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ReqRef> DOT=<.> */
		Len = ENCODE_c_RequestReference (Buffer, CurrOfs, (&(Source->ReqRef)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:983> Error encoding subfield ReqRef\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for TimingAdvance */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->TimingAdvance> DOT=<.> */
		Len = ENCODE_c_TimingAdvance (Buffer, CurrOfs, (&(Source->TimingAdvance)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:984> Error encoding subfield TimingAdvance\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for MobileAllocation */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->MobileAllocation> DOT=<.> */
		Len = ENCODE_c_MobileAllocation (Buffer, CurrOfs+8, (&(Source->MobileAllocation)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:985> Error encoding subfield MobileAllocation\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for StartingTime */
	{
		if (Source->StartingTime_Present) {
			/* Append to buffer IEI tag 0x7C */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x7C), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->StartingTime> DOT=<->> */
			Len = ENCODE_c_StartingTime (Buffer, CurrOfs, Source->StartingTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:986> Error encoding subfield StartingTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for EndOfL2Length */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->EndOfL2Length> DOT=<.> */
		Len = 0;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:987> Error encoding subfield EndOfL2Length\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
		/* Encode L2 Pseudo Length */
		if (Mode == 0) {
			EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)((CurrOfs-BitOffset-8)>>3), 6);
			EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
		}
	}
	
	/* Code for IaRestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->IaRestOctets> DOT=<.> */
		Len = ENCODE_c_IARestOctets (Buffer, CurrOfs, (&(Source->IaRestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:988> Error encoding subfield IaRestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE IMMEDIATE_ASSIGNMENT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_IMMEDIATE_ASSIGNMENT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_IMMEDIATE_ASSIGNMENT_DN* ED_CONST Source))
{
	return L3_ENCODE_c_IMMEDIATE_ASSIGNMENT_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE IMMEDIATE_ASSIGNMENT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_IMMEDIATE_ASSIGNMENT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_IMMEDIATE_ASSIGNMENT_DN* ED_CONST Source))
{
	return L3_ENCODE_c_IMMEDIATE_ASSIGNMENT_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE IMMEDIATE_ASSIGNMENT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_IMMEDIATE_ASSIGNMENT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_IMMEDIATE_ASSIGNMENT_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_IMMEDIATE_ASSIGNMENT_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE IMMEDIATE_ASSIGNMENT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_IMMEDIATE_ASSIGNMENT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_IMMEDIATE_ASSIGNMENT_DN* ED_CONST Destin, ED_EXLONG Length))
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
		{0, 0, ED_SKIPLIST_OPTIONAL}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_OPTIONAL}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{124, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	/* Stores condition result */
	int CondTrue;
	ED_WARNING_REMOVER (TLVSkipItems);
	
	/*----------------------------------------------------- 
		Code for IE PageMode
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_PageMode (Buffer, (CurrOfs+4), (&(Destin->PageMode)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:989> Error decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 989, (Destin->PageMode))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:990> Message too short decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 989, (Destin->PageMode))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE DedicatedModeOrTbf
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_DedicatedModeOrTBF4b (Buffer, (CurrOfs-4), (&(Destin->DedicatedModeOrTbf)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:991> Error decoding subfield DedicatedModeOrTbf\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 991, (Destin->DedicatedModeOrTbf))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:992> Message too short decoding subfield DedicatedModeOrTbf\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 991, (Destin->DedicatedModeOrTbf))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ChannelDescription
	------------------------------------------------------*/
	
	/* This is a conditional untagged field */
#define ED_IS_DECODING
#define DATA (*Destin)
	CondTrue = (!(DATA.DedicatedModeOrTbf.TD));
#undef DATA
	if (CondTrue) {
		SETPRESENT_c_IMMEDIATE_ASSIGNMENT_DN_ChannelDescription (Destin, ED_TRUE);
		CurrOfs += 0;
		Len = 24;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, Destin->ChannelDescription, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:993> Error decoding subfield ChannelDescription\n");
#if ED_HANDLE_CONDITIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_IMMEDIATE_ASSIGNMENT_DN_ChannelDescription (Destin, ED_FALSE);
#endif
			ED_HANDLE_CONDITIONAL_IE_SYNTAX_ERROR ((-1), 993, (Destin->ChannelDescription))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:994> Message too short decoding subfield ChannelDescription\n");
#if ED_HANDLE_CONDITIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_IMMEDIATE_ASSIGNMENT_DN_ChannelDescription (Destin, ED_FALSE);
#endif
			ED_HANDLE_CONDITIONAL_IE_MSG_TOO_SHORT ((-1), 993, (Destin->ChannelDescription))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE PacketChannelDescription
	------------------------------------------------------*/
	
	/* This is a conditional untagged field */
#define ED_IS_DECODING
#define DATA (*Destin)
	CondTrue = ((DATA.DedicatedModeOrTbf.TD));
#undef DATA
	if (CondTrue) {
		SETPRESENT_c_IMMEDIATE_ASSIGNMENT_DN_PacketChannelDescription (Destin, ED_TRUE);
		CurrOfs += 0;
		Len = 24;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_PacketChannelDescription (Buffer, CurrOfs, Destin->PacketChannelDescription, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:995> Error decoding subfield PacketChannelDescription\n");
#if ED_HANDLE_CONDITIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_IMMEDIATE_ASSIGNMENT_DN_PacketChannelDescription (Destin, ED_FALSE);
#endif
			ED_HANDLE_CONDITIONAL_IE_SYNTAX_ERROR ((-1), 995, (Destin->PacketChannelDescription))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:996> Message too short decoding subfield PacketChannelDescription\n");
#if ED_HANDLE_CONDITIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_IMMEDIATE_ASSIGNMENT_DN_PacketChannelDescription (Destin, ED_FALSE);
#endif
			ED_HANDLE_CONDITIONAL_IE_MSG_TOO_SHORT ((-1), 995, (Destin->PacketChannelDescription))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ReqRef
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RequestReference (Buffer, CurrOfs, (&(Destin->ReqRef)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:997> Error decoding subfield ReqRef\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 997, (Destin->ReqRef))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:998> Message too short decoding subfield ReqRef\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 997, (Destin->ReqRef))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE TimingAdvance
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_TimingAdvance (Buffer, CurrOfs, (&(Destin->TimingAdvance)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:999> Error decoding subfield TimingAdvance\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 999, (Destin->TimingAdvance))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1000> Message too short decoding subfield TimingAdvance\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 999, (Destin->TimingAdvance))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileAllocation
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Len > 64) {
		ED_SIGNAL_ERROR ("<ERRID:1001> Size error decoding IE MobileAllocation\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 1001, (Destin->MobileAllocation))
	} 
#endif
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_MobileAllocation (Buffer, CurrOfs, (&(Destin->MobileAllocation)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1002> Error decoding subfield MobileAllocation\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1002, (Destin->MobileAllocation))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1003> Message too short decoding subfield MobileAllocation\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1002, (Destin->MobileAllocation))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE StartingTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x7C */
	ED_EXPECT_OPTIONAL_IE (0x7C,  8, 1004, 7, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x7C) {
		SETPRESENT_c_IMMEDIATE_ASSIGNMENT_DN_StartingTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 16;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_StartingTime (Buffer, CurrOfs, Destin->StartingTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:1005> Error decoding subfield StartingTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_IMMEDIATE_ASSIGNMENT_DN_StartingTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x7C, 1005, (Destin->StartingTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:1006> Message too short decoding subfield StartingTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_IMMEDIATE_ASSIGNMENT_DN_StartingTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x7C, 1005, (Destin->StartingTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE EndOfL2Length
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 0;
	/* Read value part LOCATOR_16 */
	RetLen = 0;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1007> Error decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1007, (Destin->EndOfL2Length))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1008> Message too short decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1007, (Destin->EndOfL2Length))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE IaRestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_IARestOctets (Buffer, CurrOfs, (&(Destin->IaRestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1009> Error decoding subfield IaRestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1009, (Destin->IaRestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1010> Message too short decoding subfield IaRestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1009, (Destin->IaRestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE IMMEDIATE_PACKET_ASSIGNMENT_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_IMMEDIATE_PACKET_ASSIGNMENT_DN (char* Buffer, ED_EXLONG BitOffset, const c_IMMEDIATE_PACKET_ASSIGNMENT_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 105, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for PageMode */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->PageMode> DOT=<.> */
		Len = ENCODE_c_PageMode (Buffer, (CurrOfs+4), (&(Source->PageMode)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1011> Error encoding subfield PageMode\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for FeatureIndicator */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->FeatureIndicator> DOT=<.> */
		Len = ENCODE_c_FeatureIndicator (Buffer, (CurrOfs-4), (&(Source->FeatureIndicator)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1012> Error encoding subfield FeatureIndicator\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for EndOfL2Length */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->EndOfL2Length> DOT=<.> */
		Len = 0;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1013> Error encoding subfield EndOfL2Length\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
		/* Encode L2 Pseudo Length */
		if (Mode == 0) {
			EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)((CurrOfs-BitOffset-8)>>3), 6);
			EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
		}
	}
	
	/* Code for IPARestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->IPARestOctets> DOT=<.> */
		Len = ENCODE_c_IPARestOctets (Buffer, CurrOfs, (&(Source->IPARestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1014> Error encoding subfield IPARestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE IMMEDIATE_PACKET_ASSIGNMENT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_IMMEDIATE_PACKET_ASSIGNMENT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_IMMEDIATE_PACKET_ASSIGNMENT_DN* ED_CONST Source))
{
	return L3_ENCODE_c_IMMEDIATE_PACKET_ASSIGNMENT_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE IMMEDIATE_PACKET_ASSIGNMENT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_IMMEDIATE_PACKET_ASSIGNMENT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_IMMEDIATE_PACKET_ASSIGNMENT_DN* ED_CONST Source))
{
	return L3_ENCODE_c_IMMEDIATE_PACKET_ASSIGNMENT_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE IMMEDIATE_PACKET_ASSIGNMENT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_IMMEDIATE_PACKET_ASSIGNMENT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_IMMEDIATE_PACKET_ASSIGNMENT_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_IMMEDIATE_PACKET_ASSIGNMENT_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE IMMEDIATE_PACKET_ASSIGNMENT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_IMMEDIATE_PACKET_ASSIGNMENT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_IMMEDIATE_PACKET_ASSIGNMENT_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE PageMode
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_PageMode (Buffer, (CurrOfs+4), (&(Destin->PageMode)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1015> Error decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1015, (Destin->PageMode))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1016> Message too short decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1015, (Destin->PageMode))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE FeatureIndicator
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_FeatureIndicator (Buffer, (CurrOfs-4), (&(Destin->FeatureIndicator)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1017> Error decoding subfield FeatureIndicator\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1017, (Destin->FeatureIndicator))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1018> Message too short decoding subfield FeatureIndicator\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1017, (Destin->FeatureIndicator))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE EndOfL2Length
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 0;
	/* Read value part LOCATOR_16 */
	RetLen = 0;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1019> Error decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1019, (Destin->EndOfL2Length))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1020> Message too short decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1019, (Destin->EndOfL2Length))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE IPARestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 152;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_IPARestOctets (Buffer, CurrOfs, (&(Destin->IPARestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1021> Error decoding subfield IPARestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1021, (Destin->IPARestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1022> Message too short decoding subfield IPARestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1021, (Destin->IPARestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE IMMEDIATE_ASSIGNMENT_EXTENDED_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN (char* Buffer, ED_EXLONG BitOffset, const c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 57, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for PageMode */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->PageMode> DOT=<.> */
		Len = ENCODE_c_PageMode (Buffer, (CurrOfs+4), (&(Source->PageMode)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1023> Error encoding subfield PageMode\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for FeatureIndicator */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->FeatureIndicator> DOT=<.> */
		Len = ENCODE_c_FeatureIndicator (Buffer, (CurrOfs-4), (&(Source->FeatureIndicator)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1024> Error encoding subfield FeatureIndicator\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ChannelDescription1 */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ChannelDescription1> DOT=<.> */
		Len = ENCODE_c_TChDesc (Buffer, CurrOfs, (&(Source->ChannelDescription1)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1025> Error encoding subfield ChannelDescription1\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ReqRef1 */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ReqRef1> DOT=<.> */
		Len = ENCODE_c_RequestReference (Buffer, CurrOfs, (&(Source->ReqRef1)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1026> Error encoding subfield ReqRef1\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for TimingAdvance1 */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->TimingAdvance1> DOT=<.> */
		Len = ENCODE_c_TimingAdvance (Buffer, CurrOfs, (&(Source->TimingAdvance1)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1027> Error encoding subfield TimingAdvance1\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ChannelDescription2 */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ChannelDescription2> DOT=<.> */
		Len = ENCODE_c_TChDesc (Buffer, CurrOfs, (&(Source->ChannelDescription2)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1028> Error encoding subfield ChannelDescription2\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ReqRef2 */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ReqRef2> DOT=<.> */
		Len = ENCODE_c_RequestReference (Buffer, CurrOfs, (&(Source->ReqRef2)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1029> Error encoding subfield ReqRef2\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for TimingAdvance2 */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->TimingAdvance2> DOT=<.> */
		Len = ENCODE_c_TimingAdvance (Buffer, CurrOfs, (&(Source->TimingAdvance2)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1030> Error encoding subfield TimingAdvance2\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for MobileAllocation */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->MobileAllocation> DOT=<.> */
		Len = ENCODE_c_MobileAllocation (Buffer, CurrOfs+8, (&(Source->MobileAllocation)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1031> Error encoding subfield MobileAllocation\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for StartingTime */
	{
		if (Source->StartingTime_Present) {
			/* Append to buffer IEI tag 0x7C */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x7C), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->StartingTime> DOT=<->> */
			Len = ENCODE_c_StartingTime (Buffer, CurrOfs, Source->StartingTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:1032> Error encoding subfield StartingTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for EndOfL2Length */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->EndOfL2Length> DOT=<.> */
		Len = 0;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1033> Error encoding subfield EndOfL2Length\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
		/* Encode L2 Pseudo Length */
		if (Mode == 0) {
			EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)((CurrOfs-BitOffset-8)>>3), 6);
			EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
		}
	}
	
	/* Code for IaxRestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->IaxRestOctets> DOT=<.> */
		Len = ENCODE_c_IAXRestOctets (Buffer, CurrOfs, (&(Source->IaxRestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1034> Error encoding subfield IaxRestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE IMMEDIATE_ASSIGNMENT_EXTENDED_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN* ED_CONST Source))
{
	return L3_ENCODE_c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE IMMEDIATE_ASSIGNMENT_EXTENDED_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN* ED_CONST Source))
{
	return L3_ENCODE_c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE IMMEDIATE_ASSIGNMENT_EXTENDED_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE IMMEDIATE_ASSIGNMENT_EXTENDED_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN* ED_CONST Destin, ED_EXLONG Length))
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
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{124, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	ED_WARNING_REMOVER (TLVSkipItems);
	
	/*----------------------------------------------------- 
		Code for IE PageMode
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_PageMode (Buffer, (CurrOfs+4), (&(Destin->PageMode)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1035> Error decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1035, (Destin->PageMode))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1036> Message too short decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1035, (Destin->PageMode))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE FeatureIndicator
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_FeatureIndicator (Buffer, (CurrOfs-4), (&(Destin->FeatureIndicator)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1037> Error decoding subfield FeatureIndicator\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1037, (Destin->FeatureIndicator))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1038> Message too short decoding subfield FeatureIndicator\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1037, (Destin->FeatureIndicator))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ChannelDescription1
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, (&(Destin->ChannelDescription1)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1039> Error decoding subfield ChannelDescription1\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1039, (Destin->ChannelDescription1))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1040> Message too short decoding subfield ChannelDescription1\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1039, (Destin->ChannelDescription1))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ReqRef1
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RequestReference (Buffer, CurrOfs, (&(Destin->ReqRef1)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1041> Error decoding subfield ReqRef1\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1041, (Destin->ReqRef1))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1042> Message too short decoding subfield ReqRef1\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1041, (Destin->ReqRef1))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE TimingAdvance1
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_TimingAdvance (Buffer, CurrOfs, (&(Destin->TimingAdvance1)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1043> Error decoding subfield TimingAdvance1\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1043, (Destin->TimingAdvance1))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1044> Message too short decoding subfield TimingAdvance1\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1043, (Destin->TimingAdvance1))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ChannelDescription2
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, (&(Destin->ChannelDescription2)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1045> Error decoding subfield ChannelDescription2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1045, (Destin->ChannelDescription2))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1046> Message too short decoding subfield ChannelDescription2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1045, (Destin->ChannelDescription2))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ReqRef2
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RequestReference (Buffer, CurrOfs, (&(Destin->ReqRef2)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1047> Error decoding subfield ReqRef2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1047, (Destin->ReqRef2))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1048> Message too short decoding subfield ReqRef2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1047, (Destin->ReqRef2))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE TimingAdvance2
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_TimingAdvance (Buffer, CurrOfs, (&(Destin->TimingAdvance2)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1049> Error decoding subfield TimingAdvance2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1049, (Destin->TimingAdvance2))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1050> Message too short decoding subfield TimingAdvance2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1049, (Destin->TimingAdvance2))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileAllocation
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Len > 32) {
		ED_SIGNAL_ERROR ("<ERRID:1051> Size error decoding IE MobileAllocation\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 1051, (Destin->MobileAllocation))
	} 
#endif
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_MobileAllocation (Buffer, CurrOfs, (&(Destin->MobileAllocation)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1052> Error decoding subfield MobileAllocation\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1052, (Destin->MobileAllocation))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1053> Message too short decoding subfield MobileAllocation\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1052, (Destin->MobileAllocation))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE StartingTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x7C */
	ED_EXPECT_OPTIONAL_IE (0x7C,  8, 1054, 9, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x7C) {
		SETPRESENT_c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN_StartingTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 16;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_StartingTime (Buffer, CurrOfs, Destin->StartingTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:1055> Error decoding subfield StartingTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN_StartingTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x7C, 1055, (Destin->StartingTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:1056> Message too short decoding subfield StartingTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN_StartingTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x7C, 1055, (Destin->StartingTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE EndOfL2Length
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 0;
	/* Read value part LOCATOR_16 */
	RetLen = 0;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1057> Error decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1057, (Destin->EndOfL2Length))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1058> Message too short decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1057, (Destin->EndOfL2Length))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE IaxRestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_IAXRestOctets (Buffer, CurrOfs, (&(Destin->IaxRestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1059> Error decoding subfield IaxRestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1059, (Destin->IaxRestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1060> Message too short decoding subfield IaxRestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1059, (Destin->IaxRestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE IMMEDIATE_ASSIGNMENT_REJECT_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_IMMEDIATE_ASSIGNMENT_REJECT_DN (char* Buffer, ED_EXLONG BitOffset, const c_IMMEDIATE_ASSIGNMENT_REJECT_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 58, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for PageMode */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->PageMode> DOT=<.> */
		Len = ENCODE_c_PageMode (Buffer, (CurrOfs+4), (&(Source->PageMode)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1061> Error encoding subfield PageMode\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for FeatureIndicator */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->FeatureIndicator> DOT=<.> */
		Len = ENCODE_c_FeatureIndicator (Buffer, (CurrOfs-4), (&(Source->FeatureIndicator)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1062> Error encoding subfield FeatureIndicator\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ReqRef1 */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ReqRef1> DOT=<.> */
		Len = ENCODE_c_RequestReference (Buffer, CurrOfs, (&(Source->ReqRef1)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1063> Error encoding subfield ReqRef1\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for WaitIndication1 */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->WaitIndication1> DOT=<.> */
		EDIntToBits (Buffer, (CurrOfs), (int)(Source->WaitIndication1), 8);
		Len = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1064> Error encoding subfield WaitIndication1\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ReqRef2 */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ReqRef2> DOT=<.> */
		Len = ENCODE_c_RequestReference (Buffer, CurrOfs, (&(Source->ReqRef2)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1065> Error encoding subfield ReqRef2\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for WaitIndication2 */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->WaitIndication2> DOT=<.> */
		EDIntToBits (Buffer, (CurrOfs), (int)(Source->WaitIndication2), 8);
		Len = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1066> Error encoding subfield WaitIndication2\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ReqRef3 */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ReqRef3> DOT=<.> */
		Len = ENCODE_c_RequestReference (Buffer, CurrOfs, (&(Source->ReqRef3)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1067> Error encoding subfield ReqRef3\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for WaitIndication3 */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->WaitIndication3> DOT=<.> */
		EDIntToBits (Buffer, (CurrOfs), (int)(Source->WaitIndication3), 8);
		Len = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1068> Error encoding subfield WaitIndication3\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ReqRef4 */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ReqRef4> DOT=<.> */
		Len = ENCODE_c_RequestReference (Buffer, CurrOfs, (&(Source->ReqRef4)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1069> Error encoding subfield ReqRef4\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for WaitIndication4 */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->WaitIndication4> DOT=<.> */
		EDIntToBits (Buffer, (CurrOfs), (int)(Source->WaitIndication4), 8);
		Len = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1070> Error encoding subfield WaitIndication4\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for IarRestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->IarRestOctets> DOT=<.> */
		Len = ENCODE_c_IARRestOctets (Buffer, CurrOfs, (&(Source->IarRestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1071> Error encoding subfield IarRestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(19), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE IMMEDIATE_ASSIGNMENT_REJECT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_IMMEDIATE_ASSIGNMENT_REJECT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_IMMEDIATE_ASSIGNMENT_REJECT_DN* ED_CONST Source))
{
	return L3_ENCODE_c_IMMEDIATE_ASSIGNMENT_REJECT_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE IMMEDIATE_ASSIGNMENT_REJECT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_IMMEDIATE_ASSIGNMENT_REJECT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_IMMEDIATE_ASSIGNMENT_REJECT_DN* ED_CONST Source))
{
	return L3_ENCODE_c_IMMEDIATE_ASSIGNMENT_REJECT_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE IMMEDIATE_ASSIGNMENT_REJECT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_IMMEDIATE_ASSIGNMENT_REJECT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_IMMEDIATE_ASSIGNMENT_REJECT_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_IMMEDIATE_ASSIGNMENT_REJECT_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE IMMEDIATE_ASSIGNMENT_REJECT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_IMMEDIATE_ASSIGNMENT_REJECT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_IMMEDIATE_ASSIGNMENT_REJECT_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE PageMode
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_PageMode (Buffer, (CurrOfs+4), (&(Destin->PageMode)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1072> Error decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1072, (Destin->PageMode))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1073> Message too short decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1072, (Destin->PageMode))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE FeatureIndicator
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_FeatureIndicator (Buffer, (CurrOfs-4), (&(Destin->FeatureIndicator)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1074> Error decoding subfield FeatureIndicator\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1074, (Destin->FeatureIndicator))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1075> Message too short decoding subfield FeatureIndicator\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1074, (Destin->FeatureIndicator))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ReqRef1
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RequestReference (Buffer, CurrOfs, (&(Destin->ReqRef1)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1076> Error decoding subfield ReqRef1\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1076, (Destin->ReqRef1))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1077> Message too short decoding subfield ReqRef1\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1076, (Destin->ReqRef1))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE WaitIndication1
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	Destin->WaitIndication1 = (ED_OCTET)EDBitsToInt (Buffer, (CurrOfs), 8);
	/* LOCATOR SETTINGS LOCINT */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-52198=EDCore::TDMInteger) */Destin->WaitIndication1___LOCATOR), CurrOfs, 8);
	RetLen = 8;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1078> Error decoding subfield WaitIndication1\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1078, (Destin->WaitIndication1))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1079> Message too short decoding subfield WaitIndication1\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1078, (Destin->WaitIndication1))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ReqRef2
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RequestReference (Buffer, CurrOfs, (&(Destin->ReqRef2)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1080> Error decoding subfield ReqRef2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1080, (Destin->ReqRef2))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1081> Message too short decoding subfield ReqRef2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1080, (Destin->ReqRef2))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE WaitIndication2
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	Destin->WaitIndication2 = (ED_OCTET)EDBitsToInt (Buffer, (CurrOfs), 8);
	/* LOCATOR SETTINGS LOCINT */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-52202=EDCore::TDMInteger) */Destin->WaitIndication2___LOCATOR), CurrOfs, 8);
	RetLen = 8;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1082> Error decoding subfield WaitIndication2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1082, (Destin->WaitIndication2))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1083> Message too short decoding subfield WaitIndication2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1082, (Destin->WaitIndication2))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ReqRef3
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RequestReference (Buffer, CurrOfs, (&(Destin->ReqRef3)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1084> Error decoding subfield ReqRef3\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1084, (Destin->ReqRef3))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1085> Message too short decoding subfield ReqRef3\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1084, (Destin->ReqRef3))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE WaitIndication3
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	Destin->WaitIndication3 = (ED_OCTET)EDBitsToInt (Buffer, (CurrOfs), 8);
	/* LOCATOR SETTINGS LOCINT */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-52206=EDCore::TDMInteger) */Destin->WaitIndication3___LOCATOR), CurrOfs, 8);
	RetLen = 8;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1086> Error decoding subfield WaitIndication3\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1086, (Destin->WaitIndication3))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1087> Message too short decoding subfield WaitIndication3\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1086, (Destin->WaitIndication3))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ReqRef4
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RequestReference (Buffer, CurrOfs, (&(Destin->ReqRef4)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1088> Error decoding subfield ReqRef4\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1088, (Destin->ReqRef4))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1089> Message too short decoding subfield ReqRef4\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1088, (Destin->ReqRef4))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE WaitIndication4
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	Destin->WaitIndication4 = (ED_OCTET)EDBitsToInt (Buffer, (CurrOfs), 8);
	/* LOCATOR SETTINGS LOCINT */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-52210=EDCore::TDMInteger) */Destin->WaitIndication4___LOCATOR), CurrOfs, 8);
	RetLen = 8;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1090> Error decoding subfield WaitIndication4\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1090, (Destin->WaitIndication4))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1091> Message too short decoding subfield WaitIndication4\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1090, (Destin->WaitIndication4))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE IarRestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_IARRestOctets (Buffer, CurrOfs, (&(Destin->IarRestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1092> Error decoding subfield IarRestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1092, (Destin->IarRestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1093> Message too short decoding subfield IarRestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1092, (Destin->IarRestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE NOTIFICATION_NCH_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_NOTIFICATION_NCH_DN (char* Buffer, ED_EXLONG BitOffset, const c_NOTIFICATION_NCH_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 32, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for NtNRestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->NtNRestOctets> DOT=<.> */
		Len = ENCODE_c_NTNRestOctets (Buffer, CurrOfs, (&(Source->NtNRestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1094> Error encoding subfield NtNRestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(1), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE NOTIFICATION_NCH_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_NOTIFICATION_NCH_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_NOTIFICATION_NCH_DN* ED_CONST Source))
{
	return L3_ENCODE_c_NOTIFICATION_NCH_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE NOTIFICATION_NCH_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_NOTIFICATION_NCH_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_NOTIFICATION_NCH_DN* ED_CONST Source))
{
	return L3_ENCODE_c_NOTIFICATION_NCH_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE NOTIFICATION_NCH_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_NOTIFICATION_NCH_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_NOTIFICATION_NCH_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_NOTIFICATION_NCH_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE NOTIFICATION_NCH_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_NOTIFICATION_NCH_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_NOTIFICATION_NCH_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE NtNRestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_NTNRestOctets (Buffer, CurrOfs, (&(Destin->NtNRestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1095> Error decoding subfield NtNRestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1095, (Destin->NtNRestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1096> Message too short decoding subfield NtNRestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1095, (Destin->NtNRestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE PAGING_REQUEST_TYPE_1_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_PAGING_REQUEST_TYPE_1_DN (char* Buffer, ED_EXLONG BitOffset, const c_PAGING_REQUEST_TYPE_1_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 33, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for PageMode */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->PageMode> DOT=<.> */
		Len = ENCODE_c_PageMode (Buffer, (CurrOfs+4), (&(Source->PageMode)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1097> Error encoding subfield PageMode\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ChannelsNeededForMobiles1And2 */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ChannelsNeededForMobiles1And2> DOT=<.> */
		Len = ENCODE_c_ChannelNeeded (Buffer, (CurrOfs-4), (&(Source->ChannelsNeededForMobiles1And2)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1098> Error encoding subfield ChannelsNeededForMobiles1And2\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for MobileId1 */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->MobileId1> DOT=<.> */
		Len = ENCODE_c_RRMobileId (Buffer, CurrOfs+8, (&(Source->MobileId1)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1099> Error encoding subfield MobileId1\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for MobileId2 */
	{
		int TLV_Base = CurrOfs;
		if (Source->MobileId2_Present) {
			/* Append to buffer IEI tag 0x17 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x17), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->MobileId2> DOT=<->> */
			Len = ENCODE_c_RRMobileId (Buffer, CurrOfs+8, Source->MobileId2);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:1100> Error encoding subfield MobileId2\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for EndOfL2Length */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->EndOfL2Length> DOT=<.> */
		Len = 0;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1101> Error encoding subfield EndOfL2Length\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
		/* Encode L2 Pseudo Length */
		if (Mode == 0) {
			EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)((CurrOfs-BitOffset-8)>>3), 6);
			EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
		}
	}
	
	/* Code for P1RestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->P1RestOctets> DOT=<.> */
		Len = ENCODE_c_P1RestOctets (Buffer, CurrOfs, (&(Source->P1RestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1102> Error encoding subfield P1RestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE PAGING_REQUEST_TYPE_1_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PAGING_REQUEST_TYPE_1_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PAGING_REQUEST_TYPE_1_DN* ED_CONST Source))
{
	return L3_ENCODE_c_PAGING_REQUEST_TYPE_1_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE PAGING_REQUEST_TYPE_1_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_PAGING_REQUEST_TYPE_1_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PAGING_REQUEST_TYPE_1_DN* ED_CONST Source))
{
	return L3_ENCODE_c_PAGING_REQUEST_TYPE_1_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PAGING_REQUEST_TYPE_1_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PAGING_REQUEST_TYPE_1_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PAGING_REQUEST_TYPE_1_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_PAGING_REQUEST_TYPE_1_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PAGING_REQUEST_TYPE_1_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_PAGING_REQUEST_TYPE_1_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PAGING_REQUEST_TYPE_1_DN* ED_CONST Destin, ED_EXLONG Length))
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
		{23, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	ED_WARNING_REMOVER (TLVSkipItems);
	
	/*----------------------------------------------------- 
		Code for IE PageMode
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_PageMode (Buffer, (CurrOfs+4), (&(Destin->PageMode)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1103> Error decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1103, (Destin->PageMode))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1104> Message too short decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1103, (Destin->PageMode))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ChannelsNeededForMobiles1And2
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_ChannelNeeded (Buffer, (CurrOfs-4), (&(Destin->ChannelsNeededForMobiles1And2)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1105> Error decoding subfield ChannelsNeededForMobiles1And2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1105, (Destin->ChannelsNeededForMobiles1And2))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1106> Message too short decoding subfield ChannelsNeededForMobiles1And2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1105, (Destin->ChannelsNeededForMobiles1And2))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileId1
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if ((Len < 8) || (Len > 64)) {
		ED_SIGNAL_ERROR ("<ERRID:1107> Size error decoding IE MobileId1\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 1107, (Destin->MobileId1))
	} 
#endif
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RRMobileId (Buffer, CurrOfs, (&(Destin->MobileId1)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1108> Error decoding subfield MobileId1\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1108, (Destin->MobileId1))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1109> Message too short decoding subfield MobileId1\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1108, (Destin->MobileId1))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileId2
	------------------------------------------------------*/
	/* Detect IEI tag 0x17 */
	ED_EXPECT_OPTIONAL_IE (0x17,  8, 1110, 3, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x17) {
		SETPRESENT_c_PAGING_REQUEST_TYPE_1_DN_MobileId2 (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 64)) {
			ED_SIGNAL_ERROR ("<ERRID:1111> Size error decoding IE MobileId2\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_PAGING_REQUEST_TYPE_1_DN_MobileId2 (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x17, 1111, (Destin->MobileId2))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_RRMobileId (Buffer, CurrOfs, Destin->MobileId2, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:1112> Error decoding subfield MobileId2\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_PAGING_REQUEST_TYPE_1_DN_MobileId2 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x17, 1112, (Destin->MobileId2))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:1113> Message too short decoding subfield MobileId2\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_PAGING_REQUEST_TYPE_1_DN_MobileId2 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x17, 1112, (Destin->MobileId2))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE EndOfL2Length
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 0;
	/* Read value part LOCATOR_16 */
	RetLen = 0;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1114> Error decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1114, (Destin->EndOfL2Length))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1115> Message too short decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1114, (Destin->EndOfL2Length))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE P1RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_P1RestOctets (Buffer, CurrOfs, (&(Destin->P1RestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1116> Error decoding subfield P1RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1116, (Destin->P1RestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1117> Message too short decoding subfield P1RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1116, (Destin->P1RestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE PAGING_REQUEST_TYPE_2_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_PAGING_REQUEST_TYPE_2_DN (char* Buffer, ED_EXLONG BitOffset, const c_PAGING_REQUEST_TYPE_2_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 34, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for PageMode */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->PageMode> DOT=<.> */
		Len = ENCODE_c_PageMode (Buffer, (CurrOfs+4), (&(Source->PageMode)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1118> Error encoding subfield PageMode\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ChannelsNeededForMobiles1And2 */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ChannelsNeededForMobiles1And2> DOT=<.> */
		Len = ENCODE_c_ChannelNeeded (Buffer, (CurrOfs-4), (&(Source->ChannelsNeededForMobiles1And2)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1119> Error encoding subfield ChannelsNeededForMobiles1And2\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for MobileId1 */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->MobileId1> DOT=<.> */
		EDIntToBits (Buffer, (CurrOfs), (int)(Source->MobileId1), 32);
		Len = 32;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1120> Error encoding subfield MobileId1\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for MobileId2 */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->MobileId2> DOT=<.> */
		EDIntToBits (Buffer, (CurrOfs), (int)(Source->MobileId2), 32);
		Len = 32;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1121> Error encoding subfield MobileId2\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for MobileId3 */
	{
		int TLV_Base = CurrOfs;
		if (Source->MobileId3_Present) {
			/* Append to buffer IEI tag 0x17 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x17), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->MobileId3> DOT=<->> */
			Len = ENCODE_c_RRMobileId (Buffer, CurrOfs+8, Source->MobileId3);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:1122> Error encoding subfield MobileId3\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for EndOfL2Length */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->EndOfL2Length> DOT=<.> */
		Len = 0;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1123> Error encoding subfield EndOfL2Length\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
		/* Encode L2 Pseudo Length */
		if (Mode == 0) {
			EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)((CurrOfs-BitOffset-8)>>3), 6);
			EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
		}
	}
	
	/* Code for P2RestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->P2RestOctets> DOT=<.> */
		Len = ENCODE_c_P2RestOctets (Buffer, CurrOfs, (&(Source->P2RestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1124> Error encoding subfield P2RestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE PAGING_REQUEST_TYPE_2_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PAGING_REQUEST_TYPE_2_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PAGING_REQUEST_TYPE_2_DN* ED_CONST Source))
{
	return L3_ENCODE_c_PAGING_REQUEST_TYPE_2_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE PAGING_REQUEST_TYPE_2_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_PAGING_REQUEST_TYPE_2_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PAGING_REQUEST_TYPE_2_DN* ED_CONST Source))
{
	return L3_ENCODE_c_PAGING_REQUEST_TYPE_2_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PAGING_REQUEST_TYPE_2_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PAGING_REQUEST_TYPE_2_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PAGING_REQUEST_TYPE_2_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_PAGING_REQUEST_TYPE_2_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PAGING_REQUEST_TYPE_2_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_PAGING_REQUEST_TYPE_2_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PAGING_REQUEST_TYPE_2_DN* ED_CONST Destin, ED_EXLONG Length))
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
		{23, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	ED_WARNING_REMOVER (TLVSkipItems);
	
	/*----------------------------------------------------- 
		Code for IE PageMode
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_PageMode (Buffer, (CurrOfs+4), (&(Destin->PageMode)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1125> Error decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1125, (Destin->PageMode))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1126> Message too short decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1125, (Destin->PageMode))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ChannelsNeededForMobiles1And2
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_ChannelNeeded (Buffer, (CurrOfs-4), (&(Destin->ChannelsNeededForMobiles1And2)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1127> Error decoding subfield ChannelsNeededForMobiles1And2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1127, (Destin->ChannelsNeededForMobiles1And2))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1128> Message too short decoding subfield ChannelsNeededForMobiles1And2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1127, (Destin->ChannelsNeededForMobiles1And2))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileId1
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 32;
	/* Read value part LOCATOR_16 */
	Destin->MobileId1 = (ED_LONG)EDBitsToInt (Buffer, (CurrOfs), 32);
	/* LOCATOR SETTINGS LOCINT */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-52235=EDCore::TDMInteger) */Destin->MobileId1___LOCATOR), CurrOfs, 32);
	RetLen = 32;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1129> Error decoding subfield MobileId1\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1129, (Destin->MobileId1))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1130> Message too short decoding subfield MobileId1\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1129, (Destin->MobileId1))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileId2
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 32;
	/* Read value part LOCATOR_16 */
	Destin->MobileId2 = (ED_LONG)EDBitsToInt (Buffer, (CurrOfs), 32);
	/* LOCATOR SETTINGS LOCINT */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-52237=EDCore::TDMInteger) */Destin->MobileId2___LOCATOR), CurrOfs, 32);
	RetLen = 32;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1131> Error decoding subfield MobileId2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1131, (Destin->MobileId2))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1132> Message too short decoding subfield MobileId2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1131, (Destin->MobileId2))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileId3
	------------------------------------------------------*/
	/* Detect IEI tag 0x17 */
	ED_EXPECT_OPTIONAL_IE (0x17,  8, 1133, 4, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x17) {
		SETPRESENT_c_PAGING_REQUEST_TYPE_2_DN_MobileId3 (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 64)) {
			ED_SIGNAL_ERROR ("<ERRID:1134> Size error decoding IE MobileId3\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_PAGING_REQUEST_TYPE_2_DN_MobileId3 (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x17, 1134, (Destin->MobileId3))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_RRMobileId (Buffer, CurrOfs, Destin->MobileId3, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:1135> Error decoding subfield MobileId3\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_PAGING_REQUEST_TYPE_2_DN_MobileId3 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x17, 1135, (Destin->MobileId3))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:1136> Message too short decoding subfield MobileId3\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_PAGING_REQUEST_TYPE_2_DN_MobileId3 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x17, 1135, (Destin->MobileId3))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE EndOfL2Length
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 0;
	/* Read value part LOCATOR_16 */
	RetLen = 0;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1137> Error decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1137, (Destin->EndOfL2Length))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1138> Message too short decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1137, (Destin->EndOfL2Length))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE P2RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_P2RestOctets (Buffer, CurrOfs, (&(Destin->P2RestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1139> Error decoding subfield P2RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1139, (Destin->P2RestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1140> Message too short decoding subfield P2RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1139, (Destin->P2RestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE PAGING_REQUEST_TYPE_3_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_PAGING_REQUEST_TYPE_3_DN (char* Buffer, ED_EXLONG BitOffset, const c_PAGING_REQUEST_TYPE_3_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 36, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for PageMode */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->PageMode> DOT=<.> */
		Len = ENCODE_c_PageMode (Buffer, (CurrOfs+4), (&(Source->PageMode)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1141> Error encoding subfield PageMode\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ChannelsNeededForMobiles1And2 */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ChannelsNeededForMobiles1And2> DOT=<.> */
		Len = ENCODE_c_ChannelNeeded (Buffer, (CurrOfs-4), (&(Source->ChannelsNeededForMobiles1And2)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1142> Error encoding subfield ChannelsNeededForMobiles1And2\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for MobileId1 */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->MobileId1> DOT=<.> */
		EDIntToBits (Buffer, (CurrOfs), (int)(Source->MobileId1), 32);
		Len = 32;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1143> Error encoding subfield MobileId1\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for MobileId2 */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->MobileId2> DOT=<.> */
		EDIntToBits (Buffer, (CurrOfs), (int)(Source->MobileId2), 32);
		Len = 32;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1144> Error encoding subfield MobileId2\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for MobileId3 */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->MobileId3> DOT=<.> */
		EDIntToBits (Buffer, (CurrOfs), (int)(Source->MobileId3), 32);
		Len = 32;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1145> Error encoding subfield MobileId3\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for MobileId4 */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->MobileId4> DOT=<.> */
		EDIntToBits (Buffer, (CurrOfs), (int)(Source->MobileId4), 32);
		Len = 32;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1146> Error encoding subfield MobileId4\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for P3RestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->P3RestOctets> DOT=<.> */
		Len = ENCODE_c_P3RestOctets (Buffer, CurrOfs, (&(Source->P3RestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1147> Error encoding subfield P3RestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(19), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE PAGING_REQUEST_TYPE_3_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PAGING_REQUEST_TYPE_3_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PAGING_REQUEST_TYPE_3_DN* ED_CONST Source))
{
	return L3_ENCODE_c_PAGING_REQUEST_TYPE_3_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE PAGING_REQUEST_TYPE_3_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_PAGING_REQUEST_TYPE_3_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PAGING_REQUEST_TYPE_3_DN* ED_CONST Source))
{
	return L3_ENCODE_c_PAGING_REQUEST_TYPE_3_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PAGING_REQUEST_TYPE_3_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PAGING_REQUEST_TYPE_3_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PAGING_REQUEST_TYPE_3_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_PAGING_REQUEST_TYPE_3_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PAGING_REQUEST_TYPE_3_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_PAGING_REQUEST_TYPE_3_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PAGING_REQUEST_TYPE_3_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE PageMode
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_PageMode (Buffer, (CurrOfs+4), (&(Destin->PageMode)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1148> Error decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1148, (Destin->PageMode))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1149> Message too short decoding subfield PageMode\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1148, (Destin->PageMode))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ChannelsNeededForMobiles1And2
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_ChannelNeeded (Buffer, (CurrOfs-4), (&(Destin->ChannelsNeededForMobiles1And2)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1150> Error decoding subfield ChannelsNeededForMobiles1And2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1150, (Destin->ChannelsNeededForMobiles1And2))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1151> Message too short decoding subfield ChannelsNeededForMobiles1And2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1150, (Destin->ChannelsNeededForMobiles1And2))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileId1
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 32;
	/* Read value part LOCATOR_16 */
	Destin->MobileId1 = (ED_LONG)EDBitsToInt (Buffer, (CurrOfs), 32);
	/* LOCATOR SETTINGS LOCINT */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-52250=EDCore::TDMInteger) */Destin->MobileId1___LOCATOR), CurrOfs, 32);
	RetLen = 32;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1152> Error decoding subfield MobileId1\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1152, (Destin->MobileId1))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1153> Message too short decoding subfield MobileId1\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1152, (Destin->MobileId1))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileId2
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 32;
	/* Read value part LOCATOR_16 */
	Destin->MobileId2 = (ED_LONG)EDBitsToInt (Buffer, (CurrOfs), 32);
	/* LOCATOR SETTINGS LOCINT */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-52252=EDCore::TDMInteger) */Destin->MobileId2___LOCATOR), CurrOfs, 32);
	RetLen = 32;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1154> Error decoding subfield MobileId2\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1154, (Destin->MobileId2))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1155> Message too short decoding subfield MobileId2\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1154, (Destin->MobileId2))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileId3
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 32;
	/* Read value part LOCATOR_16 */
	Destin->MobileId3 = (ED_LONG)EDBitsToInt (Buffer, (CurrOfs), 32);
	/* LOCATOR SETTINGS LOCINT */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-52254=EDCore::TDMInteger) */Destin->MobileId3___LOCATOR), CurrOfs, 32);
	RetLen = 32;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1156> Error decoding subfield MobileId3\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1156, (Destin->MobileId3))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1157> Message too short decoding subfield MobileId3\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1156, (Destin->MobileId3))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileId4
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 32;
	/* Read value part LOCATOR_16 */
	Destin->MobileId4 = (ED_LONG)EDBitsToInt (Buffer, (CurrOfs), 32);
	/* LOCATOR SETTINGS LOCINT */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-52256=EDCore::TDMInteger) */Destin->MobileId4___LOCATOR), CurrOfs, 32);
	RetLen = 32;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1158> Error decoding subfield MobileId4\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1158, (Destin->MobileId4))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1159> Message too short decoding subfield MobileId4\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1158, (Destin->MobileId4))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE P3RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_P3RestOctets (Buffer, CurrOfs, (&(Destin->P3RestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1160> Error decoding subfield P3RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1160, (Destin->P3RestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1161> Message too short decoding subfield P3RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1160, (Destin->P3RestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_1_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_1_DN (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_1_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 25, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for CellChannelDescription */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->CellChannelDescription> DOT=<.> */
		Len = ENCODE_c_CellChannel (Buffer, CurrOfs, (&(Source->CellChannelDescription)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1162> Error encoding subfield CellChannelDescription\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for RachControlParam */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->RachControlParam> DOT=<.> */
		Len = ENCODE_c_RACHCtrlParam (Buffer, CurrOfs, (&(Source->RachControlParam)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1163> Error encoding subfield RachControlParam\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for Si1RestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->Si1RestOctets> DOT=<.> */
		Len = ENCODE_c_SI1RestOctets (Buffer, CurrOfs, (&(Source->Si1RestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1164> Error encoding subfield Si1RestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(21), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_1_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_1_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_1_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_1_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_1_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_1_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_1_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_1_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_1_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_1_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_1_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_1_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_1_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_1_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_1_DN* ED_CONST Destin, ED_EXLONG Length))
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
		ED_SIGNAL_ERROR ("<ERRID:1165> Error decoding subfield CellChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1165, (Destin->CellChannelDescription))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1166> Message too short decoding subfield CellChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1165, (Destin->CellChannelDescription))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE RachControlParam
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RACHCtrlParam (Buffer, CurrOfs, (&(Destin->RachControlParam)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1167> Error decoding subfield RachControlParam\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1167, (Destin->RachControlParam))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1168> Message too short decoding subfield RachControlParam\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1167, (Destin->RachControlParam))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE Si1RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_SI1RestOctets (Buffer, CurrOfs, (&(Destin->Si1RestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1169> Error decoding subfield Si1RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1169, (Destin->Si1RestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1170> Message too short decoding subfield Si1RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1169, (Destin->Si1RestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_2_DN (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_2_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 26, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for BcchFrequencyList */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->BcchFrequencyList> DOT=<.> */
		Len = ENCODE_c_NeighbourCellDescription (Buffer, CurrOfs, (&(Source->BcchFrequencyList)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1171> Error encoding subfield BcchFrequencyList\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for NccPermitted */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->NccPermitted> DOT=<.> */
		EDIntToBits (Buffer, (CurrOfs), (int)(Source->NccPermitted), 8);
		Len = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1172> Error encoding subfield NccPermitted\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for RachControlParam */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->RachControlParam> DOT=<.> */
		Len = ENCODE_c_RACHCtrlParam (Buffer, CurrOfs, (&(Source->RachControlParam)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1173> Error encoding subfield RachControlParam\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(22), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_2_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_2_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_2_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_2_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_2_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_2_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_2_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_2_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_2_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_2_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_2_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE BcchFrequencyList
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 128;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_NeighbourCellDescription (Buffer, CurrOfs, (&(Destin->BcchFrequencyList)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1174> Error decoding subfield BcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1174, (Destin->BcchFrequencyList))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1175> Message too short decoding subfield BcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1174, (Destin->BcchFrequencyList))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE NccPermitted
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	Destin->NccPermitted = (ED_OCTET)EDBitsToInt (Buffer, (CurrOfs), 8);
	/* LOCATOR SETTINGS LOCINT */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-52270=EDCore::TDMInteger) */Destin->NccPermitted___LOCATOR), CurrOfs, 8);
	RetLen = 8;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1176> Error decoding subfield NccPermitted\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1176, (Destin->NccPermitted))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1177> Message too short decoding subfield NccPermitted\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1176, (Destin->NccPermitted))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE RachControlParam
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RACHCtrlParam (Buffer, CurrOfs, (&(Destin->RachControlParam)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1178> Error decoding subfield RachControlParam\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1178, (Destin->RachControlParam))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1179> Message too short decoding subfield RachControlParam\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1178, (Destin->RachControlParam))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2BIS_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_2BIS_DN (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_2BIS_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 2, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for ExtendedBcchFrequencyList */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ExtendedBcchFrequencyList> DOT=<.> */
		Len = ENCODE_c_NeighbourCellDescription (Buffer, CurrOfs, (&(Source->ExtendedBcchFrequencyList)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1180> Error encoding subfield ExtendedBcchFrequencyList\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for RachControlParameters */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->RachControlParameters> DOT=<.> */
		Len = ENCODE_c_RACHCtrlParam (Buffer, CurrOfs, (&(Source->RachControlParameters)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1181> Error encoding subfield RachControlParameters\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for Si2bisRestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->Si2bisRestOctets> DOT=<.> */
		Len = ENCODE_c_SI2bisRestOctets (Buffer, CurrOfs, (&(Source->Si2bisRestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1182> Error encoding subfield Si2bisRestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(21), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2BIS_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_2BIS_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_2BIS_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_2BIS_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2BIS_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_2BIS_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_2BIS_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_2BIS_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2BIS_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_2BIS_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_2BIS_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_2BIS_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2BIS_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_2BIS_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_2BIS_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE ExtendedBcchFrequencyList
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 128;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_NeighbourCellDescription (Buffer, CurrOfs, (&(Destin->ExtendedBcchFrequencyList)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1183> Error decoding subfield ExtendedBcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1183, (Destin->ExtendedBcchFrequencyList))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1184> Message too short decoding subfield ExtendedBcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1183, (Destin->ExtendedBcchFrequencyList))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE RachControlParameters
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RACHCtrlParam (Buffer, CurrOfs, (&(Destin->RachControlParameters)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1185> Error decoding subfield RachControlParameters\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1185, (Destin->RachControlParameters))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1186> Message too short decoding subfield RachControlParameters\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1185, (Destin->RachControlParameters))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE Si2bisRestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_SI2bisRestOctets (Buffer, CurrOfs, (&(Destin->Si2bisRestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1187> Error decoding subfield Si2bisRestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1187, (Destin->Si2bisRestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1188> Message too short decoding subfield Si2bisRestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1187, (Destin->Si2bisRestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2TER_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_2TER_DN (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_2TER_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 3, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for ExtendedBcchFrequencyList */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ExtendedBcchFrequencyList> DOT=<.> */
		Len = ENCODE_c_NeighbourCellDescription2 (Buffer, CurrOfs, (&(Source->ExtendedBcchFrequencyList)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1189> Error encoding subfield ExtendedBcchFrequencyList\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for Si2terRestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->Si2terRestOctets> DOT=<.> */
		Len = ENCODE_c_SI2terRestOctets (Buffer, CurrOfs, (&(Source->Si2terRestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1190> Error encoding subfield Si2terRestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(18), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2TER_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_2TER_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_2TER_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_2TER_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2TER_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_2TER_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_2TER_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_2TER_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2TER_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_2TER_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_2TER_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_2TER_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2TER_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_2TER_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_2TER_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE ExtendedBcchFrequencyList
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 128;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_NeighbourCellDescription2 (Buffer, CurrOfs, (&(Destin->ExtendedBcchFrequencyList)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1191> Error decoding subfield ExtendedBcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1191, (Destin->ExtendedBcchFrequencyList))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1192> Message too short decoding subfield ExtendedBcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1191, (Destin->ExtendedBcchFrequencyList))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE Si2terRestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 32;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_SI2terRestOctets (Buffer, CurrOfs, (&(Destin->Si2terRestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1193> Error decoding subfield Si2terRestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1193, (Destin->Si2terRestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1194> Message too short decoding subfield Si2terRestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1193, (Destin->Si2terRestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2QUATER_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_2QUATER_DN (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_2QUATER_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 7, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for Si2QuaterRestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->Si2QuaterRestOctets> DOT=<.> */
		Len = ENCODE_c_SI2quaterRestOctets (Buffer, CurrOfs, (&(Source->Si2QuaterRestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1195> Error encoding subfield Si2QuaterRestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(1), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2QUATER_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_2QUATER_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_2QUATER_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_2QUATER_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2QUATER_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_2QUATER_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_2QUATER_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_2QUATER_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2QUATER_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_2QUATER_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_2QUATER_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_2QUATER_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_2QUATER_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_2QUATER_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_2QUATER_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE Si2QuaterRestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 160;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_SI2quaterRestOctets (Buffer, CurrOfs, (&(Destin->Si2QuaterRestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1196> Error decoding subfield Si2QuaterRestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1196, (Destin->Si2QuaterRestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1197> Message too short decoding subfield Si2QuaterRestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1196, (Destin->Si2QuaterRestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_3_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_3_DN (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_3_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 27, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for CellId */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->CellId> DOT=<.> */
		EDIntToBits (Buffer, (CurrOfs), (int)(Source->CellId), 16);
		Len = 16;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1198> Error encoding subfield CellId\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for LocationAreaId */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->LocationAreaId> DOT=<.> */
		Len = ENCODE_c_RRLocationAreaId (Buffer, CurrOfs, (&(Source->LocationAreaId)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1199> Error encoding subfield LocationAreaId\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for ControlChannelDescription */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ControlChannelDescription> DOT=<.> */
		Len = ENCODE_c_CtrlChannelDesc (Buffer, CurrOfs, (&(Source->ControlChannelDescription)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1200> Error encoding subfield ControlChannelDescription\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for CellOpt */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->CellOpt> DOT=<.> */
		Len = ENCODE_c_CellOptions (Buffer, CurrOfs, (&(Source->CellOpt)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1201> Error encoding subfield CellOpt\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for CellSelectionParameters */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->CellSelectionParameters> DOT=<.> */
		Len = ENCODE_c_CellSelParam (Buffer, CurrOfs, (&(Source->CellSelectionParameters)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1202> Error encoding subfield CellSelectionParameters\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for RachControlParameters */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->RachControlParameters> DOT=<.> */
		Len = ENCODE_c_RACHCtrlParam (Buffer, CurrOfs, (&(Source->RachControlParameters)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1203> Error encoding subfield RachControlParameters\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for Si3RestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->Si3RestOctets> DOT=<.> */
		Len = ENCODE_c_SI3RestOctet (Buffer, CurrOfs, (&(Source->Si3RestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1204> Error encoding subfield Si3RestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(18), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_3_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_3_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_3_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_3_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_3_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_3_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_3_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_3_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_3_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_3_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_3_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_3_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_3_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_3_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_3_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE CellId
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 16;
	/* Read value part LOCATOR_16 */
	Destin->CellId = (ED_SHORT)EDBitsToInt (Buffer, (CurrOfs), 16);
	/* LOCATOR SETTINGS LOCINT */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-52290=EDCore::TDMInteger) */Destin->CellId___LOCATOR), CurrOfs, 16);
	RetLen = 16;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1205> Error decoding subfield CellId\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1205, (Destin->CellId))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1206> Message too short decoding subfield CellId\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1205, (Destin->CellId))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE LocationAreaId
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 40;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RRLocationAreaId (Buffer, CurrOfs, (&(Destin->LocationAreaId)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1207> Error decoding subfield LocationAreaId\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1207, (Destin->LocationAreaId))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1208> Message too short decoding subfield LocationAreaId\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1207, (Destin->LocationAreaId))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ControlChannelDescription
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_CtrlChannelDesc (Buffer, CurrOfs, (&(Destin->ControlChannelDescription)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1209> Error decoding subfield ControlChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1209, (Destin->ControlChannelDescription))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1210> Message too short decoding subfield ControlChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1209, (Destin->ControlChannelDescription))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE CellOpt
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_CellOptions (Buffer, CurrOfs, (&(Destin->CellOpt)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1211> Error decoding subfield CellOpt\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1211, (Destin->CellOpt))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1212> Message too short decoding subfield CellOpt\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1211, (Destin->CellOpt))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE CellSelectionParameters
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 16;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_CellSelParam (Buffer, CurrOfs, (&(Destin->CellSelectionParameters)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1213> Error decoding subfield CellSelectionParameters\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1213, (Destin->CellSelectionParameters))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1214> Message too short decoding subfield CellSelectionParameters\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1213, (Destin->CellSelectionParameters))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE RachControlParameters
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RACHCtrlParam (Buffer, CurrOfs, (&(Destin->RachControlParameters)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1215> Error decoding subfield RachControlParameters\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1215, (Destin->RachControlParameters))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1216> Message too short decoding subfield RachControlParameters\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1215, (Destin->RachControlParameters))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE Si3RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 32;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_SI3RestOctet (Buffer, CurrOfs, (&(Destin->Si3RestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1217> Error decoding subfield Si3RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1217, (Destin->Si3RestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1218> Message too short decoding subfield Si3RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1217, (Destin->Si3RestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_4_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_4_DN (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_4_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 28, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for LocationAreaId */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->LocationAreaId> DOT=<.> */
		Len = ENCODE_c_RRLocationAreaId (Buffer, CurrOfs, (&(Source->LocationAreaId)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1219> Error encoding subfield LocationAreaId\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for CellSelectionParameters */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->CellSelectionParameters> DOT=<.> */
		Len = ENCODE_c_CellSelParam (Buffer, CurrOfs, (&(Source->CellSelectionParameters)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1220> Error encoding subfield CellSelectionParameters\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for RachControlParameters */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->RachControlParameters> DOT=<.> */
		Len = ENCODE_c_RACHCtrlParam (Buffer, CurrOfs, (&(Source->RachControlParameters)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1221> Error encoding subfield RachControlParameters\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for CbchChannelDescription */
	{
		if (Source->CbchChannelDescription_Present) {
			/* Append to buffer IEI tag 0x64 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x64), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->CbchChannelDescription> DOT=<->> */
			Len = ENCODE_c_TChDesc (Buffer, CurrOfs, Source->CbchChannelDescription);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:1222> Error encoding subfield CbchChannelDescription\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for CbchMobileAllocation */
	{
		int TLV_Base = CurrOfs;
		if (Source->CbchMobileAllocation_Present) {
			/* Append to buffer IEI tag 0x72 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x72), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->CbchMobileAllocation> DOT=<->> */
			Len = ENCODE_c_MobileAllocation (Buffer, CurrOfs+8, Source->CbchMobileAllocation);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:1223> Error encoding subfield CbchMobileAllocation\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for EndOfL2Length */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->EndOfL2Length> DOT=<.> */
		Len = 0;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1224> Error encoding subfield EndOfL2Length\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
		/* Encode L2 Pseudo Length */
		if (Mode == 0) {
			EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)((CurrOfs-BitOffset-8)>>3), 6);
			EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
		}
	}
	
	/* Code for Si4RestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->Si4RestOctets> DOT=<.> */
		Len = ENCODE_c_SI4_Rest_Octets (Buffer, CurrOfs, (&(Source->Si4RestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1225> Error encoding subfield Si4RestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_4_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_4_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_4_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_4_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_4_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_4_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_4_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_4_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_4_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_4_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_4_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_4_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_4_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_4_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_4_DN* ED_CONST Destin, ED_EXLONG Length))
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
		{100, 255, ED_SKIPLIST_OPTIONAL},
		{114, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_MANDATORY}, /* Untagged item, matches all! */
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	ED_WARNING_REMOVER (TLVSkipItems);
	
	/*----------------------------------------------------- 
		Code for IE LocationAreaId
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 40;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RRLocationAreaId (Buffer, CurrOfs, (&(Destin->LocationAreaId)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1226> Error decoding subfield LocationAreaId\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1226, (Destin->LocationAreaId))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1227> Message too short decoding subfield LocationAreaId\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1226, (Destin->LocationAreaId))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE CellSelectionParameters
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 16;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_CellSelParam (Buffer, CurrOfs, (&(Destin->CellSelectionParameters)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1228> Error decoding subfield CellSelectionParameters\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1228, (Destin->CellSelectionParameters))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1229> Message too short decoding subfield CellSelectionParameters\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1228, (Destin->CellSelectionParameters))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE RachControlParameters
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RACHCtrlParam (Buffer, CurrOfs, (&(Destin->RachControlParameters)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1230> Error decoding subfield RachControlParameters\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1230, (Destin->RachControlParameters))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1231> Message too short decoding subfield RachControlParameters\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1230, (Destin->RachControlParameters))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE CbchChannelDescription
	------------------------------------------------------*/
	/* Detect IEI tag 0x64 */
	ED_EXPECT_OPTIONAL_IE (0x64,  8, 1232, 3, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x64) {
		SETPRESENT_c_SYSTEM_INFORMATION_TYPE_4_DN_CbchChannelDescription (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 24;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, Destin->CbchChannelDescription, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:1233> Error decoding subfield CbchChannelDescription\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_SYSTEM_INFORMATION_TYPE_4_DN_CbchChannelDescription (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x64, 1233, (Destin->CbchChannelDescription))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:1234> Message too short decoding subfield CbchChannelDescription\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_SYSTEM_INFORMATION_TYPE_4_DN_CbchChannelDescription (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x64, 1233, (Destin->CbchChannelDescription))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE CbchMobileAllocation
	------------------------------------------------------*/
	/* Detect IEI tag 0x72 */
	ED_EXPECT_OPTIONAL_IE (0x72,  8, 1235, 4, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x72) {
		SETPRESENT_c_SYSTEM_INFORMATION_TYPE_4_DN_CbchMobileAllocation (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 32)) {
			ED_SIGNAL_ERROR ("<ERRID:1236> Size error decoding IE CbchMobileAllocation\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_SYSTEM_INFORMATION_TYPE_4_DN_CbchMobileAllocation (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x72, 1236, (Destin->CbchMobileAllocation))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_MobileAllocation (Buffer, CurrOfs, Destin->CbchMobileAllocation, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:1237> Error decoding subfield CbchMobileAllocation\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_SYSTEM_INFORMATION_TYPE_4_DN_CbchMobileAllocation (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x72, 1237, (Destin->CbchMobileAllocation))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:1238> Message too short decoding subfield CbchMobileAllocation\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_SYSTEM_INFORMATION_TYPE_4_DN_CbchMobileAllocation (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x72, 1237, (Destin->CbchMobileAllocation))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE EndOfL2Length
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 0;
	/* Read value part LOCATOR_16 */
	RetLen = 0;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1239> Error decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1239, (Destin->EndOfL2Length))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1240> Message too short decoding subfield EndOfL2Length\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1239, (Destin->EndOfL2Length))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE Si4RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_SI4_Rest_Octets (Buffer, CurrOfs, (&(Destin->Si4RestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1241> Error decoding subfield Si4RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1241, (Destin->Si4RestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1242> Message too short decoding subfield Si4RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1241, (Destin->Si4RestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_5_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_5_DN (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_5_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 29, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for BcchFrequencyList */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->BcchFrequencyList> DOT=<.> */
		Len = ENCODE_c_NeighbourCellDescription (Buffer, CurrOfs, (&(Source->BcchFrequencyList)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1243> Error encoding subfield BcchFrequencyList\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(18), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_5_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_5_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_5_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_5_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_5_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_5_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_5_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_5_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_5_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_5_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_5_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_5_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_5_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_5_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_5_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE BcchFrequencyList
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 128;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_NeighbourCellDescription (Buffer, CurrOfs, (&(Destin->BcchFrequencyList)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1244> Error decoding subfield BcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1244, (Destin->BcchFrequencyList))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1245> Message too short decoding subfield BcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1244, (Destin->BcchFrequencyList))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_5BIS_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_5BIS_DN (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_5BIS_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 5, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for ExtOfTheBcchFrequencyListDescription */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ExtOfTheBcchFrequencyListDescription> DOT=<.> */
		Len = ENCODE_c_NeighbourCellDescription (Buffer, CurrOfs, (&(Source->ExtOfTheBcchFrequencyListDescription)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1246> Error encoding subfield ExtOfTheBcchFrequencyListDescription\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(18), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_5BIS_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_5BIS_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_5BIS_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_5BIS_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_5BIS_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_5BIS_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_5BIS_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_5BIS_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_5BIS_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_5BIS_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_5BIS_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_5BIS_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_5BIS_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_5BIS_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_5BIS_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE ExtOfTheBcchFrequencyListDescription
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 128;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_NeighbourCellDescription (Buffer, CurrOfs, (&(Destin->ExtOfTheBcchFrequencyListDescription)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1247> Error decoding subfield ExtOfTheBcchFrequencyListDescription\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1247, (Destin->ExtOfTheBcchFrequencyListDescription))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1248> Message too short decoding subfield ExtOfTheBcchFrequencyListDescription\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1247, (Destin->ExtOfTheBcchFrequencyListDescription))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_5TER_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_5TER_DN (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_5TER_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for ExtendedBcchFrequencyList */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ExtendedBcchFrequencyList> DOT=<.> */
		Len = ENCODE_c_NeighbourCellDescription2 (Buffer, CurrOfs, (&(Source->ExtendedBcchFrequencyList)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1249> Error encoding subfield ExtendedBcchFrequencyList\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(18), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_5TER_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_5TER_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_5TER_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_5TER_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_5TER_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_5TER_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_5TER_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_5TER_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_5TER_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_5TER_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_5TER_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_5TER_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_5TER_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_5TER_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_5TER_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE ExtendedBcchFrequencyList
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 128;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_NeighbourCellDescription2 (Buffer, CurrOfs, (&(Destin->ExtendedBcchFrequencyList)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1250> Error decoding subfield ExtendedBcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1250, (Destin->ExtendedBcchFrequencyList))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1251> Message too short decoding subfield ExtendedBcchFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1250, (Destin->ExtendedBcchFrequencyList))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_6_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_6_DN (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_6_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 30, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for CellId */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->CellId> DOT=<.> */
		EDIntToBits (Buffer, (CurrOfs), (int)(Source->CellId), 16);
		Len = 16;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1252> Error encoding subfield CellId\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for LocationAreaId */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->LocationAreaId> DOT=<.> */
		Len = ENCODE_c_RRLocationAreaId (Buffer, CurrOfs, (&(Source->LocationAreaId)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1253> Error encoding subfield LocationAreaId\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for CellOpt */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->CellOpt> DOT=<.> */
		Len = ENCODE_c_CellOptions (Buffer, CurrOfs, (&(Source->CellOpt)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1254> Error encoding subfield CellOpt\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for NccPermitted */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->NccPermitted> DOT=<.> */
		EDIntToBits (Buffer, (CurrOfs), (int)(Source->NccPermitted), 8);
		Len = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1255> Error encoding subfield NccPermitted\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for Si6RestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->Si6RestOctets> DOT=<.> */
		Len = ENCODE_c_SI6RestOctet (Buffer, CurrOfs, (&(Source->Si6RestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1256> Error encoding subfield Si6RestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(11), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_6_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_6_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_6_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_6_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_6_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_6_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_6_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_6_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_6_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_6_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_6_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_6_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_6_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_6_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_6_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE CellId
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 16;
	/* Read value part LOCATOR_16 */
	Destin->CellId = (ED_SHORT)EDBitsToInt (Buffer, (CurrOfs), 16);
	/* LOCATOR SETTINGS LOCINT */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-52329=EDCore::TDMInteger) */Destin->CellId___LOCATOR), CurrOfs, 16);
	RetLen = 16;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1257> Error decoding subfield CellId\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1257, (Destin->CellId))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1258> Message too short decoding subfield CellId\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1257, (Destin->CellId))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE LocationAreaId
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 40;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RRLocationAreaId (Buffer, CurrOfs, (&(Destin->LocationAreaId)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1259> Error decoding subfield LocationAreaId\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1259, (Destin->LocationAreaId))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1260> Message too short decoding subfield LocationAreaId\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1259, (Destin->LocationAreaId))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE CellOpt
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_CellOptions (Buffer, CurrOfs, (&(Destin->CellOpt)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1261> Error decoding subfield CellOpt\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1261, (Destin->CellOpt))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1262> Message too short decoding subfield CellOpt\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1261, (Destin->CellOpt))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE NccPermitted
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	Destin->NccPermitted = (ED_OCTET)EDBitsToInt (Buffer, (CurrOfs), 8);
	/* LOCATOR SETTINGS LOCINT */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-52335=EDCore::TDMInteger) */Destin->NccPermitted___LOCATOR), CurrOfs, 8);
	RetLen = 8;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1263> Error decoding subfield NccPermitted\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1263, (Destin->NccPermitted))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1264> Message too short decoding subfield NccPermitted\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1263, (Destin->NccPermitted))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE Si6RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_SI6RestOctet (Buffer, CurrOfs, (&(Destin->Si6RestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1265> Error decoding subfield Si6RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1265, (Destin->Si6RestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1266> Message too short decoding subfield Si6RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1265, (Destin->Si6RestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_7_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_7_DN (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_7_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 31, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for Si7RestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->Si7RestOctets> DOT=<.> */
		Len = ENCODE_c_SI7_Rest_Octets (Buffer, CurrOfs, (&(Source->Si7RestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1267> Error encoding subfield Si7RestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(1), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_7_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_7_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_7_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_7_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_7_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_7_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_7_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_7_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_7_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_7_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_7_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_7_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_7_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_7_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_7_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE Si7RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 160;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_SI7_Rest_Octets (Buffer, CurrOfs, (&(Destin->Si7RestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1268> Error decoding subfield Si7RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1268, (Destin->Si7RestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1269> Message too short decoding subfield Si7RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1268, (Destin->Si7RestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_8_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_8_DN (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_8_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 24, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for Si8RestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->Si8RestOctets> DOT=<.> */
		Len = ENCODE_c_SI8_Rest_Octets (Buffer, CurrOfs, (&(Source->Si8RestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1270> Error encoding subfield Si8RestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(1), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_8_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_8_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_8_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_8_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_8_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_8_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_8_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_8_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_8_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_8_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_8_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_8_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_8_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_8_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_8_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE Si8RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 160;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_SI8_Rest_Octets (Buffer, CurrOfs, (&(Destin->Si8RestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1271> Error decoding subfield Si8RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1271, (Destin->Si8RestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1272> Message too short decoding subfield Si8RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1271, (Destin->Si8RestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_9_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_9_DN (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_9_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 4, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for RachControlParam */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->RachControlParam> DOT=<.> */
		Len = ENCODE_c_RACHCtrlParam (Buffer, CurrOfs, (&(Source->RachControlParam)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1273> Error encoding subfield RachControlParam\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for Si9RestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->Si9RestOctets> DOT=<.> */
		EDCopyBits (Buffer, CurrOfs, (Source->Si9RestOctets), 0, 136);
		Len = 136;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1274> Error encoding subfield Si9RestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(1), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_9_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_9_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_9_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_9_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_9_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_9_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_9_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_9_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_9_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_9_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_9_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_9_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_9_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_9_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_9_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE RachControlParam
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RACHCtrlParam (Buffer, CurrOfs, (&(Destin->RachControlParam)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1275> Error decoding subfield RachControlParam\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1275, (Destin->RachControlParam))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1276> Message too short decoding subfield RachControlParam\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1275, (Destin->RachControlParam))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE Si9RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 136;
	/* Read value part LOCATOR_16 */
	EDCopyBits (Destin->Si9RestOctets, 0, Buffer, CurrOfs, 136);
	/* LOCATOR SETTINGS LOCBIN1 */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-52348=EDCore::TDMBinary) */Destin->Si9RestOctets___LOCATOR), CurrOfs, 136);
	RetLen = 136;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1277> Error decoding subfield Si9RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1277, (Destin->Si9RestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1278> Message too short decoding subfield Si9RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1277, (Destin->Si9RestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_13_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_13_DN (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_13_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 0, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for Si13RestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->Si13RestOctets> DOT=<.> */
		Len = ENCODE_c_SI13RestOctets (Buffer, CurrOfs, (&(Source->Si13RestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1279> Error encoding subfield Si13RestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(0), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_13_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_13_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_13_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_13_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_13_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_13_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_13_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_13_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_13_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_13_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_13_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_13_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_13_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_13_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_13_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE Si13RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_SI13RestOctets (Buffer, CurrOfs, (&(Destin->Si13RestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1280> Error decoding subfield Si13RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1280, (Destin->Si13RestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1281> Message too short decoding subfield Si13RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1280, (Destin->Si13RestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_16_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_16_DN (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_16_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 61, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for Si16RestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->Si16RestOctets> DOT=<.> */
		Len = ENCODE_c_SI16RestOctet (Buffer, CurrOfs, (&(Source->Si16RestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1282> Error encoding subfield Si16RestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(1), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_16_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_16_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_16_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_16_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_16_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_16_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_16_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_16_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_16_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_16_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_16_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_16_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_16_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_16_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_16_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE Si16RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_SI16RestOctet (Buffer, CurrOfs, (&(Destin->Si16RestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1283> Error decoding subfield Si16RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1283, (Destin->Si16RestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1284> Message too short decoding subfield Si16RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1283, (Destin->Si16RestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_17_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_17_DN (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_17_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 62, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for Si17RestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->Si17RestOctets> DOT=<.> */
		Len = ENCODE_c_SI16RestOctet (Buffer, CurrOfs, (&(Source->Si17RestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1285> Error encoding subfield Si17RestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(1), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_17_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_17_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_17_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_17_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_17_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_17_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_17_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_17_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_17_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_17_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_17_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_17_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_17_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_17_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_17_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE Si17RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_SI16RestOctet (Buffer, CurrOfs, (&(Destin->Si17RestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1286> Error decoding subfield Si17RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1286, (Destin->Si17RestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1287> Message too short decoding subfield Si17RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1286, (Destin->Si17RestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_19_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_19_DN (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_19_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 65, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for Si19RestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->Si19RestOctets> DOT=<.> */
		EDCopyBits (Buffer, CurrOfs, Source->Si19RestOctets.value, 0, Source->Si19RestOctets.usedBits);
		Len = Source->Si19RestOctets.usedBits;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1288> Error encoding subfield Si19RestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(1), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_19_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_19_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_19_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_19_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_19_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_19_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_19_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_19_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_19_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_19_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_19_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_19_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_19_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_19_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_19_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE Si19RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	/* LOCATOR SETTINGS LOCBIN2 */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-52360=EDCore::TDMBinary) */Destin->Si19RestOctets___LOCATOR), CurrOfs, Len);
	if (Len > 0) {
		/* BINDEC02 */
		ALLOC_c_SYSTEM_INFORMATION_TYPE_19_DN_Si19RestOctets (&(Destin->Si19RestOctets), Len);
	
		EDCopyBits (Destin->Si19RestOctets.value, 0, Buffer, CurrOfs, Len);
		Destin->Si19RestOctets.usedBits = Len;
	}
	
	RetLen = Len;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1289> Error decoding subfield Si19RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1289, (Destin->Si19RestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1290> Message too short decoding subfield Si19RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1289, (Destin->Si19RestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_18_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_18_DN (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_18_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 64, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for Si18RestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->Si18RestOctets> DOT=<.> */
		Len = ENCODE_c_SI18RestOctet (Buffer, CurrOfs, (&(Source->Si18RestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1291> Error encoding subfield Si18RestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(1), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_18_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_18_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_18_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_18_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_18_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_18_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_18_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_18_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_18_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_18_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_18_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_18_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_18_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_18_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_18_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE Si18RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_SI18RestOctet (Buffer, CurrOfs, (&(Destin->Si18RestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1292> Error decoding subfield Si18RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1292, (Destin->Si18RestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1293> Message too short decoding subfield Si18RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1292, (Destin->Si18RestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_20_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_20_DN (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_20_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 66, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for Si20RestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->Si20RestOctets> DOT=<.> */
		Len = ENCODE_c_SI18RestOctet (Buffer, CurrOfs, (&(Source->Si20RestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1294> Error encoding subfield Si20RestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(1), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_20_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_20_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_20_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_20_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_20_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_20_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_20_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_20_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_20_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_20_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_20_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_20_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_20_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_20_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_20_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE Si20RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_SI18RestOctet (Buffer, CurrOfs, (&(Destin->Si20RestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1295> Error decoding subfield Si20RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1295, (Destin->Si20RestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1296> Message too short decoding subfield Si20RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1295, (Destin->Si20RestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_14_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_14_DN (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_14_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 1, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for Si14RestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->Si14RestOctets> DOT=<.> */
		Len = ENCODE_c_SI14RestOctets (Buffer, CurrOfs, (&(Source->Si14RestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1297> Error encoding subfield Si14RestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(18), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_14_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_14_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_14_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_14_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_14_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_14_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_14_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_14_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_14_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_14_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_14_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_14_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_14_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_14_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_14_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE Si14RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 128;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_SI14RestOctets (Buffer, CurrOfs, (&(Destin->Si14RestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1298> Error decoding subfield Si14RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1298, (Destin->Si14RestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1299> Message too short decoding subfield Si14RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1298, (Destin->Si14RestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_15_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_15_DN (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_15_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 67, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for Si15RestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->Si15RestOctets> DOT=<.> */
		Len = ENCODE_c_SI15RestOctets (Buffer, CurrOfs, (&(Source->Si15RestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1300> Error encoding subfield Si15RestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(1), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_15_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_15_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_15_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_15_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_15_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_15_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_15_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_15_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_15_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_15_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_15_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_15_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_15_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_15_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_15_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE Si15RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 160;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_SI15RestOctets (Buffer, CurrOfs, (&(Destin->Si15RestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1301> Error decoding subfield Si15RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1301, (Destin->Si15RestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1302> Message too short decoding subfield Si15RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1301, (Destin->Si15RestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_13alt_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_13alt_DN (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_13alt_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 68, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for Si13altRestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->Si13altRestOctets> DOT=<.> */
		Len = ENCODE_c_SI13altRestOctets (Buffer, CurrOfs, (&(Source->Si13altRestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1303> Error encoding subfield Si13altRestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(0), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_13alt_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_13alt_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_13alt_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_13alt_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_13alt_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_13alt_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_13alt_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_13alt_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_13alt_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_13alt_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_13alt_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_13alt_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_13alt_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_13alt_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_13alt_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE Si13altRestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 160;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_SI13altRestOctets (Buffer, CurrOfs, (&(Destin->Si13altRestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1304> Error decoding subfield Si13altRestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1304, (Destin->Si13altRestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1305> Message too short decoding subfield Si13altRestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1304, (Destin->Si13altRestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_21_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_21_DN (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_21_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 70, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for Si21RestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->Si21RestOctets> DOT=<.> */
		Len = ENCODE_c_SI21RestOctets (Buffer, CurrOfs, (&(Source->Si21RestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1306> Error encoding subfield Si21RestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(0), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_21_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_21_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_21_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_21_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_21_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_21_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_21_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_21_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_21_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_21_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_21_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_21_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_21_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_21_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_21_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE Si21RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_SI21RestOctets (Buffer, CurrOfs, (&(Destin->Si21RestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1307> Error decoding subfield Si21RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1307, (Destin->Si21RestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1308> Message too short decoding subfield Si21RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1307, (Destin->Si21RestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_22_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_22_DN (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_22_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 71, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for Si22RestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->Si22RestOctets> DOT=<.> */
		Len = ENCODE_c_SI22RestOctets (Buffer, CurrOfs, (&(Source->Si22RestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1309> Error encoding subfield Si22RestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(2), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_22_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_22_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_22_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_22_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_22_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_22_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_22_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_22_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_22_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_22_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_22_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_22_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_22_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_22_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_22_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE Si22RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 160;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_SI22RestOctets (Buffer, CurrOfs, (&(Destin->Si22RestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1310> Error decoding subfield Si22RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1310, (Destin->Si22RestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1311> Message too short decoding subfield Si22RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1310, (Destin->Si22RestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_23_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_23_DN (char* Buffer, ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_23_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 79, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for Si23RestOctets */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->Si23RestOctets> DOT=<.> */
		Len = ENCODE_c_SI23RestOctets (Buffer, CurrOfs, (&(Source->Si23RestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1312> Error encoding subfield Si23RestOctets\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(2), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_23_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_23_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_23_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_23_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_23_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_SYSTEM_INFORMATION_TYPE_23_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_23_DN* ED_CONST Source))
{
	return L3_ENCODE_c_SYSTEM_INFORMATION_TYPE_23_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_23_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_23_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_23_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_23_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE SYSTEM_INFORMATION_TYPE_23_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_SYSTEM_INFORMATION_TYPE_23_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_23_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE Si23RestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 160;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_SI23RestOctets (Buffer, CurrOfs, (&(Destin->Si23RestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1313> Error decoding subfield Si23RestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1313, (Destin->Si23RestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1314> Message too short decoding subfield Si23RestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1313, (Destin->Si23RestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE EXTENDED_MEASUREMENT_ORDER_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_EXTENDED_MEASUREMENT_ORDER_DN (char* Buffer, ED_EXLONG BitOffset, const c_EXTENDED_MEASUREMENT_ORDER_DN* Source, int Mode)
{
	int Len=0;
	ED_EXLONG CurrOfs = BitOffset+Len;
	ED_EXTRAPARAMS_CODE
						
	ED_WARNING_REMOVER (Buffer);
	ED_WARNING_REMOVER (BitOffset);
	ED_WARNING_REMOVER (Source);
	ED_WARNING_REMOVER (Mode);
	
	if (Mode == 0) {
		CurrOfs += 8; /* L2 Pseudo Length offset */
		/* Encode protocol discriminator */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 6, 8);
		CurrOfs += 8;

		/* Encode message type */
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 55, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for ExtendedMeasurementFrequencyList */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ExtendedMeasurementFrequencyList> DOT=<.> */
		Len = ENCODE_c_CellChannel (Buffer, CurrOfs, (&(Source->ExtendedMeasurementFrequencyList)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1315> Error encoding subfield ExtendedMeasurementFrequencyList\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	if (Mode == 0) {
		/* Encode the L2 Pseudo Length - User defined value  */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset, (int)(18), 6);
		/* Encode the L2 Pseudo Length - bits 1 and 2 are set to "01" */
		EDIntToBits (Buffer, (ED_EXLONG)BitOffset+6, 1, 2);
	}
	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE EXTENDED_MEASUREMENT_ORDER_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EXTENDED_MEASUREMENT_ORDER_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EXTENDED_MEASUREMENT_ORDER_DN* ED_CONST Source))
{
	return L3_ENCODE_c_EXTENDED_MEASUREMENT_ORDER_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE EXTENDED_MEASUREMENT_ORDER_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_EXTENDED_MEASUREMENT_ORDER_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EXTENDED_MEASUREMENT_ORDER_DN* ED_CONST Source))
{
	return L3_ENCODE_c_EXTENDED_MEASUREMENT_ORDER_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE EXTENDED_MEASUREMENT_ORDER_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EXTENDED_MEASUREMENT_ORDER_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EXTENDED_MEASUREMENT_ORDER_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_EXTENDED_MEASUREMENT_ORDER_DN (Buffer, (BitOffset+16 + 8 /* L2 Pseudo Length offset */), Destin, Length-(16 + 8 /* L2 Pseudo Length offset */));
	if (Len < 0) return Len;
	
	return Len+16 + 8 /* L2 Pseudo Length offset */;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE EXTENDED_MEASUREMENT_ORDER_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_EXTENDED_MEASUREMENT_ORDER_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EXTENDED_MEASUREMENT_ORDER_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE ExtendedMeasurementFrequencyList
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 128;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, (&(Destin->ExtendedMeasurementFrequencyList)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:1316> Error decoding subfield ExtendedMeasurementFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 1316, (Destin->ExtendedMeasurementFrequencyList))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:1317> Message too short decoding subfield ExtendedMeasurementFrequencyList\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 1316, (Destin->ExtendedMeasurementFrequencyList))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
int Match_c_IMMEDIATE_ASSIGNMENT_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 63) /* message type */
	);
}

int Match_c_IMMEDIATE_PACKET_ASSIGNMENT_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 105) /* message type */
	);
}

int Match_c_IMMEDIATE_ASSIGNMENT_EXTENDED_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 57) /* message type */
	);
}

int Match_c_IMMEDIATE_ASSIGNMENT_REJECT_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 58) /* message type */
	);
}

int Match_c_NOTIFICATION_NCH_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 32) /* message type */
	);
}

int Match_c_PAGING_REQUEST_TYPE_1_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 33) /* message type */
	);
}

int Match_c_PAGING_REQUEST_TYPE_2_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 34) /* message type */
	);
}

int Match_c_PAGING_REQUEST_TYPE_3_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 36) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_1_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 25) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_2_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 26) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_2BIS_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 2) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_2TER_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 3) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_2QUATER_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 7) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_3_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 27) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_4_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 28) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_5_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 29) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_5BIS_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 5) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_5TER_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 6) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_6_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 30) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_7_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 31) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_8_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 24) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_9_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 4) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_13_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 0) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_16_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 61) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_17_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 62) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_19_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 65) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_18_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 64) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_20_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 66) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_14_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 1) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_15_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 67) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_13alt_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 68) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_21_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 70) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_22_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 71) /* message type */
	);
}

int Match_c_SYSTEM_INFORMATION_TYPE_23_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 79) /* message type */
	);
}

int Match_c_EXTENDED_MEASUREMENT_ORDER_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 55) /* message type */
	);
}


/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.152
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#include "RRDownlink_RR.h"
#include "ed_c_known_ie_RR.h"
#include "ed_tlv.h"
#include "UserDefinedDataTypes_RR.h"
#include "CSN1DataTypes_RR.h"
#if ED_VERSION != 10152
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.152
#endif


#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE ADDITIONAL_ASSIGNMENT_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_ADDITIONAL_ASSIGNMENT_DN (char* Buffer, ED_EXLONG BitOffset, const c_ADDITIONAL_ASSIGNMENT_DN* Source, int Mode)
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
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 59, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for ChannelDescription */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ChannelDescription> DOT=<.> */
		Len = ENCODE_c_TChDesc (Buffer, CurrOfs, (&(Source->ChannelDescription)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:1> Error encoding subfield ChannelDescription\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for MobileAllocation */
	{
		int TLV_Base = CurrOfs;
		if (Source->MobileAllocation_Present) {
			/* Append to buffer IEI tag 0x72 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x72), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->MobileAllocation> DOT=<->> */
			Len = ENCODE_c_MobileAllocation (Buffer, CurrOfs+8, Source->MobileAllocation);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:2> Error encoding subfield MobileAllocation\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
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
				ED_SIGNAL_ERROR ("<ERRID:3> Error encoding subfield StartingTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
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
				ED_SIGNAL_ERROR ("<ERRID:4> Error encoding subfield ExtendedTSCSet\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE ADDITIONAL_ASSIGNMENT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_ADDITIONAL_ASSIGNMENT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ADDITIONAL_ASSIGNMENT_DN* ED_CONST Source))
{
	return L3_ENCODE_c_ADDITIONAL_ASSIGNMENT_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE ADDITIONAL_ASSIGNMENT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_ADDITIONAL_ASSIGNMENT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ADDITIONAL_ASSIGNMENT_DN* ED_CONST Source))
{
	return L3_ENCODE_c_ADDITIONAL_ASSIGNMENT_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE ADDITIONAL_ASSIGNMENT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_ADDITIONAL_ASSIGNMENT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ADDITIONAL_ASSIGNMENT_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_ADDITIONAL_ASSIGNMENT_DN (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE ADDITIONAL_ASSIGNMENT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_ADDITIONAL_ASSIGNMENT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ADDITIONAL_ASSIGNMENT_DN* ED_CONST Destin, ED_EXLONG Length))
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
		{114, 255, ED_SKIPLIST_OPTIONAL},
		{124, 255, ED_SKIPLIST_OPTIONAL},
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
	RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, (&(Destin->ChannelDescription)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:5> Error decoding subfield ChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 5, (Destin->ChannelDescription))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:6> Message too short decoding subfield ChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 5, (Destin->ChannelDescription))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE MobileAllocation
	------------------------------------------------------*/
	/* Detect IEI tag 0x72 */
	ED_EXPECT_OPTIONAL_IE (0x72,  8, 7, 1, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x72) {
		SETPRESENT_c_ADDITIONAL_ASSIGNMENT_DN_MobileAllocation (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 64)) {
			ED_SIGNAL_ERROR ("<ERRID:8> Size error decoding IE MobileAllocation\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_ADDITIONAL_ASSIGNMENT_DN_MobileAllocation (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x72, 8, (Destin->MobileAllocation))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_MobileAllocation (Buffer, CurrOfs, Destin->MobileAllocation, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:9> Error decoding subfield MobileAllocation\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ADDITIONAL_ASSIGNMENT_DN_MobileAllocation (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x72, 9, (Destin->MobileAllocation))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:10> Message too short decoding subfield MobileAllocation\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ADDITIONAL_ASSIGNMENT_DN_MobileAllocation (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x72, 9, (Destin->MobileAllocation))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE StartingTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x7C */
	ED_EXPECT_OPTIONAL_IE (0x7C,  8, 11, 2, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x7C) {
		SETPRESENT_c_ADDITIONAL_ASSIGNMENT_DN_StartingTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 16;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_StartingTime (Buffer, CurrOfs, Destin->StartingTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:12> Error decoding subfield StartingTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ADDITIONAL_ASSIGNMENT_DN_StartingTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x7C, 12, (Destin->StartingTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:13> Message too short decoding subfield StartingTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ADDITIONAL_ASSIGNMENT_DN_StartingTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x7C, 12, (Destin->StartingTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ExtendedTSCSet
	------------------------------------------------------*/
	/* Detect IEI tag 0x6D */
	ED_EXPECT_OPTIONAL_IE (0x6D,  8, 14, 3, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x6D) {
		SETPRESENT_c_ADDITIONAL_ASSIGNMENT_DN_ExtendedTSCSet (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ExtendedTSCSet (Buffer, CurrOfs, Destin->ExtendedTSCSet, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:15> Error decoding subfield ExtendedTSCSet\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ADDITIONAL_ASSIGNMENT_DN_ExtendedTSCSet (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x6D, 15, (Destin->ExtendedTSCSet))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:16> Message too short decoding subfield ExtendedTSCSet\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ADDITIONAL_ASSIGNMENT_DN_ExtendedTSCSet (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x6D, 15, (Destin->ExtendedTSCSet))
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE ASSIGNMENT_COMMAND_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_ASSIGNMENT_COMMAND_DN (char* Buffer, ED_EXLONG BitOffset, const c_ASSIGNMENT_COMMAND_DN* Source, int Mode)
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
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 46, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for DescOfTheFirstChannelAfterTime */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->DescOfTheFirstChannelAfterTime> DOT=<.> */
		Len = ENCODE_c_TChDesc2 (Buffer, CurrOfs, (&(Source->DescOfTheFirstChannelAfterTime)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:17> Error encoding subfield DescOfTheFirstChannelAfterTime\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for PowerCommand */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->PowerCommand> DOT=<.> */
		Len = ENCODE_c_PowerCommand (Buffer, CurrOfs, (&(Source->PowerCommand)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:18> Error encoding subfield PowerCommand\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for FrequencyListAfterTime */
	{
		int TLV_Base = CurrOfs;
		if (Source->FrequencyListAfterTime_Present) {
			/* Append to buffer IEI tag 0x05 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x05), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->FrequencyListAfterTime> DOT=<->> */
			Len = ENCODE_c_CellChannel (Buffer, CurrOfs+8, Source->FrequencyListAfterTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:19> Error encoding subfield FrequencyListAfterTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for CellChannelDescription */
	{
		if (Source->CellChannelDescription_Present) {
			/* Append to buffer IEI tag 0x62 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x62), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->CellChannelDescription> DOT=<->> */
			Len = ENCODE_c_CellChannel (Buffer, CurrOfs, Source->CellChannelDescription);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:20> Error encoding subfield CellChannelDescription\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for DescriptionOfTheMultislotCfg */
	{
		int TLV_Base = CurrOfs;
		if (Source->DescriptionOfTheMultislotCfg_Present) {
			/* Append to buffer IEI tag 0x10 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x10), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->DescriptionOfTheMultislotCfg> DOT=<->> */
			EDCopyBits (Buffer, CurrOfs+8, Source->DescriptionOfTheMultislotCfg->value, 0, Source->DescriptionOfTheMultislotCfg->usedBits);
			Len = Source->DescriptionOfTheMultislotCfg->usedBits;
			
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:21> Error encoding subfield DescriptionOfTheMultislotCfg\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for ModeOfTheFirstChannelChannelSet1 */
	{
		if (Source->ModeOfTheFirstChannelChannelSet1_Present) {
			/* Append to buffer IEI tag 0x63 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x63), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ModeOfTheFirstChannelChannelSet1> DOT=<->> */
			Len = ENCODE_c_ChannelMode (Buffer, CurrOfs, Source->ModeOfTheFirstChannelChannelSet1);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:22> Error encoding subfield ModeOfTheFirstChannelChannelSet1\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for ModeOfChannelSet2 */
	{
		if (Source->ModeOfChannelSet2_Present) {
			/* Append to buffer IEI tag 0x11 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x11), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ModeOfChannelSet2> DOT=<->> */
			Len = ENCODE_c_ChannelMode (Buffer, CurrOfs, Source->ModeOfChannelSet2);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:23> Error encoding subfield ModeOfChannelSet2\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for ModeOfChannelSet3 */
	{
		if (Source->ModeOfChannelSet3_Present) {
			/* Append to buffer IEI tag 0x13 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x13), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ModeOfChannelSet3> DOT=<->> */
			Len = ENCODE_c_ChannelMode (Buffer, CurrOfs, Source->ModeOfChannelSet3);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:24> Error encoding subfield ModeOfChannelSet3\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for ModeOfChannelSet4 */
	{
		if (Source->ModeOfChannelSet4_Present) {
			/* Append to buffer IEI tag 0x14 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x14), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ModeOfChannelSet4> DOT=<->> */
			Len = ENCODE_c_ChannelMode (Buffer, CurrOfs, Source->ModeOfChannelSet4);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:25> Error encoding subfield ModeOfChannelSet4\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for ModeOfChannelSet5 */
	{
		if (Source->ModeOfChannelSet5_Present) {
			/* Append to buffer IEI tag 0x15 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x15), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ModeOfChannelSet5> DOT=<->> */
			Len = ENCODE_c_ChannelMode (Buffer, CurrOfs, Source->ModeOfChannelSet5);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:26> Error encoding subfield ModeOfChannelSet5\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for ModeOfChannelSet6 */
	{
		if (Source->ModeOfChannelSet6_Present) {
			/* Append to buffer IEI tag 0x16 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x16), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ModeOfChannelSet6> DOT=<->> */
			Len = ENCODE_c_ChannelMode (Buffer, CurrOfs, Source->ModeOfChannelSet6);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:27> Error encoding subfield ModeOfChannelSet6\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for ModeOfChannelSet7 */
	{
		if (Source->ModeOfChannelSet7_Present) {
			/* Append to buffer IEI tag 0x17 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x17), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ModeOfChannelSet7> DOT=<->> */
			Len = ENCODE_c_ChannelMode (Buffer, CurrOfs, Source->ModeOfChannelSet7);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:28> Error encoding subfield ModeOfChannelSet7\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for ModeOfChannelSet8 */
	{
		if (Source->ModeOfChannelSet8_Present) {
			/* Append to buffer IEI tag 0x18 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x18), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ModeOfChannelSet8> DOT=<->> */
			Len = ENCODE_c_ChannelMode (Buffer, CurrOfs, Source->ModeOfChannelSet8);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:29> Error encoding subfield ModeOfChannelSet8\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for DescOfTheSecondChannelAfterTime */
	{
		if (Source->DescOfTheSecondChannelAfterTime_Present) {
			/* Append to buffer IEI tag 0x64 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x64), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->DescOfTheSecondChannelAfterTime> DOT=<->> */
			Len = ENCODE_c_TChDesc (Buffer, CurrOfs, Source->DescOfTheSecondChannelAfterTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:30> Error encoding subfield DescOfTheSecondChannelAfterTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for ModeOfTheSecondChannel */
	{
		if (Source->ModeOfTheSecondChannel_Present) {
			/* Append to buffer IEI tag 0x66 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x66), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ModeOfTheSecondChannel> DOT=<.> */
			EDIntToBits (Buffer, (CurrOfs), (int)(Source->ModeOfTheSecondChannel), 8);
			Len = 8;
			
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:31> Error encoding subfield ModeOfTheSecondChannel\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for MobileAllocationAfterTime */
	{
		int TLV_Base = CurrOfs;
		if (Source->MobileAllocationAfterTime_Present) {
			/* Append to buffer IEI tag 0x72 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x72), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->MobileAllocationAfterTime> DOT=<->> */
			Len = ENCODE_c_MobileAllocation (Buffer, CurrOfs+8, Source->MobileAllocationAfterTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:32> Error encoding subfield MobileAllocationAfterTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
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
				ED_SIGNAL_ERROR ("<ERRID:33> Error encoding subfield StartingTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for FrequencyListBeforeTime */
	{
		int TLV_Base = CurrOfs;
		if (Source->FrequencyListBeforeTime_Present) {
			/* Append to buffer IEI tag 0x19 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x19), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->FrequencyListBeforeTime> DOT=<->> */
			Len = ENCODE_c_CellChannel (Buffer, CurrOfs+8, Source->FrequencyListBeforeTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:34> Error encoding subfield FrequencyListBeforeTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for DescOfTheFirstChannelBeforeTime */
	{
		if (Source->DescOfTheFirstChannelBeforeTime_Present) {
			/* Append to buffer IEI tag 0x1C */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x1C), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->DescOfTheFirstChannelBeforeTime> DOT=<->> */
			Len = ENCODE_c_TChDesc2 (Buffer, CurrOfs, Source->DescOfTheFirstChannelBeforeTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:35> Error encoding subfield DescOfTheFirstChannelBeforeTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for DescOfTheSecondChannelBeforeTime */
	{
		if (Source->DescOfTheSecondChannelBeforeTime_Present) {
			/* Append to buffer IEI tag 0x1D */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x1D), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->DescOfTheSecondChannelBeforeTime> DOT=<->> */
			Len = ENCODE_c_TChDesc (Buffer, CurrOfs, Source->DescOfTheSecondChannelBeforeTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:36> Error encoding subfield DescOfTheSecondChannelBeforeTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for FrequencyChannelSequenceBeforeTime */
	{
		if (Source->FrequencyChannelSequenceBeforeTime_Present) {
			/* Append to buffer IEI tag 0x1E */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x1E), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->FrequencyChannelSequenceBeforeTime> DOT=<->> */
			Len = ENCODE_c_FreqChannelSeq (Buffer, CurrOfs, Source->FrequencyChannelSequenceBeforeTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:37> Error encoding subfield FrequencyChannelSequenceBeforeTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for MobileAllocationBeforeTime */
	{
		int TLV_Base = CurrOfs;
		if (Source->MobileAllocationBeforeTime_Present) {
			/* Append to buffer IEI tag 0x21 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x21), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->MobileAllocationBeforeTime> DOT=<->> */
			Len = ENCODE_c_MobileAllocation (Buffer, CurrOfs+8, Source->MobileAllocationBeforeTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:38> Error encoding subfield MobileAllocationBeforeTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for CipherModeSetting */
	{
		if (Source->CipherModeSetting_Present) {
			/* Append to buffer IEI tag 0x09 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x09), 4);
			CurrOfs += 4;
			/* Append to buffer value part DEBUG FIELD=<Source->CipherModeSetting> DOT=<->> */
			Len = ENCODE_c_CipherModeSetting (Buffer, CurrOfs, Source->CipherModeSetting);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:39> Error encoding subfield CipherModeSetting\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for VgcsTargetModeIndication */
	{
		int TLV_Base = CurrOfs;
		if (Source->VgcsTargetModeIndication_Present) {
			/* Append to buffer IEI tag 0x01 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x01), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->VgcsTargetModeIndication> DOT=<.> */
			EDIntToBits (Buffer, (CurrOfs+8), (int)(Source->VgcsTargetModeIndication), 8);
			Len = 8;
			
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:40> Error encoding subfield VgcsTargetModeIndication\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for MultiRateCfg */
	{
		int TLV_Base = CurrOfs;
		if (Source->MultiRateCfg_Present) {
			/* Append to buffer IEI tag 0x03 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x03), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->MultiRateCfg> DOT=<->> */
			Len = ENCODE_c_MultirateSpeechCfgIE (Buffer, CurrOfs+8, Source->MultiRateCfg);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:41> Error encoding subfield MultiRateCfg\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for VGCSCipheringParameters */
	{
		int TLV_Base = CurrOfs;
		if (Source->VGCSCipheringParameters_Present) {
			/* Append to buffer IEI tag 0x04 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x04), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->VGCSCipheringParameters> DOT=<->> */
			Len = ENCODE_c_VGCSCipheringParameters (Buffer, CurrOfs+8, Source->VGCSCipheringParameters);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:42> Error encoding subfield VGCSCipheringParameters\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for ExtendedTSCSetAfterTime */
	{
		if (Source->ExtendedTSCSetAfterTime_Present) {
			/* Append to buffer IEI tag 0x6D */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x6D), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ExtendedTSCSetAfterTime> DOT=<->> */
			Len = ENCODE_c_ExtendedTSCSet (Buffer, CurrOfs, Source->ExtendedTSCSetAfterTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:43> Error encoding subfield ExtendedTSCSetAfterTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for ExtendedTSCSetBeforeTime */
	{
		if (Source->ExtendedTSCSetBeforeTime_Present) {
			/* Append to buffer IEI tag 0x6E */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x6E), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ExtendedTSCSetBeforeTime> DOT=<->> */
			Len = ENCODE_c_ExtendedTSCSet (Buffer, CurrOfs, Source->ExtendedTSCSetBeforeTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:44> Error encoding subfield ExtendedTSCSetBeforeTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE ASSIGNMENT_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_ASSIGNMENT_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ASSIGNMENT_COMMAND_DN* ED_CONST Source))
{
	return L3_ENCODE_c_ASSIGNMENT_COMMAND_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE ASSIGNMENT_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_ASSIGNMENT_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ASSIGNMENT_COMMAND_DN* ED_CONST Source))
{
	return L3_ENCODE_c_ASSIGNMENT_COMMAND_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE ASSIGNMENT_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_ASSIGNMENT_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ASSIGNMENT_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_ASSIGNMENT_COMMAND_DN (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE ASSIGNMENT_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_ASSIGNMENT_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ASSIGNMENT_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length))
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
		{5, 255, ED_SKIPLIST_OPTIONAL},
		{98, 255, ED_SKIPLIST_OPTIONAL},
		{16, 255, ED_SKIPLIST_OPTIONAL},
		{99, 255, ED_SKIPLIST_OPTIONAL},
		{17, 255, ED_SKIPLIST_OPTIONAL},
		{19, 255, ED_SKIPLIST_OPTIONAL},
		{20, 255, ED_SKIPLIST_OPTIONAL},
		{21, 255, ED_SKIPLIST_OPTIONAL},
		{22, 255, ED_SKIPLIST_OPTIONAL},
		{23, 255, ED_SKIPLIST_OPTIONAL},
		{24, 255, ED_SKIPLIST_OPTIONAL},
		{100, 255, ED_SKIPLIST_OPTIONAL},
		{102, 255, ED_SKIPLIST_OPTIONAL},
		{114, 255, ED_SKIPLIST_OPTIONAL},
		{124, 255, ED_SKIPLIST_OPTIONAL},
		{25, 255, ED_SKIPLIST_OPTIONAL},
		{28, 255, ED_SKIPLIST_OPTIONAL},
		{29, 255, ED_SKIPLIST_OPTIONAL},
		{30, 255, ED_SKIPLIST_OPTIONAL},
		{33, 255, ED_SKIPLIST_OPTIONAL},
		{144, 240, ED_SKIPLIST_OPTIONAL},
		{1, 255, ED_SKIPLIST_OPTIONAL},
		{3, 255, ED_SKIPLIST_OPTIONAL},
		{4, 255, ED_SKIPLIST_OPTIONAL},
		{109, 255, ED_SKIPLIST_OPTIONAL},
		{110, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	ED_WARNING_REMOVER (TLVSkipItems);
	
	/*----------------------------------------------------- 
		Code for IE DescOfTheFirstChannelAfterTime
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_TChDesc2 (Buffer, CurrOfs, (&(Destin->DescOfTheFirstChannelAfterTime)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:45> Error decoding subfield DescOfTheFirstChannelAfterTime\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 45, (Destin->DescOfTheFirstChannelAfterTime))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:46> Message too short decoding subfield DescOfTheFirstChannelAfterTime\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 45, (Destin->DescOfTheFirstChannelAfterTime))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE PowerCommand
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_PowerCommand (Buffer, CurrOfs, (&(Destin->PowerCommand)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:47> Error decoding subfield PowerCommand\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 47, (Destin->PowerCommand))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:48> Message too short decoding subfield PowerCommand\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 47, (Destin->PowerCommand))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE FrequencyListAfterTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x05 */
	ED_EXPECT_OPTIONAL_IE (0x05,  8, 49, 2, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x05) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DN_FrequencyListAfterTime (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 16) || (Len > 1040)) {
			ED_SIGNAL_ERROR ("<ERRID:50> Size error decoding IE FrequencyListAfterTime\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_FrequencyListAfterTime (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x05, 50, (Destin->FrequencyListAfterTime))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, Destin->FrequencyListAfterTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:51> Error decoding subfield FrequencyListAfterTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_FrequencyListAfterTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x05, 51, (Destin->FrequencyListAfterTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:52> Message too short decoding subfield FrequencyListAfterTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_FrequencyListAfterTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x05, 51, (Destin->FrequencyListAfterTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE CellChannelDescription
	------------------------------------------------------*/
	/* Detect IEI tag 0x62 */
	ED_EXPECT_OPTIONAL_IE (0x62,  8, 53, 3, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x62) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DN_CellChannelDescription (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 128;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, Destin->CellChannelDescription, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:54> Error decoding subfield CellChannelDescription\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_CellChannelDescription (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x62, 54, (Destin->CellChannelDescription))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:55> Message too short decoding subfield CellChannelDescription\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_CellChannelDescription (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x62, 54, (Destin->CellChannelDescription))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE DescriptionOfTheMultislotCfg
	------------------------------------------------------*/
	/* Detect IEI tag 0x10 */
	ED_EXPECT_OPTIONAL_IE (0x10,  8, 56, 4, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x10) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DN_DescriptionOfTheMultislotCfg (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 80)) {
			ED_SIGNAL_ERROR ("<ERRID:57> Size error decoding IE DescriptionOfTheMultislotCfg\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_DescriptionOfTheMultislotCfg (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x10, 57, (Destin->DescriptionOfTheMultislotCfg))
		} 
#endif
		/* Read value part LOCATOR_16 */
		/* LOCATOR SETTINGS LOCBIN2 */;
		ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-51609=EDCore::TDMBinary) */Destin->DescriptionOfTheMultislotCfg___LOCATOR), CurrOfs, Len);
		if (Len > 0) {
			/* BINDEC02 */
			ALLOC_c_ASSIGNMENT_COMMAND_DN_DescriptionOfTheMultislotCfg (Destin->DescriptionOfTheMultislotCfg, Len);
		
			EDCopyBits (Destin->DescriptionOfTheMultislotCfg->value, 0, Buffer, CurrOfs, Len);
			Destin->DescriptionOfTheMultislotCfg->usedBits = Len;
		}
		
		RetLen = Len;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:58> Error decoding subfield DescriptionOfTheMultislotCfg\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_DescriptionOfTheMultislotCfg (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x10, 58, (Destin->DescriptionOfTheMultislotCfg))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:59> Message too short decoding subfield DescriptionOfTheMultislotCfg\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_DescriptionOfTheMultislotCfg (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x10, 58, (Destin->DescriptionOfTheMultislotCfg))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfTheFirstChannelChannelSet1
	------------------------------------------------------*/
	/* Detect IEI tag 0x63 */
	ED_EXPECT_OPTIONAL_IE (0x63,  8, 60, 5, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x63) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ModeOfTheFirstChannelChannelSet1 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ChannelMode (Buffer, CurrOfs, Destin->ModeOfTheFirstChannelChannelSet1, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:61> Error decoding subfield ModeOfTheFirstChannelChannelSet1\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ModeOfTheFirstChannelChannelSet1 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x63, 61, (Destin->ModeOfTheFirstChannelChannelSet1))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:62> Message too short decoding subfield ModeOfTheFirstChannelChannelSet1\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ModeOfTheFirstChannelChannelSet1 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x63, 61, (Destin->ModeOfTheFirstChannelChannelSet1))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet2
	------------------------------------------------------*/
	/* Detect IEI tag 0x11 */
	ED_EXPECT_OPTIONAL_IE (0x11,  8, 63, 6, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x11) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ModeOfChannelSet2 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ChannelMode (Buffer, CurrOfs, Destin->ModeOfChannelSet2, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:64> Error decoding subfield ModeOfChannelSet2\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ModeOfChannelSet2 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x11, 64, (Destin->ModeOfChannelSet2))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:65> Message too short decoding subfield ModeOfChannelSet2\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ModeOfChannelSet2 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x11, 64, (Destin->ModeOfChannelSet2))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet3
	------------------------------------------------------*/
	/* Detect IEI tag 0x13 */
	ED_EXPECT_OPTIONAL_IE (0x13,  8, 66, 7, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x13) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ModeOfChannelSet3 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ChannelMode (Buffer, CurrOfs, Destin->ModeOfChannelSet3, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:67> Error decoding subfield ModeOfChannelSet3\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ModeOfChannelSet3 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x13, 67, (Destin->ModeOfChannelSet3))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:68> Message too short decoding subfield ModeOfChannelSet3\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ModeOfChannelSet3 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x13, 67, (Destin->ModeOfChannelSet3))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet4
	------------------------------------------------------*/
	/* Detect IEI tag 0x14 */
	ED_EXPECT_OPTIONAL_IE (0x14,  8, 69, 8, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x14) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ModeOfChannelSet4 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ChannelMode (Buffer, CurrOfs, Destin->ModeOfChannelSet4, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:70> Error decoding subfield ModeOfChannelSet4\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ModeOfChannelSet4 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x14, 70, (Destin->ModeOfChannelSet4))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:71> Message too short decoding subfield ModeOfChannelSet4\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ModeOfChannelSet4 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x14, 70, (Destin->ModeOfChannelSet4))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet5
	------------------------------------------------------*/
	/* Detect IEI tag 0x15 */
	ED_EXPECT_OPTIONAL_IE (0x15,  8, 72, 9, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x15) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ModeOfChannelSet5 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ChannelMode (Buffer, CurrOfs, Destin->ModeOfChannelSet5, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:73> Error decoding subfield ModeOfChannelSet5\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ModeOfChannelSet5 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x15, 73, (Destin->ModeOfChannelSet5))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:74> Message too short decoding subfield ModeOfChannelSet5\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ModeOfChannelSet5 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x15, 73, (Destin->ModeOfChannelSet5))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet6
	------------------------------------------------------*/
	/* Detect IEI tag 0x16 */
	ED_EXPECT_OPTIONAL_IE (0x16,  8, 75, 10, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x16) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ModeOfChannelSet6 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ChannelMode (Buffer, CurrOfs, Destin->ModeOfChannelSet6, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:76> Error decoding subfield ModeOfChannelSet6\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ModeOfChannelSet6 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x16, 76, (Destin->ModeOfChannelSet6))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:77> Message too short decoding subfield ModeOfChannelSet6\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ModeOfChannelSet6 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x16, 76, (Destin->ModeOfChannelSet6))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet7
	------------------------------------------------------*/
	/* Detect IEI tag 0x17 */
	ED_EXPECT_OPTIONAL_IE (0x17,  8, 78, 11, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x17) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ModeOfChannelSet7 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ChannelMode (Buffer, CurrOfs, Destin->ModeOfChannelSet7, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:79> Error decoding subfield ModeOfChannelSet7\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ModeOfChannelSet7 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x17, 79, (Destin->ModeOfChannelSet7))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:80> Message too short decoding subfield ModeOfChannelSet7\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ModeOfChannelSet7 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x17, 79, (Destin->ModeOfChannelSet7))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet8
	------------------------------------------------------*/
	/* Detect IEI tag 0x18 */
	ED_EXPECT_OPTIONAL_IE (0x18,  8, 81, 12, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x18) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ModeOfChannelSet8 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ChannelMode (Buffer, CurrOfs, Destin->ModeOfChannelSet8, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:82> Error decoding subfield ModeOfChannelSet8\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ModeOfChannelSet8 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x18, 82, (Destin->ModeOfChannelSet8))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:83> Message too short decoding subfield ModeOfChannelSet8\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ModeOfChannelSet8 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x18, 82, (Destin->ModeOfChannelSet8))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE DescOfTheSecondChannelAfterTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x64 */
	ED_EXPECT_OPTIONAL_IE (0x64,  8, 84, 13, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x64) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DN_DescOfTheSecondChannelAfterTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 24;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, Destin->DescOfTheSecondChannelAfterTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:85> Error decoding subfield DescOfTheSecondChannelAfterTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_DescOfTheSecondChannelAfterTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x64, 85, (Destin->DescOfTheSecondChannelAfterTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:86> Message too short decoding subfield DescOfTheSecondChannelAfterTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_DescOfTheSecondChannelAfterTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x64, 85, (Destin->DescOfTheSecondChannelAfterTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfTheSecondChannel
	------------------------------------------------------*/
	/* Detect IEI tag 0x66 */
	ED_EXPECT_OPTIONAL_IE (0x66,  8, 87, 14, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x66) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ModeOfTheSecondChannel (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		Destin->ModeOfTheSecondChannel = (ED_OCTET)EDBitsToInt (Buffer, (CurrOfs), 8);
		/* LOCATOR SETTINGS LOCINT */;
		ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-51629=EDCore::TDMInteger) */Destin->ModeOfTheSecondChannel___LOCATOR), CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:88> Error decoding subfield ModeOfTheSecondChannel\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ModeOfTheSecondChannel (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x66, 88, (Destin->ModeOfTheSecondChannel))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:89> Message too short decoding subfield ModeOfTheSecondChannel\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ModeOfTheSecondChannel (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x66, 88, (Destin->ModeOfTheSecondChannel))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE MobileAllocationAfterTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x72 */
	ED_EXPECT_OPTIONAL_IE (0x72,  8, 90, 15, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x72) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DN_MobileAllocationAfterTime (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 64)) {
			ED_SIGNAL_ERROR ("<ERRID:91> Size error decoding IE MobileAllocationAfterTime\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_MobileAllocationAfterTime (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x72, 91, (Destin->MobileAllocationAfterTime))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_MobileAllocation (Buffer, CurrOfs, Destin->MobileAllocationAfterTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:92> Error decoding subfield MobileAllocationAfterTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_MobileAllocationAfterTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x72, 92, (Destin->MobileAllocationAfterTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:93> Message too short decoding subfield MobileAllocationAfterTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_MobileAllocationAfterTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x72, 92, (Destin->MobileAllocationAfterTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE StartingTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x7C */
	ED_EXPECT_OPTIONAL_IE (0x7C,  8, 94, 16, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x7C) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DN_StartingTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 16;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_StartingTime (Buffer, CurrOfs, Destin->StartingTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:95> Error decoding subfield StartingTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_StartingTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x7C, 95, (Destin->StartingTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:96> Message too short decoding subfield StartingTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_StartingTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x7C, 95, (Destin->StartingTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE FrequencyListBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x19 */
	ED_EXPECT_OPTIONAL_IE (0x19,  8, 97, 17, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x19) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DN_FrequencyListBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 16) || (Len > 1040)) {
			ED_SIGNAL_ERROR ("<ERRID:98> Size error decoding IE FrequencyListBeforeTime\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_FrequencyListBeforeTime (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x19, 98, (Destin->FrequencyListBeforeTime))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, Destin->FrequencyListBeforeTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:99> Error decoding subfield FrequencyListBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_FrequencyListBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x19, 99, (Destin->FrequencyListBeforeTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:100> Message too short decoding subfield FrequencyListBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_FrequencyListBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x19, 99, (Destin->FrequencyListBeforeTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE DescOfTheFirstChannelBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x1C */
	ED_EXPECT_OPTIONAL_IE (0x1C,  8, 101, 18, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x1C) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DN_DescOfTheFirstChannelBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 24;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_TChDesc2 (Buffer, CurrOfs, Destin->DescOfTheFirstChannelBeforeTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:102> Error decoding subfield DescOfTheFirstChannelBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_DescOfTheFirstChannelBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x1C, 102, (Destin->DescOfTheFirstChannelBeforeTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:103> Message too short decoding subfield DescOfTheFirstChannelBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_DescOfTheFirstChannelBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x1C, 102, (Destin->DescOfTheFirstChannelBeforeTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE DescOfTheSecondChannelBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x1D */
	ED_EXPECT_OPTIONAL_IE (0x1D,  8, 104, 19, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x1D) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DN_DescOfTheSecondChannelBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 24;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, Destin->DescOfTheSecondChannelBeforeTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:105> Error decoding subfield DescOfTheSecondChannelBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_DescOfTheSecondChannelBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x1D, 105, (Destin->DescOfTheSecondChannelBeforeTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:106> Message too short decoding subfield DescOfTheSecondChannelBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_DescOfTheSecondChannelBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x1D, 105, (Destin->DescOfTheSecondChannelBeforeTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE FrequencyChannelSequenceBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x1E */
	ED_EXPECT_OPTIONAL_IE (0x1E,  8, 107, 20, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x1E) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DN_FrequencyChannelSequenceBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 72;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_FreqChannelSeq (Buffer, CurrOfs, Destin->FrequencyChannelSequenceBeforeTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:108> Error decoding subfield FrequencyChannelSequenceBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_FrequencyChannelSequenceBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x1E, 108, (Destin->FrequencyChannelSequenceBeforeTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:109> Message too short decoding subfield FrequencyChannelSequenceBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_FrequencyChannelSequenceBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x1E, 108, (Destin->FrequencyChannelSequenceBeforeTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE MobileAllocationBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x21 */
	ED_EXPECT_OPTIONAL_IE (0x21,  8, 110, 21, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x21) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DN_MobileAllocationBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 64)) {
			ED_SIGNAL_ERROR ("<ERRID:111> Size error decoding IE MobileAllocationBeforeTime\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_MobileAllocationBeforeTime (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x21, 111, (Destin->MobileAllocationBeforeTime))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_MobileAllocation (Buffer, CurrOfs, Destin->MobileAllocationBeforeTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:112> Error decoding subfield MobileAllocationBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_MobileAllocationBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x21, 112, (Destin->MobileAllocationBeforeTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:113> Message too short decoding subfield MobileAllocationBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_MobileAllocationBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x21, 112, (Destin->MobileAllocationBeforeTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE CipherModeSetting
	------------------------------------------------------*/
	/* Detect IEI tag 0x09 */
	ED_EXPECT_OPTIONAL_IE (0x09,  4, 114, 22, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 4); */
	
	/* This is an optional field */
	if (Tag == 0x09) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DN_CipherModeSetting (Destin, ED_TRUE);
		CurrOfs += 4;
		Len = 4;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_CipherModeSetting (Buffer, CurrOfs, Destin->CipherModeSetting, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:115> Error decoding subfield CipherModeSetting\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_CipherModeSetting (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x09, 115, (Destin->CipherModeSetting))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:116> Message too short decoding subfield CipherModeSetting\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_CipherModeSetting (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x09, 115, (Destin->CipherModeSetting))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE VgcsTargetModeIndication
	------------------------------------------------------*/
	/* Detect IEI tag 0x01 */
	ED_EXPECT_OPTIONAL_IE (0x01,  8, 117, 23, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x01) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DN_VgcsTargetModeIndication (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len != 8) {
			ED_SIGNAL_ERROR ("<ERRID:118> Size error decoding IE VgcsTargetModeIndication\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_VgcsTargetModeIndication (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x01, 118, (Destin->VgcsTargetModeIndication))
		} 
#endif
		/* Read value part LOCATOR_16 */
		Destin->VgcsTargetModeIndication = (ED_OCTET)EDBitsToInt (Buffer, (CurrOfs), 8);
		/* LOCATOR SETTINGS LOCINT */;
		ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-51647=EDCore::TDMInteger) */Destin->VgcsTargetModeIndication___LOCATOR), CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:119> Error decoding subfield VgcsTargetModeIndication\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_VgcsTargetModeIndication (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x01, 119, (Destin->VgcsTargetModeIndication))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:120> Message too short decoding subfield VgcsTargetModeIndication\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_VgcsTargetModeIndication (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x01, 119, (Destin->VgcsTargetModeIndication))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE MultiRateCfg
	------------------------------------------------------*/
	/* Detect IEI tag 0x03 */
	ED_EXPECT_OPTIONAL_IE (0x03,  8, 121, 24, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x03) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DN_MultiRateCfg (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 16) || (Len > 48)) {
			ED_SIGNAL_ERROR ("<ERRID:122> Size error decoding IE MultiRateCfg\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_MultiRateCfg (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x03, 122, (Destin->MultiRateCfg))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_MultirateSpeechCfgIE (Buffer, CurrOfs, Destin->MultiRateCfg, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:123> Error decoding subfield MultiRateCfg\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_MultiRateCfg (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x03, 123, (Destin->MultiRateCfg))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:124> Message too short decoding subfield MultiRateCfg\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_MultiRateCfg (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x03, 123, (Destin->MultiRateCfg))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE VGCSCipheringParameters
	------------------------------------------------------*/
	/* Detect IEI tag 0x04 */
	ED_EXPECT_OPTIONAL_IE (0x04,  8, 125, 25, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x04) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DN_VGCSCipheringParameters (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 104)) {
			ED_SIGNAL_ERROR ("<ERRID:126> Size error decoding IE VGCSCipheringParameters\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_VGCSCipheringParameters (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x04, 126, (Destin->VGCSCipheringParameters))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_VGCSCipheringParameters (Buffer, CurrOfs, Destin->VGCSCipheringParameters, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:127> Error decoding subfield VGCSCipheringParameters\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_VGCSCipheringParameters (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x04, 127, (Destin->VGCSCipheringParameters))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:128> Message too short decoding subfield VGCSCipheringParameters\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_VGCSCipheringParameters (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x04, 127, (Destin->VGCSCipheringParameters))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ExtendedTSCSetAfterTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x6D */
	ED_EXPECT_OPTIONAL_IE (0x6D,  8, 129, 26, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x6D) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ExtendedTSCSetAfterTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ExtendedTSCSet (Buffer, CurrOfs, Destin->ExtendedTSCSetAfterTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:130> Error decoding subfield ExtendedTSCSetAfterTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ExtendedTSCSetAfterTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x6D, 130, (Destin->ExtendedTSCSetAfterTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:131> Message too short decoding subfield ExtendedTSCSetAfterTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ExtendedTSCSetAfterTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x6D, 130, (Destin->ExtendedTSCSetAfterTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ExtendedTSCSetBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x6E */
	ED_EXPECT_OPTIONAL_IE (0x6E,  8, 132, 27, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x6E) {
		SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ExtendedTSCSetBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ExtendedTSCSet (Buffer, CurrOfs, Destin->ExtendedTSCSetBeforeTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:133> Error decoding subfield ExtendedTSCSetBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ExtendedTSCSetBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x6E, 133, (Destin->ExtendedTSCSetBeforeTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:134> Message too short decoding subfield ExtendedTSCSetBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_ASSIGNMENT_COMMAND_DN_ExtendedTSCSetBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x6E, 133, (Destin->ExtendedTSCSetBeforeTime))
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CHANNEL_MODE_MODIFY_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_CHANNEL_MODE_MODIFY_DN (char* Buffer, ED_EXLONG BitOffset, const c_CHANNEL_MODE_MODIFY_DN* Source, int Mode)
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
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 16, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for ChannelDescription */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ChannelDescription> DOT=<.> */
		Len = ENCODE_c_TChDesc2 (Buffer, CurrOfs, (&(Source->ChannelDescription)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:135> Error encoding subfield ChannelDescription\n");
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
			ED_SIGNAL_ERROR ("<ERRID:136> Error encoding subfield ChannelMode\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for VgcsTargetModeIndication */
	{
		int TLV_Base = CurrOfs;
		if (Source->VgcsTargetModeIndication_Present) {
			/* Append to buffer IEI tag 0x01 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x01), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->VgcsTargetModeIndication> DOT=<.> */
			EDIntToBits (Buffer, (CurrOfs+8), (int)(Source->VgcsTargetModeIndication), 8);
			Len = 8;
			
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:137> Error encoding subfield VgcsTargetModeIndication\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for MultiRateCfg */
	{
		int TLV_Base = CurrOfs;
		if (Source->MultiRateCfg_Present) {
			/* Append to buffer IEI tag 0x03 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x03), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->MultiRateCfg> DOT=<->> */
			Len = ENCODE_c_MultirateSpeechCfgIE (Buffer, CurrOfs+8, Source->MultiRateCfg);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:138> Error encoding subfield MultiRateCfg\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for VGCSCipheringParameters */
	{
		int TLV_Base = CurrOfs;
		if (Source->VGCSCipheringParameters_Present) {
			/* Append to buffer IEI tag 0x04 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x04), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->VGCSCipheringParameters> DOT=<->> */
			Len = ENCODE_c_VGCSCipheringParameters (Buffer, CurrOfs+8, Source->VGCSCipheringParameters);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:139> Error encoding subfield VGCSCipheringParameters\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
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
				ED_SIGNAL_ERROR ("<ERRID:140> Error encoding subfield ExtendedTSCSet\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CHANNEL_MODE_MODIFY_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CHANNEL_MODE_MODIFY_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CHANNEL_MODE_MODIFY_DN* ED_CONST Source))
{
	return L3_ENCODE_c_CHANNEL_MODE_MODIFY_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE CHANNEL_MODE_MODIFY_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CHANNEL_MODE_MODIFY_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CHANNEL_MODE_MODIFY_DN* ED_CONST Source))
{
	return L3_ENCODE_c_CHANNEL_MODE_MODIFY_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CHANNEL_MODE_MODIFY_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CHANNEL_MODE_MODIFY_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CHANNEL_MODE_MODIFY_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_CHANNEL_MODE_MODIFY_DN (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CHANNEL_MODE_MODIFY_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CHANNEL_MODE_MODIFY_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CHANNEL_MODE_MODIFY_DN* ED_CONST Destin, ED_EXLONG Length))
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
		{1, 255, ED_SKIPLIST_OPTIONAL},
		{3, 255, ED_SKIPLIST_OPTIONAL},
		{4, 255, ED_SKIPLIST_OPTIONAL},
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
		ED_SIGNAL_ERROR ("<ERRID:141> Error decoding subfield ChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 141, (Destin->ChannelDescription))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:142> Message too short decoding subfield ChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 141, (Destin->ChannelDescription))
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
		ED_SIGNAL_ERROR ("<ERRID:143> Error decoding subfield ChannelMode\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 143, (Destin->ChannelMode))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:144> Message too short decoding subfield ChannelMode\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 143, (Destin->ChannelMode))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE VgcsTargetModeIndication
	------------------------------------------------------*/
	/* Detect IEI tag 0x01 */
	ED_EXPECT_OPTIONAL_IE (0x01,  8, 145, 2, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x01) {
		SETPRESENT_c_CHANNEL_MODE_MODIFY_DN_VgcsTargetModeIndication (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len != 8) {
			ED_SIGNAL_ERROR ("<ERRID:146> Size error decoding IE VgcsTargetModeIndication\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_MODE_MODIFY_DN_VgcsTargetModeIndication (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x01, 146, (Destin->VgcsTargetModeIndication))
		} 
#endif
		/* Read value part LOCATOR_16 */
		Destin->VgcsTargetModeIndication = (ED_OCTET)EDBitsToInt (Buffer, (CurrOfs), 8);
		/* LOCATOR SETTINGS LOCINT */;
		ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-51662=EDCore::TDMInteger) */Destin->VgcsTargetModeIndication___LOCATOR), CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:147> Error decoding subfield VgcsTargetModeIndication\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_MODE_MODIFY_DN_VgcsTargetModeIndication (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x01, 147, (Destin->VgcsTargetModeIndication))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:148> Message too short decoding subfield VgcsTargetModeIndication\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CHANNEL_MODE_MODIFY_DN_VgcsTargetModeIndication (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x01, 147, (Destin->VgcsTargetModeIndication))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE MultiRateCfg
	------------------------------------------------------*/
	/* Detect IEI tag 0x03 */
	ED_EXPECT_OPTIONAL_IE (0x03,  8, 149, 3, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x03) {
		SETPRESENT_c_CHANNEL_MODE_MODIFY_DN_MultiRateCfg (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 16) || (Len > 48)) {
			ED_SIGNAL_ERROR ("<ERRID:150> Size error decoding IE MultiRateCfg\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_MODE_MODIFY_DN_MultiRateCfg (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x03, 150, (Destin->MultiRateCfg))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_MultirateSpeechCfgIE (Buffer, CurrOfs, Destin->MultiRateCfg, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:151> Error decoding subfield MultiRateCfg\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_MODE_MODIFY_DN_MultiRateCfg (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x03, 151, (Destin->MultiRateCfg))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:152> Message too short decoding subfield MultiRateCfg\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CHANNEL_MODE_MODIFY_DN_MultiRateCfg (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x03, 151, (Destin->MultiRateCfg))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE VGCSCipheringParameters
	------------------------------------------------------*/
	/* Detect IEI tag 0x04 */
	ED_EXPECT_OPTIONAL_IE (0x04,  8, 153, 4, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x04) {
		SETPRESENT_c_CHANNEL_MODE_MODIFY_DN_VGCSCipheringParameters (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 104)) {
			ED_SIGNAL_ERROR ("<ERRID:154> Size error decoding IE VGCSCipheringParameters\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_MODE_MODIFY_DN_VGCSCipheringParameters (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x04, 154, (Destin->VGCSCipheringParameters))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_VGCSCipheringParameters (Buffer, CurrOfs, Destin->VGCSCipheringParameters, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:155> Error decoding subfield VGCSCipheringParameters\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_MODE_MODIFY_DN_VGCSCipheringParameters (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x04, 155, (Destin->VGCSCipheringParameters))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:156> Message too short decoding subfield VGCSCipheringParameters\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CHANNEL_MODE_MODIFY_DN_VGCSCipheringParameters (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x04, 155, (Destin->VGCSCipheringParameters))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ExtendedTSCSet
	------------------------------------------------------*/
	/* Detect IEI tag 0x6D */
	ED_EXPECT_OPTIONAL_IE (0x6D,  8, 157, 5, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x6D) {
		SETPRESENT_c_CHANNEL_MODE_MODIFY_DN_ExtendedTSCSet (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ExtendedTSCSet (Buffer, CurrOfs, Destin->ExtendedTSCSet, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:158> Error decoding subfield ExtendedTSCSet\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_MODE_MODIFY_DN_ExtendedTSCSet (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x6D, 158, (Destin->ExtendedTSCSet))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:159> Message too short decoding subfield ExtendedTSCSet\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CHANNEL_MODE_MODIFY_DN_ExtendedTSCSet (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x6D, 158, (Destin->ExtendedTSCSet))
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CHANNEL_RELEASE_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_CHANNEL_RELEASE_DN (char* Buffer, ED_EXLONG BitOffset, const c_CHANNEL_RELEASE_DN* Source, int Mode)
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
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 13, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for RrCause */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->RrCause> DOT=<.> */
		Len = ENCODE_c_RRCause (Buffer, CurrOfs, (&(Source->RrCause)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:160> Error encoding subfield RrCause\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for BaRange */
	{
		int TLV_Base = CurrOfs;
		if (Source->BaRange_Present) {
			/* Append to buffer IEI tag 0x73 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x73), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->BaRange> DOT=<->> */
			Len = ENCODE_c_BaRange (Buffer, CurrOfs+8, Source->BaRange);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:161> Error encoding subfield BaRange\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for GroupChannelDescription */
	{
		int TLV_Base = CurrOfs;
		if (Source->GroupChannelDescription_Present) {
			/* Append to buffer IEI tag 0x74 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x74), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->GroupChannelDescription> DOT=<->> */
			Len = ENCODE_c_GrpChannelDesc (Buffer, CurrOfs+8, Source->GroupChannelDescription);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:162> Error encoding subfield GroupChannelDescription\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for GroupCipherKeyNum */
	{
		if (Source->GroupCipherKeyNum_Present) {
			/* Append to buffer IEI tag 0x08 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x08), 4);
			CurrOfs += 4;
			/* Append to buffer value part DEBUG FIELD=<Source->GroupCipherKeyNum> DOT=<.> */
			EDIntToBits (Buffer, (CurrOfs), (int)(Source->GroupCipherKeyNum), 4);
			Len = 4;
			
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:163> Error encoding subfield GroupCipherKeyNum\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for GprsResumption */
	{
		if (Source->GprsResumption_Present) {
			/* Append to buffer IEI tag 0x0C */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x0C), 4);
			CurrOfs += 4;
			/* Append to buffer value part DEBUG FIELD=<Source->GprsResumption> DOT=<->> */
			Len = ENCODE_c_GPRSResumption (Buffer, CurrOfs, Source->GprsResumption);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:164> Error encoding subfield GprsResumption\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for BaListPref */
	{
		int TLV_Base = CurrOfs;
		if (Source->BaListPref_Present) {
			/* Append to buffer IEI tag 0x75 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x75), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->BaListPref> DOT=<->> */
			Len = ENCODE_c_BA_List_Pref (Buffer, CurrOfs+8, Source->BaListPref);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:165> Error encoding subfield BaListPref\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for UTRANFreqList */
	{
		int TLV_Base = CurrOfs;
		if (Source->UTRANFreqList_Present) {
			/* Append to buffer IEI tag 0x76 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x76), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->UTRANFreqList> DOT=<->> */
			Len = ENCODE_c_UTRANFreqList (Buffer, CurrOfs+8, Source->UTRANFreqList);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:166> Error encoding subfield UTRANFreqList\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for CellChannelDescription */
	{
		if (Source->CellChannelDescription_Present) {
			/* Append to buffer IEI tag 0x62 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x62), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->CellChannelDescription> DOT=<->> */
			Len = ENCODE_c_CellChannel (Buffer, CurrOfs, Source->CellChannelDescription);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:167> Error encoding subfield CellChannelDescription\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for CellSelIndAfterReleaseTCHandSDCCH */
	{
		int TLV_Base = CurrOfs;
		if (Source->CellSelIndAfterReleaseTCHandSDCCH_Present) {
			/* Append to buffer IEI tag 0x77 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x77), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->CellSelIndAfterReleaseTCHandSDCCH> DOT=<->> */
			Len = ENCODE_c_CellSelIndAfterReleaseTCHandSDCCH (Buffer, CurrOfs+8, Source->CellSelIndAfterReleaseTCHandSDCCH);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:168> Error encoding subfield CellSelIndAfterReleaseTCHandSDCCH\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for EnhancedDTMCSReleaseIndication */
	{
		if (Source->EnhancedDTMCSReleaseIndication_Present) {
			/* Append to buffer IEI tag 0x0A */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x0A), 4);
			CurrOfs += 4;
			/* Append to buffer value part DEBUG FIELD=<Source->EnhancedDTMCSReleaseIndication> DOT=<.> */
			EDIntToBits (Buffer, (CurrOfs), (int)(Source->EnhancedDTMCSReleaseIndication), 4);
			Len = 4;
			
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:169> Error encoding subfield EnhancedDTMCSReleaseIndication\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for VGCSCipheringParameters */
	{
		int TLV_Base = CurrOfs;
		if (Source->VGCSCipheringParameters_Present) {
			/* Append to buffer IEI tag 0x04 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x04), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->VGCSCipheringParameters> DOT=<->> */
			Len = ENCODE_c_VGCSCipheringParameters (Buffer, CurrOfs+8, Source->VGCSCipheringParameters);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:170> Error encoding subfield VGCSCipheringParameters\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for GroupChannelDescription2 */
	{
		int TLV_Base = CurrOfs;
		if (Source->GroupChannelDescription2_Present) {
			/* Append to buffer IEI tag 0x78 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x78), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->GroupChannelDescription2> DOT=<->> */
			Len = ENCODE_c_GroupChannelDescription2 (Buffer, CurrOfs+8, Source->GroupChannelDescription2);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:171> Error encoding subfield GroupChannelDescription2\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for TalkerIdentity */
	{
		int TLV_Base = CurrOfs;
		if (Source->TalkerIdentity_Present) {
			/* Append to buffer IEI tag 0x79 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x79), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->TalkerIdentity> DOT=<->> */
			Len = ENCODE_c_TalkerIdentity (Buffer, CurrOfs+8, Source->TalkerIdentity);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:172> Error encoding subfield TalkerIdentity\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for TalkerPriorityStatus */
	{
		int TLV_Base = CurrOfs;
		if (Source->TalkerPriorityStatus_Present) {
			/* Append to buffer IEI tag 0x7A */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x7A), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->TalkerPriorityStatus> DOT=<->> */
			Len = ENCODE_c_TalkerPriorityStatus (Buffer, CurrOfs+8, Source->TalkerPriorityStatus);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:173> Error encoding subfield TalkerPriorityStatus\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for VGCSAMRConfiguration */
	{
		int TLV_Base = CurrOfs;
		if (Source->VGCSAMRConfiguration_Present) {
			/* Append to buffer IEI tag 0x7B */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x7B), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->VGCSAMRConfiguration> DOT=<->> */
			Len = ENCODE_c_VGCSAMRConfiguration (Buffer, CurrOfs+8, Source->VGCSAMRConfiguration);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:174> Error encoding subfield VGCSAMRConfiguration\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for IndividualPriorities */
	{
		int TLV_Base = CurrOfs;
		if (Source->IndividualPriorities_Present) {
			/* Append to buffer IEI tag 0x7C */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x7C), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->IndividualPriorities> DOT=<->> */
			Len = ENCODE_c_IndividualPriorities (Buffer, CurrOfs+8, Source->IndividualPriorities);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:175> Error encoding subfield IndividualPriorities\n");
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
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CHANNEL_RELEASE_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CHANNEL_RELEASE_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CHANNEL_RELEASE_DN* ED_CONST Source))
{
	return L3_ENCODE_c_CHANNEL_RELEASE_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE CHANNEL_RELEASE_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CHANNEL_RELEASE_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CHANNEL_RELEASE_DN* ED_CONST Source))
{
	return L3_ENCODE_c_CHANNEL_RELEASE_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CHANNEL_RELEASE_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CHANNEL_RELEASE_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CHANNEL_RELEASE_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_CHANNEL_RELEASE_DN (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CHANNEL_RELEASE_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CHANNEL_RELEASE_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CHANNEL_RELEASE_DN* ED_CONST Destin, ED_EXLONG Length))
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
		{115, 255, ED_SKIPLIST_OPTIONAL},
		{116, 255, ED_SKIPLIST_OPTIONAL},
		{128, 240, ED_SKIPLIST_OPTIONAL},
		{192, 240, ED_SKIPLIST_OPTIONAL},
		{117, 255, ED_SKIPLIST_OPTIONAL},
		{118, 255, ED_SKIPLIST_OPTIONAL},
		{98, 255, ED_SKIPLIST_OPTIONAL},
		{119, 255, ED_SKIPLIST_OPTIONAL},
		{160, 240, ED_SKIPLIST_OPTIONAL},
		{4, 255, ED_SKIPLIST_OPTIONAL},
		{120, 255, ED_SKIPLIST_OPTIONAL},
		{121, 255, ED_SKIPLIST_OPTIONAL},
		{122, 255, ED_SKIPLIST_OPTIONAL},
		{123, 255, ED_SKIPLIST_OPTIONAL},
		{124, 255, ED_SKIPLIST_OPTIONAL},
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
		ED_SIGNAL_ERROR ("<ERRID:176> Error decoding subfield RrCause\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 176, (Destin->RrCause))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:177> Message too short decoding subfield RrCause\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 176, (Destin->RrCause))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE BaRange
	------------------------------------------------------*/
	/* Detect IEI tag 0x73 */
	ED_EXPECT_OPTIONAL_IE (0x73,  8, 178, 1, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x73) {
		SETPRESENT_c_CHANNEL_RELEASE_DN_BaRange (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 4784)) {
			ED_SIGNAL_ERROR ("<ERRID:179> Size error decoding IE BaRange\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_BaRange (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x73, 179, (Destin->BaRange))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_BaRange (Buffer, CurrOfs, Destin->BaRange, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:180> Error decoding subfield BaRange\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_BaRange (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x73, 180, (Destin->BaRange))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:181> Message too short decoding subfield BaRange\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_BaRange (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x73, 180, (Destin->BaRange))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE GroupChannelDescription
	------------------------------------------------------*/
	/* Detect IEI tag 0x74 */
	ED_EXPECT_OPTIONAL_IE (0x74,  8, 182, 2, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x74) {
		SETPRESENT_c_CHANNEL_RELEASE_DN_GroupChannelDescription (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 16) || (Len > 88)) {
			ED_SIGNAL_ERROR ("<ERRID:183> Size error decoding IE GroupChannelDescription\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_GroupChannelDescription (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x74, 183, (Destin->GroupChannelDescription))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_GrpChannelDesc (Buffer, CurrOfs, Destin->GroupChannelDescription, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:184> Error decoding subfield GroupChannelDescription\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_GroupChannelDescription (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x74, 184, (Destin->GroupChannelDescription))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:185> Message too short decoding subfield GroupChannelDescription\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_GroupChannelDescription (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x74, 184, (Destin->GroupChannelDescription))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE GroupCipherKeyNum
	------------------------------------------------------*/
	/* Detect IEI tag 0x08 */
	ED_EXPECT_OPTIONAL_IE (0x08,  4, 186, 3, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 4); */
	
	/* This is an optional field */
	if (Tag == 0x08) {
		SETPRESENT_c_CHANNEL_RELEASE_DN_GroupCipherKeyNum (Destin, ED_TRUE);
		CurrOfs += 4;
		Len = 4;
		/* Read value part LOCATOR_16 */
		Destin->GroupCipherKeyNum = (ED_OCTET)EDBitsToInt (Buffer, (CurrOfs), 4);
		/* LOCATOR SETTINGS LOCINT */;
		ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-51677=EDCore::TDMInteger) */Destin->GroupCipherKeyNum___LOCATOR), CurrOfs, 4);
		RetLen = 4;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:187> Error decoding subfield GroupCipherKeyNum\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_GroupCipherKeyNum (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x08, 187, (Destin->GroupCipherKeyNum))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:188> Message too short decoding subfield GroupCipherKeyNum\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_GroupCipherKeyNum (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x08, 187, (Destin->GroupCipherKeyNum))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE GprsResumption
	------------------------------------------------------*/
	/* Detect IEI tag 0x0C */
	ED_EXPECT_OPTIONAL_IE (0x0C,  4, 189, 4, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 4); */
	
	/* This is an optional field */
	if (Tag == 0x0C) {
		SETPRESENT_c_CHANNEL_RELEASE_DN_GprsResumption (Destin, ED_TRUE);
		CurrOfs += 4;
		Len = 4;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_GPRSResumption (Buffer, CurrOfs, Destin->GprsResumption, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:190> Error decoding subfield GprsResumption\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_GprsResumption (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x0C, 190, (Destin->GprsResumption))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:191> Message too short decoding subfield GprsResumption\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_GprsResumption (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x0C, 190, (Destin->GprsResumption))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE BaListPref
	------------------------------------------------------*/
	/* Detect IEI tag 0x75 */
	ED_EXPECT_OPTIONAL_IE (0x75,  8, 192, 5, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x75) {
		SETPRESENT_c_CHANNEL_RELEASE_DN_BaListPref (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 4784)) {
			ED_SIGNAL_ERROR ("<ERRID:193> Size error decoding IE BaListPref\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_BaListPref (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x75, 193, (Destin->BaListPref))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_BA_List_Pref (Buffer, CurrOfs, Destin->BaListPref, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:194> Error decoding subfield BaListPref\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_BaListPref (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x75, 194, (Destin->BaListPref))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:195> Message too short decoding subfield BaListPref\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_BaListPref (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x75, 194, (Destin->BaListPref))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE UTRANFreqList
	------------------------------------------------------*/
	/* Detect IEI tag 0x76 */
	ED_EXPECT_OPTIONAL_IE (0x76,  8, 196, 6, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x76) {
		SETPRESENT_c_CHANNEL_RELEASE_DN_UTRANFreqList (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 4784)) {
			ED_SIGNAL_ERROR ("<ERRID:197> Size error decoding IE UTRANFreqList\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_UTRANFreqList (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x76, 197, (Destin->UTRANFreqList))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_UTRANFreqList (Buffer, CurrOfs, Destin->UTRANFreqList, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:198> Error decoding subfield UTRANFreqList\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_UTRANFreqList (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x76, 198, (Destin->UTRANFreqList))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:199> Message too short decoding subfield UTRANFreqList\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_UTRANFreqList (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x76, 198, (Destin->UTRANFreqList))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE CellChannelDescription
	------------------------------------------------------*/
	/* Detect IEI tag 0x62 */
	ED_EXPECT_OPTIONAL_IE (0x62,  8, 200, 7, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x62) {
		SETPRESENT_c_CHANNEL_RELEASE_DN_CellChannelDescription (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 128;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, Destin->CellChannelDescription, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:201> Error decoding subfield CellChannelDescription\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_CellChannelDescription (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x62, 201, (Destin->CellChannelDescription))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:202> Message too short decoding subfield CellChannelDescription\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_CellChannelDescription (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x62, 201, (Destin->CellChannelDescription))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE CellSelIndAfterReleaseTCHandSDCCH
	------------------------------------------------------*/
	/* Detect IEI tag 0x77 */
	ED_EXPECT_OPTIONAL_IE (0x77,  8, 203, 8, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x77) {
		SETPRESENT_c_CHANNEL_RELEASE_DN_CellSelIndAfterReleaseTCHandSDCCH (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 16) || (Len > 4784)) {
			ED_SIGNAL_ERROR ("<ERRID:204> Size error decoding IE CellSelIndAfterReleaseTCHandSDCCH\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_CellSelIndAfterReleaseTCHandSDCCH (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x77, 204, (Destin->CellSelIndAfterReleaseTCHandSDCCH))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_CellSelIndAfterReleaseTCHandSDCCH (Buffer, CurrOfs, Destin->CellSelIndAfterReleaseTCHandSDCCH, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:205> Error decoding subfield CellSelIndAfterReleaseTCHandSDCCH\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_CellSelIndAfterReleaseTCHandSDCCH (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x77, 205, (Destin->CellSelIndAfterReleaseTCHandSDCCH))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:206> Message too short decoding subfield CellSelIndAfterReleaseTCHandSDCCH\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_CellSelIndAfterReleaseTCHandSDCCH (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x77, 205, (Destin->CellSelIndAfterReleaseTCHandSDCCH))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE EnhancedDTMCSReleaseIndication
	------------------------------------------------------*/
	/* Detect IEI tag 0x0A */
	ED_EXPECT_OPTIONAL_IE (0x0A,  4, 207, 9, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 4); */
	
	/* This is an optional field */
	if (Tag == 0x0A) {
		SETPRESENT_c_CHANNEL_RELEASE_DN_EnhancedDTMCSReleaseIndication (Destin, ED_TRUE);
		CurrOfs += 4;
		Len = 4;
		/* Read value part LOCATOR_16 */
		Destin->EnhancedDTMCSReleaseIndication = (ED_OCTET)EDBitsToInt (Buffer, (CurrOfs), 4);
		/* LOCATOR SETTINGS LOCINT */;
		ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-51689=EDCore::TDMInteger) */Destin->EnhancedDTMCSReleaseIndication___LOCATOR), CurrOfs, 4);
		RetLen = 4;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:208> Error decoding subfield EnhancedDTMCSReleaseIndication\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_EnhancedDTMCSReleaseIndication (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x0A, 208, (Destin->EnhancedDTMCSReleaseIndication))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:209> Message too short decoding subfield EnhancedDTMCSReleaseIndication\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_EnhancedDTMCSReleaseIndication (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x0A, 208, (Destin->EnhancedDTMCSReleaseIndication))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE VGCSCipheringParameters
	------------------------------------------------------*/
	/* Detect IEI tag 0x04 */
	ED_EXPECT_OPTIONAL_IE (0x04,  8, 210, 10, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x04) {
		SETPRESENT_c_CHANNEL_RELEASE_DN_VGCSCipheringParameters (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 104)) {
			ED_SIGNAL_ERROR ("<ERRID:211> Size error decoding IE VGCSCipheringParameters\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_VGCSCipheringParameters (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x04, 211, (Destin->VGCSCipheringParameters))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_VGCSCipheringParameters (Buffer, CurrOfs, Destin->VGCSCipheringParameters, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:212> Error decoding subfield VGCSCipheringParameters\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_VGCSCipheringParameters (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x04, 212, (Destin->VGCSCipheringParameters))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:213> Message too short decoding subfield VGCSCipheringParameters\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_VGCSCipheringParameters (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x04, 212, (Destin->VGCSCipheringParameters))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE GroupChannelDescription2
	------------------------------------------------------*/
	/* Detect IEI tag 0x78 */
	ED_EXPECT_OPTIONAL_IE (0x78,  8, 214, 11, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x78) {
		SETPRESENT_c_CHANNEL_RELEASE_DN_GroupChannelDescription2 (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len != 88) {
			ED_SIGNAL_ERROR ("<ERRID:215> Size error decoding IE GroupChannelDescription2\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_GroupChannelDescription2 (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x78, 215, (Destin->GroupChannelDescription2))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_GroupChannelDescription2 (Buffer, CurrOfs, Destin->GroupChannelDescription2, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:216> Error decoding subfield GroupChannelDescription2\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_GroupChannelDescription2 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x78, 216, (Destin->GroupChannelDescription2))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:217> Message too short decoding subfield GroupChannelDescription2\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_GroupChannelDescription2 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x78, 216, (Destin->GroupChannelDescription2))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE TalkerIdentity
	------------------------------------------------------*/
	/* Detect IEI tag 0x79 */
	ED_EXPECT_OPTIONAL_IE (0x79,  8, 218, 12, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x79) {
		SETPRESENT_c_CHANNEL_RELEASE_DN_TalkerIdentity (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 144)) {
			ED_SIGNAL_ERROR ("<ERRID:219> Size error decoding IE TalkerIdentity\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_TalkerIdentity (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x79, 219, (Destin->TalkerIdentity))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_TalkerIdentity (Buffer, CurrOfs, Destin->TalkerIdentity, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:220> Error decoding subfield TalkerIdentity\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_TalkerIdentity (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x79, 220, (Destin->TalkerIdentity))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:221> Message too short decoding subfield TalkerIdentity\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_TalkerIdentity (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x79, 220, (Destin->TalkerIdentity))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE TalkerPriorityStatus
	------------------------------------------------------*/
	/* Detect IEI tag 0x7A */
	ED_EXPECT_OPTIONAL_IE (0x7A,  8, 222, 13, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x7A) {
		SETPRESENT_c_CHANNEL_RELEASE_DN_TalkerPriorityStatus (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len != 8) {
			ED_SIGNAL_ERROR ("<ERRID:223> Size error decoding IE TalkerPriorityStatus\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_TalkerPriorityStatus (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x7A, 223, (Destin->TalkerPriorityStatus))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_TalkerPriorityStatus (Buffer, CurrOfs, Destin->TalkerPriorityStatus, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:224> Error decoding subfield TalkerPriorityStatus\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_TalkerPriorityStatus (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x7A, 224, (Destin->TalkerPriorityStatus))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:225> Message too short decoding subfield TalkerPriorityStatus\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_TalkerPriorityStatus (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x7A, 224, (Destin->TalkerPriorityStatus))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE VGCSAMRConfiguration
	------------------------------------------------------*/
	/* Detect IEI tag 0x7B */
	ED_EXPECT_OPTIONAL_IE (0x7B,  8, 226, 14, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x7B) {
		SETPRESENT_c_CHANNEL_RELEASE_DN_VGCSAMRConfiguration (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len != 8) {
			ED_SIGNAL_ERROR ("<ERRID:227> Size error decoding IE VGCSAMRConfiguration\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_VGCSAMRConfiguration (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x7B, 227, (Destin->VGCSAMRConfiguration))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_VGCSAMRConfiguration (Buffer, CurrOfs, Destin->VGCSAMRConfiguration, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:228> Error decoding subfield VGCSAMRConfiguration\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_VGCSAMRConfiguration (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x7B, 228, (Destin->VGCSAMRConfiguration))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:229> Message too short decoding subfield VGCSAMRConfiguration\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_VGCSAMRConfiguration (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x7B, 228, (Destin->VGCSAMRConfiguration))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE IndividualPriorities
	------------------------------------------------------*/
	/* Detect IEI tag 0x7C */
	ED_EXPECT_OPTIONAL_IE (0x7C,  8, 230, 15, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x7C) {
		SETPRESENT_c_CHANNEL_RELEASE_DN_IndividualPriorities (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 4784)) {
			ED_SIGNAL_ERROR ("<ERRID:231> Size error decoding IE IndividualPriorities\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_IndividualPriorities (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x7C, 231, (Destin->IndividualPriorities))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_IndividualPriorities (Buffer, CurrOfs, Destin->IndividualPriorities, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:232> Error decoding subfield IndividualPriorities\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_IndividualPriorities (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x7C, 232, (Destin->IndividualPriorities))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:233> Message too short decoding subfield IndividualPriorities\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CHANNEL_RELEASE_DN_IndividualPriorities (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x7C, 232, (Destin->IndividualPriorities))
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CIPHERING_MODE_COMMAND_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_CIPHERING_MODE_COMMAND_DN (char* Buffer, ED_EXLONG BitOffset, const c_CIPHERING_MODE_COMMAND_DN* Source, int Mode)
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
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 53, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for CiphModeSetting */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->CiphModeSetting> DOT=<.> */
		Len = ENCODE_c_CipherModeSetting (Buffer, (CurrOfs+4), (&(Source->CiphModeSetting)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:234> Error encoding subfield CiphModeSetting\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for CipherResp */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->CipherResp> DOT=<.> */
		Len = ENCODE_c_CipherResponse (Buffer, (CurrOfs-4), (&(Source->CipherResp)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:235> Error encoding subfield CipherResp\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CIPHERING_MODE_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CIPHERING_MODE_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CIPHERING_MODE_COMMAND_DN* ED_CONST Source))
{
	return L3_ENCODE_c_CIPHERING_MODE_COMMAND_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE CIPHERING_MODE_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CIPHERING_MODE_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CIPHERING_MODE_COMMAND_DN* ED_CONST Source))
{
	return L3_ENCODE_c_CIPHERING_MODE_COMMAND_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CIPHERING_MODE_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CIPHERING_MODE_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CIPHERING_MODE_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_CIPHERING_MODE_COMMAND_DN (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CIPHERING_MODE_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CIPHERING_MODE_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CIPHERING_MODE_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE CiphModeSetting
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_CipherModeSetting (Buffer, (CurrOfs+4), (&(Destin->CiphModeSetting)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:236> Error decoding subfield CiphModeSetting\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 236, (Destin->CiphModeSetting))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:237> Message too short decoding subfield CiphModeSetting\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 236, (Destin->CiphModeSetting))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE CipherResp
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_CipherResponse (Buffer, (CurrOfs-4), (&(Destin->CipherResp)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:238> Error decoding subfield CipherResp\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 238, (Destin->CipherResp))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:239> Message too short decoding subfield CipherResp\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 238, (Destin->CipherResp))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CLASSMARK_ENQUIRY_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_CLASSMARK_ENQUIRY_DN (char* Buffer, ED_EXLONG BitOffset, const c_CLASSMARK_ENQUIRY_DN* Source, int Mode)
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
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 19, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for ClassmarkEnquiryMask */
	{
		int TLV_Base = CurrOfs;
		if (Source->ClassmarkEnquiryMask_Present) {
			/* Append to buffer IEI tag 0x10 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x10), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->ClassmarkEnquiryMask> DOT=<->> */
			Len = ENCODE_c_ClassmarkEnquiryMask (Buffer, CurrOfs+8, Source->ClassmarkEnquiryMask);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:240> Error encoding subfield ClassmarkEnquiryMask\n");
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
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CLASSMARK_ENQUIRY_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CLASSMARK_ENQUIRY_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CLASSMARK_ENQUIRY_DN* ED_CONST Source))
{
	return L3_ENCODE_c_CLASSMARK_ENQUIRY_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE CLASSMARK_ENQUIRY_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CLASSMARK_ENQUIRY_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CLASSMARK_ENQUIRY_DN* ED_CONST Source))
{
	return L3_ENCODE_c_CLASSMARK_ENQUIRY_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CLASSMARK_ENQUIRY_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CLASSMARK_ENQUIRY_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CLASSMARK_ENQUIRY_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_CLASSMARK_ENQUIRY_DN (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CLASSMARK_ENQUIRY_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CLASSMARK_ENQUIRY_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CLASSMARK_ENQUIRY_DN* ED_CONST Destin, ED_EXLONG Length))
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
		{16, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	ED_WARNING_REMOVER (TLVSkipItems);
	
	/*----------------------------------------------------- 
		Code for IE ClassmarkEnquiryMask
	------------------------------------------------------*/
	/* Detect IEI tag 0x10 */
	ED_EXPECT_OPTIONAL_IE (0x10,  8, 241, 0, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x10) {
		SETPRESENT_c_CLASSMARK_ENQUIRY_DN_ClassmarkEnquiryMask (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len != 8) {
			ED_SIGNAL_ERROR ("<ERRID:242> Size error decoding IE ClassmarkEnquiryMask\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_CLASSMARK_ENQUIRY_DN_ClassmarkEnquiryMask (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x10, 242, (Destin->ClassmarkEnquiryMask))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ClassmarkEnquiryMask (Buffer, CurrOfs, Destin->ClassmarkEnquiryMask, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:243> Error decoding subfield ClassmarkEnquiryMask\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CLASSMARK_ENQUIRY_DN_ClassmarkEnquiryMask (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x10, 243, (Destin->ClassmarkEnquiryMask))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:244> Message too short decoding subfield ClassmarkEnquiryMask\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CLASSMARK_ENQUIRY_DN_ClassmarkEnquiryMask (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x10, 243, (Destin->ClassmarkEnquiryMask))
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CONFIGURATION_CHANGE_COMMAND_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_CONFIGURATION_CHANGE_COMMAND_DN (char* Buffer, ED_EXLONG BitOffset, const c_CONFIGURATION_CHANGE_COMMAND_DN* Source, int Mode)
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
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 48, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for DescriptionOfTheMultislotCfg */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->DescriptionOfTheMultislotCfg> DOT=<.> */
		EDCopyBits (Buffer, CurrOfs+8, Source->DescriptionOfTheMultislotCfg.value, 0, Source->DescriptionOfTheMultislotCfg.usedBits);
		Len = Source->DescriptionOfTheMultislotCfg.usedBits;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:245> Error encoding subfield DescriptionOfTheMultislotCfg\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for ModeOfChannelSet1 */
	{
		if (Source->ModeOfChannelSet1_Present) {
			/* Append to buffer IEI tag 0x63 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x63), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ModeOfChannelSet1> DOT=<->> */
			Len = ENCODE_c_ChannelMode (Buffer, CurrOfs, Source->ModeOfChannelSet1);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:246> Error encoding subfield ModeOfChannelSet1\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for ModeOfChannelSet2 */
	{
		if (Source->ModeOfChannelSet2_Present) {
			/* Append to buffer IEI tag 0x11 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x11), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ModeOfChannelSet2> DOT=<->> */
			Len = ENCODE_c_ChannelMode (Buffer, CurrOfs, Source->ModeOfChannelSet2);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:247> Error encoding subfield ModeOfChannelSet2\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for ModeOfChannelSet3 */
	{
		if (Source->ModeOfChannelSet3_Present) {
			/* Append to buffer IEI tag 0x13 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x13), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ModeOfChannelSet3> DOT=<->> */
			Len = ENCODE_c_ChannelMode (Buffer, CurrOfs, Source->ModeOfChannelSet3);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:248> Error encoding subfield ModeOfChannelSet3\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for ModeOfChannelSet4 */
	{
		if (Source->ModeOfChannelSet4_Present) {
			/* Append to buffer IEI tag 0x14 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x14), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ModeOfChannelSet4> DOT=<->> */
			Len = ENCODE_c_ChannelMode (Buffer, CurrOfs, Source->ModeOfChannelSet4);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:249> Error encoding subfield ModeOfChannelSet4\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for ModeOfChannelSet5 */
	{
		if (Source->ModeOfChannelSet5_Present) {
			/* Append to buffer IEI tag 0x15 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x15), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ModeOfChannelSet5> DOT=<->> */
			Len = ENCODE_c_ChannelMode (Buffer, CurrOfs, Source->ModeOfChannelSet5);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:250> Error encoding subfield ModeOfChannelSet5\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for ModeOfChannelSet6 */
	{
		if (Source->ModeOfChannelSet6_Present) {
			/* Append to buffer IEI tag 0x16 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x16), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ModeOfChannelSet6> DOT=<->> */
			Len = ENCODE_c_ChannelMode (Buffer, CurrOfs, Source->ModeOfChannelSet6);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:251> Error encoding subfield ModeOfChannelSet6\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for ModeOfChannelSet7 */
	{
		if (Source->ModeOfChannelSet7_Present) {
			/* Append to buffer IEI tag 0x17 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x17), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ModeOfChannelSet7> DOT=<->> */
			Len = ENCODE_c_ChannelMode (Buffer, CurrOfs, Source->ModeOfChannelSet7);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:252> Error encoding subfield ModeOfChannelSet7\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for ModeOfChannelSet8 */
	{
		if (Source->ModeOfChannelSet8_Present) {
			/* Append to buffer IEI tag 0x18 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x18), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ModeOfChannelSet8> DOT=<->> */
			Len = ENCODE_c_ChannelMode (Buffer, CurrOfs, Source->ModeOfChannelSet8);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:253> Error encoding subfield ModeOfChannelSet8\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE CONFIGURATION_CHANGE_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CONFIGURATION_CHANGE_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONFIGURATION_CHANGE_COMMAND_DN* ED_CONST Source))
{
	return L3_ENCODE_c_CONFIGURATION_CHANGE_COMMAND_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE CONFIGURATION_CHANGE_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_CONFIGURATION_CHANGE_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CONFIGURATION_CHANGE_COMMAND_DN* ED_CONST Source))
{
	return L3_ENCODE_c_CONFIGURATION_CHANGE_COMMAND_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CONFIGURATION_CHANGE_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CONFIGURATION_CHANGE_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONFIGURATION_CHANGE_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_CONFIGURATION_CHANGE_COMMAND_DN (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE CONFIGURATION_CHANGE_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_CONFIGURATION_CHANGE_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CONFIGURATION_CHANGE_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length))
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
		{99, 255, ED_SKIPLIST_OPTIONAL},
		{17, 255, ED_SKIPLIST_OPTIONAL},
		{19, 255, ED_SKIPLIST_OPTIONAL},
		{20, 255, ED_SKIPLIST_OPTIONAL},
		{21, 255, ED_SKIPLIST_OPTIONAL},
		{22, 255, ED_SKIPLIST_OPTIONAL},
		{23, 255, ED_SKIPLIST_OPTIONAL},
		{24, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	ED_WARNING_REMOVER (TLVSkipItems);
	
	/*----------------------------------------------------- 
		Code for IE DescriptionOfTheMultislotCfg
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if ((Len < 8) || (Len > 80)) {
		ED_SIGNAL_ERROR ("<ERRID:254> Size error decoding IE DescriptionOfTheMultislotCfg\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 254, (Destin->DescriptionOfTheMultislotCfg))
	} 
#endif
	/* Read value part LOCATOR_16 */
	/* LOCATOR SETTINGS LOCBIN2 */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-51712=EDCore::TDMBinary) */Destin->DescriptionOfTheMultislotCfg___LOCATOR), CurrOfs, Len);
	if (Len > 0) {
		/* BINDEC02 */
		ALLOC_c_CONFIGURATION_CHANGE_COMMAND_DN_DescriptionOfTheMultislotCfg (&(Destin->DescriptionOfTheMultislotCfg), Len);
	
		EDCopyBits (Destin->DescriptionOfTheMultislotCfg.value, 0, Buffer, CurrOfs, Len);
		Destin->DescriptionOfTheMultislotCfg.usedBits = Len;
	}
	
	RetLen = Len;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:255> Error decoding subfield DescriptionOfTheMultislotCfg\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 255, (Destin->DescriptionOfTheMultislotCfg))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:256> Message too short decoding subfield DescriptionOfTheMultislotCfg\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 255, (Destin->DescriptionOfTheMultislotCfg))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet1
	------------------------------------------------------*/
	/* Detect IEI tag 0x63 */
	ED_EXPECT_OPTIONAL_IE (0x63,  8, 257, 1, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x63) {
		SETPRESENT_c_CONFIGURATION_CHANGE_COMMAND_DN_ModeOfChannelSet1 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ChannelMode (Buffer, CurrOfs, Destin->ModeOfChannelSet1, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:258> Error decoding subfield ModeOfChannelSet1\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CONFIGURATION_CHANGE_COMMAND_DN_ModeOfChannelSet1 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x63, 258, (Destin->ModeOfChannelSet1))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:259> Message too short decoding subfield ModeOfChannelSet1\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CONFIGURATION_CHANGE_COMMAND_DN_ModeOfChannelSet1 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x63, 258, (Destin->ModeOfChannelSet1))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet2
	------------------------------------------------------*/
	/* Detect IEI tag 0x11 */
	ED_EXPECT_OPTIONAL_IE (0x11,  8, 260, 2, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x11) {
		SETPRESENT_c_CONFIGURATION_CHANGE_COMMAND_DN_ModeOfChannelSet2 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ChannelMode (Buffer, CurrOfs, Destin->ModeOfChannelSet2, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:261> Error decoding subfield ModeOfChannelSet2\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CONFIGURATION_CHANGE_COMMAND_DN_ModeOfChannelSet2 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x11, 261, (Destin->ModeOfChannelSet2))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:262> Message too short decoding subfield ModeOfChannelSet2\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CONFIGURATION_CHANGE_COMMAND_DN_ModeOfChannelSet2 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x11, 261, (Destin->ModeOfChannelSet2))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet3
	------------------------------------------------------*/
	/* Detect IEI tag 0x13 */
	ED_EXPECT_OPTIONAL_IE (0x13,  8, 263, 3, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x13) {
		SETPRESENT_c_CONFIGURATION_CHANGE_COMMAND_DN_ModeOfChannelSet3 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ChannelMode (Buffer, CurrOfs, Destin->ModeOfChannelSet3, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:264> Error decoding subfield ModeOfChannelSet3\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CONFIGURATION_CHANGE_COMMAND_DN_ModeOfChannelSet3 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x13, 264, (Destin->ModeOfChannelSet3))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:265> Message too short decoding subfield ModeOfChannelSet3\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CONFIGURATION_CHANGE_COMMAND_DN_ModeOfChannelSet3 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x13, 264, (Destin->ModeOfChannelSet3))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet4
	------------------------------------------------------*/
	/* Detect IEI tag 0x14 */
	ED_EXPECT_OPTIONAL_IE (0x14,  8, 266, 4, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x14) {
		SETPRESENT_c_CONFIGURATION_CHANGE_COMMAND_DN_ModeOfChannelSet4 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ChannelMode (Buffer, CurrOfs, Destin->ModeOfChannelSet4, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:267> Error decoding subfield ModeOfChannelSet4\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CONFIGURATION_CHANGE_COMMAND_DN_ModeOfChannelSet4 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x14, 267, (Destin->ModeOfChannelSet4))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:268> Message too short decoding subfield ModeOfChannelSet4\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CONFIGURATION_CHANGE_COMMAND_DN_ModeOfChannelSet4 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x14, 267, (Destin->ModeOfChannelSet4))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet5
	------------------------------------------------------*/
	/* Detect IEI tag 0x15 */
	ED_EXPECT_OPTIONAL_IE (0x15,  8, 269, 5, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x15) {
		SETPRESENT_c_CONFIGURATION_CHANGE_COMMAND_DN_ModeOfChannelSet5 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ChannelMode (Buffer, CurrOfs, Destin->ModeOfChannelSet5, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:270> Error decoding subfield ModeOfChannelSet5\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CONFIGURATION_CHANGE_COMMAND_DN_ModeOfChannelSet5 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x15, 270, (Destin->ModeOfChannelSet5))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:271> Message too short decoding subfield ModeOfChannelSet5\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CONFIGURATION_CHANGE_COMMAND_DN_ModeOfChannelSet5 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x15, 270, (Destin->ModeOfChannelSet5))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet6
	------------------------------------------------------*/
	/* Detect IEI tag 0x16 */
	ED_EXPECT_OPTIONAL_IE (0x16,  8, 272, 6, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x16) {
		SETPRESENT_c_CONFIGURATION_CHANGE_COMMAND_DN_ModeOfChannelSet6 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ChannelMode (Buffer, CurrOfs, Destin->ModeOfChannelSet6, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:273> Error decoding subfield ModeOfChannelSet6\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CONFIGURATION_CHANGE_COMMAND_DN_ModeOfChannelSet6 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x16, 273, (Destin->ModeOfChannelSet6))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:274> Message too short decoding subfield ModeOfChannelSet6\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CONFIGURATION_CHANGE_COMMAND_DN_ModeOfChannelSet6 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x16, 273, (Destin->ModeOfChannelSet6))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet7
	------------------------------------------------------*/
	/* Detect IEI tag 0x17 */
	ED_EXPECT_OPTIONAL_IE (0x17,  8, 275, 7, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x17) {
		SETPRESENT_c_CONFIGURATION_CHANGE_COMMAND_DN_ModeOfChannelSet7 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ChannelMode (Buffer, CurrOfs, Destin->ModeOfChannelSet7, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:276> Error decoding subfield ModeOfChannelSet7\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CONFIGURATION_CHANGE_COMMAND_DN_ModeOfChannelSet7 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x17, 276, (Destin->ModeOfChannelSet7))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:277> Message too short decoding subfield ModeOfChannelSet7\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CONFIGURATION_CHANGE_COMMAND_DN_ModeOfChannelSet7 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x17, 276, (Destin->ModeOfChannelSet7))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet8
	------------------------------------------------------*/
	/* Detect IEI tag 0x18 */
	ED_EXPECT_OPTIONAL_IE (0x18,  8, 278, 8, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x18) {
		SETPRESENT_c_CONFIGURATION_CHANGE_COMMAND_DN_ModeOfChannelSet8 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ChannelMode (Buffer, CurrOfs, Destin->ModeOfChannelSet8, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:279> Error decoding subfield ModeOfChannelSet8\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_CONFIGURATION_CHANGE_COMMAND_DN_ModeOfChannelSet8 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x18, 279, (Destin->ModeOfChannelSet8))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:280> Message too short decoding subfield ModeOfChannelSet8\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_CONFIGURATION_CHANGE_COMMAND_DN_ModeOfChannelSet8 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x18, 279, (Destin->ModeOfChannelSet8))
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE DTM_ASSIGNMENT_COMMAND_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_DTM_ASSIGNMENT_COMMAND_DN (char* Buffer, ED_EXLONG BitOffset, const c_DTM_ASSIGNMENT_COMMAND_DN* Source, int Mode)
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
	
	
	/* Code for CsPowerCommand */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->CsPowerCommand> DOT=<.> */
		Len = ENCODE_c_PowerCommand (Buffer, CurrOfs, (&(Source->CsPowerCommand)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:281> Error encoding subfield CsPowerCommand\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for DescOfTheCsCh */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->DescOfTheCsCh> DOT=<.> */
		Len = ENCODE_c_TChDesc (Buffer, CurrOfs, (&(Source->DescOfTheCsCh)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:282> Error encoding subfield DescOfTheCsCh\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for GprsBroadcastInfo */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->GprsBroadcastInfo> DOT=<.> */
		Len = ENCODE_c_GPRSBCastInfo (Buffer, CurrOfs+8, (&(Source->GprsBroadcastInfo)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:283> Error encoding subfield GprsBroadcastInfo\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for CellChDesc */
	{
		if (Source->CellChDesc_Present) {
			/* Append to buffer IEI tag 0x10 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x10), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->CellChDesc> DOT=<->> */
			Len = ENCODE_c_CellChannel (Buffer, CurrOfs, Source->CellChDesc);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:284> Error encoding subfield CellChDesc\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for ChMode */
	{
		if (Source->ChMode_Present) {
			/* Append to buffer IEI tag 0x11 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x11), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ChMode> DOT=<->> */
			Len = ENCODE_c_ChannelMode (Buffer, CurrOfs, Source->ChMode);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:285> Error encoding subfield ChMode\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for FrequencyList */
	{
		int TLV_Base = CurrOfs;
		if (Source->FrequencyList_Present) {
			/* Append to buffer IEI tag 0x12 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x12), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->FrequencyList> DOT=<->> */
			Len = ENCODE_c_CellChannel (Buffer, CurrOfs+8, Source->FrequencyList);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:286> Error encoding subfield FrequencyList\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for MobileAllocation */
	{
		int TLV_Base = CurrOfs;
		if (Source->MobileAllocation_Present) {
			/* Append to buffer IEI tag 0x13 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x13), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->MobileAllocation> DOT=<->> */
			Len = ENCODE_c_MobileAllocation (Buffer, CurrOfs+8, Source->MobileAllocation);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:287> Error encoding subfield MobileAllocation\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for TbfStartingTime */
	{
		if (Source->TbfStartingTime_Present) {
			/* Append to buffer IEI tag 0x14 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x14), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->TbfStartingTime> DOT=<->> */
			Len = ENCODE_c_StartingTime (Buffer, CurrOfs, Source->TbfStartingTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:288> Error encoding subfield TbfStartingTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for DescOfTheUplinkPktChAss */
	{
		int TLV_Base = CurrOfs;
		if (Source->DescOfTheUplinkPktChAss_Present) {
			/* Append to buffer IEI tag 0x15 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x15), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->DescOfTheUplinkPktChAss> DOT=<->> */
			Len = ENCODE_c_RRPacketUplinkAssignment (Buffer, CurrOfs+8, Source->DescOfTheUplinkPktChAss);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:289> Error encoding subfield DescOfTheUplinkPktChAss\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for DescOfTheDownlinkPktChAss */
	{
		int TLV_Base = CurrOfs;
		if (Source->DescOfTheDownlinkPktChAss_Present) {
			/* Append to buffer IEI tag 0x16 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x16), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->DescOfTheDownlinkPktChAss> DOT=<->> */
			Len = ENCODE_c_RRPktDownlinkAssi (Buffer, CurrOfs+8, Source->DescOfTheDownlinkPktChAss);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:290> Error encoding subfield DescOfTheDownlinkPktChAss\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for MultiRateconfiguration */
	{
		int TLV_Base = CurrOfs;
		if (Source->MultiRateconfiguration_Present) {
			/* Append to buffer IEI tag 0x17 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x17), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->MultiRateconfiguration> DOT=<->> */
			Len = ENCODE_c_MultirateSpeechCfgIE (Buffer, CurrOfs+8, Source->MultiRateconfiguration);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:291> Error encoding subfield MultiRateconfiguration\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for CipheringModeSetting */
	{
		if (Source->CipheringModeSetting_Present) {
			/* Append to buffer IEI tag 0x09 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x09), 4);
			CurrOfs += 4;
			/* Append to buffer value part DEBUG FIELD=<Source->CipheringModeSetting> DOT=<->> */
			Len = ENCODE_c_CipherModeSetting (Buffer, CurrOfs, Source->CipheringModeSetting);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:292> Error encoding subfield CipheringModeSetting\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for MobileAllocationC2 */
	{
		int TLV_Base = CurrOfs;
		if (Source->MobileAllocationC2_Present) {
			/* Append to buffer IEI tag 0x18 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x18), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->MobileAllocationC2> DOT=<->> */
			Len = ENCODE_c_MobileAllocation (Buffer, CurrOfs+8, Source->MobileAllocationC2);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:293> Error encoding subfield MobileAllocationC2\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for FrequencyListC2 */
	{
		int TLV_Base = CurrOfs;
		if (Source->FrequencyListC2_Present) {
			/* Append to buffer IEI tag 0x19 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x19), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->FrequencyListC2> DOT=<->> */
			Len = ENCODE_c_CellChannel (Buffer, CurrOfs+8, Source->FrequencyListC2);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:294> Error encoding subfield FrequencyListC2\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for DescDownlinkPacketChannelAssigType2 */
	{
		int TLV_Base = CurrOfs;
		if (Source->DescDownlinkPacketChannelAssigType2_Present) {
			/* Append to buffer IEI tag 0x20 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x20), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->DescDownlinkPacketChannelAssigType2> DOT=<->> */
			Len = ENCODE_c_RRPacketDownlinkAssignmentType2 (Buffer, CurrOfs+8, Source->DescDownlinkPacketChannelAssigType2);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:295> Error encoding subfield DescDownlinkPacketChannelAssigType2\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for ChannelDescriptionC2 */
	{
		if (Source->ChannelDescriptionC2_Present) {
			/* Append to buffer IEI tag 0x21 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x21), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ChannelDescriptionC2> DOT=<->> */
			Len = ENCODE_c_TChDesc3 (Buffer, CurrOfs, Source->ChannelDescriptionC2);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:296> Error encoding subfield ChannelDescriptionC2\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
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
				ED_SIGNAL_ERROR ("<ERRID:297> Error encoding subfield ExtendedTSCSet\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE DTM_ASSIGNMENT_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_DTM_ASSIGNMENT_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DTM_ASSIGNMENT_COMMAND_DN* ED_CONST Source))
{
	return L3_ENCODE_c_DTM_ASSIGNMENT_COMMAND_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE DTM_ASSIGNMENT_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_DTM_ASSIGNMENT_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DTM_ASSIGNMENT_COMMAND_DN* ED_CONST Source))
{
	return L3_ENCODE_c_DTM_ASSIGNMENT_COMMAND_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE DTM_ASSIGNMENT_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_DTM_ASSIGNMENT_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DTM_ASSIGNMENT_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_DTM_ASSIGNMENT_COMMAND_DN (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE DTM_ASSIGNMENT_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_DTM_ASSIGNMENT_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DTM_ASSIGNMENT_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length))
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
		{16, 255, ED_SKIPLIST_OPTIONAL},
		{17, 255, ED_SKIPLIST_OPTIONAL},
		{18, 255, ED_SKIPLIST_OPTIONAL},
		{19, 255, ED_SKIPLIST_OPTIONAL},
		{20, 255, ED_SKIPLIST_OPTIONAL},
		{21, 255, ED_SKIPLIST_OPTIONAL},
		{22, 255, ED_SKIPLIST_OPTIONAL},
		{23, 255, ED_SKIPLIST_OPTIONAL},
		{144, 240, ED_SKIPLIST_OPTIONAL},
		{24, 255, ED_SKIPLIST_OPTIONAL},
		{25, 255, ED_SKIPLIST_OPTIONAL},
		{32, 255, ED_SKIPLIST_OPTIONAL},
		{33, 255, ED_SKIPLIST_OPTIONAL},
		{109, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	ED_WARNING_REMOVER (TLVSkipItems);
	
	/*----------------------------------------------------- 
		Code for IE CsPowerCommand
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_PowerCommand (Buffer, CurrOfs, (&(Destin->CsPowerCommand)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:298> Error decoding subfield CsPowerCommand\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 298, (Destin->CsPowerCommand))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:299> Message too short decoding subfield CsPowerCommand\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 298, (Destin->CsPowerCommand))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE DescOfTheCsCh
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, (&(Destin->DescOfTheCsCh)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:300> Error decoding subfield DescOfTheCsCh\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 300, (Destin->DescOfTheCsCh))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:301> Message too short decoding subfield DescOfTheCsCh\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 300, (Destin->DescOfTheCsCh))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE GprsBroadcastInfo
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if ((Len < 48) || (Len > 4792)) {
		ED_SIGNAL_ERROR ("<ERRID:302> Size error decoding IE GprsBroadcastInfo\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 302, (Destin->GprsBroadcastInfo))
	} 
#endif
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_GPRSBCastInfo (Buffer, CurrOfs, (&(Destin->GprsBroadcastInfo)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:303> Error decoding subfield GprsBroadcastInfo\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 303, (Destin->GprsBroadcastInfo))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:304> Message too short decoding subfield GprsBroadcastInfo\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 303, (Destin->GprsBroadcastInfo))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE CellChDesc
	------------------------------------------------------*/
	/* Detect IEI tag 0x10 */
	ED_EXPECT_OPTIONAL_IE (0x10,  8, 305, 3, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x10) {
		SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_CellChDesc (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 128;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, Destin->CellChDesc, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:306> Error decoding subfield CellChDesc\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_CellChDesc (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x10, 306, (Destin->CellChDesc))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:307> Message too short decoding subfield CellChDesc\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_CellChDesc (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x10, 306, (Destin->CellChDesc))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ChMode
	------------------------------------------------------*/
	/* Detect IEI tag 0x11 */
	ED_EXPECT_OPTIONAL_IE (0x11,  8, 308, 4, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x11) {
		SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_ChMode (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ChannelMode (Buffer, CurrOfs, Destin->ChMode, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:309> Error decoding subfield ChMode\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_ChMode (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x11, 309, (Destin->ChMode))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:310> Message too short decoding subfield ChMode\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_ChMode (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x11, 309, (Destin->ChMode))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE FrequencyList
	------------------------------------------------------*/
	/* Detect IEI tag 0x12 */
	ED_EXPECT_OPTIONAL_IE (0x12,  8, 311, 5, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x12) {
		SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_FrequencyList (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 16) || (Len > 1040)) {
			ED_SIGNAL_ERROR ("<ERRID:312> Size error decoding IE FrequencyList\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_FrequencyList (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x12, 312, (Destin->FrequencyList))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, Destin->FrequencyList, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:313> Error decoding subfield FrequencyList\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_FrequencyList (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x12, 313, (Destin->FrequencyList))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:314> Message too short decoding subfield FrequencyList\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_FrequencyList (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x12, 313, (Destin->FrequencyList))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE MobileAllocation
	------------------------------------------------------*/
	/* Detect IEI tag 0x13 */
	ED_EXPECT_OPTIONAL_IE (0x13,  8, 315, 6, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x13) {
		SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_MobileAllocation (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 64)) {
			ED_SIGNAL_ERROR ("<ERRID:316> Size error decoding IE MobileAllocation\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_MobileAllocation (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x13, 316, (Destin->MobileAllocation))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_MobileAllocation (Buffer, CurrOfs, Destin->MobileAllocation, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:317> Error decoding subfield MobileAllocation\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_MobileAllocation (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x13, 317, (Destin->MobileAllocation))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:318> Message too short decoding subfield MobileAllocation\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_MobileAllocation (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x13, 317, (Destin->MobileAllocation))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE TbfStartingTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x14 */
	ED_EXPECT_OPTIONAL_IE (0x14,  8, 319, 7, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x14) {
		SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_TbfStartingTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 16;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_StartingTime (Buffer, CurrOfs, Destin->TbfStartingTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:320> Error decoding subfield TbfStartingTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_TbfStartingTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x14, 320, (Destin->TbfStartingTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:321> Message too short decoding subfield TbfStartingTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_TbfStartingTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x14, 320, (Destin->TbfStartingTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE DescOfTheUplinkPktChAss
	------------------------------------------------------*/
	/* Detect IEI tag 0x15 */
	ED_EXPECT_OPTIONAL_IE (0x15,  8, 322, 8, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x15) {
		SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_DescOfTheUplinkPktChAss (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 4784)) {
			ED_SIGNAL_ERROR ("<ERRID:323> Size error decoding IE DescOfTheUplinkPktChAss\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_DescOfTheUplinkPktChAss (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x15, 323, (Destin->DescOfTheUplinkPktChAss))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_RRPacketUplinkAssignment (Buffer, CurrOfs, Destin->DescOfTheUplinkPktChAss, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:324> Error decoding subfield DescOfTheUplinkPktChAss\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_DescOfTheUplinkPktChAss (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x15, 324, (Destin->DescOfTheUplinkPktChAss))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:325> Message too short decoding subfield DescOfTheUplinkPktChAss\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_DescOfTheUplinkPktChAss (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x15, 324, (Destin->DescOfTheUplinkPktChAss))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE DescOfTheDownlinkPktChAss
	------------------------------------------------------*/
	/* Detect IEI tag 0x16 */
	ED_EXPECT_OPTIONAL_IE (0x16,  8, 326, 9, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x16) {
		SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_DescOfTheDownlinkPktChAss (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 4784)) {
			ED_SIGNAL_ERROR ("<ERRID:327> Size error decoding IE DescOfTheDownlinkPktChAss\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_DescOfTheDownlinkPktChAss (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x16, 327, (Destin->DescOfTheDownlinkPktChAss))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_RRPktDownlinkAssi (Buffer, CurrOfs, Destin->DescOfTheDownlinkPktChAss, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:328> Error decoding subfield DescOfTheDownlinkPktChAss\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_DescOfTheDownlinkPktChAss (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x16, 328, (Destin->DescOfTheDownlinkPktChAss))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:329> Message too short decoding subfield DescOfTheDownlinkPktChAss\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_DescOfTheDownlinkPktChAss (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x16, 328, (Destin->DescOfTheDownlinkPktChAss))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE MultiRateconfiguration
	------------------------------------------------------*/
	/* Detect IEI tag 0x17 */
	ED_EXPECT_OPTIONAL_IE (0x17,  8, 330, 10, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x17) {
		SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_MultiRateconfiguration (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 16) || (Len > 48)) {
			ED_SIGNAL_ERROR ("<ERRID:331> Size error decoding IE MultiRateconfiguration\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_MultiRateconfiguration (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x17, 331, (Destin->MultiRateconfiguration))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_MultirateSpeechCfgIE (Buffer, CurrOfs, Destin->MultiRateconfiguration, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:332> Error decoding subfield MultiRateconfiguration\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_MultiRateconfiguration (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x17, 332, (Destin->MultiRateconfiguration))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:333> Message too short decoding subfield MultiRateconfiguration\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_MultiRateconfiguration (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x17, 332, (Destin->MultiRateconfiguration))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE CipheringModeSetting
	------------------------------------------------------*/
	/* Detect IEI tag 0x09 */
	ED_EXPECT_OPTIONAL_IE (0x09,  4, 334, 11, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 4); */
	
	/* This is an optional field */
	if (Tag == 0x09) {
		SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_CipheringModeSetting (Destin, ED_TRUE);
		CurrOfs += 4;
		Len = 4;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_CipherModeSetting (Buffer, CurrOfs, Destin->CipheringModeSetting, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:335> Error decoding subfield CipheringModeSetting\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_CipheringModeSetting (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x09, 335, (Destin->CipheringModeSetting))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:336> Message too short decoding subfield CipheringModeSetting\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_CipheringModeSetting (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x09, 335, (Destin->CipheringModeSetting))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE MobileAllocationC2
	------------------------------------------------------*/
	/* Detect IEI tag 0x18 */
	ED_EXPECT_OPTIONAL_IE (0x18,  8, 337, 12, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x18) {
		SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_MobileAllocationC2 (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 64)) {
			ED_SIGNAL_ERROR ("<ERRID:338> Size error decoding IE MobileAllocationC2\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_MobileAllocationC2 (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x18, 338, (Destin->MobileAllocationC2))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_MobileAllocation (Buffer, CurrOfs, Destin->MobileAllocationC2, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:339> Error decoding subfield MobileAllocationC2\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_MobileAllocationC2 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x18, 339, (Destin->MobileAllocationC2))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:340> Message too short decoding subfield MobileAllocationC2\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_MobileAllocationC2 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x18, 339, (Destin->MobileAllocationC2))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE FrequencyListC2
	------------------------------------------------------*/
	/* Detect IEI tag 0x19 */
	ED_EXPECT_OPTIONAL_IE (0x19,  8, 341, 13, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x19) {
		SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_FrequencyListC2 (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 16) || (Len > 1040)) {
			ED_SIGNAL_ERROR ("<ERRID:342> Size error decoding IE FrequencyListC2\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_FrequencyListC2 (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x19, 342, (Destin->FrequencyListC2))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, Destin->FrequencyListC2, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:343> Error decoding subfield FrequencyListC2\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_FrequencyListC2 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x19, 343, (Destin->FrequencyListC2))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:344> Message too short decoding subfield FrequencyListC2\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_FrequencyListC2 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x19, 343, (Destin->FrequencyListC2))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE DescDownlinkPacketChannelAssigType2
	------------------------------------------------------*/
	/* Detect IEI tag 0x20 */
	ED_EXPECT_OPTIONAL_IE (0x20,  8, 345, 14, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x20) {
		SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_DescDownlinkPacketChannelAssigType2 (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 4784)) {
			ED_SIGNAL_ERROR ("<ERRID:346> Size error decoding IE DescDownlinkPacketChannelAssigType2\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_DescDownlinkPacketChannelAssigType2 (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x20, 346, (Destin->DescDownlinkPacketChannelAssigType2))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_RRPacketDownlinkAssignmentType2 (Buffer, CurrOfs, Destin->DescDownlinkPacketChannelAssigType2, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:347> Error decoding subfield DescDownlinkPacketChannelAssigType2\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_DescDownlinkPacketChannelAssigType2 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x20, 347, (Destin->DescDownlinkPacketChannelAssigType2))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:348> Message too short decoding subfield DescDownlinkPacketChannelAssigType2\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_DescDownlinkPacketChannelAssigType2 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x20, 347, (Destin->DescDownlinkPacketChannelAssigType2))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ChannelDescriptionC2
	------------------------------------------------------*/
	/* Detect IEI tag 0x21 */
	ED_EXPECT_OPTIONAL_IE (0x21,  8, 349, 15, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x21) {
		SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_ChannelDescriptionC2 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 16;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_TChDesc3 (Buffer, CurrOfs, Destin->ChannelDescriptionC2, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:350> Error decoding subfield ChannelDescriptionC2\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_ChannelDescriptionC2 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x21, 350, (Destin->ChannelDescriptionC2))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:351> Message too short decoding subfield ChannelDescriptionC2\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_ChannelDescriptionC2 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x21, 350, (Destin->ChannelDescriptionC2))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ExtendedTSCSet
	------------------------------------------------------*/
	/* Detect IEI tag 0x6D */
	ED_EXPECT_OPTIONAL_IE (0x6D,  8, 352, 16, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x6D) {
		SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_ExtendedTSCSet (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ExtendedTSCSet (Buffer, CurrOfs, Destin->ExtendedTSCSet, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:353> Error decoding subfield ExtendedTSCSet\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_ExtendedTSCSet (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x6D, 353, (Destin->ExtendedTSCSet))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:354> Message too short decoding subfield ExtendedTSCSet\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_DTM_ASSIGNMENT_COMMAND_DN_ExtendedTSCSet (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x6D, 353, (Destin->ExtendedTSCSet))
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE DTM_INFORMATION_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_DTM_INFORMATION_DN (char* Buffer, ED_EXLONG BitOffset, const c_DTM_INFORMATION_DN* Source, int Mode)
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
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 77, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for RouteingAreaId */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->RouteingAreaId> DOT=<.> */
		Len = ENCODE_c_RoutingAreaIdentity (Buffer, CurrOfs, (&(Source->RouteingAreaId)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:355> Error encoding subfield RouteingAreaId\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for DtmInfoRestOctets */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->DtmInfoRestOctets> DOT=<.> */
		Len = ENCODE_c_DTMInfoRestOctets (Buffer, CurrOfs+8, (&(Source->DtmInfoRestOctets)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:356> Error encoding subfield DtmInfoRestOctets\n");
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
	ENCODING FUNCTION FOR GSM-L3 MESSAGE DTM_INFORMATION_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_DTM_INFORMATION_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DTM_INFORMATION_DN* ED_CONST Source))
{
	return L3_ENCODE_c_DTM_INFORMATION_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE DTM_INFORMATION_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_DTM_INFORMATION_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DTM_INFORMATION_DN* ED_CONST Source))
{
	return L3_ENCODE_c_DTM_INFORMATION_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE DTM_INFORMATION_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_DTM_INFORMATION_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DTM_INFORMATION_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_DTM_INFORMATION_DN (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE DTM_INFORMATION_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_DTM_INFORMATION_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DTM_INFORMATION_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE RouteingAreaId
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 48;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RoutingAreaIdentity (Buffer, CurrOfs, (&(Destin->RouteingAreaId)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:357> Error decoding subfield RouteingAreaId\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 357, (Destin->RouteingAreaId))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:358> Message too short decoding subfield RouteingAreaId\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 357, (Destin->RouteingAreaId))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE DtmInfoRestOctets
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (Len != 8) {
		ED_SIGNAL_ERROR ("<ERRID:359> Size error decoding IE DtmInfoRestOctets\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 359, (Destin->DtmInfoRestOctets))
	} 
#endif
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_DTMInfoRestOctets (Buffer, CurrOfs, (&(Destin->DtmInfoRestOctets)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:360> Error decoding subfield DtmInfoRestOctets\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 360, (Destin->DtmInfoRestOctets))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:361> Message too short decoding subfield DtmInfoRestOctets\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 360, (Destin->DtmInfoRestOctets))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE DTM_REJECT_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_DTM_REJECT_DN (char* Buffer, ED_EXLONG BitOffset, const c_DTM_REJECT_DN* Source, int Mode)
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
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 73, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for DtmWaitIndication */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->DtmWaitIndication> DOT=<.> */
		EDIntToBits (Buffer, (CurrOfs), (int)(Source->DtmWaitIndication), 8);
		Len = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:362> Error encoding subfield DtmWaitIndication\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE DTM_REJECT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_DTM_REJECT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DTM_REJECT_DN* ED_CONST Source))
{
	return L3_ENCODE_c_DTM_REJECT_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE DTM_REJECT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_DTM_REJECT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DTM_REJECT_DN* ED_CONST Source))
{
	return L3_ENCODE_c_DTM_REJECT_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE DTM_REJECT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_DTM_REJECT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DTM_REJECT_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_DTM_REJECT_DN (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE DTM_REJECT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_DTM_REJECT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DTM_REJECT_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE DtmWaitIndication
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	Destin->DtmWaitIndication = (ED_OCTET)EDBitsToInt (Buffer, (CurrOfs), 8);
	/* LOCATOR SETTINGS LOCINT */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-51771=EDCore::TDMInteger) */Destin->DtmWaitIndication___LOCATOR), CurrOfs, 8);
	RetLen = 8;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:363> Error decoding subfield DtmWaitIndication\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 363, (Destin->DtmWaitIndication))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:364> Message too short decoding subfield DtmWaitIndication\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 363, (Destin->DtmWaitIndication))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE FREQUENCY_REDEFINITION_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_FREQUENCY_REDEFINITION_DN (char* Buffer, ED_EXLONG BitOffset, const c_FREQUENCY_REDEFINITION_DN* Source, int Mode)
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
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 20, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for ChannelDescription */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ChannelDescription> DOT=<.> */
		Len = ENCODE_c_TChDesc (Buffer, CurrOfs, (&(Source->ChannelDescription)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:365> Error encoding subfield ChannelDescription\n");
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
			ED_SIGNAL_ERROR ("<ERRID:366> Error encoding subfield MobileAllocation\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for StartingTime */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->StartingTime> DOT=<.> */
		Len = ENCODE_c_StartingTime (Buffer, CurrOfs, (&(Source->StartingTime)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:367> Error encoding subfield StartingTime\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for CellChannelDescription */
	{
		if (Source->CellChannelDescription_Present) {
			/* Append to buffer IEI tag 0x62 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x62), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->CellChannelDescription> DOT=<->> */
			Len = ENCODE_c_CellChannel (Buffer, CurrOfs, Source->CellChannelDescription);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:368> Error encoding subfield CellChannelDescription\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for CarrierIndication */
	{
		if (Source->CarrierIndication_Present) {
			/* Append to buffer IEI tag 0x09 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x09), 4);
			CurrOfs += 4;
			/* Append to buffer value part DEBUG FIELD=<Source->CarrierIndication> DOT=<.> */
			EDIntToBits (Buffer, (CurrOfs), (int)(Source->CarrierIndication), 4);
			Len = 4;
			
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:369> Error encoding subfield CarrierIndication\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for MobileAllocationC2 */
	{
		int TLV_Base = CurrOfs;
		if (Source->MobileAllocationC2_Present) {
			/* Append to buffer IEI tag 0x11 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x11), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->MobileAllocationC2> DOT=<->> */
			Len = ENCODE_c_MobileAllocation (Buffer, CurrOfs+8, Source->MobileAllocationC2);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:370> Error encoding subfield MobileAllocationC2\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for ChannelDescriptionC2 */
	{
		if (Source->ChannelDescriptionC2_Present) {
			/* Append to buffer IEI tag 0x12 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x12), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ChannelDescriptionC2> DOT=<->> */
			Len = ENCODE_c_TChDesc3 (Buffer, CurrOfs, Source->ChannelDescriptionC2);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:371> Error encoding subfield ChannelDescriptionC2\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
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
				ED_SIGNAL_ERROR ("<ERRID:372> Error encoding subfield ExtendedTSCSet\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE FREQUENCY_REDEFINITION_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FREQUENCY_REDEFINITION_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FREQUENCY_REDEFINITION_DN* ED_CONST Source))
{
	return L3_ENCODE_c_FREQUENCY_REDEFINITION_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE FREQUENCY_REDEFINITION_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_FREQUENCY_REDEFINITION_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FREQUENCY_REDEFINITION_DN* ED_CONST Source))
{
	return L3_ENCODE_c_FREQUENCY_REDEFINITION_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE FREQUENCY_REDEFINITION_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FREQUENCY_REDEFINITION_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FREQUENCY_REDEFINITION_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_FREQUENCY_REDEFINITION_DN (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE FREQUENCY_REDEFINITION_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_FREQUENCY_REDEFINITION_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FREQUENCY_REDEFINITION_DN* ED_CONST Destin, ED_EXLONG Length))
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
		{98, 255, ED_SKIPLIST_OPTIONAL},
		{144, 240, ED_SKIPLIST_OPTIONAL},
		{17, 255, ED_SKIPLIST_OPTIONAL},
		{18, 255, ED_SKIPLIST_OPTIONAL},
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
	RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, (&(Destin->ChannelDescription)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:373> Error decoding subfield ChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 373, (Destin->ChannelDescription))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:374> Message too short decoding subfield ChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 373, (Destin->ChannelDescription))
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
		ED_SIGNAL_ERROR ("<ERRID:375> Size error decoding IE MobileAllocation\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 375, (Destin->MobileAllocation))
	} 
#endif
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_MobileAllocation (Buffer, CurrOfs, (&(Destin->MobileAllocation)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:376> Error decoding subfield MobileAllocation\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 376, (Destin->MobileAllocation))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:377> Message too short decoding subfield MobileAllocation\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 376, (Destin->MobileAllocation))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE StartingTime
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 16;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_StartingTime (Buffer, CurrOfs, (&(Destin->StartingTime)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:378> Error decoding subfield StartingTime\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 378, (Destin->StartingTime))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:379> Message too short decoding subfield StartingTime\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 378, (Destin->StartingTime))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE CellChannelDescription
	------------------------------------------------------*/
	/* Detect IEI tag 0x62 */
	ED_EXPECT_OPTIONAL_IE (0x62,  8, 380, 3, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x62) {
		SETPRESENT_c_FREQUENCY_REDEFINITION_DN_CellChannelDescription (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 128;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, Destin->CellChannelDescription, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:381> Error decoding subfield CellChannelDescription\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_FREQUENCY_REDEFINITION_DN_CellChannelDescription (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x62, 381, (Destin->CellChannelDescription))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:382> Message too short decoding subfield CellChannelDescription\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_FREQUENCY_REDEFINITION_DN_CellChannelDescription (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x62, 381, (Destin->CellChannelDescription))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE CarrierIndication
	------------------------------------------------------*/
	/* Detect IEI tag 0x09 */
	ED_EXPECT_OPTIONAL_IE (0x09,  4, 383, 4, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 4); */
	
	/* This is an optional field */
	if (Tag == 0x09) {
		SETPRESENT_c_FREQUENCY_REDEFINITION_DN_CarrierIndication (Destin, ED_TRUE);
		CurrOfs += 4;
		Len = 4;
		/* Read value part LOCATOR_16 */
		Destin->CarrierIndication = (unsigned char)EDBitsToInt (Buffer, CurrOfs, 4);
		/* LOCATOR SETTINGS LOCOCTET */;
		ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMOctet'-51782=EDCore::TDMOctet) */Destin->CarrierIndication___LOCATOR), CurrOfs, 4);
		RetLen = 4;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:384> Error decoding subfield CarrierIndication\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_FREQUENCY_REDEFINITION_DN_CarrierIndication (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x09, 384, (Destin->CarrierIndication))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:385> Message too short decoding subfield CarrierIndication\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_FREQUENCY_REDEFINITION_DN_CarrierIndication (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x09, 384, (Destin->CarrierIndication))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE MobileAllocationC2
	------------------------------------------------------*/
	/* Detect IEI tag 0x11 */
	ED_EXPECT_OPTIONAL_IE (0x11,  8, 386, 5, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x11) {
		SETPRESENT_c_FREQUENCY_REDEFINITION_DN_MobileAllocationC2 (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 64)) {
			ED_SIGNAL_ERROR ("<ERRID:387> Size error decoding IE MobileAllocationC2\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_FREQUENCY_REDEFINITION_DN_MobileAllocationC2 (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x11, 387, (Destin->MobileAllocationC2))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_MobileAllocation (Buffer, CurrOfs, Destin->MobileAllocationC2, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:388> Error decoding subfield MobileAllocationC2\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_FREQUENCY_REDEFINITION_DN_MobileAllocationC2 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x11, 388, (Destin->MobileAllocationC2))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:389> Message too short decoding subfield MobileAllocationC2\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_FREQUENCY_REDEFINITION_DN_MobileAllocationC2 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x11, 388, (Destin->MobileAllocationC2))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ChannelDescriptionC2
	------------------------------------------------------*/
	/* Detect IEI tag 0x12 */
	ED_EXPECT_OPTIONAL_IE (0x12,  8, 390, 6, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x12) {
		SETPRESENT_c_FREQUENCY_REDEFINITION_DN_ChannelDescriptionC2 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 16;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_TChDesc3 (Buffer, CurrOfs, Destin->ChannelDescriptionC2, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:391> Error decoding subfield ChannelDescriptionC2\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_FREQUENCY_REDEFINITION_DN_ChannelDescriptionC2 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x12, 391, (Destin->ChannelDescriptionC2))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:392> Message too short decoding subfield ChannelDescriptionC2\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_FREQUENCY_REDEFINITION_DN_ChannelDescriptionC2 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x12, 391, (Destin->ChannelDescriptionC2))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ExtendedTSCSet
	------------------------------------------------------*/
	/* Detect IEI tag 0x6D */
	ED_EXPECT_OPTIONAL_IE (0x6D,  8, 393, 7, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x6D) {
		SETPRESENT_c_FREQUENCY_REDEFINITION_DN_ExtendedTSCSet (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ExtendedTSCSet (Buffer, CurrOfs, Destin->ExtendedTSCSet, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:394> Error decoding subfield ExtendedTSCSet\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_FREQUENCY_REDEFINITION_DN_ExtendedTSCSet (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x6D, 394, (Destin->ExtendedTSCSet))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:395> Message too short decoding subfield ExtendedTSCSet\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_FREQUENCY_REDEFINITION_DN_ExtendedTSCSet (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x6D, 394, (Destin->ExtendedTSCSet))
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE PDCH_ASSIGNMENT_COMMAND_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_PDCH_ASSIGNMENT_COMMAND_DN (char* Buffer, ED_EXLONG BitOffset, const c_PDCH_ASSIGNMENT_COMMAND_DN* Source, int Mode)
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
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 35, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for DescriptionOfTheChannelAfterTime */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->DescriptionOfTheChannelAfterTime> DOT=<.> */
		Len = ENCODE_c_TChDesc (Buffer, CurrOfs, (&(Source->DescriptionOfTheChannelAfterTime)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:396> Error encoding subfield DescriptionOfTheChannelAfterTime\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for CellChannelDescription */
	{
		if (Source->CellChannelDescription_Present) {
			/* Append to buffer IEI tag 0x62 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x62), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->CellChannelDescription> DOT=<->> */
			Len = ENCODE_c_CellChannel (Buffer, CurrOfs, Source->CellChannelDescription);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:397> Error encoding subfield CellChannelDescription\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for FrequencyListAfterTime */
	{
		int TLV_Base = CurrOfs;
		if (Source->FrequencyListAfterTime_Present) {
			/* Append to buffer IEI tag 0x05 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x05), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->FrequencyListAfterTime> DOT=<->> */
			Len = ENCODE_c_CellChannel (Buffer, CurrOfs+8, Source->FrequencyListAfterTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:398> Error encoding subfield FrequencyListAfterTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for MobileAllocationAfterTime */
	{
		int TLV_Base = CurrOfs;
		if (Source->MobileAllocationAfterTime_Present) {
			/* Append to buffer IEI tag 0x72 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x72), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->MobileAllocationAfterTime> DOT=<->> */
			Len = ENCODE_c_MobileAllocation (Buffer, CurrOfs+8, Source->MobileAllocationAfterTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:399> Error encoding subfield MobileAllocationAfterTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
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
				ED_SIGNAL_ERROR ("<ERRID:400> Error encoding subfield StartingTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for FrequencyListBeforeTime */
	{
		int TLV_Base = CurrOfs;
		if (Source->FrequencyListBeforeTime_Present) {
			/* Append to buffer IEI tag 0x19 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x19), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->FrequencyListBeforeTime> DOT=<->> */
			Len = ENCODE_c_CellChannel (Buffer, CurrOfs+8, Source->FrequencyListBeforeTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:401> Error encoding subfield FrequencyListBeforeTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for DescriptionOfTheChannelBeforeTime */
	{
		if (Source->DescriptionOfTheChannelBeforeTime_Present) {
			/* Append to buffer IEI tag 0x1C */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x1C), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->DescriptionOfTheChannelBeforeTime> DOT=<->> */
			Len = ENCODE_c_TChDesc (Buffer, CurrOfs, Source->DescriptionOfTheChannelBeforeTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:402> Error encoding subfield DescriptionOfTheChannelBeforeTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for FrequencyChannelSequenceBeforeTime */
	{
		if (Source->FrequencyChannelSequenceBeforeTime_Present) {
			/* Append to buffer IEI tag 0x1E */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x1E), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->FrequencyChannelSequenceBeforeTime> DOT=<->> */
			Len = ENCODE_c_FreqChannelSeq (Buffer, CurrOfs, Source->FrequencyChannelSequenceBeforeTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:403> Error encoding subfield FrequencyChannelSequenceBeforeTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for MobileAllocationBeforeTime */
	{
		int TLV_Base = CurrOfs;
		if (Source->MobileAllocationBeforeTime_Present) {
			/* Append to buffer IEI tag 0x21 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x21), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->MobileAllocationBeforeTime> DOT=<->> */
			Len = ENCODE_c_MobileAllocation (Buffer, CurrOfs+8, Source->MobileAllocationBeforeTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:404> Error encoding subfield MobileAllocationBeforeTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for RrPacketUplinkAssignment */
	{
		int TLV_Base = CurrOfs;
		if (Source->RrPacketUplinkAssignment_Present) {
			/* Append to buffer IEI tag 0x22 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x22), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->RrPacketUplinkAssignment> DOT=<->> */
			Len = ENCODE_c_PacketChannelDescription (Buffer, CurrOfs+8, Source->RrPacketUplinkAssignment);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:405> Error encoding subfield RrPacketUplinkAssignment\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for RrPacketDownlinkAssignment */
	{
		int TLV_Base = CurrOfs;
		if (Source->RrPacketDownlinkAssignment_Present) {
			/* Append to buffer IEI tag 0x23 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x23), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->RrPacketDownlinkAssignment> DOT=<->> */
			Len = ENCODE_c_DedicatedModeOrTBF (Buffer, CurrOfs+8, Source->RrPacketDownlinkAssignment);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:406> Error encoding subfield RrPacketDownlinkAssignment\n");
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
	ENCODING FUNCTION FOR GSM-L3 MESSAGE PDCH_ASSIGNMENT_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PDCH_ASSIGNMENT_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PDCH_ASSIGNMENT_COMMAND_DN* ED_CONST Source))
{
	return L3_ENCODE_c_PDCH_ASSIGNMENT_COMMAND_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE PDCH_ASSIGNMENT_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_PDCH_ASSIGNMENT_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PDCH_ASSIGNMENT_COMMAND_DN* ED_CONST Source))
{
	return L3_ENCODE_c_PDCH_ASSIGNMENT_COMMAND_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PDCH_ASSIGNMENT_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PDCH_ASSIGNMENT_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PDCH_ASSIGNMENT_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_PDCH_ASSIGNMENT_COMMAND_DN (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PDCH_ASSIGNMENT_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_PDCH_ASSIGNMENT_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PDCH_ASSIGNMENT_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length))
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
		{98, 255, ED_SKIPLIST_OPTIONAL},
		{5, 255, ED_SKIPLIST_OPTIONAL},
		{114, 255, ED_SKIPLIST_OPTIONAL},
		{124, 255, ED_SKIPLIST_OPTIONAL},
		{25, 255, ED_SKIPLIST_OPTIONAL},
		{28, 255, ED_SKIPLIST_OPTIONAL},
		{30, 255, ED_SKIPLIST_OPTIONAL},
		{33, 255, ED_SKIPLIST_OPTIONAL},
		{34, 255, ED_SKIPLIST_OPTIONAL},
		{35, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	ED_WARNING_REMOVER (TLVSkipItems);
	
	/*----------------------------------------------------- 
		Code for IE DescriptionOfTheChannelAfterTime
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, (&(Destin->DescriptionOfTheChannelAfterTime)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:407> Error decoding subfield DescriptionOfTheChannelAfterTime\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 407, (Destin->DescriptionOfTheChannelAfterTime))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:408> Message too short decoding subfield DescriptionOfTheChannelAfterTime\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 407, (Destin->DescriptionOfTheChannelAfterTime))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE CellChannelDescription
	------------------------------------------------------*/
	/* Detect IEI tag 0x62 */
	ED_EXPECT_OPTIONAL_IE (0x62,  8, 409, 1, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x62) {
		SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_CellChannelDescription (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 128;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, Destin->CellChannelDescription, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:410> Error decoding subfield CellChannelDescription\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_CellChannelDescription (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x62, 410, (Destin->CellChannelDescription))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:411> Message too short decoding subfield CellChannelDescription\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_CellChannelDescription (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x62, 410, (Destin->CellChannelDescription))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE FrequencyListAfterTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x05 */
	ED_EXPECT_OPTIONAL_IE (0x05,  8, 412, 2, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x05) {
		SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_FrequencyListAfterTime (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 16) || (Len > 1040)) {
			ED_SIGNAL_ERROR ("<ERRID:413> Size error decoding IE FrequencyListAfterTime\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_FrequencyListAfterTime (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x05, 413, (Destin->FrequencyListAfterTime))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, Destin->FrequencyListAfterTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:414> Error decoding subfield FrequencyListAfterTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_FrequencyListAfterTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x05, 414, (Destin->FrequencyListAfterTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:415> Message too short decoding subfield FrequencyListAfterTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_FrequencyListAfterTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x05, 414, (Destin->FrequencyListAfterTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE MobileAllocationAfterTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x72 */
	ED_EXPECT_OPTIONAL_IE (0x72,  8, 416, 3, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x72) {
		SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_MobileAllocationAfterTime (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 64)) {
			ED_SIGNAL_ERROR ("<ERRID:417> Size error decoding IE MobileAllocationAfterTime\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_MobileAllocationAfterTime (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x72, 417, (Destin->MobileAllocationAfterTime))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_MobileAllocation (Buffer, CurrOfs, Destin->MobileAllocationAfterTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:418> Error decoding subfield MobileAllocationAfterTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_MobileAllocationAfterTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x72, 418, (Destin->MobileAllocationAfterTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:419> Message too short decoding subfield MobileAllocationAfterTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_MobileAllocationAfterTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x72, 418, (Destin->MobileAllocationAfterTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE StartingTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x7C */
	ED_EXPECT_OPTIONAL_IE (0x7C,  8, 420, 4, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x7C) {
		SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_StartingTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 16;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_StartingTime (Buffer, CurrOfs, Destin->StartingTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:421> Error decoding subfield StartingTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_StartingTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x7C, 421, (Destin->StartingTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:422> Message too short decoding subfield StartingTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_StartingTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x7C, 421, (Destin->StartingTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE FrequencyListBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x19 */
	ED_EXPECT_OPTIONAL_IE (0x19,  8, 423, 5, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x19) {
		SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_FrequencyListBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 16) || (Len > 1040)) {
			ED_SIGNAL_ERROR ("<ERRID:424> Size error decoding IE FrequencyListBeforeTime\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_FrequencyListBeforeTime (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x19, 424, (Destin->FrequencyListBeforeTime))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, Destin->FrequencyListBeforeTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:425> Error decoding subfield FrequencyListBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_FrequencyListBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x19, 425, (Destin->FrequencyListBeforeTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:426> Message too short decoding subfield FrequencyListBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_FrequencyListBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x19, 425, (Destin->FrequencyListBeforeTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE DescriptionOfTheChannelBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x1C */
	ED_EXPECT_OPTIONAL_IE (0x1C,  8, 427, 6, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x1C) {
		SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_DescriptionOfTheChannelBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 24;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, Destin->DescriptionOfTheChannelBeforeTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:428> Error decoding subfield DescriptionOfTheChannelBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_DescriptionOfTheChannelBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x1C, 428, (Destin->DescriptionOfTheChannelBeforeTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:429> Message too short decoding subfield DescriptionOfTheChannelBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_DescriptionOfTheChannelBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x1C, 428, (Destin->DescriptionOfTheChannelBeforeTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE FrequencyChannelSequenceBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x1E */
	ED_EXPECT_OPTIONAL_IE (0x1E,  8, 430, 7, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x1E) {
		SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_FrequencyChannelSequenceBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 72;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_FreqChannelSeq (Buffer, CurrOfs, Destin->FrequencyChannelSequenceBeforeTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:431> Error decoding subfield FrequencyChannelSequenceBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_FrequencyChannelSequenceBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x1E, 431, (Destin->FrequencyChannelSequenceBeforeTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:432> Message too short decoding subfield FrequencyChannelSequenceBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_FrequencyChannelSequenceBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x1E, 431, (Destin->FrequencyChannelSequenceBeforeTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE MobileAllocationBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x21 */
	ED_EXPECT_OPTIONAL_IE (0x21,  8, 433, 8, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x21) {
		SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_MobileAllocationBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 64)) {
			ED_SIGNAL_ERROR ("<ERRID:434> Size error decoding IE MobileAllocationBeforeTime\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_MobileAllocationBeforeTime (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x21, 434, (Destin->MobileAllocationBeforeTime))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_MobileAllocation (Buffer, CurrOfs, Destin->MobileAllocationBeforeTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:435> Error decoding subfield MobileAllocationBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_MobileAllocationBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x21, 435, (Destin->MobileAllocationBeforeTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:436> Message too short decoding subfield MobileAllocationBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_MobileAllocationBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x21, 435, (Destin->MobileAllocationBeforeTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE RrPacketUplinkAssignment
	------------------------------------------------------*/
	/* Detect IEI tag 0x22 */
	ED_EXPECT_OPTIONAL_IE (0x22,  8, 437, 9, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x22) {
		SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_RrPacketUplinkAssignment (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 4784)) {
			ED_SIGNAL_ERROR ("<ERRID:438> Size error decoding IE RrPacketUplinkAssignment\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_RrPacketUplinkAssignment (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x22, 438, (Destin->RrPacketUplinkAssignment))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_PacketChannelDescription (Buffer, CurrOfs, Destin->RrPacketUplinkAssignment, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:439> Error decoding subfield RrPacketUplinkAssignment\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_RrPacketUplinkAssignment (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x22, 439, (Destin->RrPacketUplinkAssignment))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:440> Message too short decoding subfield RrPacketUplinkAssignment\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_RrPacketUplinkAssignment (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x22, 439, (Destin->RrPacketUplinkAssignment))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE RrPacketDownlinkAssignment
	------------------------------------------------------*/
	/* Detect IEI tag 0x23 */
	ED_EXPECT_OPTIONAL_IE (0x23,  8, 441, 10, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x23) {
		SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_RrPacketDownlinkAssignment (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 4784)) {
			ED_SIGNAL_ERROR ("<ERRID:442> Size error decoding IE RrPacketDownlinkAssignment\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_RrPacketDownlinkAssignment (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x23, 442, (Destin->RrPacketDownlinkAssignment))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_DedicatedModeOrTBF (Buffer, CurrOfs, Destin->RrPacketDownlinkAssignment, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:443> Error decoding subfield RrPacketDownlinkAssignment\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_RrPacketDownlinkAssignment (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x23, 443, (Destin->RrPacketDownlinkAssignment))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:444> Message too short decoding subfield RrPacketDownlinkAssignment\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_PDCH_ASSIGNMENT_COMMAND_DN_RrPacketDownlinkAssignment (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x23, 443, (Destin->RrPacketDownlinkAssignment))
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_COMMAND_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_HANDOVER_COMMAND_DN (char* Buffer, ED_EXLONG BitOffset, const c_HANDOVER_COMMAND_DN* Source, int Mode)
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
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 43, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for CellDescription */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->CellDescription> DOT=<.> */
		Len = ENCODE_c_CellDescription (Buffer, CurrOfs, (&(Source->CellDescription)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:445> Error encoding subfield CellDescription\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for DescriptionOfTheFirstChannelAfterTime */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->DescriptionOfTheFirstChannelAfterTime> DOT=<.> */
		Len = ENCODE_c_TChDesc2 (Buffer, CurrOfs, (&(Source->DescriptionOfTheFirstChannelAfterTime)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:446> Error encoding subfield DescriptionOfTheFirstChannelAfterTime\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for HandoverRef */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->HandoverRef> DOT=<.> */
		EDIntToBits (Buffer, (CurrOfs), (int)(Source->HandoverRef), 8);
		Len = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:447> Error encoding subfield HandoverRef\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for PowerCommandAndAccessType */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->PowerCommandAndAccessType> DOT=<.> */
		Len = ENCODE_c_PowerCommandAndAccessType (Buffer, CurrOfs, (&(Source->PowerCommandAndAccessType)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:448> Error encoding subfield PowerCommandAndAccessType\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for SynchronizationIndication */
	{
		if (Source->SynchronizationIndication_Present) {
			/* Append to buffer IEI tag 0x0D */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x0D), 4);
			CurrOfs += 4;
			/* Append to buffer value part DEBUG FIELD=<Source->SynchronizationIndication> DOT=<->> */
			Len = ENCODE_c_SyncInd (Buffer, CurrOfs, Source->SynchronizationIndication);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:449> Error encoding subfield SynchronizationIndication\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for FrequencyShortListAfterTime */
	{
		if (Source->FrequencyShortListAfterTime_Present) {
			/* Append to buffer IEI tag 0x02 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x02), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->FrequencyShortListAfterTime> DOT=<->> */
			Len = ENCODE_c_CellChannel (Buffer, CurrOfs, Source->FrequencyShortListAfterTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:450> Error encoding subfield FrequencyShortListAfterTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for FrequencyListAfterTime */
	{
		int TLV_Base = CurrOfs;
		if (Source->FrequencyListAfterTime_Present) {
			/* Append to buffer IEI tag 0x05 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x05), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->FrequencyListAfterTime> DOT=<->> */
			Len = ENCODE_c_CellChannel (Buffer, CurrOfs+8, Source->FrequencyListAfterTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:451> Error encoding subfield FrequencyListAfterTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for CellChannelDescription */
	{
		if (Source->CellChannelDescription_Present) {
			/* Append to buffer IEI tag 0x62 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x62), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->CellChannelDescription> DOT=<->> */
			Len = ENCODE_c_CellChannel (Buffer, CurrOfs, Source->CellChannelDescription);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:452> Error encoding subfield CellChannelDescription\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for DescriptionOfTheMultislotCfg */
	{
		int TLV_Base = CurrOfs;
		if (Source->DescriptionOfTheMultislotCfg_Present) {
			/* Append to buffer IEI tag 0x10 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x10), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->DescriptionOfTheMultislotCfg> DOT=<->> */
			EDCopyBits (Buffer, CurrOfs+8, Source->DescriptionOfTheMultislotCfg->value, 0, Source->DescriptionOfTheMultislotCfg->usedBits);
			Len = Source->DescriptionOfTheMultislotCfg->usedBits;
			
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:453> Error encoding subfield DescriptionOfTheMultislotCfg\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for ModeOfTheFirstChannelChannelSet1 */
	{
		if (Source->ModeOfTheFirstChannelChannelSet1_Present) {
			/* Append to buffer IEI tag 0x63 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x63), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ModeOfTheFirstChannelChannelSet1> DOT=<->> */
			Len = ENCODE_c_ChannelMode (Buffer, CurrOfs, Source->ModeOfTheFirstChannelChannelSet1);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:454> Error encoding subfield ModeOfTheFirstChannelChannelSet1\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for ModeOfChannelSet2 */
	{
		if (Source->ModeOfChannelSet2_Present) {
			/* Append to buffer IEI tag 0x11 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x11), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ModeOfChannelSet2> DOT=<->> */
			Len = ENCODE_c_ChannelMode (Buffer, CurrOfs, Source->ModeOfChannelSet2);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:455> Error encoding subfield ModeOfChannelSet2\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for ModeOfChannelSet3 */
	{
		if (Source->ModeOfChannelSet3_Present) {
			/* Append to buffer IEI tag 0x13 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x13), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ModeOfChannelSet3> DOT=<->> */
			Len = ENCODE_c_ChannelMode (Buffer, CurrOfs, Source->ModeOfChannelSet3);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:456> Error encoding subfield ModeOfChannelSet3\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for ModeOfChannelSet4 */
	{
		if (Source->ModeOfChannelSet4_Present) {
			/* Append to buffer IEI tag 0x14 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x14), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ModeOfChannelSet4> DOT=<->> */
			Len = ENCODE_c_ChannelMode (Buffer, CurrOfs, Source->ModeOfChannelSet4);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:457> Error encoding subfield ModeOfChannelSet4\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for ModeOfChannelSet5 */
	{
		if (Source->ModeOfChannelSet5_Present) {
			/* Append to buffer IEI tag 0x15 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x15), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ModeOfChannelSet5> DOT=<->> */
			Len = ENCODE_c_ChannelMode (Buffer, CurrOfs, Source->ModeOfChannelSet5);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:458> Error encoding subfield ModeOfChannelSet5\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for ModeOfChannelSet6 */
	{
		if (Source->ModeOfChannelSet6_Present) {
			/* Append to buffer IEI tag 0x16 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x16), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ModeOfChannelSet6> DOT=<->> */
			Len = ENCODE_c_ChannelMode (Buffer, CurrOfs, Source->ModeOfChannelSet6);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:459> Error encoding subfield ModeOfChannelSet6\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for ModeOfChannelSet7 */
	{
		if (Source->ModeOfChannelSet7_Present) {
			/* Append to buffer IEI tag 0x17 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x17), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ModeOfChannelSet7> DOT=<->> */
			Len = ENCODE_c_ChannelMode (Buffer, CurrOfs, Source->ModeOfChannelSet7);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:460> Error encoding subfield ModeOfChannelSet7\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for ModeOfChannelSet8 */
	{
		if (Source->ModeOfChannelSet8_Present) {
			/* Append to buffer IEI tag 0x18 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x18), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ModeOfChannelSet8> DOT=<->> */
			Len = ENCODE_c_ChannelMode (Buffer, CurrOfs, Source->ModeOfChannelSet8);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:461> Error encoding subfield ModeOfChannelSet8\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for DescriptionOfTheSecondChannelAfterTime */
	{
		if (Source->DescriptionOfTheSecondChannelAfterTime_Present) {
			/* Append to buffer IEI tag 0x64 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x64), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->DescriptionOfTheSecondChannelAfterTime> DOT=<->> */
			Len = ENCODE_c_TChDesc (Buffer, CurrOfs, Source->DescriptionOfTheSecondChannelAfterTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:462> Error encoding subfield DescriptionOfTheSecondChannelAfterTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for ModeOfTheSecondChannel */
	{
		if (Source->ModeOfTheSecondChannel_Present) {
			/* Append to buffer IEI tag 0x66 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x66), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ModeOfTheSecondChannel> DOT=<.> */
			EDIntToBits (Buffer, (CurrOfs), (int)(Source->ModeOfTheSecondChannel), 8);
			Len = 8;
			
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:463> Error encoding subfield ModeOfTheSecondChannel\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for FrequencyChannelSequenceAfterTime */
	{
		if (Source->FrequencyChannelSequenceAfterTime_Present) {
			/* Append to buffer IEI tag 0x69 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x69), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->FrequencyChannelSequenceAfterTime> DOT=<->> */
			Len = ENCODE_c_FreqChannelSeq (Buffer, CurrOfs, Source->FrequencyChannelSequenceAfterTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:464> Error encoding subfield FrequencyChannelSequenceAfterTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for MobileAllocationAfterTime */
	{
		int TLV_Base = CurrOfs;
		if (Source->MobileAllocationAfterTime_Present) {
			/* Append to buffer IEI tag 0x72 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x72), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->MobileAllocationAfterTime> DOT=<->> */
			Len = ENCODE_c_MobileAllocation (Buffer, CurrOfs+8, Source->MobileAllocationAfterTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:465> Error encoding subfield MobileAllocationAfterTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
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
				ED_SIGNAL_ERROR ("<ERRID:466> Error encoding subfield StartingTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for RealTimeDifference */
	{
		int TLV_Base = CurrOfs;
		if (Source->RealTimeDifference_Present) {
			/* Append to buffer IEI tag 0x7B */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x7B), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->RealTimeDifference> DOT=<.> */
			EDIntToBits (Buffer, (CurrOfs+8), (int)(Source->RealTimeDifference), 8);
			Len = 8;
			
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:467> Error encoding subfield RealTimeDifference\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for TimingAdvance */
	{
		if (Source->TimingAdvance_Present) {
			/* Append to buffer IEI tag 0x7D */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x7D), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->TimingAdvance> DOT=<->> */
			Len = ENCODE_c_TimingAdvance (Buffer, CurrOfs, Source->TimingAdvance);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:468> Error encoding subfield TimingAdvance\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for FrequencyShortListBeforeTime */
	{
		if (Source->FrequencyShortListBeforeTime_Present) {
			/* Append to buffer IEI tag 0x12 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x12), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->FrequencyShortListBeforeTime> DOT=<->> */
			Len = ENCODE_c_CellChannel (Buffer, CurrOfs, Source->FrequencyShortListBeforeTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:469> Error encoding subfield FrequencyShortListBeforeTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for FrequencyListBeforeTime */
	{
		int TLV_Base = CurrOfs;
		if (Source->FrequencyListBeforeTime_Present) {
			/* Append to buffer IEI tag 0x19 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x19), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->FrequencyListBeforeTime> DOT=<->> */
			Len = ENCODE_c_CellChannel (Buffer, CurrOfs+8, Source->FrequencyListBeforeTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:470> Error encoding subfield FrequencyListBeforeTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for DescriptionFirstChannelBeforeTime */
	{
		if (Source->DescriptionFirstChannelBeforeTime_Present) {
			/* Append to buffer IEI tag 0x1C */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x1C), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->DescriptionFirstChannelBeforeTime> DOT=<->> */
			Len = ENCODE_c_TChDesc2 (Buffer, CurrOfs, Source->DescriptionFirstChannelBeforeTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:471> Error encoding subfield DescriptionFirstChannelBeforeTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for DescriptionSecondChannelBeforeTime */
	{
		if (Source->DescriptionSecondChannelBeforeTime_Present) {
			/* Append to buffer IEI tag 0x1D */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x1D), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->DescriptionSecondChannelBeforeTime> DOT=<->> */
			Len = ENCODE_c_TChDesc (Buffer, CurrOfs, Source->DescriptionSecondChannelBeforeTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:472> Error encoding subfield DescriptionSecondChannelBeforeTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for FrequencyChannelSequenceBeforeTime */
	{
		if (Source->FrequencyChannelSequenceBeforeTime_Present) {
			/* Append to buffer IEI tag 0x1E */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x1E), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->FrequencyChannelSequenceBeforeTime> DOT=<->> */
			Len = ENCODE_c_FreqChannelSeq (Buffer, CurrOfs, Source->FrequencyChannelSequenceBeforeTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:473> Error encoding subfield FrequencyChannelSequenceBeforeTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for MobileAllocationBeforeTime */
	{
		int TLV_Base = CurrOfs;
		if (Source->MobileAllocationBeforeTime_Present) {
			/* Append to buffer IEI tag 0x21 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x21), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->MobileAllocationBeforeTime> DOT=<->> */
			Len = ENCODE_c_MobileAllocation (Buffer, CurrOfs+8, Source->MobileAllocationBeforeTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:474> Error encoding subfield MobileAllocationBeforeTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for CipherModeSetting */
	{
		if (Source->CipherModeSetting_Present) {
			/* Append to buffer IEI tag 0x09 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x09), 4);
			CurrOfs += 4;
			/* Append to buffer value part DEBUG FIELD=<Source->CipherModeSetting> DOT=<->> */
			Len = ENCODE_c_CipherModeSetting (Buffer, CurrOfs, Source->CipherModeSetting);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:475> Error encoding subfield CipherModeSetting\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for VgcsTargetModeIndication */
	{
		int TLV_Base = CurrOfs;
		if (Source->VgcsTargetModeIndication_Present) {
			/* Append to buffer IEI tag 0x01 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x01), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->VgcsTargetModeIndication> DOT=<.> */
			EDIntToBits (Buffer, (CurrOfs+8), (int)(Source->VgcsTargetModeIndication), 8);
			Len = 8;
			
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:476> Error encoding subfield VgcsTargetModeIndication\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for MultiRateCfg */
	{
		int TLV_Base = CurrOfs;
		if (Source->MultiRateCfg_Present) {
			/* Append to buffer IEI tag 0x03 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x03), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->MultiRateCfg> DOT=<->> */
			Len = ENCODE_c_MultirateSpeechCfgIE (Buffer, CurrOfs+8, Source->MultiRateCfg);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:477> Error encoding subfield MultiRateCfg\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for DynamicARFCNMapping */
	{
		int TLV_Base = CurrOfs;
		if (Source->DynamicARFCNMapping_Present) {
			/* Append to buffer IEI tag 0x76 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x76), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->DynamicARFCNMapping> DOT=<->> */
			Len = ENCODE_c_DynamicARFCNMapping (Buffer, CurrOfs+8, Source->DynamicARFCNMapping);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:478> Error encoding subfield DynamicARFCNMapping\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for VGCSCipheringParameters */
	{
		int TLV_Base = CurrOfs;
		if (Source->VGCSCipheringParameters_Present) {
			/* Append to buffer IEI tag 0x04 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x04), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->VGCSCipheringParameters> DOT=<->> */
			Len = ENCODE_c_VGCSCipheringParameters (Buffer, CurrOfs+8, Source->VGCSCipheringParameters);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:479> Error encoding subfield VGCSCipheringParameters\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for DedicatedServiceInformation */
	{
		if (Source->DedicatedServiceInformation_Present) {
			/* Append to buffer IEI tag 0x51 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x51), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->DedicatedServiceInformation> DOT=<->> */
			Len = ENCODE_c_DedicatedServiceInformation (Buffer, CurrOfs, Source->DedicatedServiceInformation);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:480> Error encoding subfield DedicatedServiceInformation\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for PLMNIndex */
	{
		if (Source->PLMNIndex_Present) {
			/* Append to buffer IEI tag 0x0A */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x0A), 4);
			CurrOfs += 4;
			/* Append to buffer value part DEBUG FIELD=<Source->PLMNIndex> DOT=<.> */
			EDIntToBits (Buffer, (CurrOfs), (int)(Source->PLMNIndex), 4);
			Len = 4;
			
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:481> Error encoding subfield PLMNIndex\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for ExtendedTSCSetAfterTime */
	{
		if (Source->ExtendedTSCSetAfterTime_Present) {
			/* Append to buffer IEI tag 0x6D */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x6D), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ExtendedTSCSetAfterTime> DOT=<->> */
			Len = ENCODE_c_ExtendedTSCSet (Buffer, CurrOfs, Source->ExtendedTSCSetAfterTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:482> Error encoding subfield ExtendedTSCSetAfterTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for ExtendedTSCSetBeforeTime */
	{
		if (Source->ExtendedTSCSetBeforeTime_Present) {
			/* Append to buffer IEI tag 0x6E */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x6E), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ExtendedTSCSetBeforeTime> DOT=<->> */
			Len = ENCODE_c_ExtendedTSCSet (Buffer, CurrOfs, Source->ExtendedTSCSetBeforeTime);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:483> Error encoding subfield ExtendedTSCSetBeforeTime\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_HANDOVER_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_HANDOVER_COMMAND_DN* ED_CONST Source))
{
	return L3_ENCODE_c_HANDOVER_COMMAND_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_HANDOVER_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_HANDOVER_COMMAND_DN* ED_CONST Source))
{
	return L3_ENCODE_c_HANDOVER_COMMAND_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_HANDOVER_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_HANDOVER_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_HANDOVER_COMMAND_DN (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_HANDOVER_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_HANDOVER_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length))
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
		{208, 240, ED_SKIPLIST_OPTIONAL},
		{2, 255, ED_SKIPLIST_OPTIONAL},
		{5, 255, ED_SKIPLIST_OPTIONAL},
		{98, 255, ED_SKIPLIST_OPTIONAL},
		{16, 255, ED_SKIPLIST_OPTIONAL},
		{99, 255, ED_SKIPLIST_OPTIONAL},
		{17, 255, ED_SKIPLIST_OPTIONAL},
		{19, 255, ED_SKIPLIST_OPTIONAL},
		{20, 255, ED_SKIPLIST_OPTIONAL},
		{21, 255, ED_SKIPLIST_OPTIONAL},
		{22, 255, ED_SKIPLIST_OPTIONAL},
		{23, 255, ED_SKIPLIST_OPTIONAL},
		{24, 255, ED_SKIPLIST_OPTIONAL},
		{100, 255, ED_SKIPLIST_OPTIONAL},
		{102, 255, ED_SKIPLIST_OPTIONAL},
		{105, 255, ED_SKIPLIST_OPTIONAL},
		{114, 255, ED_SKIPLIST_OPTIONAL},
		{124, 255, ED_SKIPLIST_OPTIONAL},
		{123, 255, ED_SKIPLIST_OPTIONAL},
		{125, 255, ED_SKIPLIST_OPTIONAL},
		{18, 255, ED_SKIPLIST_OPTIONAL},
		{25, 255, ED_SKIPLIST_OPTIONAL},
		{28, 255, ED_SKIPLIST_OPTIONAL},
		{29, 255, ED_SKIPLIST_OPTIONAL},
		{30, 255, ED_SKIPLIST_OPTIONAL},
		{33, 255, ED_SKIPLIST_OPTIONAL},
		{144, 240, ED_SKIPLIST_OPTIONAL},
		{1, 255, ED_SKIPLIST_OPTIONAL},
		{3, 255, ED_SKIPLIST_OPTIONAL},
		{118, 255, ED_SKIPLIST_OPTIONAL},
		{4, 255, ED_SKIPLIST_OPTIONAL},
		{81, 255, ED_SKIPLIST_OPTIONAL},
		{160, 240, ED_SKIPLIST_OPTIONAL},
		{109, 255, ED_SKIPLIST_OPTIONAL},
		{110, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	ED_WARNING_REMOVER (TLVSkipItems);
	
	/*----------------------------------------------------- 
		Code for IE CellDescription
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 16;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_CellDescription (Buffer, CurrOfs, (&(Destin->CellDescription)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:484> Error decoding subfield CellDescription\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 484, (Destin->CellDescription))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:485> Message too short decoding subfield CellDescription\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 484, (Destin->CellDescription))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE DescriptionOfTheFirstChannelAfterTime
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_TChDesc2 (Buffer, CurrOfs, (&(Destin->DescriptionOfTheFirstChannelAfterTime)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:486> Error decoding subfield DescriptionOfTheFirstChannelAfterTime\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 486, (Destin->DescriptionOfTheFirstChannelAfterTime))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:487> Message too short decoding subfield DescriptionOfTheFirstChannelAfterTime\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 486, (Destin->DescriptionOfTheFirstChannelAfterTime))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE HandoverRef
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	Destin->HandoverRef = (ED_OCTET)EDBitsToInt (Buffer, (CurrOfs), 8);
	/* LOCATOR SETTINGS LOCINT */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-51818=EDCore::TDMInteger) */Destin->HandoverRef___LOCATOR), CurrOfs, 8);
	RetLen = 8;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:488> Error decoding subfield HandoverRef\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 488, (Destin->HandoverRef))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:489> Message too short decoding subfield HandoverRef\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 488, (Destin->HandoverRef))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE PowerCommandAndAccessType
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_PowerCommandAndAccessType (Buffer, CurrOfs, (&(Destin->PowerCommandAndAccessType)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:490> Error decoding subfield PowerCommandAndAccessType\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 490, (Destin->PowerCommandAndAccessType))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:491> Message too short decoding subfield PowerCommandAndAccessType\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 490, (Destin->PowerCommandAndAccessType))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE SynchronizationIndication
	------------------------------------------------------*/
	/* Detect IEI tag 0x0D */
	ED_EXPECT_OPTIONAL_IE (0x0D,  4, 492, 4, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 4); */
	
	/* This is an optional field */
	if (Tag == 0x0D) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_SynchronizationIndication (Destin, ED_TRUE);
		CurrOfs += 4;
		Len = 4;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_SyncInd (Buffer, CurrOfs, Destin->SynchronizationIndication, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:493> Error decoding subfield SynchronizationIndication\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_SynchronizationIndication (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x0D, 493, (Destin->SynchronizationIndication))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:494> Message too short decoding subfield SynchronizationIndication\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_SynchronizationIndication (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x0D, 493, (Destin->SynchronizationIndication))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE FrequencyShortListAfterTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x02 */
	ED_EXPECT_OPTIONAL_IE (0x02,  8, 495, 5, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x02) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_FrequencyShortListAfterTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 72;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, Destin->FrequencyShortListAfterTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:496> Error decoding subfield FrequencyShortListAfterTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_FrequencyShortListAfterTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x02, 496, (Destin->FrequencyShortListAfterTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:497> Message too short decoding subfield FrequencyShortListAfterTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_FrequencyShortListAfterTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x02, 496, (Destin->FrequencyShortListAfterTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE FrequencyListAfterTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x05 */
	ED_EXPECT_OPTIONAL_IE (0x05,  8, 498, 6, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x05) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_FrequencyListAfterTime (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 16) || (Len > 1032)) {
			ED_SIGNAL_ERROR ("<ERRID:499> Size error decoding IE FrequencyListAfterTime\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_FrequencyListAfterTime (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x05, 499, (Destin->FrequencyListAfterTime))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, Destin->FrequencyListAfterTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:500> Error decoding subfield FrequencyListAfterTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_FrequencyListAfterTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x05, 500, (Destin->FrequencyListAfterTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:501> Message too short decoding subfield FrequencyListAfterTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_FrequencyListAfterTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x05, 500, (Destin->FrequencyListAfterTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE CellChannelDescription
	------------------------------------------------------*/
	/* Detect IEI tag 0x62 */
	ED_EXPECT_OPTIONAL_IE (0x62,  8, 502, 7, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x62) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_CellChannelDescription (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 128;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, Destin->CellChannelDescription, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:503> Error decoding subfield CellChannelDescription\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_CellChannelDescription (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x62, 503, (Destin->CellChannelDescription))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:504> Message too short decoding subfield CellChannelDescription\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_CellChannelDescription (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x62, 503, (Destin->CellChannelDescription))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE DescriptionOfTheMultislotCfg
	------------------------------------------------------*/
	/* Detect IEI tag 0x10 */
	ED_EXPECT_OPTIONAL_IE (0x10,  8, 505, 8, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x10) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_DescriptionOfTheMultislotCfg (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 80)) {
			ED_SIGNAL_ERROR ("<ERRID:506> Size error decoding IE DescriptionOfTheMultislotCfg\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_DescriptionOfTheMultislotCfg (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x10, 506, (Destin->DescriptionOfTheMultislotCfg))
		} 
#endif
		/* Read value part LOCATOR_16 */
		/* LOCATOR SETTINGS LOCBIN2 */;
		ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-51830=EDCore::TDMBinary) */Destin->DescriptionOfTheMultislotCfg___LOCATOR), CurrOfs, Len);
		if (Len > 0) {
			/* BINDEC02 */
			ALLOC_c_HANDOVER_COMMAND_DN_DescriptionOfTheMultislotCfg (Destin->DescriptionOfTheMultislotCfg, Len);
		
			EDCopyBits (Destin->DescriptionOfTheMultislotCfg->value, 0, Buffer, CurrOfs, Len);
			Destin->DescriptionOfTheMultislotCfg->usedBits = Len;
		}
		
		RetLen = Len;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:507> Error decoding subfield DescriptionOfTheMultislotCfg\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_DescriptionOfTheMultislotCfg (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x10, 507, (Destin->DescriptionOfTheMultislotCfg))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:508> Message too short decoding subfield DescriptionOfTheMultislotCfg\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_DescriptionOfTheMultislotCfg (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x10, 507, (Destin->DescriptionOfTheMultislotCfg))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfTheFirstChannelChannelSet1
	------------------------------------------------------*/
	/* Detect IEI tag 0x63 */
	ED_EXPECT_OPTIONAL_IE (0x63,  8, 509, 9, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x63) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_ModeOfTheFirstChannelChannelSet1 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ChannelMode (Buffer, CurrOfs, Destin->ModeOfTheFirstChannelChannelSet1, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:510> Error decoding subfield ModeOfTheFirstChannelChannelSet1\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_ModeOfTheFirstChannelChannelSet1 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x63, 510, (Destin->ModeOfTheFirstChannelChannelSet1))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:511> Message too short decoding subfield ModeOfTheFirstChannelChannelSet1\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_ModeOfTheFirstChannelChannelSet1 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x63, 510, (Destin->ModeOfTheFirstChannelChannelSet1))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet2
	------------------------------------------------------*/
	/* Detect IEI tag 0x11 */
	ED_EXPECT_OPTIONAL_IE (0x11,  8, 512, 10, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x11) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_ModeOfChannelSet2 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ChannelMode (Buffer, CurrOfs, Destin->ModeOfChannelSet2, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:513> Error decoding subfield ModeOfChannelSet2\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_ModeOfChannelSet2 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x11, 513, (Destin->ModeOfChannelSet2))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:514> Message too short decoding subfield ModeOfChannelSet2\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_ModeOfChannelSet2 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x11, 513, (Destin->ModeOfChannelSet2))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet3
	------------------------------------------------------*/
	/* Detect IEI tag 0x13 */
	ED_EXPECT_OPTIONAL_IE (0x13,  8, 515, 11, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x13) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_ModeOfChannelSet3 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ChannelMode (Buffer, CurrOfs, Destin->ModeOfChannelSet3, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:516> Error decoding subfield ModeOfChannelSet3\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_ModeOfChannelSet3 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x13, 516, (Destin->ModeOfChannelSet3))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:517> Message too short decoding subfield ModeOfChannelSet3\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_ModeOfChannelSet3 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x13, 516, (Destin->ModeOfChannelSet3))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet4
	------------------------------------------------------*/
	/* Detect IEI tag 0x14 */
	ED_EXPECT_OPTIONAL_IE (0x14,  8, 518, 12, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x14) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_ModeOfChannelSet4 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ChannelMode (Buffer, CurrOfs, Destin->ModeOfChannelSet4, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:519> Error decoding subfield ModeOfChannelSet4\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_ModeOfChannelSet4 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x14, 519, (Destin->ModeOfChannelSet4))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:520> Message too short decoding subfield ModeOfChannelSet4\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_ModeOfChannelSet4 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x14, 519, (Destin->ModeOfChannelSet4))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet5
	------------------------------------------------------*/
	/* Detect IEI tag 0x15 */
	ED_EXPECT_OPTIONAL_IE (0x15,  8, 521, 13, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x15) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_ModeOfChannelSet5 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ChannelMode (Buffer, CurrOfs, Destin->ModeOfChannelSet5, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:522> Error decoding subfield ModeOfChannelSet5\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_ModeOfChannelSet5 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x15, 522, (Destin->ModeOfChannelSet5))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:523> Message too short decoding subfield ModeOfChannelSet5\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_ModeOfChannelSet5 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x15, 522, (Destin->ModeOfChannelSet5))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet6
	------------------------------------------------------*/
	/* Detect IEI tag 0x16 */
	ED_EXPECT_OPTIONAL_IE (0x16,  8, 524, 14, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x16) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_ModeOfChannelSet6 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ChannelMode (Buffer, CurrOfs, Destin->ModeOfChannelSet6, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:525> Error decoding subfield ModeOfChannelSet6\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_ModeOfChannelSet6 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x16, 525, (Destin->ModeOfChannelSet6))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:526> Message too short decoding subfield ModeOfChannelSet6\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_ModeOfChannelSet6 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x16, 525, (Destin->ModeOfChannelSet6))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet7
	------------------------------------------------------*/
	/* Detect IEI tag 0x17 */
	ED_EXPECT_OPTIONAL_IE (0x17,  8, 527, 15, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x17) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_ModeOfChannelSet7 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ChannelMode (Buffer, CurrOfs, Destin->ModeOfChannelSet7, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:528> Error decoding subfield ModeOfChannelSet7\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_ModeOfChannelSet7 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x17, 528, (Destin->ModeOfChannelSet7))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:529> Message too short decoding subfield ModeOfChannelSet7\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_ModeOfChannelSet7 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x17, 528, (Destin->ModeOfChannelSet7))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfChannelSet8
	------------------------------------------------------*/
	/* Detect IEI tag 0x18 */
	ED_EXPECT_OPTIONAL_IE (0x18,  8, 530, 16, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x18) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_ModeOfChannelSet8 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ChannelMode (Buffer, CurrOfs, Destin->ModeOfChannelSet8, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:531> Error decoding subfield ModeOfChannelSet8\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_ModeOfChannelSet8 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x18, 531, (Destin->ModeOfChannelSet8))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:532> Message too short decoding subfield ModeOfChannelSet8\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_ModeOfChannelSet8 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x18, 531, (Destin->ModeOfChannelSet8))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE DescriptionOfTheSecondChannelAfterTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x64 */
	ED_EXPECT_OPTIONAL_IE (0x64,  8, 533, 17, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x64) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_DescriptionOfTheSecondChannelAfterTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 24;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, Destin->DescriptionOfTheSecondChannelAfterTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:534> Error decoding subfield DescriptionOfTheSecondChannelAfterTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_DescriptionOfTheSecondChannelAfterTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x64, 534, (Destin->DescriptionOfTheSecondChannelAfterTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:535> Message too short decoding subfield DescriptionOfTheSecondChannelAfterTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_DescriptionOfTheSecondChannelAfterTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x64, 534, (Destin->DescriptionOfTheSecondChannelAfterTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ModeOfTheSecondChannel
	------------------------------------------------------*/
	/* Detect IEI tag 0x66 */
	ED_EXPECT_OPTIONAL_IE (0x66,  8, 536, 18, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x66) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_ModeOfTheSecondChannel (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		Destin->ModeOfTheSecondChannel = (ED_OCTET)EDBitsToInt (Buffer, (CurrOfs), 8);
		/* LOCATOR SETTINGS LOCINT */;
		ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-51850=EDCore::TDMInteger) */Destin->ModeOfTheSecondChannel___LOCATOR), CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:537> Error decoding subfield ModeOfTheSecondChannel\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_ModeOfTheSecondChannel (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x66, 537, (Destin->ModeOfTheSecondChannel))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:538> Message too short decoding subfield ModeOfTheSecondChannel\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_ModeOfTheSecondChannel (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x66, 537, (Destin->ModeOfTheSecondChannel))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE FrequencyChannelSequenceAfterTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x69 */
	ED_EXPECT_OPTIONAL_IE (0x69,  8, 539, 19, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x69) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_FrequencyChannelSequenceAfterTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 72;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_FreqChannelSeq (Buffer, CurrOfs, Destin->FrequencyChannelSequenceAfterTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:540> Error decoding subfield FrequencyChannelSequenceAfterTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_FrequencyChannelSequenceAfterTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x69, 540, (Destin->FrequencyChannelSequenceAfterTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:541> Message too short decoding subfield FrequencyChannelSequenceAfterTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_FrequencyChannelSequenceAfterTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x69, 540, (Destin->FrequencyChannelSequenceAfterTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE MobileAllocationAfterTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x72 */
	ED_EXPECT_OPTIONAL_IE (0x72,  8, 542, 20, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x72) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_MobileAllocationAfterTime (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 64)) {
			ED_SIGNAL_ERROR ("<ERRID:543> Size error decoding IE MobileAllocationAfterTime\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_MobileAllocationAfterTime (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x72, 543, (Destin->MobileAllocationAfterTime))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_MobileAllocation (Buffer, CurrOfs, Destin->MobileAllocationAfterTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:544> Error decoding subfield MobileAllocationAfterTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_MobileAllocationAfterTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x72, 544, (Destin->MobileAllocationAfterTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:545> Message too short decoding subfield MobileAllocationAfterTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_MobileAllocationAfterTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x72, 544, (Destin->MobileAllocationAfterTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE StartingTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x7C */
	ED_EXPECT_OPTIONAL_IE (0x7C,  8, 546, 21, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x7C) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_StartingTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 16;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_StartingTime (Buffer, CurrOfs, Destin->StartingTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:547> Error decoding subfield StartingTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_StartingTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x7C, 547, (Destin->StartingTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:548> Message too short decoding subfield StartingTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_StartingTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x7C, 547, (Destin->StartingTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE RealTimeDifference
	------------------------------------------------------*/
	/* Detect IEI tag 0x7B */
	ED_EXPECT_OPTIONAL_IE (0x7B,  8, 549, 22, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x7B) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_RealTimeDifference (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len != 8) {
			ED_SIGNAL_ERROR ("<ERRID:550> Size error decoding IE RealTimeDifference\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_RealTimeDifference (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x7B, 550, (Destin->RealTimeDifference))
		} 
#endif
		/* Read value part LOCATOR_16 */
		Destin->RealTimeDifference = (ED_OCTET)EDBitsToInt (Buffer, (CurrOfs), 8);
		/* LOCATOR SETTINGS LOCINT */;
		ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-51858=EDCore::TDMInteger) */Destin->RealTimeDifference___LOCATOR), CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:551> Error decoding subfield RealTimeDifference\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_RealTimeDifference (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x7B, 551, (Destin->RealTimeDifference))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:552> Message too short decoding subfield RealTimeDifference\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_RealTimeDifference (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x7B, 551, (Destin->RealTimeDifference))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE TimingAdvance
	------------------------------------------------------*/
	/* Detect IEI tag 0x7D */
	ED_EXPECT_OPTIONAL_IE (0x7D,  8, 553, 23, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x7D) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_TimingAdvance (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_TimingAdvance (Buffer, CurrOfs, Destin->TimingAdvance, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:554> Error decoding subfield TimingAdvance\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_TimingAdvance (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x7D, 554, (Destin->TimingAdvance))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:555> Message too short decoding subfield TimingAdvance\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_TimingAdvance (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x7D, 554, (Destin->TimingAdvance))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE FrequencyShortListBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x12 */
	ED_EXPECT_OPTIONAL_IE (0x12,  8, 556, 24, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x12) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_FrequencyShortListBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 72;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, Destin->FrequencyShortListBeforeTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:557> Error decoding subfield FrequencyShortListBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_FrequencyShortListBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x12, 557, (Destin->FrequencyShortListBeforeTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:558> Message too short decoding subfield FrequencyShortListBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_FrequencyShortListBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x12, 557, (Destin->FrequencyShortListBeforeTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE FrequencyListBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x19 */
	ED_EXPECT_OPTIONAL_IE (0x19,  8, 559, 25, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x19) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_FrequencyListBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 16) || (Len > 1032)) {
			ED_SIGNAL_ERROR ("<ERRID:560> Size error decoding IE FrequencyListBeforeTime\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_FrequencyListBeforeTime (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x19, 560, (Destin->FrequencyListBeforeTime))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, Destin->FrequencyListBeforeTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:561> Error decoding subfield FrequencyListBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_FrequencyListBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x19, 561, (Destin->FrequencyListBeforeTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:562> Message too short decoding subfield FrequencyListBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_FrequencyListBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x19, 561, (Destin->FrequencyListBeforeTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE DescriptionFirstChannelBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x1C */
	ED_EXPECT_OPTIONAL_IE (0x1C,  8, 563, 26, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x1C) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_DescriptionFirstChannelBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 24;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_TChDesc2 (Buffer, CurrOfs, Destin->DescriptionFirstChannelBeforeTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:564> Error decoding subfield DescriptionFirstChannelBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_DescriptionFirstChannelBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x1C, 564, (Destin->DescriptionFirstChannelBeforeTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:565> Message too short decoding subfield DescriptionFirstChannelBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_DescriptionFirstChannelBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x1C, 564, (Destin->DescriptionFirstChannelBeforeTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE DescriptionSecondChannelBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x1D */
	ED_EXPECT_OPTIONAL_IE (0x1D,  8, 566, 27, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x1D) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_DescriptionSecondChannelBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 24;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, Destin->DescriptionSecondChannelBeforeTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:567> Error decoding subfield DescriptionSecondChannelBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_DescriptionSecondChannelBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x1D, 567, (Destin->DescriptionSecondChannelBeforeTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:568> Message too short decoding subfield DescriptionSecondChannelBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_DescriptionSecondChannelBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x1D, 567, (Destin->DescriptionSecondChannelBeforeTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE FrequencyChannelSequenceBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x1E */
	ED_EXPECT_OPTIONAL_IE (0x1E,  8, 569, 28, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x1E) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_FrequencyChannelSequenceBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 72;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_FreqChannelSeq (Buffer, CurrOfs, Destin->FrequencyChannelSequenceBeforeTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:570> Error decoding subfield FrequencyChannelSequenceBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_FrequencyChannelSequenceBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x1E, 570, (Destin->FrequencyChannelSequenceBeforeTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:571> Message too short decoding subfield FrequencyChannelSequenceBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_FrequencyChannelSequenceBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x1E, 570, (Destin->FrequencyChannelSequenceBeforeTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE MobileAllocationBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x21 */
	ED_EXPECT_OPTIONAL_IE (0x21,  8, 572, 29, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x21) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_MobileAllocationBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 64)) {
			ED_SIGNAL_ERROR ("<ERRID:573> Size error decoding IE MobileAllocationBeforeTime\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_MobileAllocationBeforeTime (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x21, 573, (Destin->MobileAllocationBeforeTime))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_MobileAllocation (Buffer, CurrOfs, Destin->MobileAllocationBeforeTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:574> Error decoding subfield MobileAllocationBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_MobileAllocationBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x21, 574, (Destin->MobileAllocationBeforeTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:575> Message too short decoding subfield MobileAllocationBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_MobileAllocationBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x21, 574, (Destin->MobileAllocationBeforeTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE CipherModeSetting
	------------------------------------------------------*/
	/* Detect IEI tag 0x09 */
	ED_EXPECT_OPTIONAL_IE (0x09,  4, 576, 30, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 4); */
	
	/* This is an optional field */
	if (Tag == 0x09) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_CipherModeSetting (Destin, ED_TRUE);
		CurrOfs += 4;
		Len = 4;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_CipherModeSetting (Buffer, CurrOfs, Destin->CipherModeSetting, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:577> Error decoding subfield CipherModeSetting\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_CipherModeSetting (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x09, 577, (Destin->CipherModeSetting))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:578> Message too short decoding subfield CipherModeSetting\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_CipherModeSetting (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x09, 577, (Destin->CipherModeSetting))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE VgcsTargetModeIndication
	------------------------------------------------------*/
	/* Detect IEI tag 0x01 */
	ED_EXPECT_OPTIONAL_IE (0x01,  8, 579, 31, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x01) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_VgcsTargetModeIndication (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len != 8) {
			ED_SIGNAL_ERROR ("<ERRID:580> Size error decoding IE VgcsTargetModeIndication\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_VgcsTargetModeIndication (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x01, 580, (Destin->VgcsTargetModeIndication))
		} 
#endif
		/* Read value part LOCATOR_16 */
		Destin->VgcsTargetModeIndication = (ED_OCTET)EDBitsToInt (Buffer, (CurrOfs), 8);
		/* LOCATOR SETTINGS LOCINT */;
		ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-51876=EDCore::TDMInteger) */Destin->VgcsTargetModeIndication___LOCATOR), CurrOfs, 8);
		RetLen = 8;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:581> Error decoding subfield VgcsTargetModeIndication\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_VgcsTargetModeIndication (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x01, 581, (Destin->VgcsTargetModeIndication))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:582> Message too short decoding subfield VgcsTargetModeIndication\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_VgcsTargetModeIndication (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x01, 581, (Destin->VgcsTargetModeIndication))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE MultiRateCfg
	------------------------------------------------------*/
	/* Detect IEI tag 0x03 */
	ED_EXPECT_OPTIONAL_IE (0x03,  8, 583, 32, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x03) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_MultiRateCfg (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 16) || (Len > 48)) {
			ED_SIGNAL_ERROR ("<ERRID:584> Size error decoding IE MultiRateCfg\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_MultiRateCfg (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x03, 584, (Destin->MultiRateCfg))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_MultirateSpeechCfgIE (Buffer, CurrOfs, Destin->MultiRateCfg, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:585> Error decoding subfield MultiRateCfg\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_MultiRateCfg (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x03, 585, (Destin->MultiRateCfg))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:586> Message too short decoding subfield MultiRateCfg\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_MultiRateCfg (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x03, 585, (Destin->MultiRateCfg))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE DynamicARFCNMapping
	------------------------------------------------------*/
	/* Detect IEI tag 0x76 */
	ED_EXPECT_OPTIONAL_IE (0x76,  8, 587, 33, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x76) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_DynamicARFCNMapping (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 32) || (Len > 256)) {
			ED_SIGNAL_ERROR ("<ERRID:588> Size error decoding IE DynamicARFCNMapping\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_DynamicARFCNMapping (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x76, 588, (Destin->DynamicARFCNMapping))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_DynamicARFCNMapping (Buffer, CurrOfs, Destin->DynamicARFCNMapping, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:589> Error decoding subfield DynamicARFCNMapping\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_DynamicARFCNMapping (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x76, 589, (Destin->DynamicARFCNMapping))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:590> Message too short decoding subfield DynamicARFCNMapping\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_DynamicARFCNMapping (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x76, 589, (Destin->DynamicARFCNMapping))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE VGCSCipheringParameters
	------------------------------------------------------*/
	/* Detect IEI tag 0x04 */
	ED_EXPECT_OPTIONAL_IE (0x04,  8, 591, 34, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x04) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_VGCSCipheringParameters (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 104)) {
			ED_SIGNAL_ERROR ("<ERRID:592> Size error decoding IE VGCSCipheringParameters\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_VGCSCipheringParameters (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x04, 592, (Destin->VGCSCipheringParameters))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_VGCSCipheringParameters (Buffer, CurrOfs, Destin->VGCSCipheringParameters, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:593> Error decoding subfield VGCSCipheringParameters\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_VGCSCipheringParameters (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x04, 593, (Destin->VGCSCipheringParameters))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:594> Message too short decoding subfield VGCSCipheringParameters\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_VGCSCipheringParameters (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x04, 593, (Destin->VGCSCipheringParameters))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE DedicatedServiceInformation
	------------------------------------------------------*/
	/* Detect IEI tag 0x51 */
	ED_EXPECT_OPTIONAL_IE (0x51,  8, 595, 35, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x51) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_DedicatedServiceInformation (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_DedicatedServiceInformation (Buffer, CurrOfs, Destin->DedicatedServiceInformation, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:596> Error decoding subfield DedicatedServiceInformation\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_DedicatedServiceInformation (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x51, 596, (Destin->DedicatedServiceInformation))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:597> Message too short decoding subfield DedicatedServiceInformation\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_DedicatedServiceInformation (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x51, 596, (Destin->DedicatedServiceInformation))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE PLMNIndex
	------------------------------------------------------*/
	/* Detect IEI tag 0x0A */
	ED_EXPECT_OPTIONAL_IE (0x0A,  4, 598, 36, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 4); */
	
	/* This is an optional field */
	if (Tag == 0x0A) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_PLMNIndex (Destin, ED_TRUE);
		CurrOfs += 4;
		Len = 4;
		/* Read value part LOCATOR_16 */
		Destin->PLMNIndex = (ED_OCTET)EDBitsToInt (Buffer, (CurrOfs), 4);
		/* LOCATOR SETTINGS LOCINT */;
		ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-51886=EDCore::TDMInteger) */Destin->PLMNIndex___LOCATOR), CurrOfs, 4);
		RetLen = 4;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:599> Error decoding subfield PLMNIndex\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_PLMNIndex (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x0A, 599, (Destin->PLMNIndex))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:600> Message too short decoding subfield PLMNIndex\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_PLMNIndex (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x0A, 599, (Destin->PLMNIndex))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ExtendedTSCSetAfterTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x6D */
	ED_EXPECT_OPTIONAL_IE (0x6D,  8, 601, 37, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x6D) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_ExtendedTSCSetAfterTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ExtendedTSCSet (Buffer, CurrOfs, Destin->ExtendedTSCSetAfterTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:602> Error decoding subfield ExtendedTSCSetAfterTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_ExtendedTSCSetAfterTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x6D, 602, (Destin->ExtendedTSCSetAfterTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:603> Message too short decoding subfield ExtendedTSCSetAfterTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_ExtendedTSCSetAfterTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x6D, 602, (Destin->ExtendedTSCSetAfterTime))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ExtendedTSCSetBeforeTime
	------------------------------------------------------*/
	/* Detect IEI tag 0x6E */
	ED_EXPECT_OPTIONAL_IE (0x6E,  8, 604, 38, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x6E) {
		SETPRESENT_c_HANDOVER_COMMAND_DN_ExtendedTSCSetBeforeTime (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ExtendedTSCSet (Buffer, CurrOfs, Destin->ExtendedTSCSetBeforeTime, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:605> Error decoding subfield ExtendedTSCSetBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_ExtendedTSCSetBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x6E, 605, (Destin->ExtendedTSCSetBeforeTime))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:606> Message too short decoding subfield ExtendedTSCSetBeforeTime\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_HANDOVER_COMMAND_DN_ExtendedTSCSetBeforeTime (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x6E, 605, (Destin->ExtendedTSCSetBeforeTime))
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN (char* Buffer, ED_EXLONG BitOffset, const c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN* Source, int Mode)
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
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 99, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for HandoverToUtranCommand */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->HandoverToUtranCommand> DOT=<.> */
		EDCopyBits (Buffer, CurrOfs+8, Source->HandoverToUtranCommand.value, 0, Source->HandoverToUtranCommand.usedBits);
		Len = Source->HandoverToUtranCommand.usedBits;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:607> Error encoding subfield HandoverToUtranCommand\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for CNtoMSTransparentInformation */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->CNtoMSTransparentInformation> DOT=<.> */
		EDCopyBits (Buffer, CurrOfs, Source->CNtoMSTransparentInformation.value, 0, Source->CNtoMSTransparentInformation.usedBits);
		Len = Source->CNtoMSTransparentInformation.usedBits;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:608> Error encoding subfield CNtoMSTransparentInformation\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN* ED_CONST Source))
{
	return L3_ENCODE_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN* ED_CONST Source))
{
	return L3_ENCODE_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE HandoverToUtranCommand
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if ((Len < 8) || (Len > 4792)) {
		ED_SIGNAL_ERROR ("<ERRID:609> Size error decoding IE HandoverToUtranCommand\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 609, (Destin->HandoverToUtranCommand))
	} 
#endif
	/* Read value part LOCATOR_16 */
	/* LOCATOR SETTINGS LOCBIN2 */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-51893=EDCore::TDMBinary) */Destin->HandoverToUtranCommand___LOCATOR), CurrOfs, Len);
	if (Len > 0) {
		/* BINDEC02 */
		ALLOC_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN_HandoverToUtranCommand (&(Destin->HandoverToUtranCommand), Len);
	
		EDCopyBits (Destin->HandoverToUtranCommand.value, 0, Buffer, CurrOfs, Len);
		Destin->HandoverToUtranCommand.usedBits = Len;
	}
	
	RetLen = Len;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:610> Error decoding subfield HandoverToUtranCommand\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 610, (Destin->HandoverToUtranCommand))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:611> Message too short decoding subfield HandoverToUtranCommand\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 610, (Destin->HandoverToUtranCommand))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE CNtoMSTransparentInformation
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = Length + BitOffset - CurrOfs;
	/* Read value part LOCATOR_16 */
	/* LOCATOR SETTINGS LOCBIN2 */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-51895=EDCore::TDMBinary) */Destin->CNtoMSTransparentInformation___LOCATOR), CurrOfs, Len);
	if (Len > 0) {
		/* BINDEC02 */
		ALLOC_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN_CNtoMSTransparentInformation (&(Destin->CNtoMSTransparentInformation), Len);
	
		EDCopyBits (Destin->CNtoMSTransparentInformation.value, 0, Buffer, CurrOfs, Len);
		Destin->CNtoMSTransparentInformation.usedBits = Len;
	}
	
	RetLen = Len;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:612> Error decoding subfield CNtoMSTransparentInformation\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 612, (Destin->CNtoMSTransparentInformation))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:613> Message too short decoding subfield CNtoMSTransparentInformation\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 612, (Destin->CNtoMSTransparentInformation))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN (char* Buffer, ED_EXLONG BitOffset, const c_INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN* Source, int Mode)
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
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 100, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for HandoverToCdma2000Command */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->HandoverToCdma2000Command> DOT=<.> */
		EDCopyBits (Buffer, CurrOfs+8, Source->HandoverToCdma2000Command.value, 0, Source->HandoverToCdma2000Command.usedBits);
		Len = Source->HandoverToCdma2000Command.usedBits;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:614> Error encoding subfield HandoverToCdma2000Command\n");
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
	ENCODING FUNCTION FOR GSM-L3 MESSAGE INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN* ED_CONST Source))
{
	return L3_ENCODE_c_INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN* ED_CONST Source))
{
	return L3_ENCODE_c_INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE HandoverToCdma2000Command
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if ((Len < 24) || (Len > 4792)) {
		ED_SIGNAL_ERROR ("<ERRID:615> Size error decoding IE HandoverToCdma2000Command\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 615, (Destin->HandoverToCdma2000Command))
	} 
#endif
	/* Read value part LOCATOR_16 */
	/* LOCATOR SETTINGS LOCBIN2 */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-51898=EDCore::TDMBinary) */Destin->HandoverToCdma2000Command___LOCATOR), CurrOfs, Len);
	if (Len > 0) {
		/* BINDEC02 */
		ALLOC_c_INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN_HandoverToCdma2000Command (&(Destin->HandoverToCdma2000Command), Len);
	
		EDCopyBits (Destin->HandoverToCdma2000Command.value, 0, Buffer, CurrOfs, Len);
		Destin->HandoverToCdma2000Command.usedBits = Len;
	}
	
	RetLen = Len;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:616> Error decoding subfield HandoverToCdma2000Command\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 616, (Destin->HandoverToCdma2000Command))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:617> Message too short decoding subfield HandoverToCdma2000Command\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 616, (Destin->HandoverToCdma2000Command))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN (char* Buffer, ED_EXLONG BitOffset, const c_HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN* Source, int Mode)
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
	
	
	/* Code for RadioBearerReconfiguration */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->RadioBearerReconfiguration> DOT=<.> */
		EDCopyBits (Buffer, CurrOfs+8, Source->RadioBearerReconfiguration.value, 0, Source->RadioBearerReconfiguration.usedBits);
		Len = Source->RadioBearerReconfiguration.usedBits;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:618> Error encoding subfield RadioBearerReconfiguration\n");
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
	ENCODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN* ED_CONST Source))
{
	return L3_ENCODE_c_HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN* ED_CONST Source))
{
	return L3_ENCODE_c_HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE RadioBearerReconfiguration
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if ((Len < 8) || (Len > 4792)) {
		ED_SIGNAL_ERROR ("<ERRID:619> Size error decoding IE RadioBearerReconfiguration\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 619, (Destin->RadioBearerReconfiguration))
	} 
#endif
	/* Read value part LOCATOR_16 */
	/* LOCATOR SETTINGS LOCBIN2 */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-51901=EDCore::TDMBinary) */Destin->RadioBearerReconfiguration___LOCATOR), CurrOfs, Len);
	if (Len > 0) {
		/* BINDEC02 */
		ALLOC_c_HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN_RadioBearerReconfiguration (&(Destin->RadioBearerReconfiguration), Len);
	
		EDCopyBits (Destin->RadioBearerReconfiguration.value, 0, Buffer, CurrOfs, Len);
		Destin->RadioBearerReconfiguration.usedBits = Len;
	}
	
	RetLen = Len;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:620> Error decoding subfield RadioBearerReconfiguration\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 620, (Destin->RadioBearerReconfiguration))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:621> Message too short decoding subfield RadioBearerReconfiguration\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 620, (Destin->RadioBearerReconfiguration))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN (char* Buffer, ED_EXLONG BitOffset, const c_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN* Source, int Mode)
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
	
	
	/* Code for DL_DCCHMessage */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->DL_DCCHMessage> DOT=<.> */
		EDCopyBits (Buffer, CurrOfs+8, Source->DL_DCCHMessage.value, 0, Source->DL_DCCHMessage.usedBits);
		Len = Source->DL_DCCHMessage.usedBits;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:622> Error encoding subfield DL_DCCHMessage\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for CNtoMStTransparentInformation */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->CNtoMStTransparentInformation> DOT=<.> */
		EDCopyBits (Buffer, CurrOfs+8, Source->CNtoMStTransparentInformation.value, 0, Source->CNtoMStTransparentInformation.usedBits);
		Len = Source->CNtoMStTransparentInformation.usedBits;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:623> Error encoding subfield CNtoMStTransparentInformation\n");
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
	ENCODING FUNCTION FOR GSM-L3 MESSAGE INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN* ED_CONST Source))
{
	return L3_ENCODE_c_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN* ED_CONST Source))
{
	return L3_ENCODE_c_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE DL_DCCHMessage
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if ((Len < 8) || (Len > 4792)) {
		ED_SIGNAL_ERROR ("<ERRID:624> Size error decoding IE DL_DCCHMessage\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 624, (Destin->DL_DCCHMessage))
	} 
#endif
	/* Read value part LOCATOR_16 */
	/* LOCATOR SETTINGS LOCBIN2 */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-51904=EDCore::TDMBinary) */Destin->DL_DCCHMessage___LOCATOR), CurrOfs, Len);
	if (Len > 0) {
		/* BINDEC02 */
		ALLOC_c_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN_DL_DCCHMessage (&(Destin->DL_DCCHMessage), Len);
	
		EDCopyBits (Destin->DL_DCCHMessage.value, 0, Buffer, CurrOfs, Len);
		Destin->DL_DCCHMessage.usedBits = Len;
	}
	
	RetLen = Len;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:625> Error decoding subfield DL_DCCHMessage\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 625, (Destin->DL_DCCHMessage))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:626> Message too short decoding subfield DL_DCCHMessage\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 625, (Destin->DL_DCCHMessage))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE CNtoMStTransparentInformation
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if ((Len < 8) || (Len > 4792)) {
		ED_SIGNAL_ERROR ("<ERRID:627> Size error decoding IE CNtoMStTransparentInformation\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 627, (Destin->CNtoMStTransparentInformation))
	} 
#endif
	/* Read value part LOCATOR_16 */
	/* LOCATOR SETTINGS LOCBIN2 */;
	ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-51906=EDCore::TDMBinary) */Destin->CNtoMStTransparentInformation___LOCATOR), CurrOfs, Len);
	if (Len > 0) {
		/* BINDEC02 */
		ALLOC_c_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN_CNtoMStTransparentInformation (&(Destin->CNtoMStTransparentInformation), Len);
	
		EDCopyBits (Destin->CNtoMStTransparentInformation.value, 0, Buffer, CurrOfs, Len);
		Destin->CNtoMStTransparentInformation.usedBits = Len;
	}
	
	RetLen = Len;
	
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:628> Error decoding subfield CNtoMStTransparentInformation\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 628, (Destin->CNtoMStTransparentInformation))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:629> Message too short decoding subfield CNtoMStTransparentInformation\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 628, (Destin->CNtoMStTransparentInformation))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE RR_CELL_CHANGE_ORDER_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_RR_CELL_CHANGE_ORDER_DN (char* Buffer, ED_EXLONG BitOffset, const c_RR_CELL_CHANGE_ORDER_DN* Source, int Mode)
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
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 8, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for CellDescription */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->CellDescription> DOT=<.> */
		Len = ENCODE_c_CellDescription (Buffer, CurrOfs, (&(Source->CellDescription)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:630> Error encoding subfield CellDescription\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for NcModeForTargetCell */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->NcModeForTargetCell> DOT=<.> */
		Len = ENCODE_c_NCMode (Buffer, (CurrOfs+4), (&(Source->NcModeForTargetCell)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:631> Error encoding subfield NcModeForTargetCell\n");
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
			ED_SIGNAL_ERROR ("<ERRID:632> Error encoding subfield SpareHalfOctet\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}
	
	/* Code for P3GTargetCell */
	{
		int TLV_Base = CurrOfs;
		if (Source->P3GTargetCell_Present) {
			/* Append to buffer IEI tag 0x19 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x19), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->P3GTargetCell> DOT=<->> */
			EDCopyBits (Buffer, CurrOfs+8, Source->P3GTargetCell->value, 0, Source->P3GTargetCell->usedBits);
			Len = Source->P3GTargetCell->usedBits;
			
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:633> Error encoding subfield P3GTargetCell\n");
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
	ENCODING FUNCTION FOR GSM-L3 MESSAGE RR_CELL_CHANGE_ORDER_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RR_CELL_CHANGE_ORDER_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RR_CELL_CHANGE_ORDER_DN* ED_CONST Source))
{
	return L3_ENCODE_c_RR_CELL_CHANGE_ORDER_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE RR_CELL_CHANGE_ORDER_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_RR_CELL_CHANGE_ORDER_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RR_CELL_CHANGE_ORDER_DN* ED_CONST Source))
{
	return L3_ENCODE_c_RR_CELL_CHANGE_ORDER_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE RR_CELL_CHANGE_ORDER_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RR_CELL_CHANGE_ORDER_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RR_CELL_CHANGE_ORDER_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_RR_CELL_CHANGE_ORDER_DN (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE RR_CELL_CHANGE_ORDER_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_RR_CELL_CHANGE_ORDER_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RR_CELL_CHANGE_ORDER_DN* ED_CONST Destin, ED_EXLONG Length))
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
		{25, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	ED_WARNING_REMOVER (TLVSkipItems);
	
	/*----------------------------------------------------- 
		Code for IE CellDescription
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 16;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_CellDescription (Buffer, CurrOfs, (&(Destin->CellDescription)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:634> Error decoding subfield CellDescription\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 634, (Destin->CellDescription))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:635> Message too short decoding subfield CellDescription\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 634, (Destin->CellDescription))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE NcModeForTargetCell
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 4;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_NCMode (Buffer, (CurrOfs+4), (&(Destin->NcModeForTargetCell)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:636> Error decoding subfield NcModeForTargetCell\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 636, (Destin->NcModeForTargetCell))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:637> Message too short decoding subfield NcModeForTargetCell\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 636, (Destin->NcModeForTargetCell))
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
		ED_SIGNAL_ERROR ("<ERRID:638> Error decoding subfield SpareHalfOctet\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 638, (Destin->SpareHalfOctet))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:639> Message too short decoding subfield SpareHalfOctet\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 638, (Destin->SpareHalfOctet))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE P3GTargetCell
	------------------------------------------------------*/
	/* Detect IEI tag 0x19 */
	ED_EXPECT_OPTIONAL_IE (0x19,  8, 640, 3, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x19) {
		SETPRESENT_c_RR_CELL_CHANGE_ORDER_DN_P3GTargetCell (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 32)) {
			ED_SIGNAL_ERROR ("<ERRID:641> Size error decoding IE P3GTargetCell\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_RR_CELL_CHANGE_ORDER_DN_P3GTargetCell (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x19, 641, (Destin->P3GTargetCell))
		} 
#endif
		/* Read value part LOCATOR_16 */
		/* LOCATOR SETTINGS LOCBIN2 */;
		ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMBinary'-51915=EDCore::TDMBinary) */Destin->P3GTargetCell___LOCATOR), CurrOfs, Len);
		if (Len > 0) {
			/* BINDEC02 */
			ALLOC_c_RR_CELL_CHANGE_ORDER_DN_P3GTargetCell (Destin->P3GTargetCell, Len);
		
			EDCopyBits (Destin->P3GTargetCell->value, 0, Buffer, CurrOfs, Len);
			Destin->P3GTargetCell->usedBits = Len;
		}
		
		RetLen = Len;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:642> Error decoding subfield P3GTargetCell\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_RR_CELL_CHANGE_ORDER_DN_P3GTargetCell (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x19, 642, (Destin->P3GTargetCell))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:643> Message too short decoding subfield P3GTargetCell\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_RR_CELL_CHANGE_ORDER_DN_P3GTargetCell (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x19, 642, (Destin->P3GTargetCell))
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE PACKET_ASSIGNMENT_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_PACKET_ASSIGNMENT_DN (char* Buffer, ED_EXLONG BitOffset, const c_PACKET_ASSIGNMENT_DN* Source, int Mode)
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
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 75, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for GprsBroadcastInfo */
	{
		int TLV_Base = CurrOfs;
		/* Append to buffer value part DEBUG FIELD=<Source->GprsBroadcastInfo> DOT=<.> */
		Len = ENCODE_c_GPRSBCastInfo (Buffer, CurrOfs+8, (&(Source->GprsBroadcastInfo)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:644> Error encoding subfield GprsBroadcastInfo\n");
			return -1;
		} 
#endif
		CurrOfs += Len+8;
		/* Insert into buffer LEN  */
		EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
	}
	
	/* Code for DescOfTheUplinkPktChAss */
	{
		int TLV_Base = CurrOfs;
		if (Source->DescOfTheUplinkPktChAss_Present) {
			/* Append to buffer IEI tag 0x22 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x22), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->DescOfTheUplinkPktChAss> DOT=<->> */
			Len = ENCODE_c_RRPacketUplinkAssignment (Buffer, CurrOfs+8, Source->DescOfTheUplinkPktChAss);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:645> Error encoding subfield DescOfTheUplinkPktChAss\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for DescOfTheDownlinkPktChAss */
	{
		int TLV_Base = CurrOfs;
		if (Source->DescOfTheDownlinkPktChAss_Present) {
			/* Append to buffer IEI tag 0x23 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x23), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->DescOfTheDownlinkPktChAss> DOT=<->> */
			Len = ENCODE_c_RRPktDownlinkAssi (Buffer, CurrOfs+8, Source->DescOfTheDownlinkPktChAss);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:646> Error encoding subfield DescOfTheDownlinkPktChAss\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for CellChannelDescription */
	{
		if (Source->CellChannelDescription_Present) {
			/* Append to buffer IEI tag 0x10 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x10), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->CellChannelDescription> DOT=<->> */
			Len = ENCODE_c_CellChannel (Buffer, CurrOfs, Source->CellChannelDescription);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:647> Error encoding subfield CellChannelDescription\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for FrequencyList */
	{
		int TLV_Base = CurrOfs;
		if (Source->FrequencyList_Present) {
			/* Append to buffer IEI tag 0x12 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x12), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->FrequencyList> DOT=<->> */
			Len = ENCODE_c_CellChannel (Buffer, CurrOfs+8, Source->FrequencyList);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:648> Error encoding subfield FrequencyList\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for MobileAllocation */
	{
		int TLV_Base = CurrOfs;
		if (Source->MobileAllocation_Present) {
			/* Append to buffer IEI tag 0x13 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x13), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->MobileAllocation> DOT=<->> */
			Len = ENCODE_c_MobileAllocation (Buffer, CurrOfs+8, Source->MobileAllocation);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:649> Error encoding subfield MobileAllocation\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for ChannelDescriptionC2 */
	{
		if (Source->ChannelDescriptionC2_Present) {
			/* Append to buffer IEI tag 0x14 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x14), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->ChannelDescriptionC2> DOT=<->> */
			Len = ENCODE_c_TChDesc3 (Buffer, CurrOfs, Source->ChannelDescriptionC2);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:650> Error encoding subfield ChannelDescriptionC2\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for DescDownlinkPacketChannelAssigType2 */
	{
		int TLV_Base = CurrOfs;
		if (Source->DescDownlinkPacketChannelAssigType2_Present) {
			/* Append to buffer IEI tag 0x24 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x24), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->DescDownlinkPacketChannelAssigType2> DOT=<->> */
			Len = ENCODE_c_RRPacketDownlinkAssignmentType2 (Buffer, CurrOfs+8, Source->DescDownlinkPacketChannelAssigType2);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:651> Error encoding subfield DescDownlinkPacketChannelAssigType2\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
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
				ED_SIGNAL_ERROR ("<ERRID:652> Error encoding subfield ExtendedTSCSet\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE PACKET_ASSIGNMENT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PACKET_ASSIGNMENT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PACKET_ASSIGNMENT_DN* ED_CONST Source))
{
	return L3_ENCODE_c_PACKET_ASSIGNMENT_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE PACKET_ASSIGNMENT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_PACKET_ASSIGNMENT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PACKET_ASSIGNMENT_DN* ED_CONST Source))
{
	return L3_ENCODE_c_PACKET_ASSIGNMENT_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PACKET_ASSIGNMENT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PACKET_ASSIGNMENT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PACKET_ASSIGNMENT_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_PACKET_ASSIGNMENT_DN (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PACKET_ASSIGNMENT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_PACKET_ASSIGNMENT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PACKET_ASSIGNMENT_DN* ED_CONST Destin, ED_EXLONG Length))
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
		{34, 255, ED_SKIPLIST_OPTIONAL},
		{35, 255, ED_SKIPLIST_OPTIONAL},
		{16, 255, ED_SKIPLIST_OPTIONAL},
		{18, 255, ED_SKIPLIST_OPTIONAL},
		{19, 255, ED_SKIPLIST_OPTIONAL},
		{20, 255, ED_SKIPLIST_OPTIONAL},
		{36, 255, ED_SKIPLIST_OPTIONAL},
		{109, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	ED_WARNING_REMOVER (TLVSkipItems);
	
	/*----------------------------------------------------- 
		Code for IE GprsBroadcastInfo
	------------------------------------------------------*/
	CurrOfs += 0;
	/* Insert into buffer LEN  */
	Len = EDBitsToInt (Buffer, CurrOfs, 8);
	CurrOfs += 8;
	Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if ((Len < 48) || (Len > 4792)) {
		ED_SIGNAL_ERROR ("<ERRID:653> Size error decoding IE GprsBroadcastInfo\n");
		ED_HANDLE_IE_SIZE_ERROR ((-1), 653, (Destin->GprsBroadcastInfo))
	} 
#endif
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_GPRSBCastInfo (Buffer, CurrOfs, (&(Destin->GprsBroadcastInfo)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:654> Error decoding subfield GprsBroadcastInfo\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 654, (Destin->GprsBroadcastInfo))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:655> Message too short decoding subfield GprsBroadcastInfo\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 654, (Destin->GprsBroadcastInfo))
	} 
#endif
	
	
	
	/*----------------------------------------------------- 
		Code for IE DescOfTheUplinkPktChAss
	------------------------------------------------------*/
	/* Detect IEI tag 0x22 */
	ED_EXPECT_OPTIONAL_IE (0x22,  8, 656, 1, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x22) {
		SETPRESENT_c_PACKET_ASSIGNMENT_DN_DescOfTheUplinkPktChAss (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 4784)) {
			ED_SIGNAL_ERROR ("<ERRID:657> Size error decoding IE DescOfTheUplinkPktChAss\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_PACKET_ASSIGNMENT_DN_DescOfTheUplinkPktChAss (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x22, 657, (Destin->DescOfTheUplinkPktChAss))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_RRPacketUplinkAssignment (Buffer, CurrOfs, Destin->DescOfTheUplinkPktChAss, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:658> Error decoding subfield DescOfTheUplinkPktChAss\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_PACKET_ASSIGNMENT_DN_DescOfTheUplinkPktChAss (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x22, 658, (Destin->DescOfTheUplinkPktChAss))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:659> Message too short decoding subfield DescOfTheUplinkPktChAss\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_PACKET_ASSIGNMENT_DN_DescOfTheUplinkPktChAss (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x22, 658, (Destin->DescOfTheUplinkPktChAss))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE DescOfTheDownlinkPktChAss
	------------------------------------------------------*/
	/* Detect IEI tag 0x23 */
	ED_EXPECT_OPTIONAL_IE (0x23,  8, 660, 2, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x23) {
		SETPRESENT_c_PACKET_ASSIGNMENT_DN_DescOfTheDownlinkPktChAss (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 4784)) {
			ED_SIGNAL_ERROR ("<ERRID:661> Size error decoding IE DescOfTheDownlinkPktChAss\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_PACKET_ASSIGNMENT_DN_DescOfTheDownlinkPktChAss (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x23, 661, (Destin->DescOfTheDownlinkPktChAss))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_RRPktDownlinkAssi (Buffer, CurrOfs, Destin->DescOfTheDownlinkPktChAss, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:662> Error decoding subfield DescOfTheDownlinkPktChAss\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_PACKET_ASSIGNMENT_DN_DescOfTheDownlinkPktChAss (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x23, 662, (Destin->DescOfTheDownlinkPktChAss))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:663> Message too short decoding subfield DescOfTheDownlinkPktChAss\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_PACKET_ASSIGNMENT_DN_DescOfTheDownlinkPktChAss (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x23, 662, (Destin->DescOfTheDownlinkPktChAss))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE CellChannelDescription
	------------------------------------------------------*/
	/* Detect IEI tag 0x10 */
	ED_EXPECT_OPTIONAL_IE (0x10,  8, 664, 3, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x10) {
		SETPRESENT_c_PACKET_ASSIGNMENT_DN_CellChannelDescription (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 128;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, Destin->CellChannelDescription, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:665> Error decoding subfield CellChannelDescription\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_PACKET_ASSIGNMENT_DN_CellChannelDescription (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x10, 665, (Destin->CellChannelDescription))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:666> Message too short decoding subfield CellChannelDescription\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_PACKET_ASSIGNMENT_DN_CellChannelDescription (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x10, 665, (Destin->CellChannelDescription))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE FrequencyList
	------------------------------------------------------*/
	/* Detect IEI tag 0x12 */
	ED_EXPECT_OPTIONAL_IE (0x12,  8, 667, 4, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x12) {
		SETPRESENT_c_PACKET_ASSIGNMENT_DN_FrequencyList (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 16) || (Len > 1040)) {
			ED_SIGNAL_ERROR ("<ERRID:668> Size error decoding IE FrequencyList\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_PACKET_ASSIGNMENT_DN_FrequencyList (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x12, 668, (Destin->FrequencyList))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_CellChannel (Buffer, CurrOfs, Destin->FrequencyList, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:669> Error decoding subfield FrequencyList\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_PACKET_ASSIGNMENT_DN_FrequencyList (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x12, 669, (Destin->FrequencyList))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:670> Message too short decoding subfield FrequencyList\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_PACKET_ASSIGNMENT_DN_FrequencyList (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x12, 669, (Destin->FrequencyList))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE MobileAllocation
	------------------------------------------------------*/
	/* Detect IEI tag 0x13 */
	ED_EXPECT_OPTIONAL_IE (0x13,  8, 671, 5, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x13) {
		SETPRESENT_c_PACKET_ASSIGNMENT_DN_MobileAllocation (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 64)) {
			ED_SIGNAL_ERROR ("<ERRID:672> Size error decoding IE MobileAllocation\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_PACKET_ASSIGNMENT_DN_MobileAllocation (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x13, 672, (Destin->MobileAllocation))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_MobileAllocation (Buffer, CurrOfs, Destin->MobileAllocation, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:673> Error decoding subfield MobileAllocation\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_PACKET_ASSIGNMENT_DN_MobileAllocation (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x13, 673, (Destin->MobileAllocation))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:674> Message too short decoding subfield MobileAllocation\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_PACKET_ASSIGNMENT_DN_MobileAllocation (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x13, 673, (Destin->MobileAllocation))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ChannelDescriptionC2
	------------------------------------------------------*/
	/* Detect IEI tag 0x14 */
	ED_EXPECT_OPTIONAL_IE (0x14,  8, 675, 6, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x14) {
		SETPRESENT_c_PACKET_ASSIGNMENT_DN_ChannelDescriptionC2 (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 16;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_TChDesc3 (Buffer, CurrOfs, Destin->ChannelDescriptionC2, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:676> Error decoding subfield ChannelDescriptionC2\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_PACKET_ASSIGNMENT_DN_ChannelDescriptionC2 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x14, 676, (Destin->ChannelDescriptionC2))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:677> Message too short decoding subfield ChannelDescriptionC2\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_PACKET_ASSIGNMENT_DN_ChannelDescriptionC2 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x14, 676, (Destin->ChannelDescriptionC2))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE DescDownlinkPacketChannelAssigType2
	------------------------------------------------------*/
	/* Detect IEI tag 0x24 */
	ED_EXPECT_OPTIONAL_IE (0x24,  8, 678, 7, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x24) {
		SETPRESENT_c_PACKET_ASSIGNMENT_DN_DescDownlinkPacketChannelAssigType2 (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 4784)) {
			ED_SIGNAL_ERROR ("<ERRID:679> Size error decoding IE DescDownlinkPacketChannelAssigType2\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_PACKET_ASSIGNMENT_DN_DescDownlinkPacketChannelAssigType2 (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x24, 679, (Destin->DescDownlinkPacketChannelAssigType2))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_RRPacketDownlinkAssignmentType2 (Buffer, CurrOfs, Destin->DescDownlinkPacketChannelAssigType2, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:680> Error decoding subfield DescDownlinkPacketChannelAssigType2\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_PACKET_ASSIGNMENT_DN_DescDownlinkPacketChannelAssigType2 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x24, 680, (Destin->DescDownlinkPacketChannelAssigType2))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:681> Message too short decoding subfield DescDownlinkPacketChannelAssigType2\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_PACKET_ASSIGNMENT_DN_DescDownlinkPacketChannelAssigType2 (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x24, 680, (Destin->DescDownlinkPacketChannelAssigType2))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE ExtendedTSCSet
	------------------------------------------------------*/
	/* Detect IEI tag 0x6D */
	ED_EXPECT_OPTIONAL_IE (0x6D,  8, 682, 8, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x6D) {
		SETPRESENT_c_PACKET_ASSIGNMENT_DN_ExtendedTSCSet (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 8;
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_ExtendedTSCSet (Buffer, CurrOfs, Destin->ExtendedTSCSet, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:683> Error decoding subfield ExtendedTSCSet\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_PACKET_ASSIGNMENT_DN_ExtendedTSCSet (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x6D, 683, (Destin->ExtendedTSCSet))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:684> Message too short decoding subfield ExtendedTSCSet\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_PACKET_ASSIGNMENT_DN_ExtendedTSCSet (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x6D, 683, (Destin->ExtendedTSCSet))
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE PACKET_NOTIFICATION_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_PACKET_NOTIFICATION_DN (char* Buffer, ED_EXLONG BitOffset, const c_PACKET_NOTIFICATION_DN* Source, int Mode)
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
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 78, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for PktTmsi */
	{
		if (Source->PktTmsi_Present) {
			/* Append to buffer IEI tag 0x10 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x10), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->PktTmsi> DOT=<.> */
			EDIntToBits (Buffer, (CurrOfs), (int)(Source->PktTmsi), 32);
			Len = 32;
			
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:685> Error encoding subfield PktTmsi\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for MobileId */
	{
		int TLV_Base = CurrOfs;
		if (Source->MobileId_Present) {
			/* Append to buffer IEI tag 0x11 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x11), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->MobileId> DOT=<->> */
			Len = ENCODE_c_RRMobileId (Buffer, CurrOfs+8, Source->MobileId);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:686> Error encoding subfield MobileId\n");
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
	ENCODING FUNCTION FOR GSM-L3 MESSAGE PACKET_NOTIFICATION_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PACKET_NOTIFICATION_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PACKET_NOTIFICATION_DN* ED_CONST Source))
{
	return L3_ENCODE_c_PACKET_NOTIFICATION_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE PACKET_NOTIFICATION_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_PACKET_NOTIFICATION_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PACKET_NOTIFICATION_DN* ED_CONST Source))
{
	return L3_ENCODE_c_PACKET_NOTIFICATION_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PACKET_NOTIFICATION_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PACKET_NOTIFICATION_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PACKET_NOTIFICATION_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_PACKET_NOTIFICATION_DN (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PACKET_NOTIFICATION_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_PACKET_NOTIFICATION_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PACKET_NOTIFICATION_DN* ED_CONST Destin, ED_EXLONG Length))
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
		{16, 255, ED_SKIPLIST_OPTIONAL},
		{17, 255, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	ED_WARNING_REMOVER (TLVSkipItems);
	
	/*----------------------------------------------------- 
		Code for IE PktTmsi
	------------------------------------------------------*/
	/* Detect IEI tag 0x10 */
	ED_EXPECT_OPTIONAL_IE (0x10,  8, 687, 0, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x10) {
		SETPRESENT_c_PACKET_NOTIFICATION_DN_PktTmsi (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 32;
		/* Read value part LOCATOR_16 */
		Destin->PktTmsi = (ED_LONG)EDBitsToInt (Buffer, (CurrOfs), 32);
		/* LOCATOR SETTINGS LOCINT */;
		ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-51937=EDCore::TDMInteger) */Destin->PktTmsi___LOCATOR), CurrOfs, 32);
		RetLen = 32;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:688> Error decoding subfield PktTmsi\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_PACKET_NOTIFICATION_DN_PktTmsi (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x10, 688, (Destin->PktTmsi))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:689> Message too short decoding subfield PktTmsi\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_PACKET_NOTIFICATION_DN_PktTmsi (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x10, 688, (Destin->PktTmsi))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE MobileId
	------------------------------------------------------*/
	/* Detect IEI tag 0x11 */
	ED_EXPECT_OPTIONAL_IE (0x11,  8, 690, 1, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x11) {
		SETPRESENT_c_PACKET_NOTIFICATION_DN_MobileId (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 72)) {
			ED_SIGNAL_ERROR ("<ERRID:691> Size error decoding IE MobileId\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_PACKET_NOTIFICATION_DN_MobileId (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x11, 691, (Destin->MobileId))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_RRMobileId (Buffer, CurrOfs, Destin->MobileId, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:692> Error decoding subfield MobileId\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_PACKET_NOTIFICATION_DN_MobileId (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x11, 692, (Destin->MobileId))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:693> Message too short decoding subfield MobileId\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_PACKET_NOTIFICATION_DN_MobileId (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x11, 692, (Destin->MobileId))
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE PARTIAL_RELEASE_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_PARTIAL_RELEASE_DN (char* Buffer, ED_EXLONG BitOffset, const c_PARTIAL_RELEASE_DN* Source, int Mode)
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
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 10, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for ChannelDescription */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ChannelDescription> DOT=<.> */
		Len = ENCODE_c_TChDesc (Buffer, CurrOfs, (&(Source->ChannelDescription)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:694> Error encoding subfield ChannelDescription\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE PARTIAL_RELEASE_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PARTIAL_RELEASE_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PARTIAL_RELEASE_DN* ED_CONST Source))
{
	return L3_ENCODE_c_PARTIAL_RELEASE_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE PARTIAL_RELEASE_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_PARTIAL_RELEASE_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PARTIAL_RELEASE_DN* ED_CONST Source))
{
	return L3_ENCODE_c_PARTIAL_RELEASE_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PARTIAL_RELEASE_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PARTIAL_RELEASE_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PARTIAL_RELEASE_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_PARTIAL_RELEASE_DN (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PARTIAL_RELEASE_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_PARTIAL_RELEASE_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PARTIAL_RELEASE_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE ChannelDescription
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_TChDesc (Buffer, CurrOfs, (&(Destin->ChannelDescription)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:695> Error decoding subfield ChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 695, (Destin->ChannelDescription))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:696> Message too short decoding subfield ChannelDescription\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 695, (Destin->ChannelDescription))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE PHYSICAL_INFORMATION_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_PHYSICAL_INFORMATION_DN (char* Buffer, ED_EXLONG BitOffset, const c_PHYSICAL_INFORMATION_DN* Source, int Mode)
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
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 45, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for TimingAdvance */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->TimingAdvance> DOT=<.> */
		Len = ENCODE_c_TimingAdvance (Buffer, CurrOfs, (&(Source->TimingAdvance)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:697> Error encoding subfield TimingAdvance\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE PHYSICAL_INFORMATION_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PHYSICAL_INFORMATION_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PHYSICAL_INFORMATION_DN* ED_CONST Source))
{
	return L3_ENCODE_c_PHYSICAL_INFORMATION_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE PHYSICAL_INFORMATION_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_PHYSICAL_INFORMATION_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PHYSICAL_INFORMATION_DN* ED_CONST Source))
{
	return L3_ENCODE_c_PHYSICAL_INFORMATION_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PHYSICAL_INFORMATION_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PHYSICAL_INFORMATION_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PHYSICAL_INFORMATION_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_PHYSICAL_INFORMATION_DN (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE PHYSICAL_INFORMATION_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_PHYSICAL_INFORMATION_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PHYSICAL_INFORMATION_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE TimingAdvance
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 8;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_TimingAdvance (Buffer, CurrOfs, (&(Destin->TimingAdvance)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:698> Error decoding subfield TimingAdvance\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 698, (Destin->TimingAdvance))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:699> Message too short decoding subfield TimingAdvance\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 698, (Destin->TimingAdvance))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE UPLINK_BUSY_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_UPLINK_BUSY_DN (char* Buffer, ED_EXLONG BitOffset, const c_UPLINK_BUSY_DN* Source, int Mode)
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
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 42, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for TalkerPriorityAndEmergencyIndication */
	{
		int TLV_Base = CurrOfs;
		if (Source->TalkerPriorityAndEmergencyIndication_Present) {
			/* Append to buffer IEI tag 0x31 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x31), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->TalkerPriorityAndEmergencyIndication> DOT=<->> */
			Len = ENCODE_c_TalkerPriorityStatus (Buffer, CurrOfs+8, Source->TalkerPriorityAndEmergencyIndication);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:700> Error encoding subfield TalkerPriorityAndEmergencyIndication\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for Token */
	{
		if (Source->Token_Present) {
			/* Append to buffer IEI tag 0x32 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x32), 8);
			CurrOfs += 8;
			/* Append to buffer value part DEBUG FIELD=<Source->Token> DOT=<.> */
			EDIntToBits (Buffer, (CurrOfs), (int)(Source->Token), 32);
			Len = 32;
			
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:701> Error encoding subfield Token\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}
	
	/* Code for TalkerIdentity */
	{
		int TLV_Base = CurrOfs;
		if (Source->TalkerIdentity_Present) {
			/* Append to buffer IEI tag 0x33 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x33), 8);
			CurrOfs += 8;TLV_Base = CurrOfs;
			/* Append to buffer value part DEBUG FIELD=<Source->TalkerIdentity> DOT=<->> */
			Len = ENCODE_c_TalkerIdentity (Buffer, CurrOfs+8, Source->TalkerIdentity);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:702> Error encoding subfield TalkerIdentity\n");
				return -1;
			} 
#endif
			CurrOfs += Len+8;
			/* Insert into buffer LEN  */
			EDIntToBits (Buffer, (ED_EXLONG)TLV_Base, (int)((CurrOfs - TLV_Base - 8) >> 3), 8);
		}
	}
	
	/* Code for UplinkAccessIndication */
	{
		if (Source->UplinkAccessIndication_Present) {
			/* Append to buffer IEI tag 0x08 */
			EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, (int)(0x08), 4);
			CurrOfs += 4;
			/* Append to buffer value part DEBUG FIELD=<Source->UplinkAccessIndication> DOT=<.> */
			EDIntToBits (Buffer, (CurrOfs), (int)(Source->UplinkAccessIndication), 4);
			Len = 4;
			
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
			if (Len < 0) {
				ED_SIGNAL_ERROR ("<ERRID:703> Error encoding subfield UplinkAccessIndication\n");
				return -1;
			} 
#endif
			CurrOfs += Len;
		}
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE UPLINK_BUSY_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_UPLINK_BUSY_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_UPLINK_BUSY_DN* ED_CONST Source))
{
	return L3_ENCODE_c_UPLINK_BUSY_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE UPLINK_BUSY_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_UPLINK_BUSY_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_UPLINK_BUSY_DN* ED_CONST Source))
{
	return L3_ENCODE_c_UPLINK_BUSY_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE UPLINK_BUSY_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_UPLINK_BUSY_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_UPLINK_BUSY_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_UPLINK_BUSY_DN (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE UPLINK_BUSY_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_UPLINK_BUSY_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_UPLINK_BUSY_DN* ED_CONST Destin, ED_EXLONG Length))
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
		{49, 255, ED_SKIPLIST_OPTIONAL},
		{50, 255, ED_SKIPLIST_OPTIONAL},
		{51, 255, ED_SKIPLIST_OPTIONAL},
		{128, 240, ED_SKIPLIST_OPTIONAL},
		{0, 0, ED_SKIPLIST_END_OF_LIST}
	};
	/* Stores temporary TAG values for tagged IEs */
	int Tag;
	/* Stores temporary len values for L-type IEs */
	int RetLen=0, Len=0;
	ED_WARNING_REMOVER (TLVSkipItems);
	
	/*----------------------------------------------------- 
		Code for IE TalkerPriorityAndEmergencyIndication
	------------------------------------------------------*/
	/* Detect IEI tag 0x31 */
	ED_EXPECT_OPTIONAL_IE (0x31,  8, 704, 0, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x31) {
		SETPRESENT_c_UPLINK_BUSY_DN_TalkerPriorityAndEmergencyIndication (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len != 8) {
			ED_SIGNAL_ERROR ("<ERRID:705> Size error decoding IE TalkerPriorityAndEmergencyIndication\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_UPLINK_BUSY_DN_TalkerPriorityAndEmergencyIndication (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x31, 705, (Destin->TalkerPriorityAndEmergencyIndication))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_TalkerPriorityStatus (Buffer, CurrOfs, Destin->TalkerPriorityAndEmergencyIndication, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:706> Error decoding subfield TalkerPriorityAndEmergencyIndication\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_UPLINK_BUSY_DN_TalkerPriorityAndEmergencyIndication (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x31, 706, (Destin->TalkerPriorityAndEmergencyIndication))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:707> Message too short decoding subfield TalkerPriorityAndEmergencyIndication\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_UPLINK_BUSY_DN_TalkerPriorityAndEmergencyIndication (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x31, 706, (Destin->TalkerPriorityAndEmergencyIndication))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE Token
	------------------------------------------------------*/
	/* Detect IEI tag 0x32 */
	ED_EXPECT_OPTIONAL_IE (0x32,  8, 708, 1, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x32) {
		SETPRESENT_c_UPLINK_BUSY_DN_Token (Destin, ED_TRUE);
		CurrOfs += 8;
		Len = 32;
		/* Read value part LOCATOR_16 */
		Destin->Token = (ED_LONG)EDBitsToInt (Buffer, (CurrOfs), 32);
		/* LOCATOR SETTINGS LOCINT */;
		ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMInteger'-51950=EDCore::TDMInteger) */Destin->Token___LOCATOR), CurrOfs, 32);
		RetLen = 32;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:709> Error decoding subfield Token\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_UPLINK_BUSY_DN_Token (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x32, 709, (Destin->Token))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:710> Message too short decoding subfield Token\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_UPLINK_BUSY_DN_Token (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x32, 709, (Destin->Token))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE TalkerIdentity
	------------------------------------------------------*/
	/* Detect IEI tag 0x33 */
	ED_EXPECT_OPTIONAL_IE (0x33,  8, 711, 2, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 8); */
	
	/* This is an optional field */
	if (Tag == 0x33) {
		SETPRESENT_c_UPLINK_BUSY_DN_TalkerIdentity (Destin, ED_TRUE);
		CurrOfs += 8;
		/* Insert into buffer LEN  */
		Len = EDBitsToInt (Buffer, CurrOfs, 8);
		CurrOfs += 8;
		Len <<= 3;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if ((Len < 8) || (Len > 144)) {
			ED_SIGNAL_ERROR ("<ERRID:712> Size error decoding IE TalkerIdentity\n");
#if ED_HANDLE_IE_SIZE_ERROR_SET_MISSING
			SETPRESENT_c_UPLINK_BUSY_DN_TalkerIdentity (Destin, ED_FALSE);
#endif
				ED_HANDLE_IE_SIZE_ERROR (0x33, 712, (Destin->TalkerIdentity))
		} 
#endif
		/* Read value part LOCATOR_16 */
		RetLen = DECODE_c_TalkerIdentity (Buffer, CurrOfs, Destin->TalkerIdentity, Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:713> Error decoding subfield TalkerIdentity\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_UPLINK_BUSY_DN_TalkerIdentity (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x33, 713, (Destin->TalkerIdentity))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:714> Message too short decoding subfield TalkerIdentity\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_UPLINK_BUSY_DN_TalkerIdentity (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x33, 713, (Destin->TalkerIdentity))
		} 
#endif
		
	
	}
	
	
	/*----------------------------------------------------- 
		Code for IE UplinkAccessIndication
	------------------------------------------------------*/
	/* Detect IEI tag 0x08 */
	ED_EXPECT_OPTIONAL_IE (0x08,  4, 715, 3, KnownL3IEs_RR)
	/* Tag = EDBitsToInt (Buffer, CurrOfs, 4); */
	
	/* This is an optional field */
	if (Tag == 0x08) {
		SETPRESENT_c_UPLINK_BUSY_DN_UplinkAccessIndication (Destin, ED_TRUE);
		CurrOfs += 4;
		Len = 4;
		/* Read value part LOCATOR_16 */
		Destin->UplinkAccessIndication = (unsigned char)EDBitsToInt (Buffer, CurrOfs, 4);
		/* LOCATOR SETTINGS LOCOCTET */;
		ED_LOCATOR_SET (&(/*LOCATOR_16 ('TDMOctet'-51954=EDCore::TDMOctet) */Destin->UplinkAccessIndication___LOCATOR), CurrOfs, 4);
		RetLen = 4;
		
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (RetLen != Len) {
			ED_SIGNAL_ERROR ("<ERRID:716> Error decoding subfield UplinkAccessIndication\n");
#if ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR_SET_MISSING
			SETPRESENT_c_UPLINK_BUSY_DN_UplinkAccessIndication (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_SYNTAX_ERROR (0x08, 716, (Destin->UplinkAccessIndication))
		} 
#endif
		CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (CurrOfs > (BitOffset+Length)) {
			ED_SIGNAL_ERROR ("<ERRID:717> Message too short decoding subfield UplinkAccessIndication\n");
#if ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT_SET_MISSING
			SETPRESENT_c_UPLINK_BUSY_DN_UplinkAccessIndication (Destin, ED_FALSE);
#endif
			ED_HANDLE_OPTIONAL_IE_MSG_TOO_SHORT (0x08, 716, (Destin->UplinkAccessIndication))
		} 
#endif
		
	
	}
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
#define THIS Source
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE VGCS_DNLINK_GRANT_DN
	Mode: 
		0=normal (full message)
		1=body only
-----------------------------------------------------------------*/
ED_EXLONG L3_ENCODE_c_VGCS_DNLINK_GRANT_DN (char* Buffer, ED_EXLONG BitOffset, const c_VGCS_DNLINK_GRANT_DN* Source, int Mode)
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
		EDIntToBits (Buffer, (ED_EXLONG)CurrOfs, 9, 8);
		CurrOfs += 8;
		
	}
	
	
	/* Code for ReqRef */
	{
		/* Append to buffer value part DEBUG FIELD=<Source->ReqRef> DOT=<.> */
		Len = ENCODE_c_RequestReference (Buffer, CurrOfs, (&(Source->ReqRef)));
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
		if (Len < 0) {
			ED_SIGNAL_ERROR ("<ERRID:718> Error encoding subfield ReqRef\n");
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
			ED_SIGNAL_ERROR ("<ERRID:719> Error encoding subfield TimingAdvance\n");
			return -1;
		} 
#endif
		CurrOfs += Len;
	}

	return (CurrOfs - BitOffset);
}
/*-----------------------------------------------------------------
	ENCODING FUNCTION FOR GSM-L3 MESSAGE VGCS_DNLINK_GRANT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_VGCS_DNLINK_GRANT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VGCS_DNLINK_GRANT_DN* ED_CONST Source))
{
	return L3_ENCODE_c_VGCS_DNLINK_GRANT_DN (Buffer, BitOffset, Source, 0);
}

/*-----------------------------------------------------------------
	BODY-ONLY ENCODING FUNCTION FOR GSM-L3 MESSAGE VGCS_DNLINK_GRANT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_BODY_c_VGCS_DNLINK_GRANT_DN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VGCS_DNLINK_GRANT_DN* ED_CONST Source))
{
	return L3_ENCODE_c_VGCS_DNLINK_GRANT_DN (Buffer, BitOffset, Source, 1);
}

#undef THIS
#define THIS Destin
/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE VGCS_DNLINK_GRANT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_c_VGCS_DNLINK_GRANT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VGCS_DNLINK_GRANT_DN* ED_CONST Destin, ED_EXLONG Length))
{
	int Len=0;
	
	Len = DECODE_BODY_c_VGCS_DNLINK_GRANT_DN (Buffer, (BitOffset+16), Destin, Length-(16));
	if (Len < 0) return Len;
	
	return Len+16;
}

/*-----------------------------------------------------------------
	DECODING FUNCTION FOR GSM-L3 MESSAGE VGCS_DNLINK_GRANT_DN
-----------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, DECODE_BODY_c_VGCS_DNLINK_GRANT_DN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VGCS_DNLINK_GRANT_DN* ED_CONST Destin, ED_EXLONG Length))
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
		Code for IE ReqRef
	------------------------------------------------------*/
	CurrOfs += 0;
	Len = 24;
	/* Read value part LOCATOR_16 */
	RetLen = DECODE_c_RequestReference (Buffer, CurrOfs, (&(Destin->ReqRef)), Len);
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (RetLen != Len) {
		ED_SIGNAL_ERROR ("<ERRID:720> Error decoding subfield ReqRef\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 720, (Destin->ReqRef))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:721> Message too short decoding subfield ReqRef\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 720, (Destin->ReqRef))
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
		ED_SIGNAL_ERROR ("<ERRID:722> Error decoding subfield TimingAdvance\n");
		ED_HANDLE_MANDATORY_IE_SYNTAX_ERROR ((-1), 722, (Destin->TimingAdvance))
	} 
#endif
	CurrOfs += Len;
#ifndef ED_NO_EXTENSIVE_ERROR_LOGGING
	if (CurrOfs > (BitOffset+Length)) {
		ED_SIGNAL_ERROR ("<ERRID:723> Message too short decoding subfield TimingAdvance\n");
		ED_HANDLE_MANDATORY_IE_MSG_TOO_SHORT ((-1), 722, (Destin->TimingAdvance))
	} 
#endif
	
	

	return (CurrOfs - BitOffset);
	}
}
#undef THIS
int Match_c_ADDITIONAL_ASSIGNMENT_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 59) /* message type */
	);
}

int Match_c_ASSIGNMENT_COMMAND_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 46) /* message type */
	);
}

int Match_c_CHANNEL_MODE_MODIFY_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 16) /* message type */
	);
}

int Match_c_CHANNEL_RELEASE_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 13) /* message type */
	);
}

int Match_c_CIPHERING_MODE_COMMAND_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 53) /* message type */
	);
}

int Match_c_CLASSMARK_ENQUIRY_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 19) /* message type */
	);
}

int Match_c_CONFIGURATION_CHANGE_COMMAND_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 48) /* message type */
	);
}

int Match_c_DTM_ASSIGNMENT_COMMAND_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 76) /* message type */
	);
}

int Match_c_DTM_INFORMATION_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 77) /* message type */
	);
}

int Match_c_DTM_REJECT_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 73) /* message type */
	);
}

int Match_c_FREQUENCY_REDEFINITION_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 20) /* message type */
	);
}

int Match_c_PDCH_ASSIGNMENT_COMMAND_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 35) /* message type */
	);
}

int Match_c_HANDOVER_COMMAND_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 43) /* message type */
	);
}

int Match_c_INTER_SYSTEM_TO_UTRAN_HANDOVER_COMMAND_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 99) /* message type */
	);
}

int Match_c_INTER_SYSTEM_TO_CDMA2000_HANDOVER_COMMAND_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 100) /* message type */
	);
}

int Match_c_HANDOVER_TO_GERAN_Iu_MODE_COMMAND_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 101) /* message type */
	);
}

int Match_c_INTER_SYSTEM_TO_EUTRAN_HANDOVER_COMMAND_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 102) /* message type */
	);
}

int Match_c_RR_CELL_CHANGE_ORDER_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 8) /* message type */
	);
}

int Match_c_PACKET_ASSIGNMENT_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 75) /* message type */
	);
}

int Match_c_PACKET_NOTIFICATION_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 78) /* message type */
	);
}

int Match_c_PARTIAL_RELEASE_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 10) /* message type */
	);
}

int Match_c_PHYSICAL_INFORMATION_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 45) /* message type */
	);
}

int Match_c_UPLINK_BUSY_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 42) /* message type */
	);
}

int Match_c_VGCS_DNLINK_GRANT_DN (const char* Buffer, ED_CONST ED_EXLONG BitOffset)
{
	return (
		(EDBitsToInt (Buffer, BitOffset+4, 4) == 6) /* protocol discriminator & skip indicator */
		&& ((EDBitsToInt (Buffer, BitOffset+8, 8)) == 9) /* message type */
	);
}


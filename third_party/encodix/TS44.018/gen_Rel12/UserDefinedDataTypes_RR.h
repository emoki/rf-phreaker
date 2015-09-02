/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.152
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __UserDefinedDataTypes_RR_h
#define __UserDefinedDataTypes_RR_h
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
	Encoding/decoding functions for "CipheringKeySequenceNumber".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CipheringKeySequenceNumber (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CipheringKeySequenceNumber* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CipheringKeySequenceNumber (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CipheringKeySequenceNumber* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "DescGrpOrBcastCallRef".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_DescGrpOrBcastCallRef (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DescGrpOrBcastCallRef* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_DescGrpOrBcastCallRef (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DescGrpOrBcastCallRef* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CellDescription".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CellDescription (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CellDescription* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CellDescription (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CellDescription* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CellOptions".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CellOptions (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CellOptions* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CellOptions (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CellOptions* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CellSelParam".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CellSelParam (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CellSelParam* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CellSelParam (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CellSelParam* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MACModeAndChCodReq".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MACModeAndChCodReq (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MACModeAndChCodReq* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MACModeAndChCodReq (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MACModeAndChCodReq* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "TChDesc".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_TChDesc (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_TChDesc* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_TChDesc (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_TChDesc* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "TChDesc2".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_TChDesc2 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_TChDesc2* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_TChDesc2 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_TChDesc2* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "TChDesc3".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_TChDesc3 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_TChDesc3* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_TChDesc3 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_TChDesc3* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "ChannelMode".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_ChannelMode (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ChannelMode* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_ChannelMode (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ChannelMode* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "ClassmarkEnquiryMask".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_ClassmarkEnquiryMask (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ClassmarkEnquiryMask* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_ClassmarkEnquiryMask (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ClassmarkEnquiryMask* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "ChannelNeeded".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_ChannelNeeded (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ChannelNeeded* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_ChannelNeeded (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ChannelNeeded* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "ChannelRequestDesc".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_ChannelRequestDesc (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ChannelRequestDesc* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_ChannelRequestDesc (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ChannelRequestDesc* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CipherModeSetting".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CipherModeSetting (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CipherModeSetting* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CipherModeSetting (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CipherModeSetting* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CipherResponse".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CipherResponse (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CipherResponse* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CipherResponse (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CipherResponse* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CtrlChannelDesc".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CtrlChannelDesc (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CtrlChannelDesc* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CtrlChannelDesc (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CtrlChannelDesc* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FreqChannelSeq".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FreqChannelSeq (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FreqChannelSeq* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FreqChannelSeq (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FreqChannelSeq* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "GrpChannelDesc".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_GrpChannelDesc (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GrpChannelDesc* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_GrpChannelDesc (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GrpChannelDesc* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "GPRSResumption".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_GPRSResumption (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GPRSResumption* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_GPRSResumption (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GPRSResumption* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "GroupChannelDescription2".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_GroupChannelDescription2 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GroupChannelDescription2* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_GroupChannelDescription2 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GroupChannelDescription2* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "GPRSMeasurementResult".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_GPRSMeasurementResult (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GPRSMeasurementResult* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_GPRSMeasurementResult (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GPRSMeasurementResult* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MobileTimeDiff".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MobileTimeDiff (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MobileTimeDiff* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MobileTimeDiff (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MobileTimeDiff* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MobileTimeDiffHyperframe".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MobileTimeDiffHyperframe (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MobileTimeDiffHyperframe* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MobileTimeDiffHyperframe (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MobileTimeDiffHyperframe* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "NCMode".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_NCMode (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_NCMode* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_NCMode (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_NCMode* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "DedicatedModeOrTBF".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_DedicatedModeOrTBF (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DedicatedModeOrTBF* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_DedicatedModeOrTBF (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DedicatedModeOrTBF* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "DedicatedModeOrTBF4b".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_DedicatedModeOrTBF4b (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DedicatedModeOrTBF4b* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_DedicatedModeOrTBF4b (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DedicatedModeOrTBF4b* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PageMode".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PageMode (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PageMode* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PageMode (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PageMode* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PowerCommand".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PowerCommand (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PowerCommand* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PowerCommand (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PowerCommand* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PowerCommandAndAccessType".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PowerCommandAndAccessType (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PowerCommandAndAccessType* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PowerCommandAndAccessType (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PowerCommandAndAccessType* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RACHCtrlParam".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RACHCtrlParam (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RACHCtrlParam* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RACHCtrlParam (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RACHCtrlParam* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RequestReference".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RequestReference (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RequestReference* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RequestReference (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RequestReference* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "EstablishmentCauseRandomReference".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_EstablishmentCauseRandomReference (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_EstablishmentCauseRandomReference* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_EstablishmentCauseRandomReference (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_EstablishmentCauseRandomReference* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RRCause".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RRCause (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RRCause* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RRCause (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RRCause* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "StartingTime".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_StartingTime (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_StartingTime* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_StartingTime (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_StartingTime* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SyncInd".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SyncInd (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SyncInd* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SyncInd (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SyncInd* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "TimingAdvance".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_TimingAdvance (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_TimingAdvance* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_TimingAdvance (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_TimingAdvance* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "VGCSTargeModeIndication".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_VGCSTargeModeIndication (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VGCSTargeModeIndication* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_VGCSTargeModeIndication (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VGCSTargeModeIndication* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "ExtMeasurementResults".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_ExtMeasurementResults (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ExtMeasurementResults* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_ExtMeasurementResults (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ExtMeasurementResults* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "APDUFlags".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_APDUFlags (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_APDUFlags* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_APDUFlags (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_APDUFlags* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "ServiceSupport".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_ServiceSupport (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ServiceSupport* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_ServiceSupport (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ServiceSupport* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "DedicatedServiceInformation".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_DedicatedServiceInformation (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DedicatedServiceInformation* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_DedicatedServiceInformation (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DedicatedServiceInformation* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "ReducedGroupCallReference".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_ReducedGroupCallReference (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ReducedGroupCallReference* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_ReducedGroupCallReference (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ReducedGroupCallReference* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "TalkerPriorityStatus".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_TalkerPriorityStatus (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_TalkerPriorityStatus* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_TalkerPriorityStatus (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_TalkerPriorityStatus* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "TalkerIdentity".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_TalkerIdentity (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_TalkerIdentity* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_TalkerIdentity (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_TalkerIdentity* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "VGCSAMRConfiguration".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_VGCSAMRConfiguration (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VGCSAMRConfiguration* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_VGCSAMRConfiguration (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VGCSAMRConfiguration* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "DataIdentity".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_DataIdentity (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DataIdentity* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_DataIdentity (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DataIdentity* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FeatureIndicator".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FeatureIndicator (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FeatureIndicator* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FeatureIndicator (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FeatureIndicator* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "ExtendedTSCSet".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_ExtendedTSCSet (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ExtendedTSCSet* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_ExtendedTSCSet (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ExtendedTSCSet* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "LocationUpdType".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_LocationUpdType (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_LocationUpdType* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_LocationUpdType (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_LocationUpdType* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "UpdateResult".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_UpdateResult (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_UpdateResult* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_UpdateResult (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_UpdateResult* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RRLocationAreaId".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RRLocationAreaId (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RRLocationAreaId* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RRLocationAreaId (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RRLocationAreaId* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "AdditionalUpdateParameters".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_AdditionalUpdateParameters (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_AdditionalUpdateParameters* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_AdditionalUpdateParameters (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_AdditionalUpdateParameters* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RoutingAreaIdentity".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RoutingAreaIdentity (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RoutingAreaIdentity* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RoutingAreaIdentity (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RoutingAreaIdentity* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RRMobileStationClassmark2".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RRMobileStationClassmark2 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RRMobileStationClassmark2* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RRMobileStationClassmark2 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RRMobileStationClassmark2* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FDD_CELL_INFORMATION_ITEM".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FDD_CELL_INFORMATION_ITEM (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FDD_CELL_INFORMATION_ITEM* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FDD_CELL_INFORMATION_ITEM (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FDD_CELL_INFORMATION_ITEM* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "IncSkipOfARFCN".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_IncSkipOfARFCN (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_IncSkipOfARFCN* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_IncSkipOfARFCN (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_IncSkipOfARFCN* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "GrpChannelMA".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_GrpChannelMA (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GrpChannelMA* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_GrpChannelMA (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GrpChannelMA* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "TRXLEVCarriers".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_TRXLEVCarriers (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_TRXLEVCarriers* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_TRXLEVCarriers (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_TRXLEVCarriers* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "BitmapTypeReporting".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_BitmapTypeReporting (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_BitmapTypeReporting* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_BitmapTypeReporting (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_BitmapTypeReporting* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "LHBit".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_LHBit (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_LHBit* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_LHBit (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_LHBit* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "ChannelRequest".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_ChannelRequest (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ChannelRequest* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_ChannelRequest (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ChannelRequest* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "BaRange".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_BaRange (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_BaRange* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_BaRange (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_BaRange* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CellChannel".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CellChannel (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CellChannel* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CellChannel (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CellChannel* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "TChType".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_TChType (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_TChType* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_TChType (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_TChType* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "TChType2".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_TChType2 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_TChType2* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_TChType2 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_TChType2* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MobileAllocation".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MobileAllocation (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MobileAllocation* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MobileAllocation (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MobileAllocation* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "NeighbourCellDescription".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_NeighbourCellDescription (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_NeighbourCellDescription* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_NeighbourCellDescription (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_NeighbourCellDescription* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "NeighbourCellDescription2".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_NeighbourCellDescription2 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_NeighbourCellDescription2* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_NeighbourCellDescription2 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_NeighbourCellDescription2* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RRMobileId".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RRMobileId (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RRMobileId* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RRMobileId (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RRMobileId* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "FDD_CELL_INFORMATION".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_FDD_CELL_INFORMATION (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_FDD_CELL_INFORMATION* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_FDD_CELL_INFORMATION (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_FDD_CELL_INFORMATION* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "TDD_CELL_INFORMATION".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_TDD_CELL_INFORMATION (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_TDD_CELL_INFORMATION* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_TDD_CELL_INFORMATION (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_TDD_CELL_INFORMATION* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "GenericTLV_RR".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_GenericTLV_RR (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GenericTLV_RR* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_GenericTLV_RR (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GenericTLV_RR* ED_CONST Destin, ED_EXLONG Length));


#ifdef __cplusplus
	}
#endif
#endif


/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_SystemInformationBlockType1_H_
#define	_SystemInformationBlockType1_H_


#include <rf_phreaker/lte_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/lte_rrc_asn_library/P-Max.h"
#include "rf_phreaker/lte_rrc_asn_library/FreqBandIndicator.h"
#include "rf_phreaker/lte_rrc_asn_library/SchedulingInfoList.h"
#include <rf_phreaker/lte_rrc_asn_library/NativeEnumerated.h>
#include <rf_phreaker/lte_rrc_asn_library/NativeInteger.h>
#include "rf_phreaker/lte_rrc_asn_library/PLMN-IdentityList.h"
#include "rf_phreaker/lte_rrc_asn_library/TrackingAreaCode.h"
#include "rf_phreaker/lte_rrc_asn_library/CellIdentity.h"
#include <rf_phreaker/lte_rrc_asn_library/BOOLEAN.h>
#include "rf_phreaker/lte_rrc_asn_library/CSG-Identity.h"
#include <rf_phreaker/lte_rrc_asn_library/constr_SEQUENCE.h>
#include "rf_phreaker/lte_rrc_asn_library/Q-RxLevMin.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum SystemInformationBlockType1__cellAccessRelatedInfo__cellBarred {
	SystemInformationBlockType1__cellAccessRelatedInfo__cellBarred_barred	= 0,
	SystemInformationBlockType1__cellAccessRelatedInfo__cellBarred_notBarred	= 1
} e_SystemInformationBlockType1__cellAccessRelatedInfo__cellBarred;
typedef enum SystemInformationBlockType1__cellAccessRelatedInfo__intraFreqReselection {
	SystemInformationBlockType1__cellAccessRelatedInfo__intraFreqReselection_allowed	= 0,
	SystemInformationBlockType1__cellAccessRelatedInfo__intraFreqReselection_notAllowed	= 1
} e_SystemInformationBlockType1__cellAccessRelatedInfo__intraFreqReselection;
typedef enum SystemInformationBlockType1__si_WindowLength {
	SystemInformationBlockType1__si_WindowLength_ms1	= 0,
	SystemInformationBlockType1__si_WindowLength_ms2	= 1,
	SystemInformationBlockType1__si_WindowLength_ms5	= 2,
	SystemInformationBlockType1__si_WindowLength_ms10	= 3,
	SystemInformationBlockType1__si_WindowLength_ms15	= 4,
	SystemInformationBlockType1__si_WindowLength_ms20	= 5,
	SystemInformationBlockType1__si_WindowLength_ms40	= 6
} e_SystemInformationBlockType1__si_WindowLength;

/* Forward declarations */
struct TDD_Config;
struct SystemInformationBlockType1_v890_IEs;

/* SystemInformationBlockType1 */
typedef struct SystemInformationBlockType1 {
	struct SystemInformationBlockType1__cellAccessRelatedInfo {
		PLMN_IdentityList_t	 plmn_IdentityList;
		TrackingAreaCode_t	 trackingAreaCode;
		CellIdentity_t	 cellIdentity;
		long	 cellBarred;
		long	 intraFreqReselection;
		BOOLEAN_t	 csg_Indication;
		CSG_Identity_t	*csg_Identity	/* OPTIONAL */;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} cellAccessRelatedInfo;
	struct SystemInformationBlockType1__cellSelectionInfo {
		Q_RxLevMin_t	 q_RxLevMin;
		long	*q_RxLevMinOffset	/* OPTIONAL */;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} cellSelectionInfo;
	P_Max_t	*p_Max	/* OPTIONAL */;
	FreqBandIndicator_t	 freqBandIndicator;
	SchedulingInfoList_t	 schedulingInfoList;
	struct TDD_Config	*tdd_Config	/* OPTIONAL */;
	long	 si_WindowLength;
	long	 systemInfoValueTag;
	struct SystemInformationBlockType1_v890_IEs	*nonCriticalExtension	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SystemInformationBlockType1_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_cellBarred_6;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_intraFreqReselection_9;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_si_WindowLength_21;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_SystemInformationBlockType1;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/lte_rrc_asn_library/TDD-Config.h"
#include "rf_phreaker/lte_rrc_asn_library/SystemInformationBlockType1-v890-IEs.h"

#endif	/* _SystemInformationBlockType1_H_ */
#include <rf_phreaker/lte_rrc_asn_library/asn_internal.h>

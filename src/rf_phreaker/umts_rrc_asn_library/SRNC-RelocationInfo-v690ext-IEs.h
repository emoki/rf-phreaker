/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "Internode-definitions"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_SRNC_RelocationInfo_v690ext_IEs_H_
#define	_SRNC_RelocationInfo_v690ext_IEs_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/BIT_STRING.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct RAB_InformationSetupList_r6_ext;
struct MeasuredResultsOnRACHinterFreq;
struct MBMS_JoinedInformation_r6;
struct IntraFreqReportingCriteria_r6_ext;

/* SRNC-RelocationInfo-v690ext-IEs */
typedef struct SRNC_RelocationInfo_v690ext_IEs {
	BIT_STRING_t	*ueCapabilityContainer	/* OPTIONAL */;
	BIT_STRING_t	*ueCapabilityContainer_RSC	/* OPTIONAL */;
	BIT_STRING_t	*ueCapabilityContainer_UCI	/* OPTIONAL */;
	struct RAB_InformationSetupList_r6_ext	*rab_InformationSetupList	/* OPTIONAL */;
	struct MeasuredResultsOnRACHinterFreq	*measuredResultsOnRACHinterFreq	/* OPTIONAL */;
	struct MBMS_JoinedInformation_r6	*mbms_JoinedInformation	/* OPTIONAL */;
	struct IntraFreqReportingCriteria_r6_ext	*intraFreqReportingCriteria	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SRNC_RelocationInfo_v690ext_IEs_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SRNC_RelocationInfo_v690ext_IEs;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/RAB-InformationSetupList-r6-ext.h"
#include "rf_phreaker/umts_rrc_asn_library/MeasuredResultsOnRACHinterFreq.h"
#include "rf_phreaker/umts_rrc_asn_library/MBMS-JoinedInformation-r6.h"
#include "rf_phreaker/umts_rrc_asn_library/IntraFreqReportingCriteria-r6-ext.h"

#endif	/* _SRNC_RelocationInfo_v690ext_IEs_H_ */

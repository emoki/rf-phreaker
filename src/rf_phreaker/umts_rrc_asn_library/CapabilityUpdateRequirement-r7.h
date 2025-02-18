/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_CapabilityUpdateRequirement_r7_H_
#define	_CapabilityUpdateRequirement_r7_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/BOOLEAN.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct SystemSpecificCapUpdateReqList_r5;

/* CapabilityUpdateRequirement-r7 */
typedef struct CapabilityUpdateRequirement_r7 {
	BOOLEAN_t	 ue_RadioCapabilityFDDUpdateRequirement_FDD;
	BOOLEAN_t	 ue_RadioCapabilityTDDUpdateRequirement_TDD384;
	BOOLEAN_t	 ue_RadioCapabilityTDDUpdateRequirement_TDD768;
	BOOLEAN_t	 ue_RadioCapabilityTDDUpdateRequirement_TDD128;
	struct SystemSpecificCapUpdateReqList_r5	*systemSpecificCapUpdateReqList	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} CapabilityUpdateRequirement_r7_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_CapabilityUpdateRequirement_r7;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/SystemSpecificCapUpdateReqList-r5.h"

#endif	/* _CapabilityUpdateRequirement_r7_H_ */

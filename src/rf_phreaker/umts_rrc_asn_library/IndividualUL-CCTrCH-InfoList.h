/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_IndividualUL_CCTrCH_InfoList_H_
#define	_IndividualUL_CCTrCH_InfoList_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/asn_SEQUENCE_OF.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct IndividualUL_CCTrCH_Info;

/* IndividualUL-CCTrCH-InfoList */
typedef struct IndividualUL_CCTrCH_InfoList {
	A_SEQUENCE_OF(struct IndividualUL_CCTrCH_Info) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} IndividualUL_CCTrCH_InfoList_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_IndividualUL_CCTrCH_InfoList;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/IndividualUL-CCTrCH-Info.h"

#endif	/* _IndividualUL_CCTrCH_InfoList_H_ */

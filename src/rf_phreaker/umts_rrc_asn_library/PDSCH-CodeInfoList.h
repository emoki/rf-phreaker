/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_PDSCH_CodeInfoList_H_
#define	_PDSCH_CodeInfoList_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/asn_SEQUENCE_OF.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct PDSCH_CodeInfo;

/* PDSCH-CodeInfoList */
typedef struct PDSCH_CodeInfoList {
	A_SEQUENCE_OF(struct PDSCH_CodeInfo) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PDSCH_CodeInfoList_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PDSCH_CodeInfoList;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/PDSCH-CodeInfo.h"

#endif	/* _PDSCH_CodeInfoList_H_ */

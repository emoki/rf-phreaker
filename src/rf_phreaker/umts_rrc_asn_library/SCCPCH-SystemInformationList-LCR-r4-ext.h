/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_SCCPCH_SystemInformationList_LCR_r4_ext_H_
#define	_SCCPCH_SystemInformationList_LCR_r4_ext_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/asn_SEQUENCE_OF.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct SCCPCH_SystemInformation_LCR_r4_ext;

/* SCCPCH-SystemInformationList-LCR-r4-ext */
typedef struct SCCPCH_SystemInformationList_LCR_r4_ext {
	A_SEQUENCE_OF(struct SCCPCH_SystemInformation_LCR_r4_ext) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SCCPCH_SystemInformationList_LCR_r4_ext_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SCCPCH_SystemInformationList_LCR_r4_ext;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/SCCPCH-SystemInformation-LCR-r4-ext.h"

#endif	/* _SCCPCH_SystemInformationList_LCR_r4_ext_H_ */

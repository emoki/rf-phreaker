/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_SRB_InformationSetupList_r8_H_
#define	_SRB_InformationSetupList_r8_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/asn_SEQUENCE_OF.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct SRB_InformationSetup_r8;

/* SRB-InformationSetupList-r8 */
typedef struct SRB_InformationSetupList_r8 {
	A_SEQUENCE_OF(struct SRB_InformationSetup_r8) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SRB_InformationSetupList_r8_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SRB_InformationSetupList_r8;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/SRB-InformationSetup-r8.h"

#endif	/* _SRB_InformationSetupList_r8_H_ */

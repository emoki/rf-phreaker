/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_AuxInfoGANSS_ID1_H_
#define	_AuxInfoGANSS_ID1_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/asn_SEQUENCE_OF.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct AuxInfoGANSS_ID1_element;

/* AuxInfoGANSS-ID1 */
typedef struct AuxInfoGANSS_ID1 {
	A_SEQUENCE_OF(struct AuxInfoGANSS_ID1_element) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} AuxInfoGANSS_ID1_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_AuxInfoGANSS_ID1;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/AuxInfoGANSS-ID1-element.h"

#endif	/* _AuxInfoGANSS_ID1_H_ */

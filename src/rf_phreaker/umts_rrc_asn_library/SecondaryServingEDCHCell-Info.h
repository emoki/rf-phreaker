/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_SecondaryServingEDCHCell_Info_H_
#define	_SecondaryServingEDCHCell_Info_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/E-RNTI.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SecondaryServingEDCHCell-Info */
typedef struct SecondaryServingEDCHCell_Info {
	E_RNTI_t	*primary_E_RNTI	/* OPTIONAL */;
	E_RNTI_t	*secondary_E_RNTI	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SecondaryServingEDCHCell_Info_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SecondaryServingEDCHCell_Info;

#ifdef __cplusplus
}
#endif

#endif	/* _SecondaryServingEDCHCell_Info_H_ */

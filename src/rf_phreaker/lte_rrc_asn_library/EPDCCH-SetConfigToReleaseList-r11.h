/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_EPDCCH_SetConfigToReleaseList_r11_H_
#define	_EPDCCH_SetConfigToReleaseList_r11_H_


#include <rf_phreaker/lte_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/lte_rrc_asn_library/EPDCCH-SetConfigId-r11.h"
#include <rf_phreaker/lte_rrc_asn_library/asn_SEQUENCE_OF.h>
#include <rf_phreaker/lte_rrc_asn_library/constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* EPDCCH-SetConfigToReleaseList-r11 */
typedef struct EPDCCH_SetConfigToReleaseList_r11 {
	A_SEQUENCE_OF(EPDCCH_SetConfigId_r11_t) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} EPDCCH_SetConfigToReleaseList_r11_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_EPDCCH_SetConfigToReleaseList_r11;

#ifdef __cplusplus
}
#endif

#endif	/* _EPDCCH_SetConfigToReleaseList_r11_H_ */
#include <rf_phreaker/lte_rrc_asn_library/asn_internal.h>

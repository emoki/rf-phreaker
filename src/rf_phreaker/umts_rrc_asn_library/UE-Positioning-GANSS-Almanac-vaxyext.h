/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_UE_Positioning_GANSS_Almanac_vaxyext_H_
#define	_UE_Positioning_GANSS_Almanac_vaxyext_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/BOOLEAN.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* UE-Positioning-GANSS-Almanac-vaxyext */
typedef struct UE_Positioning_GANSS_Almanac_vaxyext {
	BOOLEAN_t	*complete_Almanac_Provided	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} UE_Positioning_GANSS_Almanac_vaxyext_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_UE_Positioning_GANSS_Almanac_vaxyext;

#ifdef __cplusplus
}
#endif

#endif	/* _UE_Positioning_GANSS_Almanac_vaxyext_H_ */

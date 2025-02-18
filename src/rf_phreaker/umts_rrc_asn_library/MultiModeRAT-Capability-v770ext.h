/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_MultiModeRAT_Capability_v770ext_H_
#define	_MultiModeRAT_Capability_v770ext_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeEnumerated.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum MultiModeRAT_Capability_v770ext__supportOfPSHandoverToGAN {
	MultiModeRAT_Capability_v770ext__supportOfPSHandoverToGAN_doesSupportPSHandoverToGAN	= 0
} e_MultiModeRAT_Capability_v770ext__supportOfPSHandoverToGAN;

/* MultiModeRAT-Capability-v770ext */
typedef struct MultiModeRAT_Capability_v770ext {
	long	*supportOfPSHandoverToGAN	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MultiModeRAT_Capability_v770ext_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_supportOfPSHandoverToGAN_2;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_MultiModeRAT_Capability_v770ext;

#ifdef __cplusplus
}
#endif

#endif	/* _MultiModeRAT_Capability_v770ext_H_ */

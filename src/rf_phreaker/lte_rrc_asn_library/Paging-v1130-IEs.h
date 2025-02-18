/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_Paging_v1130_IEs_H_
#define	_Paging_v1130_IEs_H_


#include <rf_phreaker/lte_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/lte_rrc_asn_library/NativeEnumerated.h>
#include <rf_phreaker/lte_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum Paging_v1130_IEs__eab_ParamModification_r11 {
	Paging_v1130_IEs__eab_ParamModification_r11_true	= 0
} e_Paging_v1130_IEs__eab_ParamModification_r11;

/* Paging-v1130-IEs */
typedef struct Paging_v1130_IEs {
	long	*eab_ParamModification_r11	/* OPTIONAL */;
	struct Paging_v1130_IEs__nonCriticalExtension {
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *nonCriticalExtension;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Paging_v1130_IEs_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_eab_ParamModification_r11_2;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_Paging_v1130_IEs;

#ifdef __cplusplus
}
#endif

#endif	/* _Paging_v1130_IEs_H_ */
#include <rf_phreaker/lte_rrc_asn_library/asn_internal.h>

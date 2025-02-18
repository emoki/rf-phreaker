/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_MIMO_Parameters_v7g0ext_H_
#define	_MIMO_Parameters_v7g0ext_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeEnumerated.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum MIMO_Parameters_v7g0ext__precodingWeightSetRestriction {
	MIMO_Parameters_v7g0ext__precodingWeightSetRestriction_true	= 0
} e_MIMO_Parameters_v7g0ext__precodingWeightSetRestriction;

/* MIMO-Parameters-v7g0ext */
typedef struct MIMO_Parameters_v7g0ext {
	long	*precodingWeightSetRestriction	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MIMO_Parameters_v7g0ext_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_precodingWeightSetRestriction_2;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_MIMO_Parameters_v7g0ext;

#ifdef __cplusplus
}
#endif

#endif	/* _MIMO_Parameters_v7g0ext_H_ */

/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "PDU-definitions"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_CompleteSIB_H_
#define	_CompleteSIB_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/SIB-Type.h"
#include <rf_phreaker/umts_rrc_asn_library/BIT_STRING.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* CompleteSIB */
typedef struct CompleteSIB {
	SIB_Type_t	 sib_Type;
	BIT_STRING_t	 sib_Data_fixed;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} CompleteSIB_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_CompleteSIB;

#ifdef __cplusplus
}
#endif

#endif	/* _CompleteSIB_H_ */

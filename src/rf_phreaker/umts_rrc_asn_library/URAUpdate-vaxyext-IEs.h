/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "PDU-definitions"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_URAUpdate_vaxyext_IEs_H_
#define	_URAUpdate_vaxyext_IEs_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeEnumerated.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum URAUpdate_vaxyext_IEs__loggedMeasRequest {
	URAUpdate_vaxyext_IEs__loggedMeasRequest_true	= 0
} e_URAUpdate_vaxyext_IEs__loggedMeasRequest;

/* URAUpdate-vaxyext-IEs */
typedef struct URAUpdate_vaxyext_IEs {
	long	*loggedMeasRequest	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} URAUpdate_vaxyext_IEs_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_loggedMeasRequest_2;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_URAUpdate_vaxyext_IEs;

#ifdef __cplusplus
}
#endif

#endif	/* _URAUpdate_vaxyext_IEs_H_ */

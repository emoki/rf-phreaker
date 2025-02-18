/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_UE_CapabilityRequest_H_
#define	_UE_CapabilityRequest_H_


#include <rf_phreaker/lte_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/lte_rrc_asn_library/RAT-Type.h"
#include <rf_phreaker/lte_rrc_asn_library/asn_SEQUENCE_OF.h>
#include <rf_phreaker/lte_rrc_asn_library/constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* UE-CapabilityRequest */
typedef struct UE_CapabilityRequest {
	A_SEQUENCE_OF(RAT_Type_t) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} UE_CapabilityRequest_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_UE_CapabilityRequest;

#ifdef __cplusplus
}
#endif

#endif	/* _UE_CapabilityRequest_H_ */
#include <rf_phreaker/lte_rrc_asn_library/asn_internal.h>

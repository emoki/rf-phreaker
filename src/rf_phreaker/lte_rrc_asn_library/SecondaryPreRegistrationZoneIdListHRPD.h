/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_SecondaryPreRegistrationZoneIdListHRPD_H_
#define	_SecondaryPreRegistrationZoneIdListHRPD_H_


#include <rf_phreaker/lte_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/lte_rrc_asn_library/PreRegistrationZoneIdHRPD.h"
#include <rf_phreaker/lte_rrc_asn_library/asn_SEQUENCE_OF.h>
#include <rf_phreaker/lte_rrc_asn_library/constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SecondaryPreRegistrationZoneIdListHRPD */
typedef struct SecondaryPreRegistrationZoneIdListHRPD {
	A_SEQUENCE_OF(PreRegistrationZoneIdHRPD_t) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SecondaryPreRegistrationZoneIdListHRPD_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SecondaryPreRegistrationZoneIdListHRPD;

#ifdef __cplusplus
}
#endif

#endif	/* _SecondaryPreRegistrationZoneIdListHRPD_H_ */
#include <rf_phreaker/lte_rrc_asn_library/asn_internal.h>

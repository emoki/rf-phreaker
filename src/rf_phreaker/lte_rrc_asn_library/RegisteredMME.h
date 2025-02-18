/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_RegisteredMME_H_
#define	_RegisteredMME_H_


#include <rf_phreaker/lte_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/lte_rrc_asn_library/BIT_STRING.h>
#include "rf_phreaker/lte_rrc_asn_library/MMEC.h"
#include <rf_phreaker/lte_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct PLMN_Identity;

/* RegisteredMME */
typedef struct RegisteredMME {
	struct PLMN_Identity	*plmn_Identity	/* OPTIONAL */;
	BIT_STRING_t	 mmegi;
	MMEC_t	 mmec;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RegisteredMME_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RegisteredMME;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/lte_rrc_asn_library/PLMN-Identity.h"

#endif	/* _RegisteredMME_H_ */
#include <rf_phreaker/lte_rrc_asn_library/asn_internal.h>

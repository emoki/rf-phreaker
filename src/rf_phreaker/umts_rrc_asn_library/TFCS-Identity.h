/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_TFCS_Identity_H_
#define	_TFCS_Identity_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/TFCS-IdentityPlain.h"
#include <rf_phreaker/umts_rrc_asn_library/BOOLEAN.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* TFCS-Identity */
typedef struct TFCS_Identity {
	TFCS_IdentityPlain_t	*tfcs_ID	/* DEFAULT 1 */;
	BOOLEAN_t	 sharedChannelIndicator;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} TFCS_Identity_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_TFCS_Identity;

#ifdef __cplusplus
}
#endif

#endif	/* _TFCS_Identity_H_ */

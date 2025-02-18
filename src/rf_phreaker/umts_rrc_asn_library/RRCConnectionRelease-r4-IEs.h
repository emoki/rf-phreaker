/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "PDU-definitions"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_RRCConnectionRelease_r4_IEs_H_
#define	_RRCConnectionRelease_r4_IEs_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/N-308.h"
#include "rf_phreaker/umts_rrc_asn_library/ReleaseCause.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct Rplmn_Information_r4;

/* RRCConnectionRelease-r4-IEs */
typedef struct RRCConnectionRelease_r4_IEs {
	N_308_t	*n_308	/* OPTIONAL */;
	ReleaseCause_t	 releaseCause;
	struct Rplmn_Information_r4	*rplmn_information	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RRCConnectionRelease_r4_IEs_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RRCConnectionRelease_r4_IEs;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/Rplmn-Information-r4.h"

#endif	/* _RRCConnectionRelease_r4_IEs_H_ */

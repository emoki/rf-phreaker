/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "PDU-definitions"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_RadioBearerReconfigurationFailure_H_
#define	_RadioBearerReconfigurationFailure_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/RRC-TransactionIdentifier.h"
#include "rf_phreaker/umts_rrc_asn_library/FailureCauseWithProtErr.h"
#include <rf_phreaker/umts_rrc_asn_library/BIT_STRING.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct RB_IdentityList;

/* RadioBearerReconfigurationFailure */
typedef struct RadioBearerReconfigurationFailure {
	RRC_TransactionIdentifier_t	 rrc_TransactionIdentifier;
	FailureCauseWithProtErr_t	 failureCause;
	struct RB_IdentityList	*potentiallySuccesfulBearerList	/* OPTIONAL */;
	struct RadioBearerReconfigurationFailure__laterNonCriticalExtensions {
		BIT_STRING_t	*radioBearerReconfigurationFailure_r3_add_ext	/* OPTIONAL */;
		struct RadioBearerReconfigurationFailure__laterNonCriticalExtensions__nonCriticalExtensions {
			
			/* Context for parsing across buffer boundaries */
			asn_struct_ctx_t _asn_ctx;
		} *nonCriticalExtensions;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *laterNonCriticalExtensions;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RadioBearerReconfigurationFailure_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RadioBearerReconfigurationFailure;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/RB-IdentityList.h"

#endif	/* _RadioBearerReconfigurationFailure_H_ */

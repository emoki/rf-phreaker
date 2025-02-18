/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "PDU-definitions"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_RRC_FailureInfo_H_
#define	_RRC_FailureInfo_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/RRC-FailureInfo-r3-IEs.h"
#include <rf_phreaker/umts_rrc_asn_library/BIT_STRING.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum RRC_FailureInfo_PR {
	RRC_FailureInfo_PR_NOTHING,	/* No components present */
	RRC_FailureInfo_PR_r3,
	RRC_FailureInfo_PR_criticalExtensions
} RRC_FailureInfo_PR;

/* RRC-FailureInfo */
typedef struct RRC_FailureInfo {
	RRC_FailureInfo_PR present;
	union RRC_FailureInfo_u {
		struct RRC_FailureInfo__r3 {
			RRC_FailureInfo_r3_IEs_t	 rRC_FailureInfo_r3;
			struct RRC_FailureInfo__r3__laterNonCriticalExtensions {
				BIT_STRING_t	*rrc_FailureInfo_r3_add_ext	/* OPTIONAL */;
				struct RRC_FailureInfo__r3__laterNonCriticalExtensions__nonCriticalExtensions {
					
					/* Context for parsing across buffer boundaries */
					asn_struct_ctx_t _asn_ctx;
				} *nonCriticalExtensions;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} *laterNonCriticalExtensions;
			
			/* Context for parsing across buffer boundaries */
			asn_struct_ctx_t _asn_ctx;
		} r3;
		struct RRC_FailureInfo__criticalExtensions {
			
			/* Context for parsing across buffer boundaries */
			asn_struct_ctx_t _asn_ctx;
		} criticalExtensions;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RRC_FailureInfo_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RRC_FailureInfo;

#ifdef __cplusplus
}
#endif

#endif	/* _RRC_FailureInfo_H_ */

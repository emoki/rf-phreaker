/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_RRCConnectionRelease_H_
#define	_RRCConnectionRelease_H_


#include <rf_phreaker/lte_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/lte_rrc_asn_library/RRC-TransactionIdentifier.h"
#include "rf_phreaker/lte_rrc_asn_library/RRCConnectionRelease-r8-IEs.h"
#include <rf_phreaker/lte_rrc_asn_library/NULL.h>
#include <rf_phreaker/lte_rrc_asn_library/constr_CHOICE.h>
#include <rf_phreaker/lte_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum RRCConnectionRelease__criticalExtensions_PR {
	RRCConnectionRelease__criticalExtensions_PR_NOTHING,	/* No components present */
	RRCConnectionRelease__criticalExtensions_PR_c1,
	RRCConnectionRelease__criticalExtensions_PR_criticalExtensionsFuture
} RRCConnectionRelease__criticalExtensions_PR;
typedef enum RRCConnectionRelease__criticalExtensions__c1_PR {
	RRCConnectionRelease__criticalExtensions__c1_PR_NOTHING,	/* No components present */
	RRCConnectionRelease__criticalExtensions__c1_PR_rrcConnectionRelease_r8,
	RRCConnectionRelease__criticalExtensions__c1_PR_spare3,
	RRCConnectionRelease__criticalExtensions__c1_PR_spare2,
	RRCConnectionRelease__criticalExtensions__c1_PR_spare1
} RRCConnectionRelease__criticalExtensions__c1_PR;

/* RRCConnectionRelease */
typedef struct RRCConnectionRelease {
	RRC_TransactionIdentifier_t	 rrc_TransactionIdentifier;
	struct RRCConnectionRelease__criticalExtensions {
		RRCConnectionRelease__criticalExtensions_PR present;
		union RRCConnectionRelease__criticalExtensions_u {
			struct RRCConnectionRelease__criticalExtensions__c1 {
				RRCConnectionRelease__criticalExtensions__c1_PR present;
				union RRCConnectionRelease__criticalExtensions__c1_u {
					RRCConnectionRelease_r8_IEs_t	 rrcConnectionRelease_r8;
					NULL_t	 spare3;
					NULL_t	 spare2;
					NULL_t	 spare1;
				} choice;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} c1;
			struct RRCConnectionRelease__criticalExtensions__criticalExtensionsFuture {
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} criticalExtensionsFuture;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} criticalExtensions;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RRCConnectionRelease_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RRCConnectionRelease;

#ifdef __cplusplus
}
#endif

#endif	/* _RRCConnectionRelease_H_ */
#include <rf_phreaker/lte_rrc_asn_library/asn_internal.h>

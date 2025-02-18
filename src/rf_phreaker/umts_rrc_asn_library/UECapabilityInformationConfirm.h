/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "PDU-definitions"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_UECapabilityInformationConfirm_H_
#define	_UECapabilityInformationConfirm_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/UECapabilityInformationConfirm-r3-IEs.h"
#include <rf_phreaker/umts_rrc_asn_library/BIT_STRING.h>
#include "rf_phreaker/umts_rrc_asn_library/UECapabilityInformationConfirm-v770ext-IEs.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>
#include "rf_phreaker/umts_rrc_asn_library/RRC-TransactionIdentifier.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum UECapabilityInformationConfirm_PR {
	UECapabilityInformationConfirm_PR_NOTHING,	/* No components present */
	UECapabilityInformationConfirm_PR_r3,
	UECapabilityInformationConfirm_PR_later_than_r3
} UECapabilityInformationConfirm_PR;

/* UECapabilityInformationConfirm */
typedef struct UECapabilityInformationConfirm {
	UECapabilityInformationConfirm_PR present;
	union UECapabilityInformationConfirm_u {
		struct UECapabilityInformationConfirm__r3 {
			UECapabilityInformationConfirm_r3_IEs_t	 ueCapabilityInformationConfirm_r3;
			struct UECapabilityInformationConfirm__r3__laterNonCriticalExtensions {
				BIT_STRING_t	*ueCapabilityInformationConfirm_r3_add_ext	/* OPTIONAL */;
				struct UECapabilityInformationConfirm__r3__laterNonCriticalExtensions__v770NonCriticalExtensions {
					UECapabilityInformationConfirm_v770ext_IEs_t	 ueCapabilityInformationConfirm_v770ext;
					struct UECapabilityInformationConfirm__r3__laterNonCriticalExtensions__v770NonCriticalExtensions__nonCriticalExtensions {
						
						/* Context for parsing across buffer boundaries */
						asn_struct_ctx_t _asn_ctx;
					} *nonCriticalExtensions;
					
					/* Context for parsing across buffer boundaries */
					asn_struct_ctx_t _asn_ctx;
				} *v770NonCriticalExtensions;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} *laterNonCriticalExtensions;
			
			/* Context for parsing across buffer boundaries */
			asn_struct_ctx_t _asn_ctx;
		} r3;
		struct UECapabilityInformationConfirm__later_than_r3 {
			RRC_TransactionIdentifier_t	 rrc_TransactionIdentifier;
			struct UECapabilityInformationConfirm__later_than_r3__criticalExtensions {
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} criticalExtensions;
			
			/* Context for parsing across buffer boundaries */
			asn_struct_ctx_t _asn_ctx;
		} later_than_r3;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} UECapabilityInformationConfirm_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_UECapabilityInformationConfirm;

#ifdef __cplusplus
}
#endif

#endif	/* _UECapabilityInformationConfirm_H_ */

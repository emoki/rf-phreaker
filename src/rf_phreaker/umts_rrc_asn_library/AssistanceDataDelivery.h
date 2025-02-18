/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "PDU-definitions"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_AssistanceDataDelivery_H_
#define	_AssistanceDataDelivery_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/AssistanceDataDelivery-r3-IEs.h"
#include "rf_phreaker/umts_rrc_asn_library/AssistanceDataDelivery-v3a0ext.h"
#include <rf_phreaker/umts_rrc_asn_library/BIT_STRING.h>
#include "rf_phreaker/umts_rrc_asn_library/AssistanceDataDelivery-v4b0ext-IEs.h"
#include "rf_phreaker/umts_rrc_asn_library/AssistanceDataDelivery-v770ext-IEs.h"
#include "rf_phreaker/umts_rrc_asn_library/AssistanceDataDelivery-v860ext-IEs.h"
#include "rf_phreaker/umts_rrc_asn_library/AssistanceDataDelivery-v920ext-IEs.h"
#include "rf_phreaker/umts_rrc_asn_library/AssistanceDataDelivery-vaxyext-IEs.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>
#include "rf_phreaker/umts_rrc_asn_library/RRC-TransactionIdentifier.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum AssistanceDataDelivery_PR {
	AssistanceDataDelivery_PR_NOTHING,	/* No components present */
	AssistanceDataDelivery_PR_r3,
	AssistanceDataDelivery_PR_later_than_r3
} AssistanceDataDelivery_PR;

/* AssistanceDataDelivery */
typedef struct AssistanceDataDelivery {
	AssistanceDataDelivery_PR present;
	union AssistanceDataDelivery_u {
		struct AssistanceDataDelivery__r3 {
			AssistanceDataDelivery_r3_IEs_t	 assistanceDataDelivery_r3;
			struct AssistanceDataDelivery__r3__v3a0NonCriticalExtensions {
				AssistanceDataDelivery_v3a0ext_t	 assistanceDataDelivery_v3a0ext;
				struct AssistanceDataDelivery__r3__v3a0NonCriticalExtensions__laterNonCriticalExtensions {
					BIT_STRING_t	*assistanceDataDelivery_r3_add_ext	/* OPTIONAL */;
					struct AssistanceDataDelivery__r3__v3a0NonCriticalExtensions__laterNonCriticalExtensions__v4b0NonCriticalExtensions {
						AssistanceDataDelivery_v4b0ext_IEs_t	 assistanceDataDelivery_v4b0ext;
						struct AssistanceDataDelivery__r3__v3a0NonCriticalExtensions__laterNonCriticalExtensions__v4b0NonCriticalExtensions__v770NonCriticalExtension {
							AssistanceDataDelivery_v770ext_IEs_t	 assistanceDataDelivery_v770ext;
							struct AssistanceDataDelivery__r3__v3a0NonCriticalExtensions__laterNonCriticalExtensions__v4b0NonCriticalExtensions__v770NonCriticalExtension__v860NonCriticalExtension {
								AssistanceDataDelivery_v860ext_IEs_t	 assistanceDataDelivery_v860ext;
								struct AssistanceDataDelivery__r3__v3a0NonCriticalExtensions__laterNonCriticalExtensions__v4b0NonCriticalExtensions__v770NonCriticalExtension__v860NonCriticalExtension__v920NonCriticalExtension {
									AssistanceDataDelivery_v920ext_IEs_t	 assistanceDataDelivery_v920ext;
									struct AssistanceDataDelivery__r3__v3a0NonCriticalExtensions__laterNonCriticalExtensions__v4b0NonCriticalExtensions__v770NonCriticalExtension__v860NonCriticalExtension__v920NonCriticalExtension__vaxyNonCriticalExtension {
										AssistanceDataDelivery_vaxyext_IEs_t	 assistanceDataDelivery_vaxyext;
										struct AssistanceDataDelivery__r3__v3a0NonCriticalExtensions__laterNonCriticalExtensions__v4b0NonCriticalExtensions__v770NonCriticalExtension__v860NonCriticalExtension__v920NonCriticalExtension__vaxyNonCriticalExtension__nonCriticalExtensions {
											
											/* Context for parsing across buffer boundaries */
											asn_struct_ctx_t _asn_ctx;
										} *nonCriticalExtensions;
										
										/* Context for parsing across buffer boundaries */
										asn_struct_ctx_t _asn_ctx;
									} *vaxyNonCriticalExtension;
									
									/* Context for parsing across buffer boundaries */
									asn_struct_ctx_t _asn_ctx;
								} *v920NonCriticalExtension;
								
								/* Context for parsing across buffer boundaries */
								asn_struct_ctx_t _asn_ctx;
							} *v860NonCriticalExtension;
							
							/* Context for parsing across buffer boundaries */
							asn_struct_ctx_t _asn_ctx;
						} *v770NonCriticalExtension;
						
						/* Context for parsing across buffer boundaries */
						asn_struct_ctx_t _asn_ctx;
					} *v4b0NonCriticalExtensions;
					
					/* Context for parsing across buffer boundaries */
					asn_struct_ctx_t _asn_ctx;
				} *laterNonCriticalExtensions;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} *v3a0NonCriticalExtensions;
			
			/* Context for parsing across buffer boundaries */
			asn_struct_ctx_t _asn_ctx;
		} r3;
		struct AssistanceDataDelivery__later_than_r3 {
			RRC_TransactionIdentifier_t	 rrc_TransactionIdentifier;
			struct AssistanceDataDelivery__later_than_r3__criticalExtensions {
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} criticalExtensions;
			
			/* Context for parsing across buffer boundaries */
			asn_struct_ctx_t _asn_ctx;
		} later_than_r3;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} AssistanceDataDelivery_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_AssistanceDataDelivery;

#ifdef __cplusplus
}
#endif

#endif	/* _AssistanceDataDelivery_H_ */

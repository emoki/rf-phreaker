/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-InterNodeDefinitions"
 * 	found in "EUTRA-InterNodeDefinitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_UERadioAccessCapabilityInformation_H_
#define	_UERadioAccessCapabilityInformation_H_


#include <rf_phreaker/lte_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/lte_rrc_asn_library/UERadioAccessCapabilityInformation-r8-IEs.h"
#include <rf_phreaker/lte_rrc_asn_library/NULL.h>
#include <rf_phreaker/lte_rrc_asn_library/constr_CHOICE.h>
#include <rf_phreaker/lte_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum UERadioAccessCapabilityInformation__criticalExtensions_PR {
	UERadioAccessCapabilityInformation__criticalExtensions_PR_NOTHING,	/* No components present */
	UERadioAccessCapabilityInformation__criticalExtensions_PR_c1,
	UERadioAccessCapabilityInformation__criticalExtensions_PR_criticalExtensionsFuture
} UERadioAccessCapabilityInformation__criticalExtensions_PR;
typedef enum UERadioAccessCapabilityInformation__criticalExtensions__c1_PR {
	UERadioAccessCapabilityInformation__criticalExtensions__c1_PR_NOTHING,	/* No components present */
	UERadioAccessCapabilityInformation__criticalExtensions__c1_PR_ueRadioAccessCapabilityInformation_r8,
	UERadioAccessCapabilityInformation__criticalExtensions__c1_PR_spare7,
	UERadioAccessCapabilityInformation__criticalExtensions__c1_PR_spare6,
	UERadioAccessCapabilityInformation__criticalExtensions__c1_PR_spare5,
	UERadioAccessCapabilityInformation__criticalExtensions__c1_PR_spare4,
	UERadioAccessCapabilityInformation__criticalExtensions__c1_PR_spare3,
	UERadioAccessCapabilityInformation__criticalExtensions__c1_PR_spare2,
	UERadioAccessCapabilityInformation__criticalExtensions__c1_PR_spare1
} UERadioAccessCapabilityInformation__criticalExtensions__c1_PR;

/* UERadioAccessCapabilityInformation */
typedef struct UERadioAccessCapabilityInformation {
	struct UERadioAccessCapabilityInformation__criticalExtensions {
		UERadioAccessCapabilityInformation__criticalExtensions_PR present;
		union UERadioAccessCapabilityInformation__criticalExtensions_u {
			struct UERadioAccessCapabilityInformation__criticalExtensions__c1 {
				UERadioAccessCapabilityInformation__criticalExtensions__c1_PR present;
				union UERadioAccessCapabilityInformation__criticalExtensions__c1_u {
					UERadioAccessCapabilityInformation_r8_IEs_t	 ueRadioAccessCapabilityInformation_r8;
					NULL_t	 spare7;
					NULL_t	 spare6;
					NULL_t	 spare5;
					NULL_t	 spare4;
					NULL_t	 spare3;
					NULL_t	 spare2;
					NULL_t	 spare1;
				} choice;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} c1;
			struct UERadioAccessCapabilityInformation__criticalExtensions__criticalExtensionsFuture {
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} criticalExtensionsFuture;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} criticalExtensions;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} UERadioAccessCapabilityInformation_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_UERadioAccessCapabilityInformation;

#ifdef __cplusplus
}
#endif

#endif	/* _UERadioAccessCapabilityInformation_H_ */
#include <rf_phreaker/lte_rrc_asn_library/asn_internal.h>

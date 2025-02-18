/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_InterFreqRSTDMeasurementIndication_r10_H_
#define	_InterFreqRSTDMeasurementIndication_r10_H_


#include <rf_phreaker/lte_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/lte_rrc_asn_library/InterFreqRSTDMeasurementIndication-r10-IEs.h"
#include <rf_phreaker/lte_rrc_asn_library/NULL.h>
#include <rf_phreaker/lte_rrc_asn_library/constr_CHOICE.h>
#include <rf_phreaker/lte_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum InterFreqRSTDMeasurementIndication_r10__criticalExtensions_PR {
	InterFreqRSTDMeasurementIndication_r10__criticalExtensions_PR_NOTHING,	/* No components present */
	InterFreqRSTDMeasurementIndication_r10__criticalExtensions_PR_c1,
	InterFreqRSTDMeasurementIndication_r10__criticalExtensions_PR_criticalExtensionsFuture
} InterFreqRSTDMeasurementIndication_r10__criticalExtensions_PR;
typedef enum InterFreqRSTDMeasurementIndication_r10__criticalExtensions__c1_PR {
	InterFreqRSTDMeasurementIndication_r10__criticalExtensions__c1_PR_NOTHING,	/* No components present */
	InterFreqRSTDMeasurementIndication_r10__criticalExtensions__c1_PR_interFreqRSTDMeasurementIndication_r10,
	InterFreqRSTDMeasurementIndication_r10__criticalExtensions__c1_PR_spare3,
	InterFreqRSTDMeasurementIndication_r10__criticalExtensions__c1_PR_spare2,
	InterFreqRSTDMeasurementIndication_r10__criticalExtensions__c1_PR_spare1
} InterFreqRSTDMeasurementIndication_r10__criticalExtensions__c1_PR;

/* InterFreqRSTDMeasurementIndication-r10 */
typedef struct InterFreqRSTDMeasurementIndication_r10 {
	struct InterFreqRSTDMeasurementIndication_r10__criticalExtensions {
		InterFreqRSTDMeasurementIndication_r10__criticalExtensions_PR present;
		union InterFreqRSTDMeasurementIndication_r10__criticalExtensions_u {
			struct InterFreqRSTDMeasurementIndication_r10__criticalExtensions__c1 {
				InterFreqRSTDMeasurementIndication_r10__criticalExtensions__c1_PR present;
				union InterFreqRSTDMeasurementIndication_r10__criticalExtensions__c1_u {
					InterFreqRSTDMeasurementIndication_r10_IEs_t	 interFreqRSTDMeasurementIndication_r10;
					NULL_t	 spare3;
					NULL_t	 spare2;
					NULL_t	 spare1;
				} choice;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} c1;
			struct InterFreqRSTDMeasurementIndication_r10__criticalExtensions__criticalExtensionsFuture {
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} criticalExtensionsFuture;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} criticalExtensions;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} InterFreqRSTDMeasurementIndication_r10_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_InterFreqRSTDMeasurementIndication_r10;

#ifdef __cplusplus
}
#endif

#endif	/* _InterFreqRSTDMeasurementIndication_r10_H_ */
#include <rf_phreaker/lte_rrc_asn_library/asn_internal.h>

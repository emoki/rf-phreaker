/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_SignalledGainFactors_H_
#define	_SignalledGainFactors_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/GainFactor.h"
#include "rf_phreaker/umts_rrc_asn_library/ReferenceTFC-ID.h"
#include <rf_phreaker/umts_rrc_asn_library/NULL.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum SignalledGainFactors__modeSpecificInfo_PR {
	SignalledGainFactors__modeSpecificInfo_PR_NOTHING,	/* No components present */
	SignalledGainFactors__modeSpecificInfo_PR_fdd,
	SignalledGainFactors__modeSpecificInfo_PR_tdd
} SignalledGainFactors__modeSpecificInfo_PR;

/* SignalledGainFactors */
typedef struct SignalledGainFactors {
	struct SignalledGainFactors__modeSpecificInfo {
		SignalledGainFactors__modeSpecificInfo_PR present;
		union SignalledGainFactors__modeSpecificInfo_u {
			struct SignalledGainFactors__modeSpecificInfo__fdd {
				GainFactor_t	 gainFactorBetaC;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} fdd;
			NULL_t	 tdd;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} modeSpecificInfo;
	GainFactor_t	 gainFactorBetaD;
	ReferenceTFC_ID_t	*referenceTFC_ID	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SignalledGainFactors_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SignalledGainFactors;

#ifdef __cplusplus
}
#endif

#endif	/* _SignalledGainFactors_H_ */

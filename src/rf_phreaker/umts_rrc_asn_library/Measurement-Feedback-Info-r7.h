/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_Measurement_Feedback_Info_r7_H_
#define	_Measurement_Feedback_Info_r7_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NULL.h>
#include "rf_phreaker/umts_rrc_asn_library/MeasurementPowerOffset.h"
#include "rf_phreaker/umts_rrc_asn_library/Feedback-cycle-r7.h"
#include "rf_phreaker/umts_rrc_asn_library/CQI-RepetitionFactor.h"
#include "rf_phreaker/umts_rrc_asn_library/DeltaCQI.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum Measurement_Feedback_Info_r7__modeSpecificInfo_PR {
	Measurement_Feedback_Info_r7__modeSpecificInfo_PR_NOTHING,	/* No components present */
	Measurement_Feedback_Info_r7__modeSpecificInfo_PR_fdd,
	Measurement_Feedback_Info_r7__modeSpecificInfo_PR_tdd
} Measurement_Feedback_Info_r7__modeSpecificInfo_PR;

/* Measurement-Feedback-Info-r7 */
typedef struct Measurement_Feedback_Info_r7 {
	struct Measurement_Feedback_Info_r7__modeSpecificInfo {
		Measurement_Feedback_Info_r7__modeSpecificInfo_PR present;
		union Measurement_Feedback_Info_r7__modeSpecificInfo_u {
			struct Measurement_Feedback_Info_r7__modeSpecificInfo__fdd {
				MeasurementPowerOffset_t	 measurementPowerOffset;
				Feedback_cycle_r7_t	 feedback_cycle;
				CQI_RepetitionFactor_t	 cqi_RepetitionFactor;
				DeltaCQI_t	 deltaCQI;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} fdd;
			NULL_t	 tdd;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} modeSpecificInfo;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Measurement_Feedback_Info_r7_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Measurement_Feedback_Info_r7;

#ifdef __cplusplus
}
#endif

#endif	/* _Measurement_Feedback_Info_r7_H_ */

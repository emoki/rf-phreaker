/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_UplinkAdditionalTimeslots_H_
#define	_UplinkAdditionalTimeslots_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/TimeslotNumber.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>
#include "rf_phreaker/umts_rrc_asn_library/IndividualTimeslotInfo.h"
#include "rf_phreaker/umts_rrc_asn_library/UL-TS-ChannelisationCodeList.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum UplinkAdditionalTimeslots__parameters_PR {
	UplinkAdditionalTimeslots__parameters_PR_NOTHING,	/* No components present */
	UplinkAdditionalTimeslots__parameters_PR_sameAsLast,
	UplinkAdditionalTimeslots__parameters_PR_newParameters
} UplinkAdditionalTimeslots__parameters_PR;

/* UplinkAdditionalTimeslots */
typedef struct UplinkAdditionalTimeslots {
	struct UplinkAdditionalTimeslots__parameters {
		UplinkAdditionalTimeslots__parameters_PR present;
		union UplinkAdditionalTimeslots__parameters_u {
			struct UplinkAdditionalTimeslots__parameters__sameAsLast {
				TimeslotNumber_t	 timeslotNumber;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} sameAsLast;
			struct UplinkAdditionalTimeslots__parameters__newParameters {
				IndividualTimeslotInfo_t	 individualTimeslotInfo;
				UL_TS_ChannelisationCodeList_t	 ul_TS_ChannelisationCodeList;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} newParameters;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} parameters;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} UplinkAdditionalTimeslots_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_UplinkAdditionalTimeslots;

#ifdef __cplusplus
}
#endif

#endif	/* _UplinkAdditionalTimeslots_H_ */

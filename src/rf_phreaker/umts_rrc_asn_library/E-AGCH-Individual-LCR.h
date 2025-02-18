/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_E_AGCH_Individual_LCR_H_
#define	_E_AGCH_Individual_LCR_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/TimeslotNumber-LCR-r4.h"
#include "rf_phreaker/umts_rrc_asn_library/HS-ChannelisationCode-LCR.h"
#include <rf_phreaker/umts_rrc_asn_library/NativeInteger.h>
#include <rf_phreaker/umts_rrc_asn_library/NULL.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_CHOICE.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum E_AGCH_Individual_LCR__midambleAllocationMode_PR {
	E_AGCH_Individual_LCR__midambleAllocationMode_PR_NOTHING,	/* No components present */
	E_AGCH_Individual_LCR__midambleAllocationMode_PR_defaultMidamble,
	E_AGCH_Individual_LCR__midambleAllocationMode_PR_commonMidamble,
	E_AGCH_Individual_LCR__midambleAllocationMode_PR_ueSpecificMidamble
} E_AGCH_Individual_LCR__midambleAllocationMode_PR;

/* E-AGCH-Individual-LCR */
typedef struct E_AGCH_Individual_LCR {
	TimeslotNumber_LCR_r4_t	 timeslotNumber;
	HS_ChannelisationCode_LCR_t	 firstChannelisationCode;
	HS_ChannelisationCode_LCR_t	 secondChannelisationCode;
	struct E_AGCH_Individual_LCR__midambleAllocationMode {
		E_AGCH_Individual_LCR__midambleAllocationMode_PR present;
		union E_AGCH_Individual_LCR__midambleAllocationMode_u {
			NULL_t	 defaultMidamble;
			NULL_t	 commonMidamble;
			long	 ueSpecificMidamble;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} midambleAllocationMode;
	long	 midambleConfiguration;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} E_AGCH_Individual_LCR_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_E_AGCH_Individual_LCR;

#ifdef __cplusplus
}
#endif

#endif	/* _E_AGCH_Individual_LCR_H_ */

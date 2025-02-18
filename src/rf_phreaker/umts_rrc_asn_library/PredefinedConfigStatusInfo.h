/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_PredefinedConfigStatusInfo_H_
#define	_PredefinedConfigStatusInfo_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NULL.h>
#include "rf_phreaker/umts_rrc_asn_library/PredefinedConfigValueTag.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum PredefinedConfigStatusInfo_PR {
	PredefinedConfigStatusInfo_PR_NOTHING,	/* No components present */
	PredefinedConfigStatusInfo_PR_storedWithValueTagSameAsPrevius,
	PredefinedConfigStatusInfo_PR_other
} PredefinedConfigStatusInfo_PR;
typedef enum PredefinedConfigStatusInfo__other_PR {
	PredefinedConfigStatusInfo__other_PR_NOTHING,	/* No components present */
	PredefinedConfigStatusInfo__other_PR_notStored,
	PredefinedConfigStatusInfo__other_PR_storedWithDifferentValueTag
} PredefinedConfigStatusInfo__other_PR;

/* PredefinedConfigStatusInfo */
typedef struct PredefinedConfigStatusInfo {
	PredefinedConfigStatusInfo_PR present;
	union PredefinedConfigStatusInfo_u {
		NULL_t	 storedWithValueTagSameAsPrevius;
		struct PredefinedConfigStatusInfo__other {
			PredefinedConfigStatusInfo__other_PR present;
			union PredefinedConfigStatusInfo__other_u {
				NULL_t	 notStored;
				PredefinedConfigValueTag_t	 storedWithDifferentValueTag;
			} choice;
			
			/* Context for parsing across buffer boundaries */
			asn_struct_ctx_t _asn_ctx;
		} other;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PredefinedConfigStatusInfo_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PredefinedConfigStatusInfo;

#ifdef __cplusplus
}
#endif

#endif	/* _PredefinedConfigStatusInfo_H_ */

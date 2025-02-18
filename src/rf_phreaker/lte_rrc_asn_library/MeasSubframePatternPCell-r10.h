/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_MeasSubframePatternPCell_r10_H_
#define	_MeasSubframePatternPCell_r10_H_


#include <rf_phreaker/lte_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/lte_rrc_asn_library/NULL.h>
#include "rf_phreaker/lte_rrc_asn_library/MeasSubframePattern-r10.h"
#include <rf_phreaker/lte_rrc_asn_library/constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum MeasSubframePatternPCell_r10_PR {
	MeasSubframePatternPCell_r10_PR_NOTHING,	/* No components present */
	MeasSubframePatternPCell_r10_PR_release,
	MeasSubframePatternPCell_r10_PR_setup
} MeasSubframePatternPCell_r10_PR;

/* MeasSubframePatternPCell-r10 */
typedef struct MeasSubframePatternPCell_r10 {
	MeasSubframePatternPCell_r10_PR present;
	union MeasSubframePatternPCell_r10_u {
		NULL_t	 release;
		MeasSubframePattern_r10_t	 setup;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MeasSubframePatternPCell_r10_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MeasSubframePatternPCell_r10;

#ifdef __cplusplus
}
#endif

#endif	/* _MeasSubframePatternPCell_r10_H_ */
#include <rf_phreaker/lte_rrc_asn_library/asn_internal.h>

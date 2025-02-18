/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "Class-definitions"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_DL_SHCCH_MessageType_H_
#define	_DL_SHCCH_MessageType_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/PhysicalSharedChannelAllocation.h"
#include <rf_phreaker/umts_rrc_asn_library/NULL.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum DL_SHCCH_MessageType_PR {
	DL_SHCCH_MessageType_PR_NOTHING,	/* No components present */
	DL_SHCCH_MessageType_PR_physicalSharedChannelAllocation,
	DL_SHCCH_MessageType_PR_spare
} DL_SHCCH_MessageType_PR;

/* DL-SHCCH-MessageType */
typedef struct DL_SHCCH_MessageType {
	DL_SHCCH_MessageType_PR present;
	union DL_SHCCH_MessageType_u {
		PhysicalSharedChannelAllocation_t	 physicalSharedChannelAllocation;
		NULL_t	 spare;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} DL_SHCCH_MessageType_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_DL_SHCCH_MessageType;

#ifdef __cplusplus
}
#endif

#endif	/* _DL_SHCCH_MessageType_H_ */

/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_RB_MappingOption_r6_H_
#define	_RB_MappingOption_r6_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct UL_LogicalChannelMappings_r6;
struct DL_LogicalChannelMappingList_r5;

/* RB-MappingOption-r6 */
typedef struct RB_MappingOption_r6 {
	struct UL_LogicalChannelMappings_r6	*ul_LogicalChannelMappings	/* OPTIONAL */;
	struct DL_LogicalChannelMappingList_r5	*dl_LogicalChannelMappingList	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RB_MappingOption_r6_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RB_MappingOption_r6;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/UL-LogicalChannelMappings-r6.h"
#include "rf_phreaker/umts_rrc_asn_library/DL-LogicalChannelMappingList-r5.h"

#endif	/* _RB_MappingOption_r6_H_ */

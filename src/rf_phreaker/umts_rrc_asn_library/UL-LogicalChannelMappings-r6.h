/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_UL_LogicalChannelMappings_r6_H_
#define	_UL_LogicalChannelMappings_r6_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/UL-LogicalChannelMapping-r6.h"
#include "rf_phreaker/umts_rrc_asn_library/UL-LogicalChannelMappingList-r6.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum UL_LogicalChannelMappings_r6_PR {
	UL_LogicalChannelMappings_r6_PR_NOTHING,	/* No components present */
	UL_LogicalChannelMappings_r6_PR_oneLogicalChannel,
	UL_LogicalChannelMappings_r6_PR_twoLogicalChannels
} UL_LogicalChannelMappings_r6_PR;

/* UL-LogicalChannelMappings-r6 */
typedef struct UL_LogicalChannelMappings_r6 {
	UL_LogicalChannelMappings_r6_PR present;
	union UL_LogicalChannelMappings_r6_u {
		UL_LogicalChannelMapping_r6_t	 oneLogicalChannel;
		UL_LogicalChannelMappingList_r6_t	 twoLogicalChannels;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} UL_LogicalChannelMappings_r6_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_UL_LogicalChannelMappings_r6;

#ifdef __cplusplus
}
#endif

#endif	/* _UL_LogicalChannelMappings_r6_H_ */

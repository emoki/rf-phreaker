/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_UL_DPCH_InfoPredef_v770ext_H_
#define	_UL_DPCH_InfoPredef_v770ext_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NULL.h>
#include "rf_phreaker/umts_rrc_asn_library/NumberOfTPC-Bits.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum UL_DPCH_InfoPredef_v770ext__modeSpecificInfo_PR {
	UL_DPCH_InfoPredef_v770ext__modeSpecificInfo_PR_NOTHING,	/* No components present */
	UL_DPCH_InfoPredef_v770ext__modeSpecificInfo_PR_fdd,
	UL_DPCH_InfoPredef_v770ext__modeSpecificInfo_PR_tdd
} UL_DPCH_InfoPredef_v770ext__modeSpecificInfo_PR;

/* UL-DPCH-InfoPredef-v770ext */
typedef struct UL_DPCH_InfoPredef_v770ext {
	struct UL_DPCH_InfoPredef_v770ext__modeSpecificInfo {
		UL_DPCH_InfoPredef_v770ext__modeSpecificInfo_PR present;
		union UL_DPCH_InfoPredef_v770ext__modeSpecificInfo_u {
			struct UL_DPCH_InfoPredef_v770ext__modeSpecificInfo__fdd {
				NumberOfTPC_Bits_t	*numberOfTPC_Bits	/* OPTIONAL */;
				
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
} UL_DPCH_InfoPredef_v770ext_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_UL_DPCH_InfoPredef_v770ext;

#ifdef __cplusplus
}
#endif

#endif	/* _UL_DPCH_InfoPredef_v770ext_H_ */

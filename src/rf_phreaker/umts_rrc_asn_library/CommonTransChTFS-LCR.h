/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_CommonTransChTFS_LCR_H_
#define	_CommonTransChTFS_LCR_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/SemistaticTF-Information.h"
#include "rf_phreaker/umts_rrc_asn_library/CommonDynamicTF-InfoList.h"
#include "rf_phreaker/umts_rrc_asn_library/CommonDynamicTF-InfoList-DynamicTTI.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_CHOICE.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum CommonTransChTFS_LCR__tti_PR {
	CommonTransChTFS_LCR__tti_PR_NOTHING,	/* No components present */
	CommonTransChTFS_LCR__tti_PR_tti5,
	CommonTransChTFS_LCR__tti_PR_tti10,
	CommonTransChTFS_LCR__tti_PR_tti20,
	CommonTransChTFS_LCR__tti_PR_tti40,
	CommonTransChTFS_LCR__tti_PR_tti80,
	CommonTransChTFS_LCR__tti_PR_dynamic
} CommonTransChTFS_LCR__tti_PR;

/* CommonTransChTFS-LCR */
typedef struct CommonTransChTFS_LCR {
	struct CommonTransChTFS_LCR__tti {
		CommonTransChTFS_LCR__tti_PR present;
		union CommonTransChTFS_LCR__tti_u {
			CommonDynamicTF_InfoList_t	 tti5;
			CommonDynamicTF_InfoList_t	 tti10;
			CommonDynamicTF_InfoList_t	 tti20;
			CommonDynamicTF_InfoList_t	 tti40;
			CommonDynamicTF_InfoList_t	 tti80;
			CommonDynamicTF_InfoList_DynamicTTI_t	 dynamic;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} tti;
	SemistaticTF_Information_t	 semistaticTF_Information;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} CommonTransChTFS_LCR_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_CommonTransChTFS_LCR;

#ifdef __cplusplus
}
#endif

#endif	/* _CommonTransChTFS_LCR_H_ */

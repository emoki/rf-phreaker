/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_RAB_InformationSetup_r5_H_
#define	_RAB_InformationSetup_r5_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/RAB-Info.h"
#include "rf_phreaker/umts_rrc_asn_library/RB-InformationSetupList-r5.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* RAB-InformationSetup-r5 */
typedef struct RAB_InformationSetup_r5 {
	RAB_Info_t	 rab_Info;
	RB_InformationSetupList_r5_t	 rb_InformationSetupList;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RAB_InformationSetup_r5_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RAB_InformationSetup_r5;

#ifdef __cplusplus
}
#endif

#endif	/* _RAB_InformationSetup_r5_H_ */

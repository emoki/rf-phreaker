/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_UE_Positioning_GANSS_AdditionalAssistanceDataRequest_v860ext_H_
#define	_UE_Positioning_GANSS_AdditionalAssistanceDataRequest_v860ext_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/BIT_STRING.h>
#include <rf_phreaker/umts_rrc_asn_library/NativeEnumerated.h>
#include "rf_phreaker/umts_rrc_asn_library/GanssRequestedGenericAssistanceDataList-v860ext.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum UE_Positioning_GANSS_AdditionalAssistanceDataRequest_v860ext__ganssEOPreq {
	UE_Positioning_GANSS_AdditionalAssistanceDataRequest_v860ext__ganssEOPreq_true	= 0
} e_UE_Positioning_GANSS_AdditionalAssistanceDataRequest_v860ext__ganssEOPreq;

/* UE-Positioning-GANSS-AdditionalAssistanceDataRequest-v860ext */
typedef struct UE_Positioning_GANSS_AdditionalAssistanceDataRequest_v860ext {
	BIT_STRING_t	*ganssAddIonoModelReq	/* OPTIONAL */;
	long	*ganssEOPreq	/* OPTIONAL */;
	GanssRequestedGenericAssistanceDataList_v860ext_t	 ganssRequestedGenericAssistanceDataList;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} UE_Positioning_GANSS_AdditionalAssistanceDataRequest_v860ext_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_ganssEOPreq_3;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_UE_Positioning_GANSS_AdditionalAssistanceDataRequest_v860ext;

#ifdef __cplusplus
}
#endif

#endif	/* _UE_Positioning_GANSS_AdditionalAssistanceDataRequest_v860ext_H_ */

/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_GSM_MessageList_H_
#define	_GSM_MessageList_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/BIT_STRING.h>
#include <rf_phreaker/umts_rrc_asn_library/asn_SEQUENCE_OF.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* GSM-MessageList */
typedef struct GSM_MessageList {
	A_SEQUENCE_OF(BIT_STRING_t) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} GSM_MessageList_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_GSM_MessageList;

#ifdef __cplusplus
}
#endif

#endif	/* _GSM_MessageList_H_ */

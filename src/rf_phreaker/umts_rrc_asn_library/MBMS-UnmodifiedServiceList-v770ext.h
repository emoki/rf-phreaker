/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_MBMS_UnmodifiedServiceList_v770ext_H_
#define	_MBMS_UnmodifiedServiceList_v770ext_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/asn_SEQUENCE_OF.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct MBMS_UnmodifiedService_v770ext;

/* MBMS-UnmodifiedServiceList-v770ext */
typedef struct MBMS_UnmodifiedServiceList_v770ext {
	A_SEQUENCE_OF(struct MBMS_UnmodifiedService_v770ext) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MBMS_UnmodifiedServiceList_v770ext_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MBMS_UnmodifiedServiceList_v770ext;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/MBMS-UnmodifiedService-v770ext.h"

#endif	/* _MBMS_UnmodifiedServiceList_v770ext_H_ */

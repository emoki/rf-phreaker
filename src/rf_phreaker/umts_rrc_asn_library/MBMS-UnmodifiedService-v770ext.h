/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_MBMS_UnmodifiedService_v770ext_H_
#define	_MBMS_UnmodifiedService_v770ext_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/MBSFN-ClusterFrequency-r7.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* MBMS-UnmodifiedService-v770ext */
typedef struct MBMS_UnmodifiedService_v770ext {
	MBSFN_ClusterFrequency_r7_t	*mbsfnClusterFrequency	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MBMS_UnmodifiedService_v770ext_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MBMS_UnmodifiedService_v770ext;

#ifdef __cplusplus
}
#endif

#endif	/* _MBMS_UnmodifiedService_v770ext_H_ */

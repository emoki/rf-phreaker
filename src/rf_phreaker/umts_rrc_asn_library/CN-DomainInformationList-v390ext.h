/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "Internode-definitions"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_CN_DomainInformationList_v390ext_H_
#define	_CN_DomainInformationList_v390ext_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/asn_SEQUENCE_OF.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct CN_DomainInformation_v390ext;

/* CN-DomainInformationList-v390ext */
typedef struct CN_DomainInformationList_v390ext {
	A_SEQUENCE_OF(struct CN_DomainInformation_v390ext) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} CN_DomainInformationList_v390ext_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_CN_DomainInformationList_v390ext;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/CN-DomainInformation-v390ext.h"

#endif	/* _CN_DomainInformationList_v390ext_H_ */

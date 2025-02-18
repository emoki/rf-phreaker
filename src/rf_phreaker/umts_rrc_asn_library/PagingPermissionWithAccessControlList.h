/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_PagingPermissionWithAccessControlList_H_
#define	_PagingPermissionWithAccessControlList_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct PagingPermissionWithAccessControlParameters;

/* PagingPermissionWithAccessControlList */
typedef struct PagingPermissionWithAccessControlList {
	struct PagingPermissionWithAccessControlParameters	*pagingPermissionWithAccessControlParametersForOperator1	/* OPTIONAL */;
	struct PagingPermissionWithAccessControlParameters	*pagingPermissionWithAccessControlParametersForOperator2	/* OPTIONAL */;
	struct PagingPermissionWithAccessControlParameters	*pagingPermissionWithAccessControlParametersForOperator3	/* OPTIONAL */;
	struct PagingPermissionWithAccessControlParameters	*pagingPermissionWithAccessControlParametersForOperator4	/* OPTIONAL */;
	struct PagingPermissionWithAccessControlParameters	*pagingPermissionWithAccessControlParametersForOperator5	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PagingPermissionWithAccessControlList_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PagingPermissionWithAccessControlList;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/PagingPermissionWithAccessControlParameters.h"

#endif	/* _PagingPermissionWithAccessControlList_H_ */

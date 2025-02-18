/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_CellMeasuredResults_v920ext_H_
#define	_CellMeasuredResults_v920ext_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/CSG-Identity.h"
#include <rf_phreaker/umts_rrc_asn_library/NativeEnumerated.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum CellMeasuredResults_v920ext__csgMemberIndication {
	CellMeasuredResults_v920ext__csgMemberIndication_member	= 0
} e_CellMeasuredResults_v920ext__csgMemberIndication;

/* CellMeasuredResults-v920ext */
typedef struct CellMeasuredResults_v920ext {
	CSG_Identity_t	*csgIdentity	/* OPTIONAL */;
	long	*csgMemberIndication	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} CellMeasuredResults_v920ext_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_csgMemberIndication_3;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_CellMeasuredResults_v920ext;

#ifdef __cplusplus
}
#endif

#endif	/* _CellMeasuredResults_v920ext_H_ */

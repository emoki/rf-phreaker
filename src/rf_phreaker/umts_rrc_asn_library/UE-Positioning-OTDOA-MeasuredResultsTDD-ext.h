/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_UE_Positioning_OTDOA_MeasuredResultsTDD_ext_H_
#define	_UE_Positioning_OTDOA_MeasuredResultsTDD_ext_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct NeighbourList_TDD_r7;

/* UE-Positioning-OTDOA-MeasuredResultsTDD-ext */
typedef struct UE_Positioning_OTDOA_MeasuredResultsTDD_ext {
	struct NeighbourList_TDD_r7	*neighbourList	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} UE_Positioning_OTDOA_MeasuredResultsTDD_ext_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_UE_Positioning_OTDOA_MeasuredResultsTDD_ext;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/NeighbourList-TDD-r7.h"

#endif	/* _UE_Positioning_OTDOA_MeasuredResultsTDD_ext_H_ */

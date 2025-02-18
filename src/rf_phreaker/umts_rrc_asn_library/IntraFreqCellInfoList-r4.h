/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_IntraFreqCellInfoList_r4_H_
#define	_IntraFreqCellInfoList_r4_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct RemovedIntraFreqCellList;
struct NewIntraFreqCellList_r4;
struct CellsForIntraFreqMeasList;

/* IntraFreqCellInfoList-r4 */
typedef struct IntraFreqCellInfoList_r4 {
	struct RemovedIntraFreqCellList	*removedIntraFreqCellList	/* OPTIONAL */;
	struct NewIntraFreqCellList_r4	*newIntraFreqCellList	/* OPTIONAL */;
	struct CellsForIntraFreqMeasList	*cellsForIntraFreqMeasList	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} IntraFreqCellInfoList_r4_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_IntraFreqCellInfoList_r4;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/RemovedIntraFreqCellList.h"
#include "rf_phreaker/umts_rrc_asn_library/NewIntraFreqCellList-r4.h"
#include "rf_phreaker/umts_rrc_asn_library/CellsForIntraFreqMeasList.h"

#endif	/* _IntraFreqCellInfoList_r4_H_ */

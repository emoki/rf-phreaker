/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_NewIntraFreqCell_r4_H_
#define	_NewIntraFreqCell_r4_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/IntraFreqCellID.h"
#include "rf_phreaker/umts_rrc_asn_library/CellInfo-r4.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* NewIntraFreqCell-r4 */
typedef struct NewIntraFreqCell_r4 {
	IntraFreqCellID_t	*intraFreqCellID	/* OPTIONAL */;
	CellInfo_r4_t	 cellInfo;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} NewIntraFreqCell_r4_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_NewIntraFreqCell_r4;

#ifdef __cplusplus
}
#endif

#endif	/* _NewIntraFreqCell_r4_H_ */

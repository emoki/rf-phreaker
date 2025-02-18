/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_NewIntraFreqCell_H_
#define	_NewIntraFreqCell_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/IntraFreqCellID.h"
#include "rf_phreaker/umts_rrc_asn_library/CellInfo.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* NewIntraFreqCell */
typedef struct NewIntraFreqCell {
	IntraFreqCellID_t	*intraFreqCellID	/* OPTIONAL */;
	CellInfo_t	 cellInfo;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} NewIntraFreqCell_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_NewIntraFreqCell;

#ifdef __cplusplus
}
#endif

#endif	/* _NewIntraFreqCell_H_ */

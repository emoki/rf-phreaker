/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_HCS_CellReselectInformation_RSCP_H_
#define	_HCS_CellReselectInformation_RSCP_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/PenaltyTime-RSCP.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* HCS-CellReselectInformation-RSCP */
typedef struct HCS_CellReselectInformation_RSCP {
	PenaltyTime_RSCP_t	 penaltyTime;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} HCS_CellReselectInformation_RSCP_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_HCS_CellReselectInformation_RSCP;

#ifdef __cplusplus
}
#endif

#endif	/* _HCS_CellReselectInformation_RSCP_H_ */

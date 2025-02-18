/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_NewInterFreqCellSI_RSCP_H_
#define	_NewInterFreqCellSI_RSCP_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/InterFreqCellID.h"
#include "rf_phreaker/umts_rrc_asn_library/CellInfoSI-RSCP.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct FrequencyInfo;

/* NewInterFreqCellSI-RSCP */
typedef struct NewInterFreqCellSI_RSCP {
	InterFreqCellID_t	*interFreqCellID	/* OPTIONAL */;
	struct FrequencyInfo	*frequencyInfo	/* OPTIONAL */;
	CellInfoSI_RSCP_t	 cellInfo;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} NewInterFreqCellSI_RSCP_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_NewInterFreqCellSI_RSCP;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/FrequencyInfo.h"

#endif	/* _NewInterFreqCellSI_RSCP_H_ */

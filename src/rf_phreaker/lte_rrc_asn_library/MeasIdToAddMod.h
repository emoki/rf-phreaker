/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_MeasIdToAddMod_H_
#define	_MeasIdToAddMod_H_


#include <rf_phreaker/lte_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/lte_rrc_asn_library/MeasId.h"
#include "rf_phreaker/lte_rrc_asn_library/MeasObjectId.h"
#include "rf_phreaker/lte_rrc_asn_library/ReportConfigId.h"
#include <rf_phreaker/lte_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* MeasIdToAddMod */
typedef struct MeasIdToAddMod {
	MeasId_t	 measId;
	MeasObjectId_t	 measObjectId;
	ReportConfigId_t	 reportConfigId;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MeasIdToAddMod_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MeasIdToAddMod;

#ifdef __cplusplus
}
#endif

#endif	/* _MeasIdToAddMod_H_ */
#include <rf_phreaker/lte_rrc_asn_library/asn_internal.h>

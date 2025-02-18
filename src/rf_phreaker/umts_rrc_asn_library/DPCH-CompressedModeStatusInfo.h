/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_DPCH_CompressedModeStatusInfo_H_
#define	_DPCH_CompressedModeStatusInfo_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/TGPS-Reconfiguration-CFN.h"
#include <rf_phreaker/umts_rrc_asn_library/asn_SEQUENCE_OF.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE_OF.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct TGP_SequenceShort;

/* DPCH-CompressedModeStatusInfo */
typedef struct DPCH_CompressedModeStatusInfo {
	TGPS_Reconfiguration_CFN_t	 tgps_Reconfiguration_CFN;
	struct DPCH_CompressedModeStatusInfo__tgp_SequenceShortList {
		A_SEQUENCE_OF(struct TGP_SequenceShort) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} tgp_SequenceShortList;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} DPCH_CompressedModeStatusInfo_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_DPCH_CompressedModeStatusInfo;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/TGP-SequenceShort.h"

#endif	/* _DPCH_CompressedModeStatusInfo_H_ */

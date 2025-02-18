/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_TMSI_and_LAI_GSM_MAP_H_
#define	_TMSI_and_LAI_GSM_MAP_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/TMSI-GSM-MAP.h"
#include "rf_phreaker/umts_rrc_asn_library/LAI.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* TMSI-and-LAI-GSM-MAP */
typedef struct TMSI_and_LAI_GSM_MAP {
	TMSI_GSM_MAP_t	 tmsi;
	LAI_t	 lai;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} TMSI_and_LAI_GSM_MAP_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_TMSI_and_LAI_GSM_MAP;

#ifdef __cplusplus
}
#endif

#endif	/* _TMSI_and_LAI_GSM_MAP_H_ */

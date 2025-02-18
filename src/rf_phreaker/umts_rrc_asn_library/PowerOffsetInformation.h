/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_PowerOffsetInformation_H_
#define	_PowerOffsetInformation_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/GainFactorInformation.h"
#include "rf_phreaker/umts_rrc_asn_library/PowerOffsetPp-m.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* PowerOffsetInformation */
typedef struct PowerOffsetInformation {
	GainFactorInformation_t	 gainFactorInformation;
	PowerOffsetPp_m_t	*powerOffsetPp_m	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PowerOffsetInformation_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PowerOffsetInformation;

#ifdef __cplusplus
}
#endif

#endif	/* _PowerOffsetInformation_H_ */

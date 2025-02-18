/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_RF_Parameters_v1060_H_
#define	_RF_Parameters_v1060_H_


#include <rf_phreaker/lte_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/lte_rrc_asn_library/SupportedBandCombinationExt-r10.h"
#include <rf_phreaker/lte_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* RF-Parameters-v1060 */
typedef struct RF_Parameters_v1060 {
	SupportedBandCombinationExt_r10_t	 supportedBandCombinationExt_r10;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RF_Parameters_v1060_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RF_Parameters_v1060;

#ifdef __cplusplus
}
#endif

#endif	/* _RF_Parameters_v1060_H_ */
#include <rf_phreaker/lte_rrc_asn_library/asn_internal.h>

/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_QuantityConfigGERAN_H_
#define	_QuantityConfigGERAN_H_


#include <rf_phreaker/lte_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/lte_rrc_asn_library/NativeEnumerated.h>
#include "rf_phreaker/lte_rrc_asn_library/FilterCoefficient.h"
#include <rf_phreaker/lte_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum QuantityConfigGERAN__measQuantityGERAN {
	QuantityConfigGERAN__measQuantityGERAN_rssi	= 0
} e_QuantityConfigGERAN__measQuantityGERAN;

/* QuantityConfigGERAN */
typedef struct QuantityConfigGERAN {
	long	 measQuantityGERAN;
	FilterCoefficient_t	*filterCoefficient	/* DEFAULT 2 */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} QuantityConfigGERAN_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_measQuantityGERAN_2;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_QuantityConfigGERAN;

#ifdef __cplusplus
}
#endif

#endif	/* _QuantityConfigGERAN_H_ */
#include <rf_phreaker/lte_rrc_asn_library/asn_internal.h>

/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_PRACH_SystemInformation_VHCR_r7_H_
#define	_PRACH_SystemInformation_VHCR_r7_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/PRACH-RACH-Info-VHCR-r7.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct PRACH_Partitioning_r7;

/* PRACH-SystemInformation-VHCR-r7 */
typedef struct PRACH_SystemInformation_VHCR_r7 {
	PRACH_RACH_Info_VHCR_r7_t	 prach_RACH_Info;
	struct PRACH_Partitioning_r7	*prach_Partitioning	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PRACH_SystemInformation_VHCR_r7_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PRACH_SystemInformation_VHCR_r7;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/PRACH-Partitioning-r7.h"

#endif	/* _PRACH_SystemInformation_VHCR_r7_H_ */

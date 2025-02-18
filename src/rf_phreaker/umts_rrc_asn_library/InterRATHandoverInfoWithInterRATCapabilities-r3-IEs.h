/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "Internode-definitions"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_InterRATHandoverInfoWithInterRATCapabilities_r3_IEs_H_
#define	_InterRATHandoverInfoWithInterRATCapabilities_r3_IEs_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/OCTET_STRING.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct InterRAT_UE_RadioAccessCapabilityList;

/* InterRATHandoverInfoWithInterRATCapabilities-r3-IEs */
typedef struct InterRATHandoverInfoWithInterRATCapabilities_r3_IEs {
	struct InterRAT_UE_RadioAccessCapabilityList	*ue_RATSpecificCapability	/* OPTIONAL */;
	OCTET_STRING_t	 interRATHandoverInfo;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} InterRATHandoverInfoWithInterRATCapabilities_r3_IEs_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_InterRATHandoverInfoWithInterRATCapabilities_r3_IEs;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/InterRAT-UE-RadioAccessCapabilityList.h"

#endif	/* _InterRATHandoverInfoWithInterRATCapabilities_r3_IEs_H_ */

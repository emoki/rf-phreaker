/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_PDCP_Capability_H_
#define	_PDCP_Capability_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/BOOLEAN.h>
#include <rf_phreaker/umts_rrc_asn_library/NULL.h>
#include "rf_phreaker/umts_rrc_asn_library/MaxHcContextSpace.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_CHOICE.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum PDCP_Capability__supportForRfc2507_PR {
	PDCP_Capability__supportForRfc2507_PR_NOTHING,	/* No components present */
	PDCP_Capability__supportForRfc2507_PR_notSupported,
	PDCP_Capability__supportForRfc2507_PR_supported
} PDCP_Capability__supportForRfc2507_PR;

/* PDCP-Capability */
typedef struct PDCP_Capability {
	BOOLEAN_t	 losslessSRNS_RelocationSupport;
	struct PDCP_Capability__supportForRfc2507 {
		PDCP_Capability__supportForRfc2507_PR present;
		union PDCP_Capability__supportForRfc2507_u {
			NULL_t	 notSupported;
			MaxHcContextSpace_t	 supported;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} supportForRfc2507;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PDCP_Capability_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PDCP_Capability;

#ifdef __cplusplus
}
#endif

#endif	/* _PDCP_Capability_H_ */

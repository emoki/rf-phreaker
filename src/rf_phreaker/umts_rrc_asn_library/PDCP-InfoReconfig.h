/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_PDCP_InfoReconfig_H_
#define	_PDCP_InfoReconfig_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/PDCP-Info.h"
#include <rf_phreaker/umts_rrc_asn_library/NativeInteger.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* PDCP-InfoReconfig */
typedef struct PDCP_InfoReconfig {
	PDCP_Info_t	 pdcp_Info;
	long	 dummy;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PDCP_InfoReconfig_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PDCP_InfoReconfig;

#ifdef __cplusplus
}
#endif

#endif	/* _PDCP_InfoReconfig_H_ */

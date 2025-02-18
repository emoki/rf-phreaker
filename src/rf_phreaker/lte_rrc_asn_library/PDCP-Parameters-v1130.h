/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_PDCP_Parameters_v1130_H_
#define	_PDCP_Parameters_v1130_H_


#include <rf_phreaker/lte_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/lte_rrc_asn_library/NativeEnumerated.h>
#include <rf_phreaker/lte_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum PDCP_Parameters_v1130__pdcp_SN_Extension_r11 {
	PDCP_Parameters_v1130__pdcp_SN_Extension_r11_supported	= 0
} e_PDCP_Parameters_v1130__pdcp_SN_Extension_r11;
typedef enum PDCP_Parameters_v1130__supportRohcContextContinue_r11 {
	PDCP_Parameters_v1130__supportRohcContextContinue_r11_supported	= 0
} e_PDCP_Parameters_v1130__supportRohcContextContinue_r11;

/* PDCP-Parameters-v1130 */
typedef struct PDCP_Parameters_v1130 {
	long	*pdcp_SN_Extension_r11	/* OPTIONAL */;
	long	*supportRohcContextContinue_r11	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PDCP_Parameters_v1130_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_pdcp_SN_Extension_r11_2;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_supportRohcContextContinue_r11_4;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_PDCP_Parameters_v1130;

#ifdef __cplusplus
}
#endif

#endif	/* _PDCP_Parameters_v1130_H_ */
#include <rf_phreaker/lte_rrc_asn_library/asn_internal.h>

/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_E_TFC_Boost_Info_r7_H_
#define	_E_TFC_Boost_Info_r7_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeInteger.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* E-TFC-Boost-Info-r7 */
typedef struct E_TFC_Boost_Info_r7 {
	long	 e_TFCI_Boost;
	long	*delta_T2TP	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} E_TFC_Boost_Info_r7_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_E_TFC_Boost_Info_r7;

#ifdef __cplusplus
}
#endif

#endif	/* _E_TFC_Boost_Info_r7_H_ */

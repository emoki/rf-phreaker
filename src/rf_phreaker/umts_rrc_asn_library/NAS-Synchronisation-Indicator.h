/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_NAS_Synchronisation_Indicator_H_
#define	_NAS_Synchronisation_Indicator_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/BIT_STRING.h>

#ifdef __cplusplus
extern "C" {
#endif

/* NAS-Synchronisation-Indicator */
typedef BIT_STRING_t	 NAS_Synchronisation_Indicator_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_NAS_Synchronisation_Indicator;
asn_struct_free_f NAS_Synchronisation_Indicator_free;
asn_struct_print_f NAS_Synchronisation_Indicator_print;
asn_constr_check_f NAS_Synchronisation_Indicator_constraint;
ber_type_decoder_f NAS_Synchronisation_Indicator_decode_ber;
der_type_encoder_f NAS_Synchronisation_Indicator_encode_der;
xer_type_decoder_f NAS_Synchronisation_Indicator_decode_xer;
xer_type_encoder_f NAS_Synchronisation_Indicator_encode_xer;
per_type_decoder_f NAS_Synchronisation_Indicator_decode_uper;
per_type_encoder_f NAS_Synchronisation_Indicator_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _NAS_Synchronisation_Indicator_H_ */

/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_TMSI_GSM_MAP_H_
#define	_TMSI_GSM_MAP_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/BIT_STRING.h>

#ifdef __cplusplus
extern "C" {
#endif

/* TMSI-GSM-MAP */
typedef BIT_STRING_t	 TMSI_GSM_MAP_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_TMSI_GSM_MAP;
asn_struct_free_f TMSI_GSM_MAP_free;
asn_struct_print_f TMSI_GSM_MAP_print;
asn_constr_check_f TMSI_GSM_MAP_constraint;
ber_type_decoder_f TMSI_GSM_MAP_decode_ber;
der_type_encoder_f TMSI_GSM_MAP_encode_der;
xer_type_decoder_f TMSI_GSM_MAP_decode_xer;
xer_type_encoder_f TMSI_GSM_MAP_encode_xer;
per_type_decoder_f TMSI_GSM_MAP_decode_uper;
per_type_encoder_f TMSI_GSM_MAP_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _TMSI_GSM_MAP_H_ */

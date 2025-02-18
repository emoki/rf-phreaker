/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_GANSS_Mode_H_
#define	_GANSS_Mode_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum GANSS_Mode {
	GANSS_Mode_networkBased	= 0,
	GANSS_Mode_uEBased	= 1,
	GANSS_Mode_both	= 2,
	GANSS_Mode_none	= 3
} e_GANSS_Mode;

/* GANSS-Mode */
typedef long	 GANSS_Mode_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_GANSS_Mode;
asn_struct_free_f GANSS_Mode_free;
asn_struct_print_f GANSS_Mode_print;
asn_constr_check_f GANSS_Mode_constraint;
ber_type_decoder_f GANSS_Mode_decode_ber;
der_type_encoder_f GANSS_Mode_encode_der;
xer_type_decoder_f GANSS_Mode_decode_xer;
xer_type_encoder_f GANSS_Mode_encode_xer;
per_type_decoder_f GANSS_Mode_decode_uper;
per_type_encoder_f GANSS_Mode_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _GANSS_Mode_H_ */

/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_N_315_H_
#define	_N_315_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum N_315 {
	N_315_s1	= 0,
	N_315_s50	= 1,
	N_315_s100	= 2,
	N_315_s200	= 3,
	N_315_s400	= 4,
	N_315_s600	= 5,
	N_315_s800	= 6,
	N_315_s1000	= 7
} e_N_315;

/* N-315 */
typedef long	 N_315_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_N_315;
asn_struct_free_f N_315_free;
asn_struct_print_f N_315_print;
asn_constr_check_f N_315_constraint;
ber_type_decoder_f N_315_decode_ber;
der_type_encoder_f N_315_encode_der;
xer_type_decoder_f N_315_decode_xer;
xer_type_encoder_f N_315_encode_xer;
per_type_decoder_f N_315_decode_uper;
per_type_encoder_f N_315_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _N_315_H_ */

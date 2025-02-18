/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_T_305_H_
#define	_T_305_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum T_305 {
	T_305_noUpdate	= 0,
	T_305_m5	= 1,
	T_305_m10	= 2,
	T_305_m30	= 3,
	T_305_m60	= 4,
	T_305_m120	= 5,
	T_305_m360	= 6,
	T_305_m720	= 7
} e_T_305;

/* T-305 */
typedef long	 T_305_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_T_305;
asn_struct_free_f T_305_free;
asn_struct_print_f T_305_print;
asn_constr_check_f T_305_constraint;
ber_type_decoder_f T_305_decode_ber;
der_type_encoder_f T_305_encode_der;
xer_type_decoder_f T_305_decode_xer;
xer_type_encoder_f T_305_encode_xer;
per_type_decoder_f T_305_decode_uper;
per_type_encoder_f T_305_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _T_305_H_ */

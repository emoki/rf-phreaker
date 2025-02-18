/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_MaxNumberOfTFC_UL_H_
#define	_MaxNumberOfTFC_UL_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum MaxNumberOfTFC_UL {
	MaxNumberOfTFC_UL_dummy1	= 0,
	MaxNumberOfTFC_UL_dummy2	= 1,
	MaxNumberOfTFC_UL_tfc16	= 2,
	MaxNumberOfTFC_UL_tfc32	= 3,
	MaxNumberOfTFC_UL_tfc48	= 4,
	MaxNumberOfTFC_UL_tfc64	= 5,
	MaxNumberOfTFC_UL_tfc96	= 6,
	MaxNumberOfTFC_UL_tfc128	= 7,
	MaxNumberOfTFC_UL_tfc256	= 8,
	MaxNumberOfTFC_UL_tfc512	= 9,
	MaxNumberOfTFC_UL_tfc1024	= 10
} e_MaxNumberOfTFC_UL;

/* MaxNumberOfTFC-UL */
typedef long	 MaxNumberOfTFC_UL_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MaxNumberOfTFC_UL;
asn_struct_free_f MaxNumberOfTFC_UL_free;
asn_struct_print_f MaxNumberOfTFC_UL_print;
asn_constr_check_f MaxNumberOfTFC_UL_constraint;
ber_type_decoder_f MaxNumberOfTFC_UL_decode_ber;
der_type_encoder_f MaxNumberOfTFC_UL_encode_der;
xer_type_decoder_f MaxNumberOfTFC_UL_decode_xer;
xer_type_encoder_f MaxNumberOfTFC_UL_encode_xer;
per_type_decoder_f MaxNumberOfTFC_UL_decode_uper;
per_type_encoder_f MaxNumberOfTFC_UL_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _MaxNumberOfTFC_UL_H_ */

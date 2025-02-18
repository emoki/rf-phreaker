/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_MaxHcContextSpace_H_
#define	_MaxHcContextSpace_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum MaxHcContextSpace {
	MaxHcContextSpace_dummy	= 0,
	MaxHcContextSpace_by1024	= 1,
	MaxHcContextSpace_by2048	= 2,
	MaxHcContextSpace_by4096	= 3,
	MaxHcContextSpace_by8192	= 4
} e_MaxHcContextSpace;

/* MaxHcContextSpace */
typedef long	 MaxHcContextSpace_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MaxHcContextSpace;
asn_struct_free_f MaxHcContextSpace_free;
asn_struct_print_f MaxHcContextSpace_print;
asn_constr_check_f MaxHcContextSpace_constraint;
ber_type_decoder_f MaxHcContextSpace_decode_ber;
der_type_encoder_f MaxHcContextSpace_encode_der;
xer_type_decoder_f MaxHcContextSpace_decode_xer;
xer_type_encoder_f MaxHcContextSpace_encode_xer;
per_type_decoder_f MaxHcContextSpace_decode_uper;
per_type_encoder_f MaxHcContextSpace_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _MaxHcContextSpace_H_ */

/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_MappingFunctionType_H_
#define	_MappingFunctionType_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum MappingFunctionType {
	MappingFunctionType_linear	= 0,
	MappingFunctionType_functionType2	= 1,
	MappingFunctionType_functionType3	= 2,
	MappingFunctionType_functionType4	= 3
} e_MappingFunctionType;

/* MappingFunctionType */
typedef long	 MappingFunctionType_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MappingFunctionType;
asn_struct_free_f MappingFunctionType_free;
asn_struct_print_f MappingFunctionType_print;
asn_constr_check_f MappingFunctionType_constraint;
ber_type_decoder_f MappingFunctionType_decode_ber;
der_type_encoder_f MappingFunctionType_encode_der;
xer_type_decoder_f MappingFunctionType_decode_xer;
xer_type_encoder_f MappingFunctionType_encode_xer;
per_type_decoder_f MappingFunctionType_decode_uper;
per_type_encoder_f MappingFunctionType_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _MappingFunctionType_H_ */

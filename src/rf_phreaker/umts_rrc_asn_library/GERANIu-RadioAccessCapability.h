/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_GERANIu_RadioAccessCapability_H_
#define	_GERANIu_RadioAccessCapability_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/BIT_STRING.h>

#ifdef __cplusplus
extern "C" {
#endif

/* GERANIu-RadioAccessCapability */
typedef BIT_STRING_t	 GERANIu_RadioAccessCapability_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_GERANIu_RadioAccessCapability;
asn_struct_free_f GERANIu_RadioAccessCapability_free;
asn_struct_print_f GERANIu_RadioAccessCapability_print;
asn_constr_check_f GERANIu_RadioAccessCapability_constraint;
ber_type_decoder_f GERANIu_RadioAccessCapability_decode_ber;
der_type_encoder_f GERANIu_RadioAccessCapability_encode_der;
xer_type_decoder_f GERANIu_RadioAccessCapability_decode_xer;
xer_type_encoder_f GERANIu_RadioAccessCapability_encode_xer;
per_type_decoder_f GERANIu_RadioAccessCapability_decode_uper;
per_type_encoder_f GERANIu_RadioAccessCapability_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _GERANIu_RadioAccessCapability_H_ */

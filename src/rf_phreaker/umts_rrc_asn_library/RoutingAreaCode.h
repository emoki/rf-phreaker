/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_RoutingAreaCode_H_
#define	_RoutingAreaCode_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/BIT_STRING.h>

#ifdef __cplusplus
extern "C" {
#endif

/* RoutingAreaCode */
typedef BIT_STRING_t	 RoutingAreaCode_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RoutingAreaCode;
asn_struct_free_f RoutingAreaCode_free;
asn_struct_print_f RoutingAreaCode_print;
asn_constr_check_f RoutingAreaCode_constraint;
ber_type_decoder_f RoutingAreaCode_decode_ber;
der_type_encoder_f RoutingAreaCode_encode_der;
xer_type_decoder_f RoutingAreaCode_decode_xer;
xer_type_encoder_f RoutingAreaCode_encode_xer;
per_type_decoder_f RoutingAreaCode_decode_uper;
per_type_encoder_f RoutingAreaCode_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _RoutingAreaCode_H_ */

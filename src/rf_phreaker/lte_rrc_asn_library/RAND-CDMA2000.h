/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_RAND_CDMA2000_H_
#define	_RAND_CDMA2000_H_


#include <rf_phreaker/lte_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/lte_rrc_asn_library/BIT_STRING.h>

#ifdef __cplusplus
extern "C" {
#endif

/* RAND-CDMA2000 */
typedef BIT_STRING_t	 RAND_CDMA2000_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RAND_CDMA2000;
asn_struct_free_f RAND_CDMA2000_free;
asn_struct_print_f RAND_CDMA2000_print;
asn_constr_check_f RAND_CDMA2000_constraint;
ber_type_decoder_f RAND_CDMA2000_decode_ber;
der_type_encoder_f RAND_CDMA2000_encode_der;
xer_type_decoder_f RAND_CDMA2000_decode_xer;
xer_type_encoder_f RAND_CDMA2000_encode_xer;
per_type_decoder_f RAND_CDMA2000_decode_uper;
per_type_encoder_f RAND_CDMA2000_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _RAND_CDMA2000_H_ */
#include <rf_phreaker/lte_rrc_asn_library/asn_internal.h>

/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_CipheringAlgorithm_H_
#define	_CipheringAlgorithm_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum CipheringAlgorithm {
	CipheringAlgorithm_uea0	= 0,
	CipheringAlgorithm_uea1	= 1
} e_CipheringAlgorithm;

/* CipheringAlgorithm */
typedef long	 CipheringAlgorithm_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_CipheringAlgorithm;
asn_struct_free_f CipheringAlgorithm_free;
asn_struct_print_f CipheringAlgorithm_print;
asn_constr_check_f CipheringAlgorithm_constraint;
ber_type_decoder_f CipheringAlgorithm_decode_ber;
der_type_encoder_f CipheringAlgorithm_encode_der;
xer_type_decoder_f CipheringAlgorithm_decode_xer;
xer_type_encoder_f CipheringAlgorithm_encode_xer;
per_type_decoder_f CipheringAlgorithm_decode_uper;
per_type_encoder_f CipheringAlgorithm_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _CipheringAlgorithm_H_ */

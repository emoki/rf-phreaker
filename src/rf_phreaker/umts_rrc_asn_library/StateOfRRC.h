/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "Internode-definitions"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_StateOfRRC_H_
#define	_StateOfRRC_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum StateOfRRC {
	StateOfRRC_cell_DCH	= 0,
	StateOfRRC_cell_FACH	= 1,
	StateOfRRC_cell_PCH	= 2,
	StateOfRRC_ura_PCH	= 3
} e_StateOfRRC;

/* StateOfRRC */
typedef long	 StateOfRRC_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_StateOfRRC;
asn_struct_free_f StateOfRRC_free;
asn_struct_print_f StateOfRRC_print;
asn_constr_check_f StateOfRRC_constraint;
ber_type_decoder_f StateOfRRC_decode_ber;
der_type_encoder_f StateOfRRC_encode_der;
xer_type_decoder_f StateOfRRC_decode_xer;
xer_type_encoder_f StateOfRRC_encode_xer;
per_type_decoder_f StateOfRRC_decode_uper;
per_type_encoder_f StateOfRRC_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _StateOfRRC_H_ */

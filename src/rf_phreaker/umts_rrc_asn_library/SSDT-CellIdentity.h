/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_SSDT_CellIdentity_H_
#define	_SSDT_CellIdentity_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum SSDT_CellIdentity {
	SSDT_CellIdentity_ssdt_id_a	= 0,
	SSDT_CellIdentity_ssdt_id_b	= 1,
	SSDT_CellIdentity_ssdt_id_c	= 2,
	SSDT_CellIdentity_ssdt_id_d	= 3,
	SSDT_CellIdentity_ssdt_id_e	= 4,
	SSDT_CellIdentity_ssdt_id_f	= 5,
	SSDT_CellIdentity_ssdt_id_g	= 6,
	SSDT_CellIdentity_ssdt_id_h	= 7
} e_SSDT_CellIdentity;

/* SSDT-CellIdentity */
typedef long	 SSDT_CellIdentity_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SSDT_CellIdentity;
asn_struct_free_f SSDT_CellIdentity_free;
asn_struct_print_f SSDT_CellIdentity_print;
asn_constr_check_f SSDT_CellIdentity_constraint;
ber_type_decoder_f SSDT_CellIdentity_decode_ber;
der_type_encoder_f SSDT_CellIdentity_encode_der;
xer_type_decoder_f SSDT_CellIdentity_decode_xer;
xer_type_encoder_f SSDT_CellIdentity_encode_xer;
per_type_decoder_f SSDT_CellIdentity_decode_uper;
per_type_encoder_f SSDT_CellIdentity_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _SSDT_CellIdentity_H_ */

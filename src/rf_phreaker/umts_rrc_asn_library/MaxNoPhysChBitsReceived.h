/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_MaxNoPhysChBitsReceived_H_
#define	_MaxNoPhysChBitsReceived_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum MaxNoPhysChBitsReceived {
	MaxNoPhysChBitsReceived_dummy	= 0,
	MaxNoPhysChBitsReceived_b1200	= 1,
	MaxNoPhysChBitsReceived_b2400	= 2,
	MaxNoPhysChBitsReceived_b3600	= 3,
	MaxNoPhysChBitsReceived_b4800	= 4,
	MaxNoPhysChBitsReceived_b7200	= 5,
	MaxNoPhysChBitsReceived_b9600	= 6,
	MaxNoPhysChBitsReceived_b14400	= 7,
	MaxNoPhysChBitsReceived_b19200	= 8,
	MaxNoPhysChBitsReceived_b28800	= 9,
	MaxNoPhysChBitsReceived_b38400	= 10,
	MaxNoPhysChBitsReceived_b48000	= 11,
	MaxNoPhysChBitsReceived_b57600	= 12,
	MaxNoPhysChBitsReceived_b67200	= 13,
	MaxNoPhysChBitsReceived_b76800	= 14
} e_MaxNoPhysChBitsReceived;

/* MaxNoPhysChBitsReceived */
typedef long	 MaxNoPhysChBitsReceived_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MaxNoPhysChBitsReceived;
asn_struct_free_f MaxNoPhysChBitsReceived_free;
asn_struct_print_f MaxNoPhysChBitsReceived_print;
asn_constr_check_f MaxNoPhysChBitsReceived_constraint;
ber_type_decoder_f MaxNoPhysChBitsReceived_decode_ber;
der_type_encoder_f MaxNoPhysChBitsReceived_encode_der;
xer_type_decoder_f MaxNoPhysChBitsReceived_decode_xer;
xer_type_encoder_f MaxNoPhysChBitsReceived_encode_xer;
per_type_decoder_f MaxNoPhysChBitsReceived_decode_uper;
per_type_encoder_f MaxNoPhysChBitsReceived_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _MaxNoPhysChBitsReceived_H_ */

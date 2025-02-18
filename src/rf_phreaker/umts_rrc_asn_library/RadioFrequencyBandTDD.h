/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_RadioFrequencyBandTDD_H_
#define	_RadioFrequencyBandTDD_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum RadioFrequencyBandTDD {
	RadioFrequencyBandTDD_a	= 0,
	RadioFrequencyBandTDD_b	= 1,
	RadioFrequencyBandTDD_c	= 2,
	RadioFrequencyBandTDD_d	= 3
} e_RadioFrequencyBandTDD;

/* RadioFrequencyBandTDD */
typedef long	 RadioFrequencyBandTDD_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RadioFrequencyBandTDD;
asn_struct_free_f RadioFrequencyBandTDD_free;
asn_struct_print_f RadioFrequencyBandTDD_print;
asn_constr_check_f RadioFrequencyBandTDD_constraint;
ber_type_decoder_f RadioFrequencyBandTDD_decode_ber;
der_type_encoder_f RadioFrequencyBandTDD_encode_der;
xer_type_decoder_f RadioFrequencyBandTDD_decode_xer;
xer_type_encoder_f RadioFrequencyBandTDD_encode_xer;
per_type_decoder_f RadioFrequencyBandTDD_decode_uper;
per_type_encoder_f RadioFrequencyBandTDD_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _RadioFrequencyBandTDD_H_ */

/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_TransmissionTimeInterval_H_
#define	_TransmissionTimeInterval_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum TransmissionTimeInterval {
	TransmissionTimeInterval_tti10	= 0,
	TransmissionTimeInterval_tti20	= 1,
	TransmissionTimeInterval_tti40	= 2,
	TransmissionTimeInterval_tti80	= 3
} e_TransmissionTimeInterval;

/* TransmissionTimeInterval */
typedef long	 TransmissionTimeInterval_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_TransmissionTimeInterval;
asn_struct_free_f TransmissionTimeInterval_free;
asn_struct_print_f TransmissionTimeInterval_print;
asn_constr_check_f TransmissionTimeInterval_constraint;
ber_type_decoder_f TransmissionTimeInterval_decode_ber;
der_type_encoder_f TransmissionTimeInterval_encode_der;
xer_type_decoder_f TransmissionTimeInterval_decode_xer;
xer_type_encoder_f TransmissionTimeInterval_encode_xer;
per_type_decoder_f TransmissionTimeInterval_decode_uper;
per_type_encoder_f TransmissionTimeInterval_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _TransmissionTimeInterval_H_ */

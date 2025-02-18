/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_Re_EstablishmentTimer_H_
#define	_Re_EstablishmentTimer_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum Re_EstablishmentTimer {
	Re_EstablishmentTimer_useT314	= 0,
	Re_EstablishmentTimer_useT315	= 1
} e_Re_EstablishmentTimer;

/* Re-EstablishmentTimer */
typedef long	 Re_EstablishmentTimer_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Re_EstablishmentTimer;
asn_struct_free_f Re_EstablishmentTimer_free;
asn_struct_print_f Re_EstablishmentTimer_print;
asn_constr_check_f Re_EstablishmentTimer_constraint;
ber_type_decoder_f Re_EstablishmentTimer_decode_ber;
der_type_encoder_f Re_EstablishmentTimer_encode_der;
xer_type_decoder_f Re_EstablishmentTimer_decode_xer;
xer_type_encoder_f Re_EstablishmentTimer_encode_xer;
per_type_decoder_f Re_EstablishmentTimer_decode_uper;
per_type_encoder_f Re_EstablishmentTimer_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _Re_EstablishmentTimer_H_ */

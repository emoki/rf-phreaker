/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_ReestablishmentCause_H_
#define	_ReestablishmentCause_H_


#include <rf_phreaker/lte_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/lte_rrc_asn_library/NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum ReestablishmentCause {
	ReestablishmentCause_reconfigurationFailure	= 0,
	ReestablishmentCause_handoverFailure	= 1,
	ReestablishmentCause_otherFailure	= 2,
	ReestablishmentCause_spare1	= 3
} e_ReestablishmentCause;

/* ReestablishmentCause */
typedef long	 ReestablishmentCause_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ReestablishmentCause;
asn_struct_free_f ReestablishmentCause_free;
asn_struct_print_f ReestablishmentCause_print;
asn_constr_check_f ReestablishmentCause_constraint;
ber_type_decoder_f ReestablishmentCause_decode_ber;
der_type_encoder_f ReestablishmentCause_encode_der;
xer_type_decoder_f ReestablishmentCause_decode_xer;
xer_type_encoder_f ReestablishmentCause_encode_xer;
per_type_decoder_f ReestablishmentCause_decode_uper;
per_type_encoder_f ReestablishmentCause_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _ReestablishmentCause_H_ */
#include <rf_phreaker/lte_rrc_asn_library/asn_internal.h>

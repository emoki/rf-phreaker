/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_ReportingAmount_H_
#define	_ReportingAmount_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum ReportingAmount {
	ReportingAmount_ra1	= 0,
	ReportingAmount_ra2	= 1,
	ReportingAmount_ra4	= 2,
	ReportingAmount_ra8	= 3,
	ReportingAmount_ra16	= 4,
	ReportingAmount_ra32	= 5,
	ReportingAmount_ra64	= 6,
	ReportingAmount_ra_Infinity	= 7
} e_ReportingAmount;

/* ReportingAmount */
typedef long	 ReportingAmount_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ReportingAmount;
asn_struct_free_f ReportingAmount_free;
asn_struct_print_f ReportingAmount_print;
asn_constr_check_f ReportingAmount_constraint;
ber_type_decoder_f ReportingAmount_decode_ber;
der_type_encoder_f ReportingAmount_encode_der;
xer_type_decoder_f ReportingAmount_decode_xer;
xer_type_encoder_f ReportingAmount_encode_xer;
per_type_decoder_f ReportingAmount_decode_uper;
per_type_encoder_f ReportingAmount_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _ReportingAmount_H_ */

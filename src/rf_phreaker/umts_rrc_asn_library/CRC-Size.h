/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_CRC_Size_H_
#define	_CRC_Size_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum CRC_Size {
	CRC_Size_crc0	= 0,
	CRC_Size_crc8	= 1,
	CRC_Size_crc12	= 2,
	CRC_Size_crc16	= 3,
	CRC_Size_crc24	= 4
} e_CRC_Size;

/* CRC-Size */
typedef long	 CRC_Size_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_CRC_Size;
asn_struct_free_f CRC_Size_free;
asn_struct_print_f CRC_Size_print;
asn_constr_check_f CRC_Size_constraint;
ber_type_decoder_f CRC_Size_decode_ber;
der_type_encoder_f CRC_Size_encode_der;
xer_type_decoder_f CRC_Size_decode_xer;
xer_type_encoder_f CRC_Size_encode_xer;
per_type_decoder_f CRC_Size_decode_uper;
per_type_encoder_f CRC_Size_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _CRC_Size_H_ */

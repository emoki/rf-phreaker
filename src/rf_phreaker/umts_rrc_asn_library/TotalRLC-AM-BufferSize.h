/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_TotalRLC_AM_BufferSize_H_
#define	_TotalRLC_AM_BufferSize_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum TotalRLC_AM_BufferSize {
	TotalRLC_AM_BufferSize_dummy	= 0,
	TotalRLC_AM_BufferSize_kb10	= 1,
	TotalRLC_AM_BufferSize_kb50	= 2,
	TotalRLC_AM_BufferSize_kb100	= 3,
	TotalRLC_AM_BufferSize_kb150	= 4,
	TotalRLC_AM_BufferSize_kb500	= 5,
	TotalRLC_AM_BufferSize_kb1000	= 6,
	TotalRLC_AM_BufferSize_spare	= 7
} e_TotalRLC_AM_BufferSize;

/* TotalRLC-AM-BufferSize */
typedef long	 TotalRLC_AM_BufferSize_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_TotalRLC_AM_BufferSize;
asn_struct_free_f TotalRLC_AM_BufferSize_free;
asn_struct_print_f TotalRLC_AM_BufferSize_print;
asn_constr_check_f TotalRLC_AM_BufferSize_constraint;
ber_type_decoder_f TotalRLC_AM_BufferSize_decode_ber;
der_type_encoder_f TotalRLC_AM_BufferSize_encode_der;
xer_type_decoder_f TotalRLC_AM_BufferSize_decode_xer;
xer_type_encoder_f TotalRLC_AM_BufferSize_encode_xer;
per_type_decoder_f TotalRLC_AM_BufferSize_decode_uper;
per_type_encoder_f TotalRLC_AM_BufferSize_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _TotalRLC_AM_BufferSize_H_ */

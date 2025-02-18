/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_UE_DPCCH_Burst_H_
#define	_UE_DPCCH_Burst_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum UE_DPCCH_Burst {
	UE_DPCCH_Burst_sub_frames_1	= 0,
	UE_DPCCH_Burst_sub_frames_2	= 1,
	UE_DPCCH_Burst_sub_frames_5	= 2,
	UE_DPCCH_Burst_spare1	= 3
} e_UE_DPCCH_Burst;

/* UE-DPCCH-Burst */
typedef long	 UE_DPCCH_Burst_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_UE_DPCCH_Burst;
asn_struct_free_f UE_DPCCH_Burst_free;
asn_struct_print_f UE_DPCCH_Burst_print;
asn_constr_check_f UE_DPCCH_Burst_constraint;
ber_type_decoder_f UE_DPCCH_Burst_decode_ber;
der_type_encoder_f UE_DPCCH_Burst_encode_der;
xer_type_decoder_f UE_DPCCH_Burst_decode_xer;
xer_type_encoder_f UE_DPCCH_Burst_encode_xer;
per_type_decoder_f UE_DPCCH_Burst_decode_uper;
per_type_encoder_f UE_DPCCH_Burst_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _UE_DPCCH_Burst_H_ */

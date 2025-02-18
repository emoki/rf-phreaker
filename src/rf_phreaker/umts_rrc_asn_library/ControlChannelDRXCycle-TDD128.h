/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_ControlChannelDRXCycle_TDD128_H_
#define	_ControlChannelDRXCycle_TDD128_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum ControlChannelDRXCycle_TDD128 {
	ControlChannelDRXCycle_TDD128_sub_frames_1	= 0,
	ControlChannelDRXCycle_TDD128_sub_frames_2	= 1,
	ControlChannelDRXCycle_TDD128_sub_frames_4	= 2,
	ControlChannelDRXCycle_TDD128_sub_frames_8	= 3,
	ControlChannelDRXCycle_TDD128_sub_frames_16	= 4,
	ControlChannelDRXCycle_TDD128_sub_frames_32	= 5,
	ControlChannelDRXCycle_TDD128_sub_frames_64	= 6,
	ControlChannelDRXCycle_TDD128_spare1	= 7
} e_ControlChannelDRXCycle_TDD128;

/* ControlChannelDRXCycle-TDD128 */
typedef long	 ControlChannelDRXCycle_TDD128_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ControlChannelDRXCycle_TDD128;
asn_struct_free_f ControlChannelDRXCycle_TDD128_free;
asn_struct_print_f ControlChannelDRXCycle_TDD128_print;
asn_constr_check_f ControlChannelDRXCycle_TDD128_constraint;
ber_type_decoder_f ControlChannelDRXCycle_TDD128_decode_ber;
der_type_encoder_f ControlChannelDRXCycle_TDD128_encode_der;
xer_type_decoder_f ControlChannelDRXCycle_TDD128_decode_xer;
xer_type_encoder_f ControlChannelDRXCycle_TDD128_encode_xer;
per_type_decoder_f ControlChannelDRXCycle_TDD128_decode_uper;
per_type_encoder_f ControlChannelDRXCycle_TDD128_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _ControlChannelDRXCycle_TDD128_H_ */

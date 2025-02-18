/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_TrafficVolumeThreshold_H_
#define	_TrafficVolumeThreshold_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum TrafficVolumeThreshold {
	TrafficVolumeThreshold_th8	= 0,
	TrafficVolumeThreshold_th16	= 1,
	TrafficVolumeThreshold_th32	= 2,
	TrafficVolumeThreshold_th64	= 3,
	TrafficVolumeThreshold_th128	= 4,
	TrafficVolumeThreshold_th256	= 5,
	TrafficVolumeThreshold_th512	= 6,
	TrafficVolumeThreshold_th1024	= 7,
	TrafficVolumeThreshold_th2k	= 8,
	TrafficVolumeThreshold_th3k	= 9,
	TrafficVolumeThreshold_th4k	= 10,
	TrafficVolumeThreshold_th6k	= 11,
	TrafficVolumeThreshold_th8k	= 12,
	TrafficVolumeThreshold_th12k	= 13,
	TrafficVolumeThreshold_th16k	= 14,
	TrafficVolumeThreshold_th24k	= 15,
	TrafficVolumeThreshold_th32k	= 16,
	TrafficVolumeThreshold_th48k	= 17,
	TrafficVolumeThreshold_th64k	= 18,
	TrafficVolumeThreshold_th96k	= 19,
	TrafficVolumeThreshold_th128k	= 20,
	TrafficVolumeThreshold_th192k	= 21,
	TrafficVolumeThreshold_th256k	= 22,
	TrafficVolumeThreshold_th384k	= 23,
	TrafficVolumeThreshold_th512k	= 24,
	TrafficVolumeThreshold_th768k	= 25
} e_TrafficVolumeThreshold;

/* TrafficVolumeThreshold */
typedef long	 TrafficVolumeThreshold_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_TrafficVolumeThreshold;
asn_struct_free_f TrafficVolumeThreshold_free;
asn_struct_print_f TrafficVolumeThreshold_print;
asn_constr_check_f TrafficVolumeThreshold_constraint;
ber_type_decoder_f TrafficVolumeThreshold_decode_ber;
der_type_encoder_f TrafficVolumeThreshold_encode_der;
xer_type_decoder_f TrafficVolumeThreshold_decode_xer;
xer_type_encoder_f TrafficVolumeThreshold_encode_xer;
per_type_decoder_f TrafficVolumeThreshold_decode_uper;
per_type_encoder_f TrafficVolumeThreshold_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _TrafficVolumeThreshold_H_ */

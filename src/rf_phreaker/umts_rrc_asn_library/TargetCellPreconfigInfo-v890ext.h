/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_TargetCellPreconfigInfo_v890ext_H_
#define	_TargetCellPreconfigInfo_v890ext_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/MIMO-Parameters-v7f0ext.h"

#ifdef __cplusplus
extern "C" {
#endif

/* TargetCellPreconfigInfo-v890ext */
typedef MIMO_Parameters_v7f0ext_t	 TargetCellPreconfigInfo_v890ext_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_TargetCellPreconfigInfo_v890ext;
asn_struct_free_f TargetCellPreconfigInfo_v890ext_free;
asn_struct_print_f TargetCellPreconfigInfo_v890ext_print;
asn_constr_check_f TargetCellPreconfigInfo_v890ext_constraint;
ber_type_decoder_f TargetCellPreconfigInfo_v890ext_decode_ber;
der_type_encoder_f TargetCellPreconfigInfo_v890ext_encode_der;
xer_type_decoder_f TargetCellPreconfigInfo_v890ext_decode_xer;
xer_type_encoder_f TargetCellPreconfigInfo_v890ext_encode_xer;
per_type_decoder_f TargetCellPreconfigInfo_v890ext_decode_uper;
per_type_encoder_f TargetCellPreconfigInfo_v890ext_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _TargetCellPreconfigInfo_v890ext_H_ */

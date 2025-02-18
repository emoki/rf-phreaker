/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_T_Reordering_H_
#define	_T_Reordering_H_


#include <rf_phreaker/lte_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/lte_rrc_asn_library/NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum T_Reordering {
	T_Reordering_ms0	= 0,
	T_Reordering_ms5	= 1,
	T_Reordering_ms10	= 2,
	T_Reordering_ms15	= 3,
	T_Reordering_ms20	= 4,
	T_Reordering_ms25	= 5,
	T_Reordering_ms30	= 6,
	T_Reordering_ms35	= 7,
	T_Reordering_ms40	= 8,
	T_Reordering_ms45	= 9,
	T_Reordering_ms50	= 10,
	T_Reordering_ms55	= 11,
	T_Reordering_ms60	= 12,
	T_Reordering_ms65	= 13,
	T_Reordering_ms70	= 14,
	T_Reordering_ms75	= 15,
	T_Reordering_ms80	= 16,
	T_Reordering_ms85	= 17,
	T_Reordering_ms90	= 18,
	T_Reordering_ms95	= 19,
	T_Reordering_ms100	= 20,
	T_Reordering_ms110	= 21,
	T_Reordering_ms120	= 22,
	T_Reordering_ms130	= 23,
	T_Reordering_ms140	= 24,
	T_Reordering_ms150	= 25,
	T_Reordering_ms160	= 26,
	T_Reordering_ms170	= 27,
	T_Reordering_ms180	= 28,
	T_Reordering_ms190	= 29,
	T_Reordering_ms200	= 30,
	T_Reordering_spare1	= 31
} e_T_Reordering;

/* T-Reordering */
typedef long	 T_Reordering_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_T_Reordering;
asn_struct_free_f T_Reordering_free;
asn_struct_print_f T_Reordering_print;
asn_constr_check_f T_Reordering_constraint;
ber_type_decoder_f T_Reordering_decode_ber;
der_type_encoder_f T_Reordering_encode_der;
xer_type_decoder_f T_Reordering_decode_xer;
xer_type_encoder_f T_Reordering_encode_xer;
per_type_decoder_f T_Reordering_decode_uper;
per_type_encoder_f T_Reordering_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _T_Reordering_H_ */
#include <rf_phreaker/lte_rrc_asn_library/asn_internal.h>

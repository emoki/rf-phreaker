/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_UE_SpecificCapabilityInformation_LCRTDD_H_
#define	_UE_SpecificCapabilityInformation_LCRTDD_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum UE_SpecificCapabilityInformation_LCRTDD {
	UE_SpecificCapabilityInformation_LCRTDD_nF	= 0,
	UE_SpecificCapabilityInformation_LCRTDD_nFMc_TriRx_UniTx	= 1,
	UE_SpecificCapabilityInformation_LCRTDD_nFMc_TriRx_TriTx	= 2,
	UE_SpecificCapabilityInformation_LCRTDD_nFMc_HexRx_UniTx	= 3,
	UE_SpecificCapabilityInformation_LCRTDD_nFMc_HexRx_TriTx	= 4,
	UE_SpecificCapabilityInformation_LCRTDD_nFMc_HexRx_HexTx	= 5,
	UE_SpecificCapabilityInformation_LCRTDD_nFMc_TwoRx_UniTx	= 6,
	UE_SpecificCapabilityInformation_LCRTDD_nFMc_TwoRx_TwoTx	= 7,
	UE_SpecificCapabilityInformation_LCRTDD_spare8	= 8,
	UE_SpecificCapabilityInformation_LCRTDD_spare7	= 9,
	UE_SpecificCapabilityInformation_LCRTDD_spare6	= 10,
	UE_SpecificCapabilityInformation_LCRTDD_spare5	= 11,
	UE_SpecificCapabilityInformation_LCRTDD_spare4	= 12,
	UE_SpecificCapabilityInformation_LCRTDD_spare3	= 13,
	UE_SpecificCapabilityInformation_LCRTDD_spare2	= 14,
	UE_SpecificCapabilityInformation_LCRTDD_spare1	= 15
} e_UE_SpecificCapabilityInformation_LCRTDD;

/* UE-SpecificCapabilityInformation-LCRTDD */
typedef long	 UE_SpecificCapabilityInformation_LCRTDD_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_UE_SpecificCapabilityInformation_LCRTDD;
asn_struct_free_f UE_SpecificCapabilityInformation_LCRTDD_free;
asn_struct_print_f UE_SpecificCapabilityInformation_LCRTDD_print;
asn_constr_check_f UE_SpecificCapabilityInformation_LCRTDD_constraint;
ber_type_decoder_f UE_SpecificCapabilityInformation_LCRTDD_decode_ber;
der_type_encoder_f UE_SpecificCapabilityInformation_LCRTDD_encode_der;
xer_type_decoder_f UE_SpecificCapabilityInformation_LCRTDD_decode_xer;
xer_type_encoder_f UE_SpecificCapabilityInformation_LCRTDD_encode_xer;
per_type_decoder_f UE_SpecificCapabilityInformation_LCRTDD_decode_uper;
per_type_encoder_f UE_SpecificCapabilityInformation_LCRTDD_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _UE_SpecificCapabilityInformation_LCRTDD_H_ */

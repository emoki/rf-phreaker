/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_RepPerLengthOffset_PICH_H_
#define	_RepPerLengthOffset_PICH_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeInteger.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum RepPerLengthOffset_PICH_PR {
	RepPerLengthOffset_PICH_PR_NOTHING,	/* No components present */
	RepPerLengthOffset_PICH_PR_rpp4_2,
	RepPerLengthOffset_PICH_PR_rpp8_2,
	RepPerLengthOffset_PICH_PR_rpp8_4,
	RepPerLengthOffset_PICH_PR_rpp16_2,
	RepPerLengthOffset_PICH_PR_rpp16_4,
	RepPerLengthOffset_PICH_PR_rpp32_2,
	RepPerLengthOffset_PICH_PR_rpp32_4,
	RepPerLengthOffset_PICH_PR_rpp64_2,
	RepPerLengthOffset_PICH_PR_rpp64_4
} RepPerLengthOffset_PICH_PR;

/* RepPerLengthOffset-PICH */
typedef struct RepPerLengthOffset_PICH {
	RepPerLengthOffset_PICH_PR present;
	union RepPerLengthOffset_PICH_u {
		long	 rpp4_2;
		long	 rpp8_2;
		long	 rpp8_4;
		long	 rpp16_2;
		long	 rpp16_4;
		long	 rpp32_2;
		long	 rpp32_4;
		long	 rpp64_2;
		long	 rpp64_4;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RepPerLengthOffset_PICH_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RepPerLengthOffset_PICH;

#ifdef __cplusplus
}
#endif

#endif	/* _RepPerLengthOffset_PICH_H_ */

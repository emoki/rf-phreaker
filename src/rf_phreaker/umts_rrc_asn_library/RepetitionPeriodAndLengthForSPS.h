/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_RepetitionPeriodAndLengthForSPS_H_
#define	_RepetitionPeriodAndLengthForSPS_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NULL.h>
#include <rf_phreaker/umts_rrc_asn_library/NativeInteger.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum RepetitionPeriodAndLengthForSPS_PR {
	RepetitionPeriodAndLengthForSPS_PR_NOTHING,	/* No components present */
	RepetitionPeriodAndLengthForSPS_PR_repetitionPeriod1,
	RepetitionPeriodAndLengthForSPS_PR_repetitionPeriod2,
	RepetitionPeriodAndLengthForSPS_PR_repetitionPeriod4,
	RepetitionPeriodAndLengthForSPS_PR_repetitionPeriod8,
	RepetitionPeriodAndLengthForSPS_PR_repetitionPeriod16,
	RepetitionPeriodAndLengthForSPS_PR_repetitionPeriod32
} RepetitionPeriodAndLengthForSPS_PR;

/* RepetitionPeriodAndLengthForSPS */
typedef struct RepetitionPeriodAndLengthForSPS {
	RepetitionPeriodAndLengthForSPS_PR present;
	union RepetitionPeriodAndLengthForSPS_u {
		NULL_t	 repetitionPeriod1;
		long	 repetitionPeriod2;
		long	 repetitionPeriod4;
		long	 repetitionPeriod8;
		long	 repetitionPeriod16;
		long	 repetitionPeriod32;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RepetitionPeriodAndLengthForSPS_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RepetitionPeriodAndLengthForSPS;

#ifdef __cplusplus
}
#endif

#endif	/* _RepetitionPeriodAndLengthForSPS_H_ */

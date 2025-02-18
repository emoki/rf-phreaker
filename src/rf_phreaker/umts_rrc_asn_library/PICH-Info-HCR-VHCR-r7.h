/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_PICH_Info_HCR_VHCR_r7_H_
#define	_PICH_Info_HCR_VHCR_r7_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/TimeslotNumber.h"
#include "rf_phreaker/umts_rrc_asn_library/MidambleShiftAndBurstType.h"
#include "rf_phreaker/umts_rrc_asn_library/PagingIndicatorLength.h"
#include "rf_phreaker/umts_rrc_asn_library/N-GAP.h"
#include "rf_phreaker/umts_rrc_asn_library/N-PCH.h"
#include "rf_phreaker/umts_rrc_asn_library/TDD-PICH-CCode.h"
#include "rf_phreaker/umts_rrc_asn_library/TDD768-PICH-CCode.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_CHOICE.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum PICH_Info_HCR_VHCR_r7__channelisationCode_PR {
	PICH_Info_HCR_VHCR_r7__channelisationCode_PR_NOTHING,	/* No components present */
	PICH_Info_HCR_VHCR_r7__channelisationCode_PR_tdd384,
	PICH_Info_HCR_VHCR_r7__channelisationCode_PR_tdd768
} PICH_Info_HCR_VHCR_r7__channelisationCode_PR;

/* Forward declarations */
struct RepPerLengthOffset_PICH;

/* PICH-Info-HCR-VHCR-r7 */
typedef struct PICH_Info_HCR_VHCR_r7 {
	struct PICH_Info_HCR_VHCR_r7__channelisationCode {
		PICH_Info_HCR_VHCR_r7__channelisationCode_PR present;
		union PICH_Info_HCR_VHCR_r7__channelisationCode_u {
			TDD_PICH_CCode_t	 tdd384;
			TDD768_PICH_CCode_t	 tdd768;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *channelisationCode;
	TimeslotNumber_t	*timeslot	/* OPTIONAL */;
	MidambleShiftAndBurstType_t	 midambleShiftAndBurstType;
	struct RepPerLengthOffset_PICH	*repetitionPeriodLengthOffset	/* OPTIONAL */;
	PagingIndicatorLength_t	 pagingIndicatorLength	/* DEFAULT 0 */;
	N_GAP_t	*n_GAP	/* DEFAULT 1 */;
	N_PCH_t	*n_PCH	/* DEFAULT 2 */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PICH_Info_HCR_VHCR_r7_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PICH_Info_HCR_VHCR_r7;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/RepPerLengthOffset-PICH.h"

#endif	/* _PICH_Info_HCR_VHCR_r7_H_ */

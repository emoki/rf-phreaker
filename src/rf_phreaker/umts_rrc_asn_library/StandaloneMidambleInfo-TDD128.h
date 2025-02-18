/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_StandaloneMidambleInfo_TDD128_H_
#define	_StandaloneMidambleInfo_TDD128_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeInteger.h>
#include <rf_phreaker/umts_rrc_asn_library/BIT_STRING.h>
#include "rf_phreaker/umts_rrc_asn_library/ActivationTime.h"
#include "rf_phreaker/umts_rrc_asn_library/RepetitionPeriodLengthAndOffset.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* StandaloneMidambleInfo-TDD128 */
typedef struct StandaloneMidambleInfo_TDD128 {
	long	 midambleConfiguration;
	long	 midambleShift;
	BIT_STRING_t	 timeSlotInformation;
	ActivationTime_t	 activationTime;
	long	 subframeNum;
	RepetitionPeriodLengthAndOffset_t	 repetitionPeriodAndLength;
	long	*referenceBeta	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} StandaloneMidambleInfo_TDD128_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_StandaloneMidambleInfo_TDD128;

#ifdef __cplusplus
}
#endif

#endif	/* _StandaloneMidambleInfo_TDD128_H_ */

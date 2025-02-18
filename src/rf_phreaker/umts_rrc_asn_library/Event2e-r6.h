/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_Event2e_r6_H_
#define	_Event2e_r6_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/HysteresisInterFreq.h"
#include "rf_phreaker/umts_rrc_asn_library/TimeToTrigger.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct ReportingCellStatus;
struct NonUsedFreqParameterList_r6;

/* Event2e-r6 */
typedef struct Event2e_r6 {
	HysteresisInterFreq_t	 hysteresis;
	TimeToTrigger_t	 timeToTrigger;
	struct ReportingCellStatus	*reportingCellStatus	/* OPTIONAL */;
	struct NonUsedFreqParameterList_r6	*nonUsedFreqParameterList	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Event2e_r6_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Event2e_r6;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/ReportingCellStatus.h"
#include "rf_phreaker/umts_rrc_asn_library/NonUsedFreqParameterList-r6.h"

#endif	/* _Event2e_r6_H_ */

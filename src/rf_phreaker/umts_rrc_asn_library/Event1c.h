/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_Event1c_H_
#define	_Event1c_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/ReplacementActivationThreshold.h"
#include "rf_phreaker/umts_rrc_asn_library/ReportingAmount.h"
#include "rf_phreaker/umts_rrc_asn_library/ReportingInterval.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Event1c */
typedef struct Event1c {
	ReplacementActivationThreshold_t	 replacementActivationThreshold;
	ReportingAmount_t	 reportingAmount;
	ReportingInterval_t	 reportingInterval;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Event1c_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Event1c;

#ifdef __cplusplus
}
#endif

#endif	/* _Event1c_H_ */

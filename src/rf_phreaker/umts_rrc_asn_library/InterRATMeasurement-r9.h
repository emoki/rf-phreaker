/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_InterRATMeasurement_r9_H_
#define	_InterRATMeasurement_r9_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/InterRATReportCriteria.h"
#include "rf_phreaker/umts_rrc_asn_library/InterRATCellInfoList-r6.h"
#include "rf_phreaker/umts_rrc_asn_library/EUTRA-FrequencyList-r9.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_CHOICE.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum InterRATMeasurement_r9__interRATMeasurementObjects_PR {
	InterRATMeasurement_r9__interRATMeasurementObjects_PR_NOTHING,	/* No components present */
	InterRATMeasurement_r9__interRATMeasurementObjects_PR_interRATCellInfoList,
	InterRATMeasurement_r9__interRATMeasurementObjects_PR_eutra_FrequencyList
} InterRATMeasurement_r9__interRATMeasurementObjects_PR;

/* Forward declarations */
struct InterRATMeasQuantity_r8;
struct InterRATReportingQuantity_r8;
struct IdleIntervalInfo;

/* InterRATMeasurement-r9 */
typedef struct InterRATMeasurement_r9 {
	struct InterRATMeasurement_r9__interRATMeasurementObjects {
		InterRATMeasurement_r9__interRATMeasurementObjects_PR present;
		union InterRATMeasurement_r9__interRATMeasurementObjects_u {
			InterRATCellInfoList_r6_t	 interRATCellInfoList;
			EUTRA_FrequencyList_r9_t	 eutra_FrequencyList;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *interRATMeasurementObjects;
	struct InterRATMeasQuantity_r8	*interRATMeasQuantity	/* OPTIONAL */;
	struct InterRATReportingQuantity_r8	*interRATReportingQuantity	/* OPTIONAL */;
	InterRATReportCriteria_t	 reportCriteria;
	struct IdleIntervalInfo	*idleIntervalInfo	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} InterRATMeasurement_r9_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_InterRATMeasurement_r9;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/InterRATMeasQuantity-r8.h"
#include "rf_phreaker/umts_rrc_asn_library/InterRATReportingQuantity-r8.h"
#include "rf_phreaker/umts_rrc_asn_library/IdleIntervalInfo.h"

#endif	/* _InterRATMeasurement_r9_H_ */

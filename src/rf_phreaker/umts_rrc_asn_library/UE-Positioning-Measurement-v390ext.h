/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_UE_Positioning_Measurement_v390ext_H_
#define	_UE_Positioning_Measurement_v390ext_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct UE_Positioning_ReportingQuantity_v390ext;
struct MeasurementValidity;
struct UE_Positioning_OTDOA_AssistanceData_UEB;

/* UE-Positioning-Measurement-v390ext */
typedef struct UE_Positioning_Measurement_v390ext {
	struct UE_Positioning_ReportingQuantity_v390ext	*ue_positioning_ReportingQuantity_v390ext	/* OPTIONAL */;
	struct MeasurementValidity	*measurementValidity	/* OPTIONAL */;
	struct UE_Positioning_OTDOA_AssistanceData_UEB	*ue_positioning_OTDOA_AssistanceData_UEB	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} UE_Positioning_Measurement_v390ext_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_UE_Positioning_Measurement_v390ext;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/UE-Positioning-ReportingQuantity-v390ext.h"
#include "rf_phreaker/umts_rrc_asn_library/MeasurementValidity.h"
#include "rf_phreaker/umts_rrc_asn_library/UE-Positioning-OTDOA-AssistanceData-UEB.h"

#endif	/* _UE_Positioning_Measurement_v390ext_H_ */

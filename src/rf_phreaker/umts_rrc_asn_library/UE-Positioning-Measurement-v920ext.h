/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_UE_Positioning_Measurement_v920ext_H_
#define	_UE_Positioning_Measurement_v920ext_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct UE_Positioning_GPS_AssistanceData_v920ext;
struct UE_Positioning_GANSS_AssistanceData_v920ext;

/* UE-Positioning-Measurement-v920ext */
typedef struct UE_Positioning_Measurement_v920ext {
	struct UE_Positioning_GPS_AssistanceData_v920ext	*ue_positioning_GPS_AssistanceData	/* OPTIONAL */;
	struct UE_Positioning_GANSS_AssistanceData_v920ext	*ue_positioning_GANSS_AssistanceData	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} UE_Positioning_Measurement_v920ext_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_UE_Positioning_Measurement_v920ext;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/UE-Positioning-GPS-AssistanceData-v920ext.h"
#include "rf_phreaker/umts_rrc_asn_library/UE-Positioning-GANSS-AssistanceData-v920ext.h"

#endif	/* _UE_Positioning_Measurement_v920ext_H_ */

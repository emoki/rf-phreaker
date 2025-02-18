/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "PDU-definitions"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_MeasurementControl_r9_IEs_H_
#define	_MeasurementControl_r9_IEs_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/MeasurementIdentity.h"
#include "rf_phreaker/umts_rrc_asn_library/MeasurementCommand-r9.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct MeasurementReportingMode;
struct AdditionalMeasurementID_List;
struct CellDCHMeasOccasionInfo_TDD128_r9;
struct DPCH_CompressedModeStatusInfo;

/* MeasurementControl-r9-IEs */
typedef struct MeasurementControl_r9_IEs {
	MeasurementIdentity_t	 measurementIdentity;
	MeasurementCommand_r9_t	 measurementCommand;
	struct MeasurementReportingMode	*measurementReportingMode	/* OPTIONAL */;
	struct AdditionalMeasurementID_List	*additionalMeasurementList	/* OPTIONAL */;
	struct CellDCHMeasOccasionInfo_TDD128_r9	*cellDCHMeasOccasionInfo_TDD128	/* OPTIONAL */;
	struct DPCH_CompressedModeStatusInfo	*dpch_CompressedModeStatusInfo	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MeasurementControl_r9_IEs_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MeasurementControl_r9_IEs;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/MeasurementReportingMode.h"
#include "rf_phreaker/umts_rrc_asn_library/AdditionalMeasurementID-List.h"
#include "rf_phreaker/umts_rrc_asn_library/CellDCHMeasOccasionInfo-TDD128-r9.h"
#include "rf_phreaker/umts_rrc_asn_library/DPCH-CompressedModeStatusInfo.h"

#endif	/* _MeasurementControl_r9_IEs_H_ */

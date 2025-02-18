/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_ReportingCellStatus_r10_H_
#define	_ReportingCellStatus_r10_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/MaxNumberOfReportingCellsType1.h"
#include "rf_phreaker/umts_rrc_asn_library/MaxNumberOfReportingCellsType3.h"
#include "rf_phreaker/umts_rrc_asn_library/MaxNumberOfReportingCellsType2.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum ReportingCellStatus_r10_PR {
	ReportingCellStatus_r10_PR_NOTHING,	/* No components present */
	ReportingCellStatus_r10_PR_withinActiveSet,
	ReportingCellStatus_r10_PR_withinMonitoredSetUsedFreq,
	ReportingCellStatus_r10_PR_withinActiveAndOrMonitoredUsedFreq,
	ReportingCellStatus_r10_PR_withinDetectedSetUsedFreq,
	ReportingCellStatus_r10_PR_withinMonitoredAndOrDetectedUsedFreq,
	ReportingCellStatus_r10_PR_allActiveplusMonitoredSet,
	ReportingCellStatus_r10_PR_allActivePlusDetectedSet,
	ReportingCellStatus_r10_PR_allActivePlusMonitoredAndOrDetectedSet,
	ReportingCellStatus_r10_PR_withinVirtualActSet,
	ReportingCellStatus_r10_PR_withinMonitoredSetNonUsedFreq,
	ReportingCellStatus_r10_PR_withinMonitoredAndOrVirtualActiveSetNonUsedFreq,
	ReportingCellStatus_r10_PR_allVirtualActSetplusMonitoredSetNonUsedFreq,
	ReportingCellStatus_r10_PR_withinActSetOrVirtualActSet_InterRATcells,
	ReportingCellStatus_r10_PR_withinActSetAndOrMonitoredUsedFreqOrVirtualActSetAndOrMonitoredNonUsedFreq,
	ReportingCellStatus_r10_PR_allVirtualActSetplusMonitoredSetplusDetectedSetNonUsedFreq
} ReportingCellStatus_r10_PR;

/* ReportingCellStatus-r10 */
typedef struct ReportingCellStatus_r10 {
	ReportingCellStatus_r10_PR present;
	union ReportingCellStatus_r10_u {
		MaxNumberOfReportingCellsType1_t	 withinActiveSet;
		MaxNumberOfReportingCellsType1_t	 withinMonitoredSetUsedFreq;
		MaxNumberOfReportingCellsType1_t	 withinActiveAndOrMonitoredUsedFreq;
		MaxNumberOfReportingCellsType1_t	 withinDetectedSetUsedFreq;
		MaxNumberOfReportingCellsType1_t	 withinMonitoredAndOrDetectedUsedFreq;
		MaxNumberOfReportingCellsType3_t	 allActiveplusMonitoredSet;
		MaxNumberOfReportingCellsType3_t	 allActivePlusDetectedSet;
		MaxNumberOfReportingCellsType3_t	 allActivePlusMonitoredAndOrDetectedSet;
		MaxNumberOfReportingCellsType1_t	 withinVirtualActSet;
		MaxNumberOfReportingCellsType1_t	 withinMonitoredSetNonUsedFreq;
		MaxNumberOfReportingCellsType1_t	 withinMonitoredAndOrVirtualActiveSetNonUsedFreq;
		MaxNumberOfReportingCellsType3_t	 allVirtualActSetplusMonitoredSetNonUsedFreq;
		MaxNumberOfReportingCellsType2_t	 withinActSetOrVirtualActSet_InterRATcells;
		MaxNumberOfReportingCellsType2_t	 withinActSetAndOrMonitoredUsedFreqOrVirtualActSetAndOrMonitoredNonUsedFreq;
		MaxNumberOfReportingCellsType3_t	 allVirtualActSetplusMonitoredSetplusDetectedSetNonUsedFreq;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ReportingCellStatus_r10_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ReportingCellStatus_r10;

#ifdef __cplusplus
}
#endif

#endif	/* _ReportingCellStatus_r10_H_ */

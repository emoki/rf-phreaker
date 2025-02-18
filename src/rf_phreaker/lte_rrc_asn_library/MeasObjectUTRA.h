/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_MeasObjectUTRA_H_
#define	_MeasObjectUTRA_H_


#include <rf_phreaker/lte_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/lte_rrc_asn_library/ARFCN-ValueUTRA.h"
#include "rf_phreaker/lte_rrc_asn_library/Q-OffsetRangeInterRAT.h"
#include "rf_phreaker/lte_rrc_asn_library/CellsToAddModListUTRA-FDD.h"
#include "rf_phreaker/lte_rrc_asn_library/CellsToAddModListUTRA-TDD.h"
#include <rf_phreaker/lte_rrc_asn_library/constr_CHOICE.h>
#include "rf_phreaker/lte_rrc_asn_library/PhysCellIdUTRA-FDD.h"
#include "rf_phreaker/lte_rrc_asn_library/PhysCellIdUTRA-TDD.h"
#include <rf_phreaker/lte_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum MeasObjectUTRA__cellsToAddModList_PR {
	MeasObjectUTRA__cellsToAddModList_PR_NOTHING,	/* No components present */
	MeasObjectUTRA__cellsToAddModList_PR_cellsToAddModListUTRA_FDD,
	MeasObjectUTRA__cellsToAddModList_PR_cellsToAddModListUTRA_TDD
} MeasObjectUTRA__cellsToAddModList_PR;
typedef enum MeasObjectUTRA__cellForWhichToReportCGI_PR {
	MeasObjectUTRA__cellForWhichToReportCGI_PR_NOTHING,	/* No components present */
	MeasObjectUTRA__cellForWhichToReportCGI_PR_utra_FDD,
	MeasObjectUTRA__cellForWhichToReportCGI_PR_utra_TDD
} MeasObjectUTRA__cellForWhichToReportCGI_PR;

/* Forward declarations */
struct CellIndexList;
struct CSG_AllowedReportingCells_r9;

/* MeasObjectUTRA */
typedef struct MeasObjectUTRA {
	ARFCN_ValueUTRA_t	 carrierFreq;
	Q_OffsetRangeInterRAT_t	 offsetFreq	/* DEFAULT 0 */;
	struct CellIndexList	*cellsToRemoveList	/* OPTIONAL */;
	struct MeasObjectUTRA__cellsToAddModList {
		MeasObjectUTRA__cellsToAddModList_PR present;
		union MeasObjectUTRA__cellsToAddModList_u {
			CellsToAddModListUTRA_FDD_t	 cellsToAddModListUTRA_FDD;
			CellsToAddModListUTRA_TDD_t	 cellsToAddModListUTRA_TDD;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *cellsToAddModList;
	struct MeasObjectUTRA__cellForWhichToReportCGI {
		MeasObjectUTRA__cellForWhichToReportCGI_PR present;
		union MeasObjectUTRA__cellForWhichToReportCGI_u {
			PhysCellIdUTRA_FDD_t	 utra_FDD;
			PhysCellIdUTRA_TDD_t	 utra_TDD;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *cellForWhichToReportCGI;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	struct CSG_AllowedReportingCells_r9	*csg_allowedReportingCells_v930	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MeasObjectUTRA_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MeasObjectUTRA;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/lte_rrc_asn_library/CellIndexList.h"
#include "rf_phreaker/lte_rrc_asn_library/CSG-AllowedReportingCells-r9.h"

#endif	/* _MeasObjectUTRA_H_ */
#include <rf_phreaker/lte_rrc_asn_library/asn_internal.h>

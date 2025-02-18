/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_UE_EUTRA_Capability_v920_IEs_H_
#define	_UE_EUTRA_Capability_v920_IEs_H_


#include <rf_phreaker/lte_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/lte_rrc_asn_library/PhyLayerParameters-v920.h"
#include "rf_phreaker/lte_rrc_asn_library/IRAT-ParametersGERAN-v920.h"
#include <rf_phreaker/lte_rrc_asn_library/NativeEnumerated.h>
#include "rf_phreaker/lte_rrc_asn_library/CSG-ProximityIndicationParameters-r9.h"
#include "rf_phreaker/lte_rrc_asn_library/NeighCellSI-AcquisitionParameters-r9.h"
#include "rf_phreaker/lte_rrc_asn_library/SON-Parameters-r9.h"
#include <rf_phreaker/lte_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum UE_EUTRA_Capability_v920_IEs__deviceType_r9 {
	UE_EUTRA_Capability_v920_IEs__deviceType_r9_noBenFromBatConsumpOpt	= 0
} e_UE_EUTRA_Capability_v920_IEs__deviceType_r9;

/* Forward declarations */
struct IRAT_ParametersUTRA_v920;
struct IRAT_ParametersCDMA2000_1XRTT_v920;
struct UE_EUTRA_Capability_v940_IEs;

/* UE-EUTRA-Capability-v920-IEs */
typedef struct UE_EUTRA_Capability_v920_IEs {
	PhyLayerParameters_v920_t	 phyLayerParameters_v920;
	IRAT_ParametersGERAN_v920_t	 interRAT_ParametersGERAN_v920;
	struct IRAT_ParametersUTRA_v920	*interRAT_ParametersUTRA_v920	/* OPTIONAL */;
	struct IRAT_ParametersCDMA2000_1XRTT_v920	*interRAT_ParametersCDMA2000_v920	/* OPTIONAL */;
	long	*deviceType_r9	/* OPTIONAL */;
	CSG_ProximityIndicationParameters_r9_t	 csg_ProximityIndicationParameters_r9;
	NeighCellSI_AcquisitionParameters_r9_t	 neighCellSI_AcquisitionParameters_r9;
	SON_Parameters_r9_t	 son_Parameters_r9;
	struct UE_EUTRA_Capability_v940_IEs	*nonCriticalExtension	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} UE_EUTRA_Capability_v920_IEs_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_deviceType_r9_6;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_UE_EUTRA_Capability_v920_IEs;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/lte_rrc_asn_library/IRAT-ParametersUTRA-v920.h"
#include "rf_phreaker/lte_rrc_asn_library/IRAT-ParametersCDMA2000-1XRTT-v920.h"
#include "rf_phreaker/lte_rrc_asn_library/UE-EUTRA-Capability-v940-IEs.h"

#endif	/* _UE_EUTRA_Capability_v920_IEs_H_ */
#include <rf_phreaker/lte_rrc_asn_library/asn_internal.h>

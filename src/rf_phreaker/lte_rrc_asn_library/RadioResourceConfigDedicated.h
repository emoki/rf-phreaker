/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_RadioResourceConfigDedicated_H_
#define	_RadioResourceConfigDedicated_H_


#include <rf_phreaker/lte_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/lte_rrc_asn_library/MAC-MainConfig.h"
#include <rf_phreaker/lte_rrc_asn_library/NULL.h>
#include <rf_phreaker/lte_rrc_asn_library/constr_CHOICE.h>
#include <rf_phreaker/lte_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum RadioResourceConfigDedicated__mac_MainConfig_PR {
	RadioResourceConfigDedicated__mac_MainConfig_PR_NOTHING,	/* No components present */
	RadioResourceConfigDedicated__mac_MainConfig_PR_explicitValue,
	RadioResourceConfigDedicated__mac_MainConfig_PR_defaultValue
} RadioResourceConfigDedicated__mac_MainConfig_PR;

/* Forward declarations */
struct SRB_ToAddModList;
struct DRB_ToAddModList;
struct DRB_ToReleaseList;
struct SPS_Config;
struct PhysicalConfigDedicated;
struct RLF_TimersAndConstants_r9;
struct MeasSubframePatternPCell_r10;
struct NeighCellsCRS_Info_r11;

/* RadioResourceConfigDedicated */
typedef struct RadioResourceConfigDedicated {
	struct SRB_ToAddModList	*srb_ToAddModList	/* OPTIONAL */;
	struct DRB_ToAddModList	*drb_ToAddModList	/* OPTIONAL */;
	struct DRB_ToReleaseList	*drb_ToReleaseList	/* OPTIONAL */;
	struct RadioResourceConfigDedicated__mac_MainConfig {
		RadioResourceConfigDedicated__mac_MainConfig_PR present;
		union RadioResourceConfigDedicated__mac_MainConfig_u {
			MAC_MainConfig_t	 explicitValue;
			NULL_t	 defaultValue;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *mac_MainConfig;
	struct SPS_Config	*sps_Config	/* OPTIONAL */;
	struct PhysicalConfigDedicated	*physicalConfigDedicated	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	struct RLF_TimersAndConstants_r9	*rlf_TimersAndConstants_r9	/* OPTIONAL */;
	struct MeasSubframePatternPCell_r10	*measSubframePatternPCell_r10	/* OPTIONAL */;
	struct NeighCellsCRS_Info_r11	*neighCellsCRS_Info_r11	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RadioResourceConfigDedicated_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RadioResourceConfigDedicated;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/lte_rrc_asn_library/SRB-ToAddModList.h"
#include "rf_phreaker/lte_rrc_asn_library/DRB-ToAddModList.h"
#include "rf_phreaker/lte_rrc_asn_library/DRB-ToReleaseList.h"
#include "rf_phreaker/lte_rrc_asn_library/SPS-Config.h"
#include "rf_phreaker/lte_rrc_asn_library/PhysicalConfigDedicated.h"
#include "rf_phreaker/lte_rrc_asn_library/RLF-TimersAndConstants-r9.h"
#include "rf_phreaker/lte_rrc_asn_library/MeasSubframePatternPCell-r10.h"
#include "rf_phreaker/lte_rrc_asn_library/NeighCellsCRS-Info-r11.h"

#endif	/* _RadioResourceConfigDedicated_H_ */
#include <rf_phreaker/lte_rrc_asn_library/asn_internal.h>

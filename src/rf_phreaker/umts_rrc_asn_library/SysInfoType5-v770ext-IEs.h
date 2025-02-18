/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_SysInfoType5_v770ext_IEs_H_
#define	_SysInfoType5_v770ext_IEs_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/HS-DSCH-CommonSystemInformation.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_CHOICE.h>
#include "rf_phreaker/umts_rrc_asn_library/SCCPCH-SystemInformation-MBMS-r7.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum SysInfoType5_v770ext_IEs__modeSpecificInfo_PR {
	SysInfoType5_v770ext_IEs__modeSpecificInfo_PR_NOTHING,	/* No components present */
	SysInfoType5_v770ext_IEs__modeSpecificInfo_PR_fdd,
	SysInfoType5_v770ext_IEs__modeSpecificInfo_PR_tdd768,
	SysInfoType5_v770ext_IEs__modeSpecificInfo_PR_tdd128
} SysInfoType5_v770ext_IEs__modeSpecificInfo_PR;
typedef enum SysInfoType5_v770ext_IEs__sccpch_SystemInformation_MBMS_PR {
	SysInfoType5_v770ext_IEs__sccpch_SystemInformation_MBMS_PR_NOTHING,	/* No components present */
	SysInfoType5_v770ext_IEs__sccpch_SystemInformation_MBMS_PR_mcchOnSCCPCHusedOnlyForMBMS
} SysInfoType5_v770ext_IEs__sccpch_SystemInformation_MBMS_PR;

/* Forward declarations */
struct SCCPCH_SystemInformationList_HCR_VHCR_r7;
struct TDD_MBSFNInformation;
struct HS_DSCH_PagingSystemInformation;
struct PUSCH_SysInfoList_SFN_VHCR;
struct PDSCH_SysInfoList_VHCR_r7;
struct PRACH_SystemInformationList_VHCR_r7;
struct PRACH_SystemInformationList_LCR_v770ext;

/* SysInfoType5-v770ext-IEs */
typedef struct SysInfoType5_v770ext_IEs {
	struct SysInfoType5_v770ext_IEs__modeSpecificInfo {
		SysInfoType5_v770ext_IEs__modeSpecificInfo_PR present;
		union SysInfoType5_v770ext_IEs__modeSpecificInfo_u {
			struct SysInfoType5_v770ext_IEs__modeSpecificInfo__fdd {
				HS_DSCH_CommonSystemInformation_t	 hs_dsch_CommonSystemInformation;
				struct HS_DSCH_PagingSystemInformation	*hs_dsch_PagingSystemInformation	/* OPTIONAL */;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} fdd;
			struct SysInfoType5_v770ext_IEs__modeSpecificInfo__tdd768 {
				struct PUSCH_SysInfoList_SFN_VHCR	*pusch_SysInfoList_SFN	/* OPTIONAL */;
				struct PDSCH_SysInfoList_VHCR_r7	*pdsch_SysInfoList_SFN	/* OPTIONAL */;
				struct PRACH_SystemInformationList_VHCR_r7	*prach_SystemInformationList	/* OPTIONAL */;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} tdd768;
			struct SysInfoType5_v770ext_IEs__modeSpecificInfo__tdd128 {
				struct PRACH_SystemInformationList_LCR_v770ext	*prach_SystemInformationList	/* OPTIONAL */;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} tdd128;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *modeSpecificInfo;
	struct SCCPCH_SystemInformationList_HCR_VHCR_r7	*sccpch_SystemInformationList	/* OPTIONAL */;
	struct SysInfoType5_v770ext_IEs__sccpch_SystemInformation_MBMS {
		SysInfoType5_v770ext_IEs__sccpch_SystemInformation_MBMS_PR present;
		union SysInfoType5_v770ext_IEs__sccpch_SystemInformation_MBMS_u {
			SCCPCH_SystemInformation_MBMS_r7_t	 mcchOnSCCPCHusedOnlyForMBMS;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *sccpch_SystemInformation_MBMS;
	struct TDD_MBSFNInformation	*tDD_MBSFNInformation	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SysInfoType5_v770ext_IEs_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SysInfoType5_v770ext_IEs;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/SCCPCH-SystemInformationList-HCR-VHCR-r7.h"
#include "rf_phreaker/umts_rrc_asn_library/TDD-MBSFNInformation.h"
#include "rf_phreaker/umts_rrc_asn_library/HS-DSCH-PagingSystemInformation.h"
#include "rf_phreaker/umts_rrc_asn_library/PUSCH-SysInfoList-SFN-VHCR.h"
#include "rf_phreaker/umts_rrc_asn_library/PDSCH-SysInfoList-VHCR-r7.h"
#include "rf_phreaker/umts_rrc_asn_library/PRACH-SystemInformationList-VHCR-r7.h"
#include "rf_phreaker/umts_rrc_asn_library/PRACH-SystemInformationList-LCR-v770ext.h"

#endif	/* _SysInfoType5_v770ext_IEs_H_ */

/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_MBMS_L23Configuration_H_
#define	_MBMS_L23Configuration_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/MBMS-SCCPCHIdentity.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>
#include "rf_phreaker/umts_rrc_asn_library/MBMS-CommonCCTrChIdentity.h"
#include "rf_phreaker/umts_rrc_asn_library/MBMS-TrCHInformation-NeighbList.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum MBMS_L23Configuration_PR {
	MBMS_L23Configuration_PR_NOTHING,	/* No components present */
	MBMS_L23Configuration_PR_sameAsCurrent,
	MBMS_L23Configuration_PR_different
} MBMS_L23Configuration_PR;

/* Forward declarations */
struct MBMS_MSCH_ConfigurationInfo_r6;

/* MBMS-L23Configuration */
typedef struct MBMS_L23Configuration {
	MBMS_L23Configuration_PR present;
	union MBMS_L23Configuration_u {
		struct MBMS_L23Configuration__sameAsCurrent {
			MBMS_SCCPCHIdentity_t	 currentCell_SCCPCH;
			struct MBMS_MSCH_ConfigurationInfo_r6	*msch_ConfigurationInfo	/* OPTIONAL */;
			
			/* Context for parsing across buffer boundaries */
			asn_struct_ctx_t _asn_ctx;
		} sameAsCurrent;
		struct MBMS_L23Configuration__different {
			MBMS_CommonCCTrChIdentity_t	*transpCh_InfoCommonForAllTrCh	/* OPTIONAL */;
			MBMS_TrCHInformation_NeighbList_t	 transpCHInformation;
			
			/* Context for parsing across buffer boundaries */
			asn_struct_ctx_t _asn_ctx;
		} different;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MBMS_L23Configuration_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MBMS_L23Configuration;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/MBMS-MSCH-ConfigurationInfo-r6.h"

#endif	/* _MBMS_L23Configuration_H_ */

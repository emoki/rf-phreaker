/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_MBMS_CurrentCell_SCCPCH_r6_H_
#define	_MBMS_CurrentCell_SCCPCH_r6_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/MBMS-SCCPCHIdentity.h"
#include "rf_phreaker/umts_rrc_asn_library/MBMS-CommonPhyChIdentity.h"
#include "rf_phreaker/umts_rrc_asn_library/MBMS-SoftComb-TimingOffset.h"
#include "rf_phreaker/umts_rrc_asn_library/MBMS-CommonCCTrChIdentity.h"
#include "rf_phreaker/umts_rrc_asn_library/MBMS-TrCHInformation-CurrList.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* MBMS-CurrentCell-SCCPCH-r6 */
typedef struct MBMS_CurrentCell_SCCPCH_r6 {
	MBMS_SCCPCHIdentity_t	*sccpchIdentity	/* OPTIONAL */;
	MBMS_CommonPhyChIdentity_t	 secondaryCCPCH_Info;
	MBMS_SoftComb_TimingOffset_t	*softComb_TimingOffset	/* OPTIONAL */;
	MBMS_CommonCCTrChIdentity_t	*transpCh_InfoCommonForAllTrCh	/* OPTIONAL */;
	MBMS_TrCHInformation_CurrList_t	 transpCHInformation;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MBMS_CurrentCell_SCCPCH_r6_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MBMS_CurrentCell_SCCPCH_r6;

#ifdef __cplusplus
}
#endif

#endif	/* _MBMS_CurrentCell_SCCPCH_r6_H_ */

/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_PDSCH_SysInfoList_SFN_HCR_r5_H_
#define	_PDSCH_SysInfoList_SFN_HCR_r5_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/asn_SEQUENCE_OF.h>
#include "rf_phreaker/umts_rrc_asn_library/PDSCH-SysInfo-HCR-r5.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct SFN_TimeInfo;

typedef struct PDSCH_SysInfoList_SFN_HCR_r5__Member {
	PDSCH_SysInfo_HCR_r5_t	 pdsch_SysInfo;
	struct SFN_TimeInfo	*sfn_TimeInfo	/* OPTIONAL */;

	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PDSCH_SysInfoList_SFN_HCR_r5__Member_t;

/* PDSCH-SysInfoList-SFN-HCR-r5 */
typedef struct PDSCH_SysInfoList_SFN_HCR_r5 {
	A_SEQUENCE_OF(PDSCH_SysInfoList_SFN_HCR_r5__Member_t) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PDSCH_SysInfoList_SFN_HCR_r5_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PDSCH_SysInfoList_SFN_HCR_r5;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/SFN-TimeInfo.h"

#endif	/* _PDSCH_SysInfoList_SFN_HCR_r5_H_ */

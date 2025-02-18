/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_UTRA_PriorityInfoList_H_
#define	_UTRA_PriorityInfoList_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeInteger.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct UTRAN_FDD_FrequencyList;
struct UTRAN_TDD_FrequencyList;

/* UTRA-PriorityInfoList */
typedef struct UTRA_PriorityInfoList {
	struct UTRA_PriorityInfoList__utra_ServingCell {
		long	 priority;
		long	 s_PrioritySearch1;
		long	*s_PrioritySearch2	/* OPTIONAL */;
		long	 threshServingLow;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} utra_ServingCell;
	struct UTRAN_FDD_FrequencyList	*utran_FDD_FrequencyList	/* OPTIONAL */;
	struct UTRAN_TDD_FrequencyList	*utran_TDD_FrequencyList	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} UTRA_PriorityInfoList_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_UTRA_PriorityInfoList;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/UTRAN-FDD-FrequencyList.h"
#include "rf_phreaker/umts_rrc_asn_library/UTRAN-TDD-FrequencyList.h"

#endif	/* _UTRA_PriorityInfoList_H_ */

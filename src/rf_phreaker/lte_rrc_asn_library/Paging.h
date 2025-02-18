/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_Paging_H_
#define	_Paging_H_


#include <rf_phreaker/lte_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/lte_rrc_asn_library/NativeEnumerated.h>
#include <rf_phreaker/lte_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum Paging__systemInfoModification {
	Paging__systemInfoModification_true	= 0
} e_Paging__systemInfoModification;
typedef enum Paging__etws_Indication {
	Paging__etws_Indication_true	= 0
} e_Paging__etws_Indication;

/* Forward declarations */
struct PagingRecordList;
struct Paging_v890_IEs;

/* Paging */
typedef struct Paging {
	struct PagingRecordList	*pagingRecordList	/* OPTIONAL */;
	long	*systemInfoModification	/* OPTIONAL */;
	long	*etws_Indication	/* OPTIONAL */;
	struct Paging_v890_IEs	*nonCriticalExtension	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Paging_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_systemInfoModification_3;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_etws_Indication_5;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_Paging;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/lte_rrc_asn_library/PagingRecordList.h"
#include "rf_phreaker/lte_rrc_asn_library/Paging-v890-IEs.h"

#endif	/* _Paging_H_ */
#include <rf_phreaker/lte_rrc_asn_library/asn_internal.h>

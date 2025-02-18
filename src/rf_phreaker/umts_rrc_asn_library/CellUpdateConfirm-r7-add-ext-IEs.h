/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "PDU-definitions"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_CellUpdateConfirm_r7_add_ext_IEs_H_
#define	_CellUpdateConfirm_r7_add_ext_IEs_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/CellUpdateConfirm-v7f0ext-IEs.h"
#include "rf_phreaker/umts_rrc_asn_library/CellUpdateConfirm-v7g0ext-IEs.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct CellUpdateConfirm_v7d0ext_IEs;

/* CellUpdateConfirm-r7-add-ext-IEs */
typedef struct CellUpdateConfirm_r7_add_ext_IEs {
	struct CellUpdateConfirm_v7d0ext_IEs	*cellUpdateConfirm_v7d0ext	/* OPTIONAL */;
	struct CellUpdateConfirm_r7_add_ext_IEs__v7f0NonCriticalExtensions {
		CellUpdateConfirm_v7f0ext_IEs_t	 cellUpdateConfirm_v7f0ext;
		struct CellUpdateConfirm_r7_add_ext_IEs__v7f0NonCriticalExtensions__v7g0NonCriticalExtensions {
			CellUpdateConfirm_v7g0ext_IEs_t	 cellUpdateConfirm_v7g0ext;
			struct CellUpdateConfirm_r7_add_ext_IEs__v7f0NonCriticalExtensions__v7g0NonCriticalExtensions__nonCriticalExtensions {
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} *nonCriticalExtensions;
			
			/* Context for parsing across buffer boundaries */
			asn_struct_ctx_t _asn_ctx;
		} *v7g0NonCriticalExtensions;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *v7f0NonCriticalExtensions;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} CellUpdateConfirm_r7_add_ext_IEs_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_CellUpdateConfirm_r7_add_ext_IEs;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/CellUpdateConfirm-v7d0ext-IEs.h"

#endif	/* _CellUpdateConfirm_r7_add_ext_IEs_H_ */

/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_PUCCH_ConfigDedicated_v1020_H_
#define	_PUCCH_ConfigDedicated_v1020_H_


#include <rf_phreaker/lte_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/lte_rrc_asn_library/NativeEnumerated.h>
#include <rf_phreaker/lte_rrc_asn_library/NativeInteger.h>
#include <rf_phreaker/lte_rrc_asn_library/asn_SEQUENCE_OF.h>
#include <rf_phreaker/lte_rrc_asn_library/constr_SEQUENCE_OF.h>
#include <rf_phreaker/lte_rrc_asn_library/NULL.h>
#include <rf_phreaker/lte_rrc_asn_library/constr_SEQUENCE.h>
#include <rf_phreaker/lte_rrc_asn_library/constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum PUCCH_ConfigDedicated_v1020__pucch_Format_r10_PR {
	PUCCH_ConfigDedicated_v1020__pucch_Format_r10_PR_NOTHING,	/* No components present */
	PUCCH_ConfigDedicated_v1020__pucch_Format_r10_PR_format3_r10,
	PUCCH_ConfigDedicated_v1020__pucch_Format_r10_PR_channelSelection_r10
} PUCCH_ConfigDedicated_v1020__pucch_Format_r10_PR;
typedef enum PUCCH_ConfigDedicated_v1020__pucch_Format_r10__format3_r10__twoAntennaPortActivatedPUCCH_Format3_r10_PR {
	PUCCH_ConfigDedicated_v1020__pucch_Format_r10__format3_r10__twoAntennaPortActivatedPUCCH_Format3_r10_PR_NOTHING,	/* No components present */
	PUCCH_ConfigDedicated_v1020__pucch_Format_r10__format3_r10__twoAntennaPortActivatedPUCCH_Format3_r10_PR_release,
	PUCCH_ConfigDedicated_v1020__pucch_Format_r10__format3_r10__twoAntennaPortActivatedPUCCH_Format3_r10_PR_setup
} PUCCH_ConfigDedicated_v1020__pucch_Format_r10__format3_r10__twoAntennaPortActivatedPUCCH_Format3_r10_PR;
typedef enum PUCCH_ConfigDedicated_v1020__pucch_Format_r10__channelSelection_r10__n1PUCCH_AN_CS_r10_PR {
	PUCCH_ConfigDedicated_v1020__pucch_Format_r10__channelSelection_r10__n1PUCCH_AN_CS_r10_PR_NOTHING,	/* No components present */
	PUCCH_ConfigDedicated_v1020__pucch_Format_r10__channelSelection_r10__n1PUCCH_AN_CS_r10_PR_release,
	PUCCH_ConfigDedicated_v1020__pucch_Format_r10__channelSelection_r10__n1PUCCH_AN_CS_r10_PR_setup
} PUCCH_ConfigDedicated_v1020__pucch_Format_r10__channelSelection_r10__n1PUCCH_AN_CS_r10_PR;
typedef enum PUCCH_ConfigDedicated_v1020__twoAntennaPortActivatedPUCCH_Format1a1b_r10 {
	PUCCH_ConfigDedicated_v1020__twoAntennaPortActivatedPUCCH_Format1a1b_r10_true	= 0
} e_PUCCH_ConfigDedicated_v1020__twoAntennaPortActivatedPUCCH_Format1a1b_r10;
typedef enum PUCCH_ConfigDedicated_v1020__simultaneousPUCCH_PUSCH_r10 {
	PUCCH_ConfigDedicated_v1020__simultaneousPUCCH_PUSCH_r10_true	= 0
} e_PUCCH_ConfigDedicated_v1020__simultaneousPUCCH_PUSCH_r10;

/* Forward declarations */
struct N1PUCCH_AN_CS_r10;

/* PUCCH-ConfigDedicated-v1020 */
typedef struct PUCCH_ConfigDedicated_v1020 {
	struct PUCCH_ConfigDedicated_v1020__pucch_Format_r10 {
		PUCCH_ConfigDedicated_v1020__pucch_Format_r10_PR present;
		union PUCCH_ConfigDedicated_v1020__pucch_Format_r10_u {
			struct PUCCH_ConfigDedicated_v1020__pucch_Format_r10__format3_r10 {
				struct PUCCH_ConfigDedicated_v1020__pucch_Format_r10__format3_r10__n3PUCCH_AN_List_r10 {
					A_SEQUENCE_OF(long) list;
					
					/* Context for parsing across buffer boundaries */
					asn_struct_ctx_t _asn_ctx;
				} *n3PUCCH_AN_List_r10;
				struct PUCCH_ConfigDedicated_v1020__pucch_Format_r10__format3_r10__twoAntennaPortActivatedPUCCH_Format3_r10 {
					PUCCH_ConfigDedicated_v1020__pucch_Format_r10__format3_r10__twoAntennaPortActivatedPUCCH_Format3_r10_PR present;
					union PUCCH_ConfigDedicated_v1020__pucch_Format_r10__format3_r10__twoAntennaPortActivatedPUCCH_Format3_r10_u {
						NULL_t	 release;
						struct PUCCH_ConfigDedicated_v1020__pucch_Format_r10__format3_r10__twoAntennaPortActivatedPUCCH_Format3_r10__setup {
							struct PUCCH_ConfigDedicated_v1020__pucch_Format_r10__format3_r10__twoAntennaPortActivatedPUCCH_Format3_r10__setup__n3PUCCH_AN_ListP1_r10 {
								A_SEQUENCE_OF(long) list;
								
								/* Context for parsing across buffer boundaries */
								asn_struct_ctx_t _asn_ctx;
							} n3PUCCH_AN_ListP1_r10;
							
							/* Context for parsing across buffer boundaries */
							asn_struct_ctx_t _asn_ctx;
						} setup;
					} choice;
					
					/* Context for parsing across buffer boundaries */
					asn_struct_ctx_t _asn_ctx;
				} *twoAntennaPortActivatedPUCCH_Format3_r10;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} format3_r10;
			struct PUCCH_ConfigDedicated_v1020__pucch_Format_r10__channelSelection_r10 {
				struct PUCCH_ConfigDedicated_v1020__pucch_Format_r10__channelSelection_r10__n1PUCCH_AN_CS_r10 {
					PUCCH_ConfigDedicated_v1020__pucch_Format_r10__channelSelection_r10__n1PUCCH_AN_CS_r10_PR present;
					union PUCCH_ConfigDedicated_v1020__pucch_Format_r10__channelSelection_r10__n1PUCCH_AN_CS_r10_u {
						NULL_t	 release;
						struct PUCCH_ConfigDedicated_v1020__pucch_Format_r10__channelSelection_r10__n1PUCCH_AN_CS_r10__setup {
							struct PUCCH_ConfigDedicated_v1020__pucch_Format_r10__channelSelection_r10__n1PUCCH_AN_CS_r10__setup__n1PUCCH_AN_CS_List_r10 {
								A_SEQUENCE_OF(struct N1PUCCH_AN_CS_r10) list;
								
								/* Context for parsing across buffer boundaries */
								asn_struct_ctx_t _asn_ctx;
							} n1PUCCH_AN_CS_List_r10;
							
							/* Context for parsing across buffer boundaries */
							asn_struct_ctx_t _asn_ctx;
						} setup;
					} choice;
					
					/* Context for parsing across buffer boundaries */
					asn_struct_ctx_t _asn_ctx;
				} *n1PUCCH_AN_CS_r10;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} channelSelection_r10;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *pucch_Format_r10;
	long	*twoAntennaPortActivatedPUCCH_Format1a1b_r10	/* OPTIONAL */;
	long	*simultaneousPUCCH_PUSCH_r10	/* OPTIONAL */;
	long	*n1PUCCH_AN_RepP1_r10	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PUCCH_ConfigDedicated_v1020_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_twoAntennaPortActivatedPUCCH_Format1a1b_r10_17;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_simultaneousPUCCH_PUSCH_r10_19;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_PUCCH_ConfigDedicated_v1020;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/lte_rrc_asn_library/N1PUCCH-AN-CS-r10.h"

#endif	/* _PUCCH_ConfigDedicated_v1020_H_ */
#include <rf_phreaker/lte_rrc_asn_library/asn_internal.h>

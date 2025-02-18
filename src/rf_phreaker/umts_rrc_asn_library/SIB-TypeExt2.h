/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_SIB_TypeExt2_H_
#define	_SIB_TypeExt2_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NULL.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum SIB_TypeExt2_PR {
	SIB_TypeExt2_PR_NOTHING,	/* No components present */
	SIB_TypeExt2_PR_systemInfoType19,
	SIB_TypeExt2_PR_systemInfoType15_2ter,
	SIB_TypeExt2_PR_systemInfoType20,
	SIB_TypeExt2_PR_spare5,
	SIB_TypeExt2_PR_spare4,
	SIB_TypeExt2_PR_spare3,
	SIB_TypeExt2_PR_spare2,
	SIB_TypeExt2_PR_spare1
} SIB_TypeExt2_PR;

/* SIB-TypeExt2 */
typedef struct SIB_TypeExt2 {
	SIB_TypeExt2_PR present;
	union SIB_TypeExt2_u {
		NULL_t	 systemInfoType19;
		NULL_t	 systemInfoType15_2ter;
		NULL_t	 systemInfoType20;
		NULL_t	 spare5;
		NULL_t	 spare4;
		NULL_t	 spare3;
		NULL_t	 spare2;
		NULL_t	 spare1;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SIB_TypeExt2_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SIB_TypeExt2;

#ifdef __cplusplus
}
#endif

#endif	/* _SIB_TypeExt2_H_ */

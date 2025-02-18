/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_TFCS_ReconfAdd_H_
#define	_TFCS_ReconfAdd_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/asn_SEQUENCE_OF.h>
#include <rf_phreaker/umts_rrc_asn_library/NativeInteger.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE_OF.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum TFCS_ReconfAdd__ctfcSize_PR {
	TFCS_ReconfAdd__ctfcSize_PR_NOTHING,	/* No components present */
	TFCS_ReconfAdd__ctfcSize_PR_ctfc2Bit,
	TFCS_ReconfAdd__ctfcSize_PR_ctfc4Bit,
	TFCS_ReconfAdd__ctfcSize_PR_ctfc6Bit,
	TFCS_ReconfAdd__ctfcSize_PR_ctfc8Bit,
	TFCS_ReconfAdd__ctfcSize_PR_ctfc12Bit,
	TFCS_ReconfAdd__ctfcSize_PR_ctfc16Bit,
	TFCS_ReconfAdd__ctfcSize_PR_ctfc24Bit
} TFCS_ReconfAdd__ctfcSize_PR;

/* Forward declarations */
struct PowerOffsetInformation;

typedef struct TFCS_ReconfAdd__ctfcSize__ctfc2Bit__Member {
	long	 ctfc2;
	struct PowerOffsetInformation	*powerOffsetInformation	/* OPTIONAL */;

	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} TFCS_ReconfAdd__ctfcSize__ctfc2Bit__Member_t;

typedef struct TFCS_ReconfAdd__ctfcSize__ctfc4Bit__Member {
	long	 ctfc4;
	struct PowerOffsetInformation	*powerOffsetInformation	/* OPTIONAL */;

	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} TFCS_ReconfAdd__ctfcSize__ctfc4Bit__Member_t;

typedef struct TFCS_ReconfAdd__ctfcSize__ctfc6Bit__Member {
	long	 ctfc6;
	struct PowerOffsetInformation	*powerOffsetInformation	/* OPTIONAL */;

	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} TFCS_ReconfAdd__ctfcSize__ctfc6Bit__Member_t;

typedef struct TFCS_ReconfAdd__ctfcSize__ctfc8Bit__Member {
	long	 ctfc8;
	struct PowerOffsetInformation	*powerOffsetInformation	/* OPTIONAL */;

	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} TFCS_ReconfAdd__ctfcSize__ctfc8Bit__Member_t;

typedef struct TFCS_ReconfAdd__ctfcSize__ctfc12Bit__Member {
	long	 ctfc12;
	struct PowerOffsetInformation	*powerOffsetInformation	/* OPTIONAL */;

	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} TFCS_ReconfAdd__ctfcSize__ctfc12Bit__Member_t;

typedef struct TFCS_ReconfAdd__ctfcSize__ctfc16Bit__Member {
	long	 ctfc16;
	struct PowerOffsetInformation	*powerOffsetInformation	/* OPTIONAL */;

	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} TFCS_ReconfAdd__ctfcSize__ctfc16Bit__Member_t;

typedef struct TFCS_ReconfAdd__ctfcSize__ctfc24Bit__Member {
	long	 ctfc24;
	struct PowerOffsetInformation	*powerOffsetInformation	/* OPTIONAL */;

	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} TFCS_ReconfAdd__ctfcSize__ctfc24Bit__Member_t;

/* TFCS-ReconfAdd */
typedef struct TFCS_ReconfAdd {
	struct TFCS_ReconfAdd__ctfcSize {
		TFCS_ReconfAdd__ctfcSize_PR present;
		union TFCS_ReconfAdd__ctfcSize_u {
			struct TFCS_ReconfAdd__ctfcSize__ctfc2Bit {
				A_SEQUENCE_OF(TFCS_ReconfAdd__ctfcSize__ctfc2Bit__Member_t) list;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} ctfc2Bit;
			struct TFCS_ReconfAdd__ctfcSize__ctfc4Bit {
				A_SEQUENCE_OF(TFCS_ReconfAdd__ctfcSize__ctfc4Bit__Member_t) list;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} ctfc4Bit;
			struct TFCS_ReconfAdd__ctfcSize__ctfc6Bit {
				A_SEQUENCE_OF(TFCS_ReconfAdd__ctfcSize__ctfc6Bit__Member_t) list;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} ctfc6Bit;
			struct TFCS_ReconfAdd__ctfcSize__ctfc8Bit {
				A_SEQUENCE_OF(TFCS_ReconfAdd__ctfcSize__ctfc8Bit__Member_t) list;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} ctfc8Bit;
			struct TFCS_ReconfAdd__ctfcSize__ctfc12Bit {
				A_SEQUENCE_OF(TFCS_ReconfAdd__ctfcSize__ctfc12Bit__Member_t) list;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} ctfc12Bit;
			struct TFCS_ReconfAdd__ctfcSize__ctfc16Bit {
				A_SEQUENCE_OF(TFCS_ReconfAdd__ctfcSize__ctfc16Bit__Member_t) list;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} ctfc16Bit;
			struct TFCS_ReconfAdd__ctfcSize__ctfc24Bit {
			A_SEQUENCE_OF(TFCS_ReconfAdd__ctfcSize__ctfc24Bit__Member_t) list;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} ctfc24Bit;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} ctfcSize;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} TFCS_ReconfAdd_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_TFCS_ReconfAdd;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/PowerOffsetInformation.h"

#endif	/* _TFCS_ReconfAdd_H_ */

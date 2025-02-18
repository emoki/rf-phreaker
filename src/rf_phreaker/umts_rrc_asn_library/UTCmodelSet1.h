/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_UTCmodelSet1_H_
#define	_UTCmodelSet1_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/BIT_STRING.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* UTCmodelSet1 */
typedef struct UTCmodelSet1 {
	BIT_STRING_t	 utcA0;
	BIT_STRING_t	 utcA1;
	BIT_STRING_t	 utcA2;
	BIT_STRING_t	 utcDeltaTls;
	BIT_STRING_t	 utcTot;
	BIT_STRING_t	 utcWNot;
	BIT_STRING_t	 utcWNlsf;
	BIT_STRING_t	 utcDN;
	BIT_STRING_t	 utcDeltaTlsf;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} UTCmodelSet1_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_UTCmodelSet1;

#ifdef __cplusplus
}
#endif

#endif	/* _UTCmodelSet1_H_ */

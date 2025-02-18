/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "PDU-definitions"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_TransportFormatCombinationControl_v820ext_IEs_H_
#define	_TransportFormatCombinationControl_v820ext_IEs_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/UL-AMR-Rate.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* TransportFormatCombinationControl-v820ext-IEs */
typedef struct TransportFormatCombinationControl_v820ext_IEs {
	UL_AMR_Rate_t	*ul_AMR_Rate	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} TransportFormatCombinationControl_v820ext_IEs_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_TransportFormatCombinationControl_v820ext_IEs;

#ifdef __cplusplus
}
#endif

#endif	/* _TransportFormatCombinationControl_v820ext_IEs_H_ */

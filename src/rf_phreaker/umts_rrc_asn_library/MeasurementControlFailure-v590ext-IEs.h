/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "PDU-definitions"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_MeasurementControlFailure_v590ext_IEs_H_
#define	_MeasurementControlFailure_v590ext_IEs_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/RRC-TransactionIdentifier.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* MeasurementControlFailure-v590ext-IEs */
typedef struct MeasurementControlFailure_v590ext_IEs {
	RRC_TransactionIdentifier_t	 rrc_TransactionIdentifier_MSP_v590ext;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MeasurementControlFailure_v590ext_IEs_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MeasurementControlFailure_v590ext_IEs;

#ifdef __cplusplus
}
#endif

#endif	/* _MeasurementControlFailure_v590ext_IEs_H_ */

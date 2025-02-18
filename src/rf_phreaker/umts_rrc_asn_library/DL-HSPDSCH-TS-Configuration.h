/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_DL_HSPDSCH_TS_Configuration_H_
#define	_DL_HSPDSCH_TS_Configuration_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/asn_SEQUENCE_OF.h>
#include "rf_phreaker/umts_rrc_asn_library/TimeslotNumber.h"
#include "rf_phreaker/umts_rrc_asn_library/MidambleShiftAndBurstType-DL.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* DL-HSPDSCH-TS-Configuration */
typedef struct DL_HSPDSCH_TS_Configuration {
	A_SEQUENCE_OF(struct DL_HSPDSCH_TS_Configuration__Member {
		TimeslotNumber_t	 timeslot;
		MidambleShiftAndBurstType_DL_t	 midambleShiftAndBurstType;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} ) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} DL_HSPDSCH_TS_Configuration_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_DL_HSPDSCH_TS_Configuration;

#ifdef __cplusplus
}
#endif

#endif	/* _DL_HSPDSCH_TS_Configuration_H_ */

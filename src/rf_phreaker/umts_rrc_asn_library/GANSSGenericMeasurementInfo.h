/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_GANSSGenericMeasurementInfo_H_
#define	_GANSSGenericMeasurementInfo_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/asn_SEQUENCE_OF.h>
#include <rf_phreaker/umts_rrc_asn_library/NativeInteger.h>
#include "rf_phreaker/umts_rrc_asn_library/GANSSMeasurementSignalList.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* GANSSGenericMeasurementInfo */
typedef struct GANSSGenericMeasurementInfo {
	A_SEQUENCE_OF(struct GANSSGenericMeasurementInfo__Member {
		long	*ganssId	/* OPTIONAL */;
		GANSSMeasurementSignalList_t	 ganssMeasurementSignalList;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} ) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} GANSSGenericMeasurementInfo_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_GANSSGenericMeasurementInfo;

#ifdef __cplusplus
}
#endif

#endif	/* _GANSSGenericMeasurementInfo_H_ */

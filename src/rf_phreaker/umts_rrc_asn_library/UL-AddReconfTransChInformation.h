/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_UL_AddReconfTransChInformation_H_
#define	_UL_AddReconfTransChInformation_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/UL-TrCH-Type.h"
#include "rf_phreaker/umts_rrc_asn_library/TransportChannelIdentity.h"
#include "rf_phreaker/umts_rrc_asn_library/TransportFormatSet.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* UL-AddReconfTransChInformation */
typedef struct UL_AddReconfTransChInformation {
	UL_TrCH_Type_t	 ul_TransportChannelType;
	TransportChannelIdentity_t	 transportChannelIdentity;
	TransportFormatSet_t	 transportFormatSet;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} UL_AddReconfTransChInformation_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_UL_AddReconfTransChInformation;

#ifdef __cplusplus
}
#endif

#endif	/* _UL_AddReconfTransChInformation_H_ */

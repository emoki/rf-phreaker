/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_DL_TransportChannelIdentity_H_
#define	_DL_TransportChannelIdentity_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/DL-TrCH-Type.h"
#include "rf_phreaker/umts_rrc_asn_library/TransportChannelIdentity.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* DL-TransportChannelIdentity */
typedef struct DL_TransportChannelIdentity {
	DL_TrCH_Type_t	 dl_TransportChannelType;
	TransportChannelIdentity_t	 dl_TransportChannelIdentity;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} DL_TransportChannelIdentity_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_DL_TransportChannelIdentity;

#ifdef __cplusplus
}
#endif

#endif	/* _DL_TransportChannelIdentity_H_ */

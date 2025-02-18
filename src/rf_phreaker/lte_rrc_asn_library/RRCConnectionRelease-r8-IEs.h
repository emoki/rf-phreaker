/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_RRCConnectionRelease_r8_IEs_H_
#define	_RRCConnectionRelease_r8_IEs_H_


#include <rf_phreaker/lte_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/lte_rrc_asn_library/ReleaseCause.h"
#include <rf_phreaker/lte_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct RedirectedCarrierInfo;
struct IdleModeMobilityControlInfo;
struct RRCConnectionRelease_v890_IEs;

/* RRCConnectionRelease-r8-IEs */
typedef struct RRCConnectionRelease_r8_IEs {
	ReleaseCause_t	 releaseCause;
	struct RedirectedCarrierInfo	*redirectedCarrierInfo	/* OPTIONAL */;
	struct IdleModeMobilityControlInfo	*idleModeMobilityControlInfo	/* OPTIONAL */;
	struct RRCConnectionRelease_v890_IEs	*nonCriticalExtension	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RRCConnectionRelease_r8_IEs_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RRCConnectionRelease_r8_IEs;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/lte_rrc_asn_library/RedirectedCarrierInfo.h"
#include "rf_phreaker/lte_rrc_asn_library/IdleModeMobilityControlInfo.h"
#include "rf_phreaker/lte_rrc_asn_library/RRCConnectionRelease-v890-IEs.h"

#endif	/* _RRCConnectionRelease_r8_IEs_H_ */
#include <rf_phreaker/lte_rrc_asn_library/asn_internal.h>

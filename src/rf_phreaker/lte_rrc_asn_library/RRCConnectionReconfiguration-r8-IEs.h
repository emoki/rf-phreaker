/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_RRCConnectionReconfiguration_r8_IEs_H_
#define	_RRCConnectionReconfiguration_r8_IEs_H_


#include <rf_phreaker/lte_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/lte_rrc_asn_library/DedicatedInfoNAS.h"
#include <rf_phreaker/lte_rrc_asn_library/asn_SEQUENCE_OF.h>
#include <rf_phreaker/lte_rrc_asn_library/constr_SEQUENCE_OF.h>
#include <rf_phreaker/lte_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct MeasConfig;
struct MobilityControlInfo;
struct RadioResourceConfigDedicated;
struct SecurityConfigHO;
struct RRCConnectionReconfiguration_v890_IEs;

/* RRCConnectionReconfiguration-r8-IEs */
typedef struct RRCConnectionReconfiguration_r8_IEs {
	struct MeasConfig	*measConfig	/* OPTIONAL */;
	struct MobilityControlInfo	*mobilityControlInfo	/* OPTIONAL */;
	struct RRCConnectionReconfiguration_r8_IEs__dedicatedInfoNASList {
		A_SEQUENCE_OF(DedicatedInfoNAS_t) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *dedicatedInfoNASList;
	struct RadioResourceConfigDedicated	*radioResourceConfigDedicated	/* OPTIONAL */;
	struct SecurityConfigHO	*securityConfigHO	/* OPTIONAL */;
	struct RRCConnectionReconfiguration_v890_IEs	*nonCriticalExtension	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RRCConnectionReconfiguration_r8_IEs_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RRCConnectionReconfiguration_r8_IEs;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/lte_rrc_asn_library/MeasConfig.h"
#include "rf_phreaker/lte_rrc_asn_library/MobilityControlInfo.h"
#include "rf_phreaker/lte_rrc_asn_library/RadioResourceConfigDedicated.h"
#include "rf_phreaker/lte_rrc_asn_library/SecurityConfigHO.h"
#include "rf_phreaker/lte_rrc_asn_library/RRCConnectionReconfiguration-v890-IEs.h"

#endif	/* _RRCConnectionReconfiguration_r8_IEs_H_ */
#include <rf_phreaker/lte_rrc_asn_library/asn_internal.h>

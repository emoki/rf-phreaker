/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "PDU-definitions"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_PUSCHCapacityRequest_H_
#define	_PUSCHCapacityRequest_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/DSCH-RNTI.h"
#include "rf_phreaker/umts_rrc_asn_library/PrimaryCCPCH-RSCP.h"
#include "rf_phreaker/umts_rrc_asn_library/ProtocolErrorIndicatorWithMoreInfo.h"
#include "rf_phreaker/umts_rrc_asn_library/PDSCH-Identity.h"
#include "rf_phreaker/umts_rrc_asn_library/PUSCH-Identity.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_CHOICE.h>
#include <rf_phreaker/umts_rrc_asn_library/BIT_STRING.h>
#include "rf_phreaker/umts_rrc_asn_library/PUSCHCapacityRequest-v590ext.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum PUSCHCapacityRequest__allocationConfirmation_PR {
	PUSCHCapacityRequest__allocationConfirmation_PR_NOTHING,	/* No components present */
	PUSCHCapacityRequest__allocationConfirmation_PR_pdschConfirmation,
	PUSCHCapacityRequest__allocationConfirmation_PR_puschConfirmation
} PUSCHCapacityRequest__allocationConfirmation_PR;

/* Forward declarations */
struct TrafficVolumeMeasuredResultsList;
struct TimeslotListWithISCP;

/* PUSCHCapacityRequest */
typedef struct PUSCHCapacityRequest {
	DSCH_RNTI_t	*dsch_RNTI	/* OPTIONAL */;
	struct TrafficVolumeMeasuredResultsList	*trafficVolume	/* OPTIONAL */;
	struct TimeslotListWithISCP	*timeslotListWithISCP	/* OPTIONAL */;
	PrimaryCCPCH_RSCP_t	*primaryCCPCH_RSCP	/* OPTIONAL */;
	struct PUSCHCapacityRequest__allocationConfirmation {
		PUSCHCapacityRequest__allocationConfirmation_PR present;
		union PUSCHCapacityRequest__allocationConfirmation_u {
			PDSCH_Identity_t	 pdschConfirmation;
			PUSCH_Identity_t	 puschConfirmation;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *allocationConfirmation;
	ProtocolErrorIndicatorWithMoreInfo_t	 protocolErrorIndicator;
	struct PUSCHCapacityRequest__laterNonCriticalExtensions {
		BIT_STRING_t	*puschCapacityRequest_r3_add_ext	/* OPTIONAL */;
		struct PUSCHCapacityRequest__laterNonCriticalExtensions__v590NonCriticalExtensions {
			PUSCHCapacityRequest_v590ext_t	 puschCapacityRequest_v590ext;
			struct PUSCHCapacityRequest__laterNonCriticalExtensions__v590NonCriticalExtensions__nonCriticalExtensions {
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} *nonCriticalExtensions;
			
			/* Context for parsing across buffer boundaries */
			asn_struct_ctx_t _asn_ctx;
		} *v590NonCriticalExtensions;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *laterNonCriticalExtensions;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PUSCHCapacityRequest_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PUSCHCapacityRequest;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/TrafficVolumeMeasuredResultsList.h"
#include "rf_phreaker/umts_rrc_asn_library/TimeslotListWithISCP.h"

#endif	/* _PUSCHCapacityRequest_H_ */

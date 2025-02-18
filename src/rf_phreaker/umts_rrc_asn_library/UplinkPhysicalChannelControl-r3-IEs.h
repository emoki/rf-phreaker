/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "PDU-definitions"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_UplinkPhysicalChannelControl_r3_IEs_H_
#define	_UplinkPhysicalChannelControl_r3_IEs_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/RRC-TransactionIdentifier.h"
#include "rf_phreaker/umts_rrc_asn_library/Alpha.h"
#include "rf_phreaker/umts_rrc_asn_library/SpecialBurstScheduling.h"
#include "rf_phreaker/umts_rrc_asn_library/ConstantValueTdd.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct CCTrCH_PowerControlInfo;
struct UL_TimingAdvanceControl;

/* UplinkPhysicalChannelControl-r3-IEs */
typedef struct UplinkPhysicalChannelControl_r3_IEs {
	RRC_TransactionIdentifier_t	 rrc_TransactionIdentifier;
	struct CCTrCH_PowerControlInfo	*ccTrCH_PowerControlInfo	/* OPTIONAL */;
	struct UL_TimingAdvanceControl	*timingAdvance	/* OPTIONAL */;
	Alpha_t	*alpha	/* OPTIONAL */;
	SpecialBurstScheduling_t	*specialBurstScheduling	/* OPTIONAL */;
	ConstantValueTdd_t	*prach_ConstantValue	/* OPTIONAL */;
	ConstantValueTdd_t	*pusch_ConstantValue	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} UplinkPhysicalChannelControl_r3_IEs_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_UplinkPhysicalChannelControl_r3_IEs;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/CCTrCH-PowerControlInfo.h"
#include "rf_phreaker/umts_rrc_asn_library/UL-TimingAdvanceControl.h"

#endif	/* _UplinkPhysicalChannelControl_r3_IEs_H_ */

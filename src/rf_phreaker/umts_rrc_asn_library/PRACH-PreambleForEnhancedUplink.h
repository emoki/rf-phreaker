/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_PRACH_PreambleForEnhancedUplink_H_
#define	_PRACH_PreambleForEnhancedUplink_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/AvailableSignatures.h"
#include <rf_phreaker/umts_rrc_asn_library/BOOLEAN.h>
#include "rf_phreaker/umts_rrc_asn_library/PreambleScramblingCodeWordNumber.h"
#include "rf_phreaker/umts_rrc_asn_library/AvailableSubChannelNumbers.h"
#include "rf_phreaker/umts_rrc_asn_library/PrimaryCPICH-TX-Power.h"
#include "rf_phreaker/umts_rrc_asn_library/ConstantValue.h"
#include <rf_phreaker/umts_rrc_asn_library/NativeInteger.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct PRACH_Partitioning_r7;
struct PersistenceScalingFactorList;
struct AC_To_ASC_MappingTable;
struct PRACH_PowerOffset;
struct RACH_TransmissionParameters;
struct AICH_Info;

/* PRACH-PreambleForEnhancedUplink */
typedef struct PRACH_PreambleForEnhancedUplink {
	AvailableSignatures_t	*availableSignatures	/* OPTIONAL */;
	BOOLEAN_t	 e_ai_Indication;
	PreambleScramblingCodeWordNumber_t	*preambleScramblingCodeWordNumber	/* OPTIONAL */;
	AvailableSubChannelNumbers_t	*availableSubChannelNumbers	/* OPTIONAL */;
	struct PRACH_Partitioning_r7	*prach_Partitioning	/* OPTIONAL */;
	struct PersistenceScalingFactorList	*persistenceScalingFactorList	/* OPTIONAL */;
	struct AC_To_ASC_MappingTable	*ac_To_ASC_MappingTable	/* OPTIONAL */;
	PrimaryCPICH_TX_Power_t	*primaryCPICH_TX_Power	/* OPTIONAL */;
	ConstantValue_t	*constantValue	/* OPTIONAL */;
	struct PRACH_PowerOffset	*prach_PowerOffset	/* OPTIONAL */;
	struct RACH_TransmissionParameters	*rach_TransmissionParameters	/* OPTIONAL */;
	struct AICH_Info	*aich_Info	/* OPTIONAL */;
	long	 powerOffsetPp_e;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PRACH_PreambleForEnhancedUplink_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PRACH_PreambleForEnhancedUplink;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/PRACH-Partitioning-r7.h"
#include "rf_phreaker/umts_rrc_asn_library/PersistenceScalingFactorList.h"
#include "rf_phreaker/umts_rrc_asn_library/AC-To-ASC-MappingTable.h"
#include "rf_phreaker/umts_rrc_asn_library/PRACH-PowerOffset.h"
#include "rf_phreaker/umts_rrc_asn_library/RACH-TransmissionParameters.h"
#include "rf_phreaker/umts_rrc_asn_library/AICH-Info.h"

#endif	/* _PRACH_PreambleForEnhancedUplink_H_ */

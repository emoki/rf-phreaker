/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_UE_RadioAccessCapability_vaxyext_IEs_H_
#define	_UE_RadioAccessCapability_vaxyext_IEs_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/PhysicalChannelCapability-vaxyext.h"
#include <rf_phreaker/umts_rrc_asn_library/NativeEnumerated.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum UE_RadioAccessCapability_vaxyext_IEs__supportOfMUMIMO {
	UE_RadioAccessCapability_vaxyext_IEs__supportOfMUMIMO_uL	= 0,
	UE_RadioAccessCapability_vaxyext_IEs__supportOfMUMIMO_uLandDL	= 1
} e_UE_RadioAccessCapability_vaxyext_IEs__supportOfMUMIMO;
typedef enum UE_RadioAccessCapability_vaxyext_IEs__supportForDualCellMimoInDifferentBands {
	UE_RadioAccessCapability_vaxyext_IEs__supportForDualCellMimoInDifferentBands_true	= 0
} e_UE_RadioAccessCapability_vaxyext_IEs__supportForDualCellMimoInDifferentBands;

/* Forward declarations */
struct SupportedCarrierCombinationList;
struct RLC_Capability_vaxyext;
struct MeasurementCapability_vaxyext;
struct UE_RadioAccessCapabBandFDDList4;
struct UE_BasedNetworkPerformanceMeasurementsParameters;

/* UE-RadioAccessCapability-vaxyext-IEs */
typedef struct UE_RadioAccessCapability_vaxyext_IEs {
	struct SupportedCarrierCombinationList	*supportedCarrierCombinationList	/* OPTIONAL */;
	PhysicalChannelCapability_vaxyext_t	 physicalChannelCapability;
	struct RLC_Capability_vaxyext	*rlc_Capability	/* OPTIONAL */;
	struct MeasurementCapability_vaxyext	*measurementCapability	/* OPTIONAL */;
	long	*supportOfMUMIMO	/* OPTIONAL */;
	struct UE_RadioAccessCapabBandFDDList4	*ue_RadioAccessCapabBandFDDList4	/* OPTIONAL */;
	struct UE_BasedNetworkPerformanceMeasurementsParameters	*ue_BasedNetworkPerformanceMeasurementsParameters	/* OPTIONAL */;
	long	*supportForDualCellMimoInDifferentBands	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} UE_RadioAccessCapability_vaxyext_IEs_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_supportOfMUMIMO_6;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_supportForDualCellMimoInDifferentBands_11;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_UE_RadioAccessCapability_vaxyext_IEs;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/SupportedCarrierCombinationList.h"
#include "rf_phreaker/umts_rrc_asn_library/RLC-Capability-vaxyext.h"
#include "rf_phreaker/umts_rrc_asn_library/MeasurementCapability-vaxyext.h"
#include "rf_phreaker/umts_rrc_asn_library/UE-RadioAccessCapabBandFDDList4.h"
#include "rf_phreaker/umts_rrc_asn_library/UE-BasedNetworkPerformanceMeasurementsParameters.h"

#endif	/* _UE_RadioAccessCapability_vaxyext_IEs_H_ */

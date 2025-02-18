/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_UL_PhysChCapabilityTDD_768_H_
#define	_UL_PhysChCapabilityTDD_768_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/MaxTS-PerFrame.h"
#include "rf_phreaker/umts_rrc_asn_library/MaxPhysChPerTimeslot.h"
#include "rf_phreaker/umts_rrc_asn_library/MinimumSF-UL.h"
#include <rf_phreaker/umts_rrc_asn_library/BOOLEAN.h>
#include <rf_phreaker/umts_rrc_asn_library/NULL.h>
#include <rf_phreaker/umts_rrc_asn_library/NativeInteger.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum UL_PhysChCapabilityTDD_768__tdd384_edch_PR {
	UL_PhysChCapabilityTDD_768__tdd384_edch_PR_NOTHING,	/* No components present */
	UL_PhysChCapabilityTDD_768__tdd384_edch_PR_supported,
	UL_PhysChCapabilityTDD_768__tdd384_edch_PR_unsupported
} UL_PhysChCapabilityTDD_768__tdd384_edch_PR;

/* UL-PhysChCapabilityTDD-768 */
typedef struct UL_PhysChCapabilityTDD_768 {
	MaxTS_PerFrame_t	 maxTS_PerFrame;
	MaxPhysChPerTimeslot_t	 maxPhysChPerTimeslot;
	MinimumSF_UL_t	 minimumSF;
	BOOLEAN_t	 supportOfPUSCH;
	struct UL_PhysChCapabilityTDD_768__tdd384_edch {
		UL_PhysChCapabilityTDD_768__tdd384_edch_PR present;
		union UL_PhysChCapabilityTDD_768__tdd384_edch_u {
			struct UL_PhysChCapabilityTDD_768__tdd384_edch__supported {
				long	 tdd_edch_PhysicalLayerCategory;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} supported;
			NULL_t	 unsupported;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} tdd384_edch;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} UL_PhysChCapabilityTDD_768_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_UL_PhysChCapabilityTDD_768;

#ifdef __cplusplus
}
#endif

#endif	/* _UL_PhysChCapabilityTDD_768_H_ */

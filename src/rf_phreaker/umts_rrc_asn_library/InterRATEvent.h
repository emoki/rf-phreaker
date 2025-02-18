/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_InterRATEvent_H_
#define	_InterRATEvent_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/Event3a.h"
#include "rf_phreaker/umts_rrc_asn_library/Event3b.h"
#include "rf_phreaker/umts_rrc_asn_library/Event3c.h"
#include "rf_phreaker/umts_rrc_asn_library/Event3d.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum InterRATEvent_PR {
	InterRATEvent_PR_NOTHING,	/* No components present */
	InterRATEvent_PR_event3a,
	InterRATEvent_PR_event3b,
	InterRATEvent_PR_event3c,
	InterRATEvent_PR_event3d
} InterRATEvent_PR;

/* InterRATEvent */
typedef struct InterRATEvent {
	InterRATEvent_PR present;
	union InterRATEvent_u {
		Event3a_t	 event3a;
		Event3b_t	 event3b;
		Event3c_t	 event3c;
		Event3d_t	 event3d;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} InterRATEvent_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_InterRATEvent;

#ifdef __cplusplus
}
#endif

#endif	/* _InterRATEvent_H_ */

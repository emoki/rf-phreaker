/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_SplitTFCI_Signalling_H_
#define	_SplitTFCI_Signalling_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/SplitType.h"
#include <rf_phreaker/umts_rrc_asn_library/NativeInteger.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct ExplicitTFCS_Configuration;
struct TFCI_Field2_Information;

/* SplitTFCI-Signalling */
typedef struct SplitTFCI_Signalling {
	SplitType_t	*splitType	/* OPTIONAL */;
	long	*tfci_Field2_Length	/* OPTIONAL */;
	struct ExplicitTFCS_Configuration	*tfci_Field1_Information	/* OPTIONAL */;
	struct TFCI_Field2_Information	*tfci_Field2_Information	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SplitTFCI_Signalling_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SplitTFCI_Signalling;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/ExplicitTFCS-Configuration.h"
#include "rf_phreaker/umts_rrc_asn_library/TFCI-Field2-Information.h"

#endif	/* _SplitTFCI_Signalling_H_ */

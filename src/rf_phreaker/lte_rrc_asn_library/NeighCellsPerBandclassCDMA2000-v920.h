/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_NeighCellsPerBandclassCDMA2000_v920_H_
#define	_NeighCellsPerBandclassCDMA2000_v920_H_


#include <rf_phreaker/lte_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/lte_rrc_asn_library/PhysCellIdListCDMA2000-v920.h"
#include <rf_phreaker/lte_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* NeighCellsPerBandclassCDMA2000-v920 */
typedef struct NeighCellsPerBandclassCDMA2000_v920 {
	PhysCellIdListCDMA2000_v920_t	 physCellIdList_v920;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} NeighCellsPerBandclassCDMA2000_v920_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_NeighCellsPerBandclassCDMA2000_v920;

#ifdef __cplusplus
}
#endif

#endif	/* _NeighCellsPerBandclassCDMA2000_v920_H_ */
#include <rf_phreaker/lte_rrc_asn_library/asn_internal.h>

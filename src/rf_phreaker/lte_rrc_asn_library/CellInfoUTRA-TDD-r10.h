/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_CellInfoUTRA_TDD_r10_H_
#define	_CellInfoUTRA_TDD_r10_H_


#include <rf_phreaker/lte_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/lte_rrc_asn_library/PhysCellIdUTRA-TDD.h"
#include "rf_phreaker/lte_rrc_asn_library/ARFCN-ValueUTRA.h"
#include <rf_phreaker/lte_rrc_asn_library/OCTET_STRING.h>
#include <rf_phreaker/lte_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* CellInfoUTRA-TDD-r10 */
typedef struct CellInfoUTRA_TDD_r10 {
	PhysCellIdUTRA_TDD_t	 physCellId_r10;
	ARFCN_ValueUTRA_t	 carrierFreq_r10;
	OCTET_STRING_t	 utra_BCCH_Container_r10;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} CellInfoUTRA_TDD_r10_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_CellInfoUTRA_TDD_r10;

#ifdef __cplusplus
}
#endif

#endif	/* _CellInfoUTRA_TDD_r10_H_ */
#include <rf_phreaker/lte_rrc_asn_library/asn_internal.h>

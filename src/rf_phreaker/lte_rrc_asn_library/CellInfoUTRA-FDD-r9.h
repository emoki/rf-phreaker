/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#ifndef	_CellInfoUTRA_FDD_r9_H_
#define	_CellInfoUTRA_FDD_r9_H_


#include <rf_phreaker/lte_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/lte_rrc_asn_library/PhysCellIdUTRA-FDD.h"
#include <rf_phreaker/lte_rrc_asn_library/OCTET_STRING.h>
#include <rf_phreaker/lte_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* CellInfoUTRA-FDD-r9 */
typedef struct CellInfoUTRA_FDD_r9 {
	PhysCellIdUTRA_FDD_t	 physCellId_r9;
	OCTET_STRING_t	 utra_BCCH_Container_r9;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} CellInfoUTRA_FDD_r9_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_CellInfoUTRA_FDD_r9;

#ifdef __cplusplus
}
#endif

#endif	/* _CellInfoUTRA_FDD_r9_H_ */
#include <rf_phreaker/lte_rrc_asn_library/asn_internal.h>

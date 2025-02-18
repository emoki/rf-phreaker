/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#include "rf_phreaker/lte_rrc_asn_library/CarrierFreqInfoUTRA-FDD-v8h0.h"

static int
memb_multiBandInfoList_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	size_t size;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	/* Determine the number of elements */
	size = _A_CSEQUENCE_FROM_VOID(sptr)->count;
	
	if((size >= 1 && size <= 8)) {
		/* Perform validation of the inner elements */
		return td->check_constraints(td, sptr, ctfailcb, app_key);
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_per_constraints_t asn_PER_type_multiBandInfoList_constr_2 GCC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 3,  3,  1,  8 }	/* (SIZE(1..8)) */,
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_multiBandInfoList_constr_2 GCC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 3,  3,  1,  8 }	/* (SIZE(1..8)) */,
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_multiBandInfoList_2[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_FreqBandIndicator_UTRA_FDD,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		""
		},
};
static ber_tlv_tag_t asn_DEF_multiBandInfoList_tags_2[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_multiBandInfoList_specs_2 = {
	sizeof(struct CarrierFreqInfoUTRA_FDD_v8h0__multiBandInfoList),
	offsetof(struct CarrierFreqInfoUTRA_FDD_v8h0__multiBandInfoList, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_multiBandInfoList_2 = {
	"multiBandInfoList",
	"multiBandInfoList",
	SEQUENCE_OF_free,
	SEQUENCE_OF_print,
	SEQUENCE_OF_constraint,
	SEQUENCE_OF_decode_ber,
	SEQUENCE_OF_encode_der,
	SEQUENCE_OF_decode_xer,
	SEQUENCE_OF_encode_xer,
	SEQUENCE_OF_decode_uper,
	SEQUENCE_OF_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_multiBandInfoList_tags_2,
	sizeof(asn_DEF_multiBandInfoList_tags_2)
		/sizeof(asn_DEF_multiBandInfoList_tags_2[0]) - 1, /* 1 */
	asn_DEF_multiBandInfoList_tags_2,	/* Same as above */
	sizeof(asn_DEF_multiBandInfoList_tags_2)
		/sizeof(asn_DEF_multiBandInfoList_tags_2[0]), /* 2 */
	&asn_PER_type_multiBandInfoList_constr_2,
	asn_MBR_multiBandInfoList_2,
	1,	/* Single element */
	&asn_SPC_multiBandInfoList_specs_2	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_CarrierFreqInfoUTRA_FDD_v8h0_1[] = {
	{ ATF_POINTER, 1, offsetof(struct CarrierFreqInfoUTRA_FDD_v8h0, multiBandInfoList),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_multiBandInfoList_2,
		memb_multiBandInfoList_constraint_1,
		&asn_PER_memb_multiBandInfoList_constr_2,
		0,
		"multiBandInfoList"
		},
};
static int asn_MAP_CarrierFreqInfoUTRA_FDD_v8h0_oms_1[] = { 0 };
static ber_tlv_tag_t asn_DEF_CarrierFreqInfoUTRA_FDD_v8h0_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_CarrierFreqInfoUTRA_FDD_v8h0_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* multiBandInfoList */
};
static asn_SEQUENCE_specifics_t asn_SPC_CarrierFreqInfoUTRA_FDD_v8h0_specs_1 = {
	sizeof(struct CarrierFreqInfoUTRA_FDD_v8h0),
	offsetof(struct CarrierFreqInfoUTRA_FDD_v8h0, _asn_ctx),
	asn_MAP_CarrierFreqInfoUTRA_FDD_v8h0_tag2el_1,
	1,	/* Count of tags in the map */
	asn_MAP_CarrierFreqInfoUTRA_FDD_v8h0_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_CarrierFreqInfoUTRA_FDD_v8h0 = {
	"CarrierFreqInfoUTRA-FDD-v8h0",
	"CarrierFreqInfoUTRA-FDD-v8h0",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	SEQUENCE_decode_uper,
	SEQUENCE_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_CarrierFreqInfoUTRA_FDD_v8h0_tags_1,
	sizeof(asn_DEF_CarrierFreqInfoUTRA_FDD_v8h0_tags_1)
		/sizeof(asn_DEF_CarrierFreqInfoUTRA_FDD_v8h0_tags_1[0]), /* 1 */
	asn_DEF_CarrierFreqInfoUTRA_FDD_v8h0_tags_1,	/* Same as above */
	sizeof(asn_DEF_CarrierFreqInfoUTRA_FDD_v8h0_tags_1)
		/sizeof(asn_DEF_CarrierFreqInfoUTRA_FDD_v8h0_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_CarrierFreqInfoUTRA_FDD_v8h0_1,
	1,	/* Elements count */
	&asn_SPC_CarrierFreqInfoUTRA_FDD_v8h0_specs_1	/* Additional specs */
};


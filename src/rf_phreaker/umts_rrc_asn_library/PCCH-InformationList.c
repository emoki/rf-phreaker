/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/PCCH-InformationList.h"

static int
memb_timeslotResourceRelatedInfo_constraint_3(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const BIT_STRING_t *st = (const BIT_STRING_t *)sptr;
	size_t size;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	if(st->size > 0) {
		/* Size in bits */
		size = 8 * st->size - (st->bits_unused & 0x07);
	} else {
		size = 0;
	}
	
	if((size == 6)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int
memb_paging_associatedHspdschInfo_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
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
	
	if((size >= 1 && size <= 16)) {
		/* Perform validation of the inner elements */
		return td->check_constraints(td, sptr, ctfailcb, app_key);
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int
memb_paging_sub_Channel_size_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 1 && value <= 3)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int
memb_transportBlockSizeList_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
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
	
	if((size >= 1 && size <= 2)) {
		/* Perform validation of the inner elements */
		return td->check_constraints(td, sptr, ctfailcb, app_key);
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_per_constraints_t asn_PER_memb_timeslotResourceRelatedInfo_constr_5 = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 0,  0,  6,  6 }	/* (SIZE(6..6)) */,
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_paging_associatedHspdschInfo_constr_2 = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 4,  4,  1,  16 }	/* (SIZE(1..16)) */,
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_transportBlockSizeList_constr_8 = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 1,  1,  1,  2 }	/* (SIZE(1..2)) */,
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_paging_associatedHspdschInfo_constr_2 = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 4,  4,  1,  16 }	/* (SIZE(1..16)) */,
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_paging_sub_Channel_size_constr_7 = {
	{ APC_CONSTRAINED,	 2,  2,  1,  3 }	/* (1..3) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_transportBlockSizeList_constr_8 = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 1,  1,  1,  2 }	/* (SIZE(1..2)) */,
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_Member_3[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct PCCH_InformationList__paging_associatedHspdschInfo__Member, hs_pdsch_MidambleConfiguration),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_HS_PDSCH_Midamble_Configuration_TDD128,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"hs-pdsch-MidambleConfiguration"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct PCCH_InformationList__paging_associatedHspdschInfo__Member, timeslotResourceRelatedInfo),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BIT_STRING,
		memb_timeslotResourceRelatedInfo_constraint_3,
		&asn_PER_memb_timeslotResourceRelatedInfo_constr_5,
		0,
		"timeslotResourceRelatedInfo"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct PCCH_InformationList__paging_associatedHspdschInfo__Member, codeResourceInformation),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CodeResourceInformation_TDD128,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"codeResourceInformation"
		},
};
static ber_tlv_tag_t asn_DEF_Member_tags_3[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_Member_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* hs-pdsch-MidambleConfiguration at 19408 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* timeslotResourceRelatedInfo at 19409 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* codeResourceInformation at 19411 */
};
static asn_SEQUENCE_specifics_t asn_SPC_Member_specs_3 = {
	sizeof(struct PCCH_InformationList__paging_associatedHspdschInfo__Member),
	offsetof(struct PCCH_InformationList__paging_associatedHspdschInfo__Member, _asn_ctx),
	asn_MAP_Member_tag2el_3,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_Member_3 = {
	"SEQUENCE",
	"SEQUENCE",
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
	asn_DEF_Member_tags_3,
	sizeof(asn_DEF_Member_tags_3)
		/sizeof(asn_DEF_Member_tags_3[0]), /* 1 */
	asn_DEF_Member_tags_3,	/* Same as above */
	sizeof(asn_DEF_Member_tags_3)
		/sizeof(asn_DEF_Member_tags_3[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_Member_3,
	3,	/* Elements count */
	&asn_SPC_Member_specs_3	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_paging_associatedHspdschInfo_2[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_Member_3,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		""
		},
};
static ber_tlv_tag_t asn_DEF_paging_associatedHspdschInfo_tags_2[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_paging_associatedHspdschInfo_specs_2 = {
	sizeof(struct PCCH_InformationList__paging_associatedHspdschInfo),
	offsetof(struct PCCH_InformationList__paging_associatedHspdschInfo, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_paging_associatedHspdschInfo_2 = {
	"paging-associatedHspdschInfo",
	"paging-associatedHspdschInfo",
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
	asn_DEF_paging_associatedHspdschInfo_tags_2,
	sizeof(asn_DEF_paging_associatedHspdschInfo_tags_2)
		/sizeof(asn_DEF_paging_associatedHspdschInfo_tags_2[0]) - 1, /* 1 */
	asn_DEF_paging_associatedHspdschInfo_tags_2,	/* Same as above */
	sizeof(asn_DEF_paging_associatedHspdschInfo_tags_2)
		/sizeof(asn_DEF_paging_associatedHspdschInfo_tags_2[0]), /* 2 */
	&asn_PER_type_paging_associatedHspdschInfo_constr_2,
	asn_MBR_paging_associatedHspdschInfo_2,
	1,	/* Single element */
	&asn_SPC_paging_associatedHspdschInfo_specs_2	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_transportBlockSizeList_8[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_TransportBlockSizeIndex,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		""
		},
};
static ber_tlv_tag_t asn_DEF_transportBlockSizeList_tags_8[] = {
	(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_transportBlockSizeList_specs_8 = {
	sizeof(struct PCCH_InformationList__transportBlockSizeList),
	offsetof(struct PCCH_InformationList__transportBlockSizeList, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_transportBlockSizeList_8 = {
	"transportBlockSizeList",
	"transportBlockSizeList",
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
	asn_DEF_transportBlockSizeList_tags_8,
	sizeof(asn_DEF_transportBlockSizeList_tags_8)
		/sizeof(asn_DEF_transportBlockSizeList_tags_8[0]) - 1, /* 1 */
	asn_DEF_transportBlockSizeList_tags_8,	/* Same as above */
	sizeof(asn_DEF_transportBlockSizeList_tags_8)
		/sizeof(asn_DEF_transportBlockSizeList_tags_8[0]), /* 2 */
	&asn_PER_type_transportBlockSizeList_constr_8,
	asn_MBR_transportBlockSizeList_8,
	1,	/* Single element */
	&asn_SPC_transportBlockSizeList_specs_8	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_PCCH_InformationList_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct PCCH_InformationList, paging_associatedHspdschInfo),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_paging_associatedHspdschInfo_2,
		memb_paging_associatedHspdschInfo_constraint_1,
		&asn_PER_memb_paging_associatedHspdschInfo_constr_2,
		0,
		"paging-associatedHspdschInfo"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct PCCH_InformationList, paging_sub_Channel_size),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		memb_paging_sub_Channel_size_constraint_1,
		&asn_PER_memb_paging_sub_Channel_size_constr_7,
		0,
		"paging-sub-Channel-size"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct PCCH_InformationList, transportBlockSizeList),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		0,
		&asn_DEF_transportBlockSizeList_8,
		memb_transportBlockSizeList_constraint_1,
		&asn_PER_memb_transportBlockSizeList_constr_8,
		0,
		"transportBlockSizeList"
		},
};
static ber_tlv_tag_t asn_DEF_PCCH_InformationList_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_PCCH_InformationList_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* paging-associatedHspdschInfo at 19411 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* paging-sub-Channel-size at 19412 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* transportBlockSizeList at 19414 */
};
static asn_SEQUENCE_specifics_t asn_SPC_PCCH_InformationList_specs_1 = {
	sizeof(struct PCCH_InformationList),
	offsetof(struct PCCH_InformationList, _asn_ctx),
	asn_MAP_PCCH_InformationList_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_PCCH_InformationList = {
	"PCCH-InformationList",
	"PCCH-InformationList",
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
	asn_DEF_PCCH_InformationList_tags_1,
	sizeof(asn_DEF_PCCH_InformationList_tags_1)
		/sizeof(asn_DEF_PCCH_InformationList_tags_1[0]), /* 1 */
	asn_DEF_PCCH_InformationList_tags_1,	/* Same as above */
	sizeof(asn_DEF_PCCH_InformationList_tags_1)
		/sizeof(asn_DEF_PCCH_InformationList_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_PCCH_InformationList_1,
	3,	/* Elements count */
	&asn_SPC_PCCH_InformationList_specs_1	/* Additional specs */
};


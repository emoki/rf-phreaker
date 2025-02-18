/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#include "rf_phreaker/lte_rrc_asn_library/IDC-SubframePattern-r11.h"

static int
memb_subframeConfig0_r11_constraint_3(asn_TYPE_descriptor_t *td, const void *sptr,
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
	
	if((size == 70)) {
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
memb_subframeConfig1_5_r11_constraint_3(asn_TYPE_descriptor_t *td, const void *sptr,
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
	
	if((size == 10)) {
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
memb_subframeConfig6_r11_constraint_3(asn_TYPE_descriptor_t *td, const void *sptr,
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
	
	if((size == 60)) {
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
memb_subframePatternFDD_r11_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
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
	
	if((size == 4)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_per_constraints_t asn_PER_memb_subframeConfig0_r11_constr_4 GCC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 0,  0,  70,  70 }	/* (SIZE(70..70)) */,
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_subframeConfig1_5_r11_constr_5 GCC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 0,  0,  10,  10 }	/* (SIZE(10..10)) */,
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_subframeConfig6_r11_constr_6 GCC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 0,  0,  60,  60 }	/* (SIZE(60..60)) */,
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_subframePatternTDD_r11_constr_3 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 2,  2,  0,  2 }	/* (0..2) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_subframePatternFDD_r11_constr_2 GCC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 0,  0,  4,  4 }	/* (SIZE(4..4)) */,
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_IDC_SubframePattern_r11_constr_1 GCC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  1,  1,  0,  1 }	/* (0..1,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_subframePatternTDD_r11_3[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct IDC_SubframePattern_r11__subframePatternTDD_r11, choice.subframeConfig0_r11),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BIT_STRING,
		memb_subframeConfig0_r11_constraint_3,
		&asn_PER_memb_subframeConfig0_r11_constr_4,
		0,
		"subframeConfig0-r11"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct IDC_SubframePattern_r11__subframePatternTDD_r11, choice.subframeConfig1_5_r11),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BIT_STRING,
		memb_subframeConfig1_5_r11_constraint_3,
		&asn_PER_memb_subframeConfig1_5_r11_constr_5,
		0,
		"subframeConfig1-5-r11"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct IDC_SubframePattern_r11__subframePatternTDD_r11, choice.subframeConfig6_r11),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BIT_STRING,
		memb_subframeConfig6_r11_constraint_3,
		&asn_PER_memb_subframeConfig6_r11_constr_6,
		0,
		"subframeConfig6-r11"
		},
};
static asn_TYPE_tag2member_t asn_MAP_subframePatternTDD_r11_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* subframeConfig0-r11 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* subframeConfig1-5-r11 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* subframeConfig6-r11 */
};
static asn_CHOICE_specifics_t asn_SPC_subframePatternTDD_r11_specs_3 = {
	sizeof(struct IDC_SubframePattern_r11__subframePatternTDD_r11),
	offsetof(struct IDC_SubframePattern_r11__subframePatternTDD_r11, _asn_ctx),
	offsetof(struct IDC_SubframePattern_r11__subframePatternTDD_r11, present),
	sizeof(((struct IDC_SubframePattern_r11__subframePatternTDD_r11 *)0)->present),
	asn_MAP_subframePatternTDD_r11_tag2el_3,
	3,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_subframePatternTDD_r11_3 = {
	"subframePatternTDD-r11",
	"subframePatternTDD-r11",
	CHOICE_free,
	CHOICE_print,
	CHOICE_constraint,
	CHOICE_decode_ber,
	CHOICE_encode_der,
	CHOICE_decode_xer,
	CHOICE_encode_xer,
	CHOICE_decode_uper,
	CHOICE_encode_uper,
	CHOICE_outmost_tag,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	&asn_PER_type_subframePatternTDD_r11_constr_3,
	asn_MBR_subframePatternTDD_r11_3,
	3,	/* Elements count */
	&asn_SPC_subframePatternTDD_r11_specs_3	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_IDC_SubframePattern_r11_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct IDC_SubframePattern_r11, choice.subframePatternFDD_r11),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BIT_STRING,
		memb_subframePatternFDD_r11_constraint_1,
		&asn_PER_memb_subframePatternFDD_r11_constr_2,
		0,
		"subframePatternFDD-r11"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct IDC_SubframePattern_r11, choice.subframePatternTDD_r11),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_subframePatternTDD_r11_3,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"subframePatternTDD-r11"
		},
};
static asn_TYPE_tag2member_t asn_MAP_IDC_SubframePattern_r11_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* subframePatternFDD-r11 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* subframePatternTDD-r11 */
};
static asn_CHOICE_specifics_t asn_SPC_IDC_SubframePattern_r11_specs_1 = {
	sizeof(struct IDC_SubframePattern_r11),
	offsetof(struct IDC_SubframePattern_r11, _asn_ctx),
	offsetof(struct IDC_SubframePattern_r11, present),
	sizeof(((struct IDC_SubframePattern_r11 *)0)->present),
	asn_MAP_IDC_SubframePattern_r11_tag2el_1,
	2,	/* Count of tags in the map */
	0,
	2	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_IDC_SubframePattern_r11 = {
	"IDC-SubframePattern-r11",
	"IDC-SubframePattern-r11",
	CHOICE_free,
	CHOICE_print,
	CHOICE_constraint,
	CHOICE_decode_ber,
	CHOICE_encode_der,
	CHOICE_decode_xer,
	CHOICE_encode_xer,
	CHOICE_decode_uper,
	CHOICE_encode_uper,
	CHOICE_outmost_tag,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	&asn_PER_type_IDC_SubframePattern_r11_constr_1,
	asn_MBR_IDC_SubframePattern_r11_1,
	2,	/* Elements count */
	&asn_SPC_IDC_SubframePattern_r11_specs_1	/* Additional specs */
};


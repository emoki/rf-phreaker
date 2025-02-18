/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/ReferenceTimeDifferenceToCell.h"

static int
memb_accuracy40_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 960)) {
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
memb_accuracy256_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 150)) {
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
memb_accuracy2560_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 15)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_per_constraints_t asn_PER_memb_accuracy40_constr_2 = {
	{ APC_CONSTRAINED,	 10,  10,  0,  960 }	/* (0..960) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_accuracy256_constr_3 = {
	{ APC_CONSTRAINED,	 8,  8,  0,  150 }	/* (0..150) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_accuracy2560_constr_4 = {
	{ APC_CONSTRAINED,	 4,  4,  0,  15 }	/* (0..15) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_ReferenceTimeDifferenceToCell_constr_1 = {
	{ APC_CONSTRAINED,	 2,  2,  0,  2 }	/* (0..2) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_ReferenceTimeDifferenceToCell_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ReferenceTimeDifferenceToCell, choice.accuracy40),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		memb_accuracy40_constraint_1,
		&asn_PER_memb_accuracy40_constr_2,
		0,
		"accuracy40"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ReferenceTimeDifferenceToCell, choice.accuracy256),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		memb_accuracy256_constraint_1,
		&asn_PER_memb_accuracy256_constr_3,
		0,
		"accuracy256"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ReferenceTimeDifferenceToCell, choice.accuracy2560),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		memb_accuracy2560_constraint_1,
		&asn_PER_memb_accuracy2560_constr_4,
		0,
		"accuracy2560"
		},
};
static asn_TYPE_tag2member_t asn_MAP_ReferenceTimeDifferenceToCell_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* accuracy40 at 26629 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* accuracy256 at 26631 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* accuracy2560 at 26633 */
};
static asn_CHOICE_specifics_t asn_SPC_ReferenceTimeDifferenceToCell_specs_1 = {
	sizeof(struct ReferenceTimeDifferenceToCell),
	offsetof(struct ReferenceTimeDifferenceToCell, _asn_ctx),
	offsetof(struct ReferenceTimeDifferenceToCell, present),
	sizeof(((struct ReferenceTimeDifferenceToCell *)0)->present),
	asn_MAP_ReferenceTimeDifferenceToCell_tag2el_1,
	3,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_ReferenceTimeDifferenceToCell = {
	"ReferenceTimeDifferenceToCell",
	"ReferenceTimeDifferenceToCell",
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
	&asn_PER_type_ReferenceTimeDifferenceToCell_constr_1,
	asn_MBR_ReferenceTimeDifferenceToCell_1,
	3,	/* Elements count */
	&asn_SPC_ReferenceTimeDifferenceToCell_specs_1	/* Additional specs */
};


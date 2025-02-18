/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/GANSSSatelliteInformation.h"

static int
memb_ganssSatId_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 63)) {
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
memb_dopplerZeroOrder_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= -2048 && value <= 2047)) {
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
memb_codePhase_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 1023)) {
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
memb_integerCodePhase_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 127)) {
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
memb_codePhaseSearchWindow_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
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
	
	if((size == 5)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_per_constraints_t asn_PER_memb_ganssSatId_constr_2 = {
	{ APC_CONSTRAINED,	 6,  6,  0,  63 }	/* (0..63) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_dopplerZeroOrder_constr_3 = {
	{ APC_CONSTRAINED,	 12,  12, -2048,  2047 }	/* (-2048..2047) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_codePhase_constr_5 = {
	{ APC_CONSTRAINED,	 10,  10,  0,  1023 }	/* (0..1023) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_integerCodePhase_constr_6 = {
	{ APC_CONSTRAINED,	 7,  7,  0,  127 }	/* (0..127) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_codePhaseSearchWindow_constr_7 = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 0,  0,  5,  5 }	/* (SIZE(5..5)) */,
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_GANSSSatelliteInformation_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct GANSSSatelliteInformation, ganssSatId),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		memb_ganssSatId_constraint_1,
		&asn_PER_memb_ganssSatId_constr_2,
		0,
		"ganssSatId"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct GANSSSatelliteInformation, dopplerZeroOrder),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		memb_dopplerZeroOrder_constraint_1,
		&asn_PER_memb_dopplerZeroOrder_constr_3,
		0,
		"dopplerZeroOrder"
		},
	{ ATF_POINTER, 1, offsetof(struct GANSSSatelliteInformation, extraDoppler),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ExtraDoppler,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"extraDoppler"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct GANSSSatelliteInformation, codePhase),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		memb_codePhase_constraint_1,
		&asn_PER_memb_codePhase_constr_5,
		0,
		"codePhase"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct GANSSSatelliteInformation, integerCodePhase),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		memb_integerCodePhase_constraint_1,
		&asn_PER_memb_integerCodePhase_constr_6,
		0,
		"integerCodePhase"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct GANSSSatelliteInformation, codePhaseSearchWindow),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BIT_STRING,
		memb_codePhaseSearchWindow_constraint_1,
		&asn_PER_memb_codePhaseSearchWindow_constr_7,
		0,
		"codePhaseSearchWindow"
		},
	{ ATF_POINTER, 1, offsetof(struct GANSSSatelliteInformation, azimuthandElevation),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_AzimuthAndElevation,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"azimuthandElevation"
		},
};
static int asn_MAP_GANSSSatelliteInformation_oms_1[] = { 2, 6 };
static ber_tlv_tag_t asn_DEF_GANSSSatelliteInformation_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_GANSSSatelliteInformation_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* ganssSatId at 23772 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* dopplerZeroOrder at 23773 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* extraDoppler at 23774 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* codePhase at 23775 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* integerCodePhase at 23776 */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* codePhaseSearchWindow at 23777 */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 } /* azimuthandElevation at 23778 */
};
static asn_SEQUENCE_specifics_t asn_SPC_GANSSSatelliteInformation_specs_1 = {
	sizeof(struct GANSSSatelliteInformation),
	offsetof(struct GANSSSatelliteInformation, _asn_ctx),
	asn_MAP_GANSSSatelliteInformation_tag2el_1,
	7,	/* Count of tags in the map */
	asn_MAP_GANSSSatelliteInformation_oms_1,	/* Optional members */
	2, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_GANSSSatelliteInformation = {
	"GANSSSatelliteInformation",
	"GANSSSatelliteInformation",
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
	asn_DEF_GANSSSatelliteInformation_tags_1,
	sizeof(asn_DEF_GANSSSatelliteInformation_tags_1)
		/sizeof(asn_DEF_GANSSSatelliteInformation_tags_1[0]), /* 1 */
	asn_DEF_GANSSSatelliteInformation_tags_1,	/* Same as above */
	sizeof(asn_DEF_GANSSSatelliteInformation_tags_1)
		/sizeof(asn_DEF_GANSSSatelliteInformation_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_GANSSSatelliteInformation_1,
	7,	/* Elements count */
	&asn_SPC_GANSSSatelliteInformation_specs_1	/* Additional specs */
};


/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#include "rf_phreaker/lte_rrc_asn_library/SecurityConfigHO.h"

static int
memb_nas_SecurityParamToEUTRA_constraint_7(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const OCTET_STRING_t *st = (const OCTET_STRING_t *)sptr;
	size_t size;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	size = st->size;
	
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

static asn_per_constraints_t asn_PER_memb_nas_SecurityParamToEUTRA_constr_9 GCC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 0,  0,  6,  6 }	/* (SIZE(6..6)) */,
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_handoverType_constr_2 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_intraLTE_3[] = {
	{ ATF_POINTER, 1, offsetof(struct SecurityConfigHO__handoverType__intraLTE, securityAlgorithmConfig),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SecurityAlgorithmConfig,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"securityAlgorithmConfig"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SecurityConfigHO__handoverType__intraLTE, keyChangeIndicator),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"keyChangeIndicator"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SecurityConfigHO__handoverType__intraLTE, nextHopChainingCount),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NextHopChainingCount,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"nextHopChainingCount"
		},
};
static int asn_MAP_intraLTE_oms_3[] = { 0 };
static ber_tlv_tag_t asn_DEF_intraLTE_tags_3[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_intraLTE_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* securityAlgorithmConfig */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* keyChangeIndicator */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* nextHopChainingCount */
};
static asn_SEQUENCE_specifics_t asn_SPC_intraLTE_specs_3 = {
	sizeof(struct SecurityConfigHO__handoverType__intraLTE),
	offsetof(struct SecurityConfigHO__handoverType__intraLTE, _asn_ctx),
	asn_MAP_intraLTE_tag2el_3,
	3,	/* Count of tags in the map */
	asn_MAP_intraLTE_oms_3,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_intraLTE_3 = {
	"intraLTE",
	"intraLTE",
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
	asn_DEF_intraLTE_tags_3,
	sizeof(asn_DEF_intraLTE_tags_3)
		/sizeof(asn_DEF_intraLTE_tags_3[0]) - 1, /* 1 */
	asn_DEF_intraLTE_tags_3,	/* Same as above */
	sizeof(asn_DEF_intraLTE_tags_3)
		/sizeof(asn_DEF_intraLTE_tags_3[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_intraLTE_3,
	3,	/* Elements count */
	&asn_SPC_intraLTE_specs_3	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_interRAT_7[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SecurityConfigHO__handoverType__interRAT, securityAlgorithmConfig),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SecurityAlgorithmConfig,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"securityAlgorithmConfig"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SecurityConfigHO__handoverType__interRAT, nas_SecurityParamToEUTRA),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OCTET_STRING,
		memb_nas_SecurityParamToEUTRA_constraint_7,
		&asn_PER_memb_nas_SecurityParamToEUTRA_constr_9,
		0,
		"nas-SecurityParamToEUTRA"
		},
};
static ber_tlv_tag_t asn_DEF_interRAT_tags_7[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_interRAT_tag2el_7[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* securityAlgorithmConfig */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* nas-SecurityParamToEUTRA */
};
static asn_SEQUENCE_specifics_t asn_SPC_interRAT_specs_7 = {
	sizeof(struct SecurityConfigHO__handoverType__interRAT),
	offsetof(struct SecurityConfigHO__handoverType__interRAT, _asn_ctx),
	asn_MAP_interRAT_tag2el_7,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_interRAT_7 = {
	"interRAT",
	"interRAT",
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
	asn_DEF_interRAT_tags_7,
	sizeof(asn_DEF_interRAT_tags_7)
		/sizeof(asn_DEF_interRAT_tags_7[0]) - 1, /* 1 */
	asn_DEF_interRAT_tags_7,	/* Same as above */
	sizeof(asn_DEF_interRAT_tags_7)
		/sizeof(asn_DEF_interRAT_tags_7[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_interRAT_7,
	2,	/* Elements count */
	&asn_SPC_interRAT_specs_7	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_handoverType_2[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SecurityConfigHO__handoverType, choice.intraLTE),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_intraLTE_3,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"intraLTE"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SecurityConfigHO__handoverType, choice.interRAT),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_interRAT_7,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"interRAT"
		},
};
static asn_TYPE_tag2member_t asn_MAP_handoverType_tag2el_2[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* intraLTE */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* interRAT */
};
static asn_CHOICE_specifics_t asn_SPC_handoverType_specs_2 = {
	sizeof(struct SecurityConfigHO__handoverType),
	offsetof(struct SecurityConfigHO__handoverType, _asn_ctx),
	offsetof(struct SecurityConfigHO__handoverType, present),
	sizeof(((struct SecurityConfigHO__handoverType *)0)->present),
	asn_MAP_handoverType_tag2el_2,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_handoverType_2 = {
	"handoverType",
	"handoverType",
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
	&asn_PER_type_handoverType_constr_2,
	asn_MBR_handoverType_2,
	2,	/* Elements count */
	&asn_SPC_handoverType_specs_2	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_SecurityConfigHO_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SecurityConfigHO, handoverType),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_handoverType_2,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"handoverType"
		},
};
static ber_tlv_tag_t asn_DEF_SecurityConfigHO_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_SecurityConfigHO_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* handoverType */
};
static asn_SEQUENCE_specifics_t asn_SPC_SecurityConfigHO_specs_1 = {
	sizeof(struct SecurityConfigHO),
	offsetof(struct SecurityConfigHO, _asn_ctx),
	asn_MAP_SecurityConfigHO_tag2el_1,
	1,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	0,	/* Start extensions */
	2	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_SecurityConfigHO = {
	"SecurityConfigHO",
	"SecurityConfigHO",
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
	asn_DEF_SecurityConfigHO_tags_1,
	sizeof(asn_DEF_SecurityConfigHO_tags_1)
		/sizeof(asn_DEF_SecurityConfigHO_tags_1[0]), /* 1 */
	asn_DEF_SecurityConfigHO_tags_1,	/* Same as above */
	sizeof(asn_DEF_SecurityConfigHO_tags_1)
		/sizeof(asn_DEF_SecurityConfigHO_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_SecurityConfigHO_1,
	1,	/* Elements count */
	&asn_SPC_SecurityConfigHO_specs_1	/* Additional specs */
};


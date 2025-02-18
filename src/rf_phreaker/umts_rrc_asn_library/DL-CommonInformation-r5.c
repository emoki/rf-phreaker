/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/DL-CommonInformation-r5.h"

static int
mac_hsResetIndicator_15_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	/* Replace with underlying type checker */
	td->check_constraints = asn_DEF_NativeEnumerated.check_constraints;
	return td->check_constraints(td, sptr, ctfailcb, app_key);
}

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static void
mac_hsResetIndicator_15_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
	td->free_struct    = asn_DEF_NativeEnumerated.free_struct;
	td->print_struct   = asn_DEF_NativeEnumerated.print_struct;
	td->ber_decoder    = asn_DEF_NativeEnumerated.ber_decoder;
	td->der_encoder    = asn_DEF_NativeEnumerated.der_encoder;
	td->xer_decoder    = asn_DEF_NativeEnumerated.xer_decoder;
	td->xer_encoder    = asn_DEF_NativeEnumerated.xer_encoder;
	td->uper_decoder   = asn_DEF_NativeEnumerated.uper_decoder;
	td->uper_encoder   = asn_DEF_NativeEnumerated.uper_encoder;
	if(!td->per_constraints)
		td->per_constraints = asn_DEF_NativeEnumerated.per_constraints;
	td->elements       = asn_DEF_NativeEnumerated.elements;
	td->elements_count = asn_DEF_NativeEnumerated.elements_count;
     /* td->specifics      = asn_DEF_NativeEnumerated.specifics;	// Defined explicitly */
}

static void
mac_hsResetIndicator_15_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	mac_hsResetIndicator_15_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

static int
mac_hsResetIndicator_15_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	mac_hsResetIndicator_15_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

static asn_dec_rval_t
mac_hsResetIndicator_15_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	mac_hsResetIndicator_15_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

static asn_enc_rval_t
mac_hsResetIndicator_15_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	mac_hsResetIndicator_15_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

static asn_dec_rval_t
mac_hsResetIndicator_15_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	mac_hsResetIndicator_15_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

static asn_enc_rval_t
mac_hsResetIndicator_15_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	mac_hsResetIndicator_15_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

static asn_dec_rval_t
mac_hsResetIndicator_15_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	mac_hsResetIndicator_15_inherit_TYPE_descriptor(td);
	return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static asn_enc_rval_t
mac_hsResetIndicator_15_encode_uper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	mac_hsResetIndicator_15_inherit_TYPE_descriptor(td);
	return td->uper_encoder(td, constraints, structure, per_out);
}

static asn_per_constraints_t asn_PER_type_tddOption_constr_10 = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_modeSpecificInfo_constr_3 = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_mac_hsResetIndicator_constr_15 = {
	{ APC_CONSTRAINED,	 0,  0,  0,  0 }	/* (0..0) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_fdd_4[] = {
	{ ATF_POINTER, 4, offsetof(struct DL_CommonInformation_r5__modeSpecificInfo__fdd, defaultDPCH_OffsetValue),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DefaultDPCH_OffsetValueFDD,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"defaultDPCH-OffsetValue"
		},
	{ ATF_POINTER, 3, offsetof(struct DL_CommonInformation_r5__modeSpecificInfo__fdd, dpch_CompressedModeInfo),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DPCH_CompressedModeInfo,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"dpch-CompressedModeInfo"
		},
	{ ATF_POINTER, 2, offsetof(struct DL_CommonInformation_r5__modeSpecificInfo__fdd, tx_DiversityMode),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TX_DiversityMode,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tx-DiversityMode"
		},
	{ ATF_POINTER, 1, offsetof(struct DL_CommonInformation_r5__modeSpecificInfo__fdd, dummy),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SSDT_Information_r4,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"dummy"
		},
};
static int asn_MAP_fdd_oms_4[] = { 0, 1, 2, 3 };
static ber_tlv_tag_t asn_DEF_fdd_tags_4[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_fdd_tag2el_4[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* defaultDPCH-OffsetValue at 16594 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* dpch-CompressedModeInfo at 16595 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* tx-DiversityMode at 16596 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* dummy at 16599 */
};
static asn_SEQUENCE_specifics_t asn_SPC_fdd_specs_4 = {
	sizeof(struct DL_CommonInformation_r5__modeSpecificInfo__fdd),
	offsetof(struct DL_CommonInformation_r5__modeSpecificInfo__fdd, _asn_ctx),
	asn_MAP_fdd_tag2el_4,
	4,	/* Count of tags in the map */
	asn_MAP_fdd_oms_4,	/* Optional members */
	4, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_fdd_4 = {
	"fdd",
	"fdd",
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
	asn_DEF_fdd_tags_4,
	sizeof(asn_DEF_fdd_tags_4)
		/sizeof(asn_DEF_fdd_tags_4[0]) - 1, /* 1 */
	asn_DEF_fdd_tags_4,	/* Same as above */
	sizeof(asn_DEF_fdd_tags_4)
		/sizeof(asn_DEF_fdd_tags_4[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_fdd_4,
	4,	/* Elements count */
	&asn_SPC_fdd_specs_4	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_tdd128_12[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct DL_CommonInformation_r5__modeSpecificInfo__tdd__tddOption__tdd128, tstd_Indicator),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tstd-Indicator"
		},
};
static ber_tlv_tag_t asn_DEF_tdd128_tags_12[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_tdd128_tag2el_12[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* tstd-Indicator at 16605 */
};
static asn_SEQUENCE_specifics_t asn_SPC_tdd128_specs_12 = {
	sizeof(struct DL_CommonInformation_r5__modeSpecificInfo__tdd__tddOption__tdd128),
	offsetof(struct DL_CommonInformation_r5__modeSpecificInfo__tdd__tddOption__tdd128, _asn_ctx),
	asn_MAP_tdd128_tag2el_12,
	1,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_tdd128_12 = {
	"tdd128",
	"tdd128",
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
	asn_DEF_tdd128_tags_12,
	sizeof(asn_DEF_tdd128_tags_12)
		/sizeof(asn_DEF_tdd128_tags_12[0]) - 1, /* 1 */
	asn_DEF_tdd128_tags_12,	/* Same as above */
	sizeof(asn_DEF_tdd128_tags_12)
		/sizeof(asn_DEF_tdd128_tags_12[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_tdd128_12,
	1,	/* Elements count */
	&asn_SPC_tdd128_specs_12	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_tddOption_10[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct DL_CommonInformation_r5__modeSpecificInfo__tdd__tddOption, choice.tdd384),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tdd384"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct DL_CommonInformation_r5__modeSpecificInfo__tdd__tddOption, choice.tdd128),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_tdd128_12,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tdd128"
		},
};
static asn_TYPE_tag2member_t asn_MAP_tddOption_tag2el_10[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* tdd384 at 16603 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* tdd128 at 16606 */
};
static asn_CHOICE_specifics_t asn_SPC_tddOption_specs_10 = {
	sizeof(struct DL_CommonInformation_r5__modeSpecificInfo__tdd__tddOption),
	offsetof(struct DL_CommonInformation_r5__modeSpecificInfo__tdd__tddOption, _asn_ctx),
	offsetof(struct DL_CommonInformation_r5__modeSpecificInfo__tdd__tddOption, present),
	sizeof(((struct DL_CommonInformation_r5__modeSpecificInfo__tdd__tddOption *)0)->present),
	asn_MAP_tddOption_tag2el_10,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_tddOption_10 = {
	"tddOption",
	"tddOption",
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
	&asn_PER_type_tddOption_constr_10,
	asn_MBR_tddOption_10,
	2,	/* Elements count */
	&asn_SPC_tddOption_specs_10	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_tdd_9[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct DL_CommonInformation_r5__modeSpecificInfo__tdd, tddOption),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_tddOption_10,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tddOption"
		},
	{ ATF_POINTER, 1, offsetof(struct DL_CommonInformation_r5__modeSpecificInfo__tdd, defaultDPCH_OffsetValue),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DefaultDPCH_OffsetValueTDD,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"defaultDPCH-OffsetValue"
		},
};
static int asn_MAP_tdd_oms_9[] = { 1 };
static ber_tlv_tag_t asn_DEF_tdd_tags_9[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_tdd_tag2el_9[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* tddOption at 16603 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* defaultDPCH-OffsetValue at 16608 */
};
static asn_SEQUENCE_specifics_t asn_SPC_tdd_specs_9 = {
	sizeof(struct DL_CommonInformation_r5__modeSpecificInfo__tdd),
	offsetof(struct DL_CommonInformation_r5__modeSpecificInfo__tdd, _asn_ctx),
	asn_MAP_tdd_tag2el_9,
	2,	/* Count of tags in the map */
	asn_MAP_tdd_oms_9,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_tdd_9 = {
	"tdd",
	"tdd",
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
	asn_DEF_tdd_tags_9,
	sizeof(asn_DEF_tdd_tags_9)
		/sizeof(asn_DEF_tdd_tags_9[0]) - 1, /* 1 */
	asn_DEF_tdd_tags_9,	/* Same as above */
	sizeof(asn_DEF_tdd_tags_9)
		/sizeof(asn_DEF_tdd_tags_9[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_tdd_9,
	2,	/* Elements count */
	&asn_SPC_tdd_specs_9	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_modeSpecificInfo_3[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct DL_CommonInformation_r5__modeSpecificInfo, choice.fdd),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_fdd_4,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"fdd"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct DL_CommonInformation_r5__modeSpecificInfo, choice.tdd),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_tdd_9,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tdd"
		},
};
static asn_TYPE_tag2member_t asn_MAP_modeSpecificInfo_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* fdd at 16594 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* tdd at 16607 */
};
static asn_CHOICE_specifics_t asn_SPC_modeSpecificInfo_specs_3 = {
	sizeof(struct DL_CommonInformation_r5__modeSpecificInfo),
	offsetof(struct DL_CommonInformation_r5__modeSpecificInfo, _asn_ctx),
	offsetof(struct DL_CommonInformation_r5__modeSpecificInfo, present),
	sizeof(((struct DL_CommonInformation_r5__modeSpecificInfo *)0)->present),
	asn_MAP_modeSpecificInfo_tag2el_3,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_modeSpecificInfo_3 = {
	"modeSpecificInfo",
	"modeSpecificInfo",
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
	&asn_PER_type_modeSpecificInfo_constr_3,
	asn_MBR_modeSpecificInfo_3,
	2,	/* Elements count */
	&asn_SPC_modeSpecificInfo_specs_3	/* Additional specs */
};

static asn_INTEGER_enum_map_t asn_MAP_mac_hsResetIndicator_value2enum_15[] = {
	{ 0,	4,	"true" }
};
static unsigned int asn_MAP_mac_hsResetIndicator_enum2value_15[] = {
	0	/* true(0) */
};
static asn_INTEGER_specifics_t asn_SPC_mac_hsResetIndicator_specs_15 = {
	asn_MAP_mac_hsResetIndicator_value2enum_15,	/* "tag" => N; sorted by tag */
	asn_MAP_mac_hsResetIndicator_enum2value_15,	/* N => "tag"; sorted by N */
	1,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static ber_tlv_tag_t asn_DEF_mac_hsResetIndicator_tags_15[] = {
	(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_mac_hsResetIndicator_15 = {
	"mac-hsResetIndicator",
	"mac-hsResetIndicator",
	mac_hsResetIndicator_15_free,
	mac_hsResetIndicator_15_print,
	mac_hsResetIndicator_15_constraint,
	mac_hsResetIndicator_15_decode_ber,
	mac_hsResetIndicator_15_encode_der,
	mac_hsResetIndicator_15_decode_xer,
	mac_hsResetIndicator_15_encode_xer,
	mac_hsResetIndicator_15_decode_uper,
	mac_hsResetIndicator_15_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_mac_hsResetIndicator_tags_15,
	sizeof(asn_DEF_mac_hsResetIndicator_tags_15)
		/sizeof(asn_DEF_mac_hsResetIndicator_tags_15[0]) - 1, /* 1 */
	asn_DEF_mac_hsResetIndicator_tags_15,	/* Same as above */
	sizeof(asn_DEF_mac_hsResetIndicator_tags_15)
		/sizeof(asn_DEF_mac_hsResetIndicator_tags_15[0]), /* 2 */
	&asn_PER_type_mac_hsResetIndicator_constr_15,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_mac_hsResetIndicator_specs_15	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_DL_CommonInformation_r5_1[] = {
	{ ATF_POINTER, 1, offsetof(struct DL_CommonInformation_r5, dl_DPCH_InfoCommon),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DL_DPCH_InfoCommon_r4,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"dl-DPCH-InfoCommon"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct DL_CommonInformation_r5, modeSpecificInfo),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_modeSpecificInfo_3,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"modeSpecificInfo"
		},
	{ ATF_POINTER, 1, offsetof(struct DL_CommonInformation_r5, mac_hsResetIndicator),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_mac_hsResetIndicator_15,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"mac-hsResetIndicator"
		},
};
static int asn_MAP_DL_CommonInformation_r5_oms_1[] = { 0, 2 };
static ber_tlv_tag_t asn_DEF_DL_CommonInformation_r5_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_DL_CommonInformation_r5_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* dl-DPCH-InfoCommon at 16591 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* modeSpecificInfo at 16600 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* mac-hsResetIndicator at 16611 */
};
static asn_SEQUENCE_specifics_t asn_SPC_DL_CommonInformation_r5_specs_1 = {
	sizeof(struct DL_CommonInformation_r5),
	offsetof(struct DL_CommonInformation_r5, _asn_ctx),
	asn_MAP_DL_CommonInformation_r5_tag2el_1,
	3,	/* Count of tags in the map */
	asn_MAP_DL_CommonInformation_r5_oms_1,	/* Optional members */
	2, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_DL_CommonInformation_r5 = {
	"DL-CommonInformation-r5",
	"DL-CommonInformation-r5",
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
	asn_DEF_DL_CommonInformation_r5_tags_1,
	sizeof(asn_DEF_DL_CommonInformation_r5_tags_1)
		/sizeof(asn_DEF_DL_CommonInformation_r5_tags_1[0]), /* 1 */
	asn_DEF_DL_CommonInformation_r5_tags_1,	/* Same as above */
	sizeof(asn_DEF_DL_CommonInformation_r5_tags_1)
		/sizeof(asn_DEF_DL_CommonInformation_r5_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_DL_CommonInformation_r5_1,
	3,	/* Elements count */
	&asn_SPC_DL_CommonInformation_r5_specs_1	/* Additional specs */
};


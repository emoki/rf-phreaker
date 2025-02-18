/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "PDU-definitions"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/UplinkPhysicalChannelControl-r7-IEs.h"

static int
tpc_Step_Size_22_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
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
tpc_Step_Size_22_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
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
tpc_Step_Size_22_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	tpc_Step_Size_22_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

static int
tpc_Step_Size_22_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	tpc_Step_Size_22_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

static asn_dec_rval_t
tpc_Step_Size_22_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	tpc_Step_Size_22_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

static asn_enc_rval_t
tpc_Step_Size_22_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	tpc_Step_Size_22_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

static asn_dec_rval_t
tpc_Step_Size_22_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	tpc_Step_Size_22_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

static asn_enc_rval_t
tpc_Step_Size_22_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	tpc_Step_Size_22_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

static asn_dec_rval_t
tpc_Step_Size_22_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	tpc_Step_Size_22_inherit_TYPE_descriptor(td);
	return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static asn_enc_rval_t
tpc_Step_Size_22_encode_uper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	tpc_Step_Size_22_inherit_TYPE_descriptor(td);
	return td->uper_encoder(td, constraints, structure, per_out);
}

static int
memb_desired_HS_SICH_PowerLevel_constraint_19(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= -120 && value <= -58)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_per_constraints_t asn_PER_type_tpc_Step_Size_constr_22 = {
	{ APC_CONSTRAINED,	 2,  2,  0,  3 }	/* (0..3) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_desired_HS_SICH_PowerLevel_constr_21 = {
	{ APC_CONSTRAINED,	 6,  6, -120, -58 }	/* (-120..-58) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_tddOption_constr_4 = {
	{ APC_CONSTRAINED,	 2,  2,  0,  2 }	/* (0..2) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_tdd384_5[] = {
	{ ATF_POINTER, 6, offsetof(struct UplinkPhysicalChannelControl_r7_IEs__tddOption__tdd384, timingAdvance),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_UL_TimingAdvanceControl_r4,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"timingAdvance"
		},
	{ ATF_POINTER, 5, offsetof(struct UplinkPhysicalChannelControl_r7_IEs__tddOption__tdd384, alpha),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Alpha,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"alpha"
		},
	{ ATF_POINTER, 4, offsetof(struct UplinkPhysicalChannelControl_r7_IEs__tddOption__tdd384, prach_ConstantValue),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ConstantValueTdd,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"prach-ConstantValue"
		},
	{ ATF_POINTER, 3, offsetof(struct UplinkPhysicalChannelControl_r7_IEs__tddOption__tdd384, pusch_ConstantValue),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ConstantValueTdd,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"pusch-ConstantValue"
		},
	{ ATF_POINTER, 2, offsetof(struct UplinkPhysicalChannelControl_r7_IEs__tddOption__tdd384, openLoopPowerControl_IPDL_TDD),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OpenLoopPowerControl_IPDL_TDD_r4,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"openLoopPowerControl-IPDL-TDD"
		},
	{ ATF_POINTER, 1, offsetof(struct UplinkPhysicalChannelControl_r7_IEs__tddOption__tdd384, hs_SICH_PowerControl),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_HS_SICH_Power_Control_Info_TDD384,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"hs-SICH-PowerControl"
		},
};
static int asn_MAP_tdd384_oms_5[] = { 0, 1, 2, 3, 4, 5 };
static ber_tlv_tag_t asn_DEF_tdd384_tags_5[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_tdd384_tag2el_5[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* timingAdvance at 9834 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* alpha at 9835 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* prach-ConstantValue at 9836 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* pusch-ConstantValue at 9837 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* openLoopPowerControl-IPDL-TDD at 9838 */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 } /* hs-SICH-PowerControl at 9839 */
};
static asn_SEQUENCE_specifics_t asn_SPC_tdd384_specs_5 = {
	sizeof(struct UplinkPhysicalChannelControl_r7_IEs__tddOption__tdd384),
	offsetof(struct UplinkPhysicalChannelControl_r7_IEs__tddOption__tdd384, _asn_ctx),
	asn_MAP_tdd384_tag2el_5,
	6,	/* Count of tags in the map */
	asn_MAP_tdd384_oms_5,	/* Optional members */
	6, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_tdd384_5 = {
	"tdd384",
	"tdd384",
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
	asn_DEF_tdd384_tags_5,
	sizeof(asn_DEF_tdd384_tags_5)
		/sizeof(asn_DEF_tdd384_tags_5[0]) - 1, /* 1 */
	asn_DEF_tdd384_tags_5,	/* Same as above */
	sizeof(asn_DEF_tdd384_tags_5)
		/sizeof(asn_DEF_tdd384_tags_5[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_tdd384_5,
	6,	/* Elements count */
	&asn_SPC_tdd384_specs_5	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_tdd768_12[] = {
	{ ATF_POINTER, 6, offsetof(struct UplinkPhysicalChannelControl_r7_IEs__tddOption__tdd768, timingAdvance),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_UL_TimingAdvanceControl_r7,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"timingAdvance"
		},
	{ ATF_POINTER, 5, offsetof(struct UplinkPhysicalChannelControl_r7_IEs__tddOption__tdd768, alpha),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Alpha,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"alpha"
		},
	{ ATF_POINTER, 4, offsetof(struct UplinkPhysicalChannelControl_r7_IEs__tddOption__tdd768, prach_ConstantValue),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ConstantValueTdd,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"prach-ConstantValue"
		},
	{ ATF_POINTER, 3, offsetof(struct UplinkPhysicalChannelControl_r7_IEs__tddOption__tdd768, pusch_ConstantValue),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ConstantValueTdd,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"pusch-ConstantValue"
		},
	{ ATF_POINTER, 2, offsetof(struct UplinkPhysicalChannelControl_r7_IEs__tddOption__tdd768, openLoopPowerControl_IPDL_TDD),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OpenLoopPowerControl_IPDL_TDD_r4,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"openLoopPowerControl-IPDL-TDD"
		},
	{ ATF_POINTER, 1, offsetof(struct UplinkPhysicalChannelControl_r7_IEs__tddOption__tdd768, hs_SICH_PowerControl),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_HS_SICH_Power_Control_Info_TDD768,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"hs-SICH-PowerControl"
		},
};
static int asn_MAP_tdd768_oms_12[] = { 0, 1, 2, 3, 4, 5 };
static ber_tlv_tag_t asn_DEF_tdd768_tags_12[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_tdd768_tag2el_12[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* timingAdvance at 9842 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* alpha at 9843 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* prach-ConstantValue at 9844 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* pusch-ConstantValue at 9845 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* openLoopPowerControl-IPDL-TDD at 9846 */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 } /* hs-SICH-PowerControl at 9847 */
};
static asn_SEQUENCE_specifics_t asn_SPC_tdd768_specs_12 = {
	sizeof(struct UplinkPhysicalChannelControl_r7_IEs__tddOption__tdd768),
	offsetof(struct UplinkPhysicalChannelControl_r7_IEs__tddOption__tdd768, _asn_ctx),
	asn_MAP_tdd768_tag2el_12,
	6,	/* Count of tags in the map */
	asn_MAP_tdd768_oms_12,	/* Optional members */
	6, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_tdd768_12 = {
	"tdd768",
	"tdd768",
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
	asn_DEF_tdd768_tags_12,
	sizeof(asn_DEF_tdd768_tags_12)
		/sizeof(asn_DEF_tdd768_tags_12[0]) - 1, /* 1 */
	asn_DEF_tdd768_tags_12,	/* Same as above */
	sizeof(asn_DEF_tdd768_tags_12)
		/sizeof(asn_DEF_tdd768_tags_12[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_tdd768_12,
	6,	/* Elements count */
	&asn_SPC_tdd768_specs_12	/* Additional specs */
};

static asn_INTEGER_enum_map_t asn_MAP_tpc_Step_Size_value2enum_22[] = {
	{ 0,	2,	"s1" },
	{ 1,	2,	"s2" },
	{ 2,	2,	"s3" },
	{ 3,	6,	"spare1" }
};
static unsigned int asn_MAP_tpc_Step_Size_enum2value_22[] = {
	0,	/* s1(0) */
	1,	/* s2(1) */
	2,	/* s3(2) */
	3	/* spare1(3) */
};
static asn_INTEGER_specifics_t asn_SPC_tpc_Step_Size_specs_22 = {
	asn_MAP_tpc_Step_Size_value2enum_22,	/* "tag" => N; sorted by tag */
	asn_MAP_tpc_Step_Size_enum2value_22,	/* N => "tag"; sorted by N */
	4,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static ber_tlv_tag_t asn_DEF_tpc_Step_Size_tags_22[] = {
	(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_tpc_Step_Size_22 = {
	"tpc-Step-Size",
	"tpc-Step-Size",
	tpc_Step_Size_22_free,
	tpc_Step_Size_22_print,
	tpc_Step_Size_22_constraint,
	tpc_Step_Size_22_decode_ber,
	tpc_Step_Size_22_encode_der,
	tpc_Step_Size_22_decode_xer,
	tpc_Step_Size_22_encode_xer,
	tpc_Step_Size_22_decode_uper,
	tpc_Step_Size_22_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_tpc_Step_Size_tags_22,
	sizeof(asn_DEF_tpc_Step_Size_tags_22)
		/sizeof(asn_DEF_tpc_Step_Size_tags_22[0]) - 1, /* 1 */
	asn_DEF_tpc_Step_Size_tags_22,	/* Same as above */
	sizeof(asn_DEF_tpc_Step_Size_tags_22)
		/sizeof(asn_DEF_tpc_Step_Size_tags_22[0]), /* 2 */
	&asn_PER_type_tpc_Step_Size_constr_22,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_tpc_Step_Size_specs_22	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_tdd128_19[] = {
	{ ATF_POINTER, 3, offsetof(struct UplinkPhysicalChannelControl_r7_IEs__tddOption__tdd128, ul_SynchronisationParameters),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UL_SynchronisationParameters_r4,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ul-SynchronisationParameters"
		},
	{ ATF_POINTER, 2, offsetof(struct UplinkPhysicalChannelControl_r7_IEs__tddOption__tdd128, desired_HS_SICH_PowerLevel),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		memb_desired_HS_SICH_PowerLevel_constraint_19,
		&asn_PER_memb_desired_HS_SICH_PowerLevel_constr_21,
		0,
		"desired-HS-SICH-PowerLevel"
		},
	{ ATF_POINTER, 1, offsetof(struct UplinkPhysicalChannelControl_r7_IEs__tddOption__tdd128, tpc_Step_Size),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_tpc_Step_Size_22,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tpc-Step-Size"
		},
};
static int asn_MAP_tdd128_oms_19[] = { 0, 1, 2 };
static ber_tlv_tag_t asn_DEF_tdd128_tags_19[] = {
	(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_tdd128_tag2el_19[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* ul-SynchronisationParameters at 9850 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* desired-HS-SICH-PowerLevel at 9851 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* tpc-Step-Size at 9852 */
};
static asn_SEQUENCE_specifics_t asn_SPC_tdd128_specs_19 = {
	sizeof(struct UplinkPhysicalChannelControl_r7_IEs__tddOption__tdd128),
	offsetof(struct UplinkPhysicalChannelControl_r7_IEs__tddOption__tdd128, _asn_ctx),
	asn_MAP_tdd128_tag2el_19,
	3,	/* Count of tags in the map */
	asn_MAP_tdd128_oms_19,	/* Optional members */
	3, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_tdd128_19 = {
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
	asn_DEF_tdd128_tags_19,
	sizeof(asn_DEF_tdd128_tags_19)
		/sizeof(asn_DEF_tdd128_tags_19[0]) - 1, /* 1 */
	asn_DEF_tdd128_tags_19,	/* Same as above */
	sizeof(asn_DEF_tdd128_tags_19)
		/sizeof(asn_DEF_tdd128_tags_19[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_tdd128_19,
	3,	/* Elements count */
	&asn_SPC_tdd128_specs_19	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_tddOption_4[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct UplinkPhysicalChannelControl_r7_IEs__tddOption, choice.tdd384),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_tdd384_5,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tdd384"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UplinkPhysicalChannelControl_r7_IEs__tddOption, choice.tdd768),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_tdd768_12,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tdd768"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UplinkPhysicalChannelControl_r7_IEs__tddOption, choice.tdd128),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		0,
		&asn_DEF_tdd128_19,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tdd128"
		},
};
static asn_TYPE_tag2member_t asn_MAP_tddOption_tag2el_4[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* tdd384 at 9834 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* tdd768 at 9842 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* tdd128 at 9850 */
};
static asn_CHOICE_specifics_t asn_SPC_tddOption_specs_4 = {
	sizeof(struct UplinkPhysicalChannelControl_r7_IEs__tddOption),
	offsetof(struct UplinkPhysicalChannelControl_r7_IEs__tddOption, _asn_ctx),
	offsetof(struct UplinkPhysicalChannelControl_r7_IEs__tddOption, present),
	sizeof(((struct UplinkPhysicalChannelControl_r7_IEs__tddOption *)0)->present),
	asn_MAP_tddOption_tag2el_4,
	3,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_tddOption_4 = {
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
	&asn_PER_type_tddOption_constr_4,
	asn_MBR_tddOption_4,
	3,	/* Elements count */
	&asn_SPC_tddOption_specs_4	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_UplinkPhysicalChannelControl_r7_IEs_1[] = {
	{ ATF_POINTER, 2, offsetof(struct UplinkPhysicalChannelControl_r7_IEs, ccTrCH_PowerControlInfo),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CCTrCH_PowerControlInfo_r7,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ccTrCH-PowerControlInfo"
		},
	{ ATF_POINTER, 1, offsetof(struct UplinkPhysicalChannelControl_r7_IEs, specialBurstScheduling),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SpecialBurstScheduling,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"specialBurstScheduling"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UplinkPhysicalChannelControl_r7_IEs, tddOption),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_tddOption_4,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tddOption"
		},
};
static int asn_MAP_UplinkPhysicalChannelControl_r7_IEs_oms_1[] = { 0, 1 };
static ber_tlv_tag_t asn_DEF_UplinkPhysicalChannelControl_r7_IEs_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_UplinkPhysicalChannelControl_r7_IEs_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* ccTrCH-PowerControlInfo at 9830 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* specialBurstScheduling at 9831 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* tddOption at 9840 */
};
static asn_SEQUENCE_specifics_t asn_SPC_UplinkPhysicalChannelControl_r7_IEs_specs_1 = {
	sizeof(struct UplinkPhysicalChannelControl_r7_IEs),
	offsetof(struct UplinkPhysicalChannelControl_r7_IEs, _asn_ctx),
	asn_MAP_UplinkPhysicalChannelControl_r7_IEs_tag2el_1,
	3,	/* Count of tags in the map */
	asn_MAP_UplinkPhysicalChannelControl_r7_IEs_oms_1,	/* Optional members */
	2, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_UplinkPhysicalChannelControl_r7_IEs = {
	"UplinkPhysicalChannelControl-r7-IEs",
	"UplinkPhysicalChannelControl-r7-IEs",
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
	asn_DEF_UplinkPhysicalChannelControl_r7_IEs_tags_1,
	sizeof(asn_DEF_UplinkPhysicalChannelControl_r7_IEs_tags_1)
		/sizeof(asn_DEF_UplinkPhysicalChannelControl_r7_IEs_tags_1[0]), /* 1 */
	asn_DEF_UplinkPhysicalChannelControl_r7_IEs_tags_1,	/* Same as above */
	sizeof(asn_DEF_UplinkPhysicalChannelControl_r7_IEs_tags_1)
		/sizeof(asn_DEF_UplinkPhysicalChannelControl_r7_IEs_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_UplinkPhysicalChannelControl_r7_IEs_1,
	3,	/* Elements count */
	&asn_SPC_UplinkPhysicalChannelControl_r7_IEs_specs_1	/* Additional specs */
};


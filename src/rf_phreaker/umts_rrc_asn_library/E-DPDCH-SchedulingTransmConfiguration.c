/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/E-DPDCH-SchedulingTransmConfiguration.h"

static int
primary_Secondary_GrantSelector_5_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
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
primary_Secondary_GrantSelector_5_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
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
primary_Secondary_GrantSelector_5_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	primary_Secondary_GrantSelector_5_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

static int
primary_Secondary_GrantSelector_5_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	primary_Secondary_GrantSelector_5_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

static asn_dec_rval_t
primary_Secondary_GrantSelector_5_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	primary_Secondary_GrantSelector_5_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

static asn_enc_rval_t
primary_Secondary_GrantSelector_5_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	primary_Secondary_GrantSelector_5_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

static asn_dec_rval_t
primary_Secondary_GrantSelector_5_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	primary_Secondary_GrantSelector_5_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

static asn_enc_rval_t
primary_Secondary_GrantSelector_5_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	primary_Secondary_GrantSelector_5_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

static asn_dec_rval_t
primary_Secondary_GrantSelector_5_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	primary_Secondary_GrantSelector_5_inherit_TYPE_descriptor(td);
	return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static asn_enc_rval_t
primary_Secondary_GrantSelector_5_encode_uper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	primary_Secondary_GrantSelector_5_inherit_TYPE_descriptor(td);
	return td->uper_encoder(td, constraints, structure, per_out);
}

static int
memb_value_constraint_3(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 38)) {
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
memb_ms2_SchedTransmGrantHARQAlloc_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
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
	
	if((size == 8)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_per_constraints_t asn_PER_type_primary_Secondary_GrantSelector_constr_5 = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_value_constr_4 = {
	{ APC_CONSTRAINED,	 6,  6,  0,  38 }	/* (0..38) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_ms2_SchedTransmGrantHARQAlloc_constr_2 = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 0,  0,  8,  8 }	/* (SIZE(8..8)) */,
	0, 0	/* No PER value map */
};
static asn_INTEGER_enum_map_t asn_MAP_primary_Secondary_GrantSelector_value2enum_5[] = {
	{ 0,	7,	"primary" },
	{ 1,	9,	"secondary" }
};
static unsigned int asn_MAP_primary_Secondary_GrantSelector_enum2value_5[] = {
	0,	/* primary(0) */
	1	/* secondary(1) */
};
static asn_INTEGER_specifics_t asn_SPC_primary_Secondary_GrantSelector_specs_5 = {
	asn_MAP_primary_Secondary_GrantSelector_value2enum_5,	/* "tag" => N; sorted by tag */
	asn_MAP_primary_Secondary_GrantSelector_enum2value_5,	/* N => "tag"; sorted by N */
	2,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static ber_tlv_tag_t asn_DEF_primary_Secondary_GrantSelector_tags_5[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_primary_Secondary_GrantSelector_5 = {
	"primary-Secondary-GrantSelector",
	"primary-Secondary-GrantSelector",
	primary_Secondary_GrantSelector_5_free,
	primary_Secondary_GrantSelector_5_print,
	primary_Secondary_GrantSelector_5_constraint,
	primary_Secondary_GrantSelector_5_decode_ber,
	primary_Secondary_GrantSelector_5_encode_der,
	primary_Secondary_GrantSelector_5_decode_xer,
	primary_Secondary_GrantSelector_5_encode_xer,
	primary_Secondary_GrantSelector_5_decode_uper,
	primary_Secondary_GrantSelector_5_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_primary_Secondary_GrantSelector_tags_5,
	sizeof(asn_DEF_primary_Secondary_GrantSelector_tags_5)
		/sizeof(asn_DEF_primary_Secondary_GrantSelector_tags_5[0]) - 1, /* 1 */
	asn_DEF_primary_Secondary_GrantSelector_tags_5,	/* Same as above */
	sizeof(asn_DEF_primary_Secondary_GrantSelector_tags_5)
		/sizeof(asn_DEF_primary_Secondary_GrantSelector_tags_5[0]), /* 2 */
	&asn_PER_type_primary_Secondary_GrantSelector_constr_5,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_primary_Secondary_GrantSelector_specs_5	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_servingGrant_3[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct E_DPDCH_SchedulingTransmConfiguration__servingGrant, value),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		memb_value_constraint_3,
		&asn_PER_memb_value_constr_4,
		0,
		"value"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct E_DPDCH_SchedulingTransmConfiguration__servingGrant, primary_Secondary_GrantSelector),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_primary_Secondary_GrantSelector_5,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"primary-Secondary-GrantSelector"
		},
};
static ber_tlv_tag_t asn_DEF_servingGrant_tags_3[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_servingGrant_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* value at 18054 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* primary-Secondary-GrantSelector at 18055 */
};
static asn_SEQUENCE_specifics_t asn_SPC_servingGrant_specs_3 = {
	sizeof(struct E_DPDCH_SchedulingTransmConfiguration__servingGrant),
	offsetof(struct E_DPDCH_SchedulingTransmConfiguration__servingGrant, _asn_ctx),
	asn_MAP_servingGrant_tag2el_3,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_servingGrant_3 = {
	"servingGrant",
	"servingGrant",
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
	asn_DEF_servingGrant_tags_3,
	sizeof(asn_DEF_servingGrant_tags_3)
		/sizeof(asn_DEF_servingGrant_tags_3[0]) - 1, /* 1 */
	asn_DEF_servingGrant_tags_3,	/* Same as above */
	sizeof(asn_DEF_servingGrant_tags_3)
		/sizeof(asn_DEF_servingGrant_tags_3[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_servingGrant_3,
	2,	/* Elements count */
	&asn_SPC_servingGrant_specs_3	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_E_DPDCH_SchedulingTransmConfiguration_1[] = {
	{ ATF_POINTER, 2, offsetof(struct E_DPDCH_SchedulingTransmConfiguration, ms2_SchedTransmGrantHARQAlloc),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BIT_STRING,
		memb_ms2_SchedTransmGrantHARQAlloc_constraint_1,
		&asn_PER_memb_ms2_SchedTransmGrantHARQAlloc_constr_2,
		0,
		"ms2-SchedTransmGrantHARQAlloc"
		},
	{ ATF_POINTER, 1, offsetof(struct E_DPDCH_SchedulingTransmConfiguration, servingGrant),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_servingGrant_3,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"servingGrant"
		},
};
static int asn_MAP_E_DPDCH_SchedulingTransmConfiguration_oms_1[] = { 0, 1 };
static ber_tlv_tag_t asn_DEF_E_DPDCH_SchedulingTransmConfiguration_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_E_DPDCH_SchedulingTransmConfiguration_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* ms2-SchedTransmGrantHARQAlloc at 18052 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* servingGrant at 18054 */
};
static asn_SEQUENCE_specifics_t asn_SPC_E_DPDCH_SchedulingTransmConfiguration_specs_1 = {
	sizeof(struct E_DPDCH_SchedulingTransmConfiguration),
	offsetof(struct E_DPDCH_SchedulingTransmConfiguration, _asn_ctx),
	asn_MAP_E_DPDCH_SchedulingTransmConfiguration_tag2el_1,
	2,	/* Count of tags in the map */
	asn_MAP_E_DPDCH_SchedulingTransmConfiguration_oms_1,	/* Optional members */
	2, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_E_DPDCH_SchedulingTransmConfiguration = {
	"E-DPDCH-SchedulingTransmConfiguration",
	"E-DPDCH-SchedulingTransmConfiguration",
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
	asn_DEF_E_DPDCH_SchedulingTransmConfiguration_tags_1,
	sizeof(asn_DEF_E_DPDCH_SchedulingTransmConfiguration_tags_1)
		/sizeof(asn_DEF_E_DPDCH_SchedulingTransmConfiguration_tags_1[0]), /* 1 */
	asn_DEF_E_DPDCH_SchedulingTransmConfiguration_tags_1,	/* Same as above */
	sizeof(asn_DEF_E_DPDCH_SchedulingTransmConfiguration_tags_1)
		/sizeof(asn_DEF_E_DPDCH_SchedulingTransmConfiguration_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_E_DPDCH_SchedulingTransmConfiguration_1,
	2,	/* Elements count */
	&asn_SPC_E_DPDCH_SchedulingTransmConfiguration_specs_1	/* Additional specs */
};


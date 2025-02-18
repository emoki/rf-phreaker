/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/LoggedMeasurementsConfigurationInfo.h"

static int
loggingDuration_3_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
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
loggingDuration_3_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
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
loggingDuration_3_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	loggingDuration_3_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

static int
loggingDuration_3_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	loggingDuration_3_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

static asn_dec_rval_t
loggingDuration_3_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	loggingDuration_3_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

static asn_enc_rval_t
loggingDuration_3_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	loggingDuration_3_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

static asn_dec_rval_t
loggingDuration_3_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	loggingDuration_3_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

static asn_enc_rval_t
loggingDuration_3_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	loggingDuration_3_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

static asn_dec_rval_t
loggingDuration_3_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	loggingDuration_3_inherit_TYPE_descriptor(td);
	return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static asn_enc_rval_t
loggingDuration_3_encode_uper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	loggingDuration_3_inherit_TYPE_descriptor(td);
	return td->uper_encoder(td, constraints, structure, per_out);
}

static int
loggingInterval_12_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
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
loggingInterval_12_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
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
loggingInterval_12_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	loggingInterval_12_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

static int
loggingInterval_12_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	loggingInterval_12_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

static asn_dec_rval_t
loggingInterval_12_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	loggingInterval_12_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

static asn_enc_rval_t
loggingInterval_12_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	loggingInterval_12_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

static asn_dec_rval_t
loggingInterval_12_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	loggingInterval_12_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

static asn_enc_rval_t
loggingInterval_12_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	loggingInterval_12_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

static asn_dec_rval_t
loggingInterval_12_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	loggingInterval_12_inherit_TYPE_descriptor(td);
	return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static asn_enc_rval_t
loggingInterval_12_encode_uper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	loggingInterval_12_inherit_TYPE_descriptor(td);
	return td->uper_encoder(td, constraints, structure, per_out);
}

static int
memb_traceId_constraint_21(asn_TYPE_descriptor_t *td, const void *sptr,
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
	
	if((size == 3)) {
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
memb_cellIDList_constraint_25(asn_TYPE_descriptor_t *td, const void *sptr,
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
	
	if((size >= 1 && size <= 32)) {
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
memb_locationAreaList_constraint_25(asn_TYPE_descriptor_t *td, const void *sptr,
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

static int
memb_routingAreaList_constraint_25(asn_TYPE_descriptor_t *td, const void *sptr,
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

static int
memb_absoluteTimeInfo_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
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
	
	if((size == 48)) {
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
memb_traceRecordingSession_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
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
	
	if((size == 2)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_per_constraints_t asn_PER_type_loggingDuration_constr_3 = {
	{ APC_CONSTRAINED,	 3,  3,  0,  7 }	/* (0..7) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_loggingInterval_constr_12 = {
	{ APC_CONSTRAINED,	 3,  3,  0,  7 }	/* (0..7) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_traceId_constr_23 = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 0,  0,  3,  3 }	/* (SIZE(3..3)) */,
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_cellIDList_constr_26 = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 5,  5,  1,  32 }	/* (SIZE(1..32)) */,
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_locationAreaList_constr_28 = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 3,  3,  1,  8 }	/* (SIZE(1..8)) */,
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_routingAreaList_constr_30 = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 3,  3,  1,  8 }	/* (SIZE(1..8)) */,
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_cellIDList_constr_26 = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 5,  5,  1,  32 }	/* (SIZE(1..32)) */,
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_locationAreaList_constr_28 = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 3,  3,  1,  8 }	/* (SIZE(1..8)) */,
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_routingAreaList_constr_30 = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 3,  3,  1,  8 }	/* (SIZE(1..8)) */,
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_areaConfiguration_constr_25 = {
	{ APC_CONSTRAINED,	 2,  2,  0,  2 }	/* (0..2) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_absoluteTimeInfo_constr_2 = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 0,  0,  48,  48 }	/* (SIZE(48..48)) */,
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_traceRecordingSession_constr_24 = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 0,  0,  2,  2 }	/* (SIZE(2..2)) */,
	0, 0	/* No PER value map */
};
static asn_INTEGER_enum_map_t asn_MAP_loggingDuration_value2enum_3[] = {
	{ 0,	5,	"min10" },
	{ 1,	5,	"min20" },
	{ 2,	5,	"min40" },
	{ 3,	3,	"hr1" },
	{ 4,	8,	"hr1min30" },
	{ 5,	3,	"hr2" },
	{ 6,	6,	"spare1" },
	{ 7,	6,	"spare2" }
};
static unsigned int asn_MAP_loggingDuration_enum2value_3[] = {
	3,	/* hr1(3) */
	4,	/* hr1min30(4) */
	5,	/* hr2(5) */
	0,	/* min10(0) */
	1,	/* min20(1) */
	2,	/* min40(2) */
	6,	/* spare1(6) */
	7	/* spare2(7) */
};
static asn_INTEGER_specifics_t asn_SPC_loggingDuration_specs_3 = {
	asn_MAP_loggingDuration_value2enum_3,	/* "tag" => N; sorted by tag */
	asn_MAP_loggingDuration_enum2value_3,	/* N => "tag"; sorted by N */
	8,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static ber_tlv_tag_t asn_DEF_loggingDuration_tags_3[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_loggingDuration_3 = {
	"loggingDuration",
	"loggingDuration",
	loggingDuration_3_free,
	loggingDuration_3_print,
	loggingDuration_3_constraint,
	loggingDuration_3_decode_ber,
	loggingDuration_3_encode_der,
	loggingDuration_3_decode_xer,
	loggingDuration_3_encode_xer,
	loggingDuration_3_decode_uper,
	loggingDuration_3_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_loggingDuration_tags_3,
	sizeof(asn_DEF_loggingDuration_tags_3)
		/sizeof(asn_DEF_loggingDuration_tags_3[0]) - 1, /* 1 */
	asn_DEF_loggingDuration_tags_3,	/* Same as above */
	sizeof(asn_DEF_loggingDuration_tags_3)
		/sizeof(asn_DEF_loggingDuration_tags_3[0]), /* 2 */
	&asn_PER_type_loggingDuration_constr_3,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_loggingDuration_specs_3	/* Additional specs */
};

static asn_INTEGER_enum_map_t asn_MAP_loggingInterval_value2enum_12[] = {
	{ 0,	5,	"li128" },
	{ 1,	5,	"li256" },
	{ 2,	5,	"li512" },
	{ 3,	6,	"li1024" },
	{ 4,	6,	"li2048" },
	{ 5,	6,	"li3072" },
	{ 6,	6,	"li4096" },
	{ 7,	6,	"li6144" }
};
static unsigned int asn_MAP_loggingInterval_enum2value_12[] = {
	3,	/* li1024(3) */
	0,	/* li128(0) */
	4,	/* li2048(4) */
	1,	/* li256(1) */
	5,	/* li3072(5) */
	6,	/* li4096(6) */
	2,	/* li512(2) */
	7	/* li6144(7) */
};
static asn_INTEGER_specifics_t asn_SPC_loggingInterval_specs_12 = {
	asn_MAP_loggingInterval_value2enum_12,	/* "tag" => N; sorted by tag */
	asn_MAP_loggingInterval_enum2value_12,	/* N => "tag"; sorted by N */
	8,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static ber_tlv_tag_t asn_DEF_loggingInterval_tags_12[] = {
	(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_loggingInterval_12 = {
	"loggingInterval",
	"loggingInterval",
	loggingInterval_12_free,
	loggingInterval_12_print,
	loggingInterval_12_constraint,
	loggingInterval_12_decode_ber,
	loggingInterval_12_encode_der,
	loggingInterval_12_decode_xer,
	loggingInterval_12_encode_xer,
	loggingInterval_12_decode_uper,
	loggingInterval_12_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_loggingInterval_tags_12,
	sizeof(asn_DEF_loggingInterval_tags_12)
		/sizeof(asn_DEF_loggingInterval_tags_12[0]) - 1, /* 1 */
	asn_DEF_loggingInterval_tags_12,	/* Same as above */
	sizeof(asn_DEF_loggingInterval_tags_12)
		/sizeof(asn_DEF_loggingInterval_tags_12[0]), /* 2 */
	&asn_PER_type_loggingInterval_constr_12,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_loggingInterval_specs_12	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_traceReference_r10_21[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct LoggedMeasurementsConfigurationInfo__traceReference_r10, plmn_Identity),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PLMN_Identity,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"plmn-Identity"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct LoggedMeasurementsConfigurationInfo__traceReference_r10, traceId),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OCTET_STRING,
		memb_traceId_constraint_21,
		&asn_PER_memb_traceId_constr_23,
		0,
		"traceId"
		},
};
static ber_tlv_tag_t asn_DEF_traceReference_r10_tags_21[] = {
	(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_traceReference_r10_tag2el_21[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* plmn-Identity at 25275 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* traceId at 25276 */
};
static asn_SEQUENCE_specifics_t asn_SPC_traceReference_r10_specs_21 = {
	sizeof(struct LoggedMeasurementsConfigurationInfo__traceReference_r10),
	offsetof(struct LoggedMeasurementsConfigurationInfo__traceReference_r10, _asn_ctx),
	asn_MAP_traceReference_r10_tag2el_21,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_traceReference_r10_21 = {
	"traceReference-r10",
	"traceReference-r10",
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
	asn_DEF_traceReference_r10_tags_21,
	sizeof(asn_DEF_traceReference_r10_tags_21)
		/sizeof(asn_DEF_traceReference_r10_tags_21[0]) - 1, /* 1 */
	asn_DEF_traceReference_r10_tags_21,	/* Same as above */
	sizeof(asn_DEF_traceReference_r10_tags_21)
		/sizeof(asn_DEF_traceReference_r10_tags_21[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_traceReference_r10_21,
	2,	/* Elements count */
	&asn_SPC_traceReference_r10_specs_21	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_cellIDList_26[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (3 << 2)),
		0,
		&asn_DEF_CellIdentity,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		""
		},
};
static ber_tlv_tag_t asn_DEF_cellIDList_tags_26[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_cellIDList_specs_26 = {
	sizeof(struct LoggedMeasurementsConfigurationInfo__areaConfiguration__cellIDList),
	offsetof(struct LoggedMeasurementsConfigurationInfo__areaConfiguration__cellIDList, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_cellIDList_26 = {
	"cellIDList",
	"cellIDList",
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
	asn_DEF_cellIDList_tags_26,
	sizeof(asn_DEF_cellIDList_tags_26)
		/sizeof(asn_DEF_cellIDList_tags_26[0]) - 1, /* 1 */
	asn_DEF_cellIDList_tags_26,	/* Same as above */
	sizeof(asn_DEF_cellIDList_tags_26)
		/sizeof(asn_DEF_cellIDList_tags_26[0]), /* 2 */
	&asn_PER_type_cellIDList_constr_26,
	asn_MBR_cellIDList_26,
	1,	/* Single element */
	&asn_SPC_cellIDList_specs_26	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_locationAreaList_28[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_LAI,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		""
		},
};
static ber_tlv_tag_t asn_DEF_locationAreaList_tags_28[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_locationAreaList_specs_28 = {
	sizeof(struct LoggedMeasurementsConfigurationInfo__areaConfiguration__locationAreaList),
	offsetof(struct LoggedMeasurementsConfigurationInfo__areaConfiguration__locationAreaList, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_locationAreaList_28 = {
	"locationAreaList",
	"locationAreaList",
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
	asn_DEF_locationAreaList_tags_28,
	sizeof(asn_DEF_locationAreaList_tags_28)
		/sizeof(asn_DEF_locationAreaList_tags_28[0]) - 1, /* 1 */
	asn_DEF_locationAreaList_tags_28,	/* Same as above */
	sizeof(asn_DEF_locationAreaList_tags_28)
		/sizeof(asn_DEF_locationAreaList_tags_28[0]), /* 2 */
	&asn_PER_type_locationAreaList_constr_28,
	asn_MBR_locationAreaList_28,
	1,	/* Single element */
	&asn_SPC_locationAreaList_specs_28	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_routingAreaList_30[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_RAI,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		""
		},
};
static ber_tlv_tag_t asn_DEF_routingAreaList_tags_30[] = {
	(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_routingAreaList_specs_30 = {
	sizeof(struct LoggedMeasurementsConfigurationInfo__areaConfiguration__routingAreaList),
	offsetof(struct LoggedMeasurementsConfigurationInfo__areaConfiguration__routingAreaList, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_routingAreaList_30 = {
	"routingAreaList",
	"routingAreaList",
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
	asn_DEF_routingAreaList_tags_30,
	sizeof(asn_DEF_routingAreaList_tags_30)
		/sizeof(asn_DEF_routingAreaList_tags_30[0]) - 1, /* 1 */
	asn_DEF_routingAreaList_tags_30,	/* Same as above */
	sizeof(asn_DEF_routingAreaList_tags_30)
		/sizeof(asn_DEF_routingAreaList_tags_30[0]), /* 2 */
	&asn_PER_type_routingAreaList_constr_30,
	asn_MBR_routingAreaList_30,
	1,	/* Single element */
	&asn_SPC_routingAreaList_specs_30	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_areaConfiguration_25[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct LoggedMeasurementsConfigurationInfo__areaConfiguration, choice.cellIDList),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_cellIDList_26,
		memb_cellIDList_constraint_25,
		&asn_PER_memb_cellIDList_constr_26,
		0,
		"cellIDList"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct LoggedMeasurementsConfigurationInfo__areaConfiguration, choice.locationAreaList),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_locationAreaList_28,
		memb_locationAreaList_constraint_25,
		&asn_PER_memb_locationAreaList_constr_28,
		0,
		"locationAreaList"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct LoggedMeasurementsConfigurationInfo__areaConfiguration, choice.routingAreaList),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		0,
		&asn_DEF_routingAreaList_30,
		memb_routingAreaList_constraint_25,
		&asn_PER_memb_routingAreaList_constr_30,
		0,
		"routingAreaList"
		},
};
static asn_TYPE_tag2member_t asn_MAP_areaConfiguration_tag2el_25[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* cellIDList at 25281 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* locationAreaList at 25283 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* routingAreaList at 25286 */
};
static asn_CHOICE_specifics_t asn_SPC_areaConfiguration_specs_25 = {
	sizeof(struct LoggedMeasurementsConfigurationInfo__areaConfiguration),
	offsetof(struct LoggedMeasurementsConfigurationInfo__areaConfiguration, _asn_ctx),
	offsetof(struct LoggedMeasurementsConfigurationInfo__areaConfiguration, present),
	sizeof(((struct LoggedMeasurementsConfigurationInfo__areaConfiguration *)0)->present),
	asn_MAP_areaConfiguration_tag2el_25,
	3,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_areaConfiguration_25 = {
	"areaConfiguration",
	"areaConfiguration",
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
	&asn_PER_type_areaConfiguration_constr_25,
	asn_MBR_areaConfiguration_25,
	3,	/* Elements count */
	&asn_SPC_areaConfiguration_specs_25	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_LoggedMeasurementsConfigurationInfo_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct LoggedMeasurementsConfigurationInfo, absoluteTimeInfo),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BIT_STRING,
		memb_absoluteTimeInfo_constraint_1,
		&asn_PER_memb_absoluteTimeInfo_constr_2,
		0,
		"absoluteTimeInfo"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct LoggedMeasurementsConfigurationInfo, loggingDuration),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_loggingDuration_3,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"loggingDuration"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct LoggedMeasurementsConfigurationInfo, loggingInterval),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_loggingInterval_12,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"loggingInterval"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct LoggedMeasurementsConfigurationInfo, traceReference_r10),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		0,
		&asn_DEF_traceReference_r10_21,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"traceReference-r10"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct LoggedMeasurementsConfigurationInfo, traceRecordingSession),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OCTET_STRING,
		memb_traceRecordingSession_constraint_1,
		&asn_PER_memb_traceRecordingSession_constr_24,
		0,
		"traceRecordingSession"
		},
	{ ATF_POINTER, 1, offsetof(struct LoggedMeasurementsConfigurationInfo, areaConfiguration),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_areaConfiguration_25,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"areaConfiguration"
		},
};
static int asn_MAP_LoggedMeasurementsConfigurationInfo_oms_1[] = { 5 };
static ber_tlv_tag_t asn_DEF_LoggedMeasurementsConfigurationInfo_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_LoggedMeasurementsConfigurationInfo_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* absoluteTimeInfo at 25271 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* loggingDuration at 25272 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* loggingInterval at 25273 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* traceReference-r10 at 25275 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* traceRecordingSession at 25278 */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 } /* areaConfiguration at 25281 */
};
static asn_SEQUENCE_specifics_t asn_SPC_LoggedMeasurementsConfigurationInfo_specs_1 = {
	sizeof(struct LoggedMeasurementsConfigurationInfo),
	offsetof(struct LoggedMeasurementsConfigurationInfo, _asn_ctx),
	asn_MAP_LoggedMeasurementsConfigurationInfo_tag2el_1,
	6,	/* Count of tags in the map */
	asn_MAP_LoggedMeasurementsConfigurationInfo_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_LoggedMeasurementsConfigurationInfo = {
	"LoggedMeasurementsConfigurationInfo",
	"LoggedMeasurementsConfigurationInfo",
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
	asn_DEF_LoggedMeasurementsConfigurationInfo_tags_1,
	sizeof(asn_DEF_LoggedMeasurementsConfigurationInfo_tags_1)
		/sizeof(asn_DEF_LoggedMeasurementsConfigurationInfo_tags_1[0]), /* 1 */
	asn_DEF_LoggedMeasurementsConfigurationInfo_tags_1,	/* Same as above */
	sizeof(asn_DEF_LoggedMeasurementsConfigurationInfo_tags_1)
		/sizeof(asn_DEF_LoggedMeasurementsConfigurationInfo_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_LoggedMeasurementsConfigurationInfo_1,
	6,	/* Elements count */
	&asn_SPC_LoggedMeasurementsConfigurationInfo_specs_1	/* Additional specs */
};


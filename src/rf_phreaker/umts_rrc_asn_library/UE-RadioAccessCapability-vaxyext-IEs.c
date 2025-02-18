/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/UE-RadioAccessCapability-vaxyext-IEs.h"

static int
supportOfMUMIMO_6_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
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
supportOfMUMIMO_6_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
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
supportOfMUMIMO_6_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	supportOfMUMIMO_6_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

static int
supportOfMUMIMO_6_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	supportOfMUMIMO_6_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

static asn_dec_rval_t
supportOfMUMIMO_6_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	supportOfMUMIMO_6_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

static asn_enc_rval_t
supportOfMUMIMO_6_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	supportOfMUMIMO_6_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

static asn_dec_rval_t
supportOfMUMIMO_6_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	supportOfMUMIMO_6_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

static asn_enc_rval_t
supportOfMUMIMO_6_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	supportOfMUMIMO_6_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

static asn_dec_rval_t
supportOfMUMIMO_6_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	supportOfMUMIMO_6_inherit_TYPE_descriptor(td);
	return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static asn_enc_rval_t
supportOfMUMIMO_6_encode_uper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	supportOfMUMIMO_6_inherit_TYPE_descriptor(td);
	return td->uper_encoder(td, constraints, structure, per_out);
}

static int
supportForDualCellMimoInDifferentBands_11_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
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
supportForDualCellMimoInDifferentBands_11_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
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
supportForDualCellMimoInDifferentBands_11_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	supportForDualCellMimoInDifferentBands_11_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

static int
supportForDualCellMimoInDifferentBands_11_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	supportForDualCellMimoInDifferentBands_11_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

static asn_dec_rval_t
supportForDualCellMimoInDifferentBands_11_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	supportForDualCellMimoInDifferentBands_11_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

static asn_enc_rval_t
supportForDualCellMimoInDifferentBands_11_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	supportForDualCellMimoInDifferentBands_11_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

static asn_dec_rval_t
supportForDualCellMimoInDifferentBands_11_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	supportForDualCellMimoInDifferentBands_11_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

static asn_enc_rval_t
supportForDualCellMimoInDifferentBands_11_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	supportForDualCellMimoInDifferentBands_11_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

static asn_dec_rval_t
supportForDualCellMimoInDifferentBands_11_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	supportForDualCellMimoInDifferentBands_11_inherit_TYPE_descriptor(td);
	return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static asn_enc_rval_t
supportForDualCellMimoInDifferentBands_11_encode_uper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	supportForDualCellMimoInDifferentBands_11_inherit_TYPE_descriptor(td);
	return td->uper_encoder(td, constraints, structure, per_out);
}

static asn_per_constraints_t asn_PER_type_supportOfMUMIMO_constr_6 = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_supportForDualCellMimoInDifferentBands_constr_11 = {
	{ APC_CONSTRAINED,	 0,  0,  0,  0 }	/* (0..0) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_INTEGER_enum_map_t asn_MAP_supportOfMUMIMO_value2enum_6[] = {
	{ 0,	2,	"uL" },
	{ 1,	7,	"uLandDL" }
};
static unsigned int asn_MAP_supportOfMUMIMO_enum2value_6[] = {
	0,	/* uL(0) */
	1	/* uLandDL(1) */
};
static asn_INTEGER_specifics_t asn_SPC_supportOfMUMIMO_specs_6 = {
	asn_MAP_supportOfMUMIMO_value2enum_6,	/* "tag" => N; sorted by tag */
	asn_MAP_supportOfMUMIMO_enum2value_6,	/* N => "tag"; sorted by N */
	2,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static ber_tlv_tag_t asn_DEF_supportOfMUMIMO_tags_6[] = {
	(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_supportOfMUMIMO_6 = {
	"supportOfMUMIMO",
	"supportOfMUMIMO",
	supportOfMUMIMO_6_free,
	supportOfMUMIMO_6_print,
	supportOfMUMIMO_6_constraint,
	supportOfMUMIMO_6_decode_ber,
	supportOfMUMIMO_6_encode_der,
	supportOfMUMIMO_6_decode_xer,
	supportOfMUMIMO_6_encode_xer,
	supportOfMUMIMO_6_decode_uper,
	supportOfMUMIMO_6_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_supportOfMUMIMO_tags_6,
	sizeof(asn_DEF_supportOfMUMIMO_tags_6)
		/sizeof(asn_DEF_supportOfMUMIMO_tags_6[0]) - 1, /* 1 */
	asn_DEF_supportOfMUMIMO_tags_6,	/* Same as above */
	sizeof(asn_DEF_supportOfMUMIMO_tags_6)
		/sizeof(asn_DEF_supportOfMUMIMO_tags_6[0]), /* 2 */
	&asn_PER_type_supportOfMUMIMO_constr_6,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_supportOfMUMIMO_specs_6	/* Additional specs */
};

static asn_INTEGER_enum_map_t asn_MAP_supportForDualCellMimoInDifferentBands_value2enum_11[] = {
	{ 0,	4,	"true" }
};
static unsigned int asn_MAP_supportForDualCellMimoInDifferentBands_enum2value_11[] = {
	0	/* true(0) */
};
static asn_INTEGER_specifics_t asn_SPC_supportForDualCellMimoInDifferentBands_specs_11 = {
	asn_MAP_supportForDualCellMimoInDifferentBands_value2enum_11,	/* "tag" => N; sorted by tag */
	asn_MAP_supportForDualCellMimoInDifferentBands_enum2value_11,	/* N => "tag"; sorted by N */
	1,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static ber_tlv_tag_t asn_DEF_supportForDualCellMimoInDifferentBands_tags_11[] = {
	(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_supportForDualCellMimoInDifferentBands_11 = {
	"supportForDualCellMimoInDifferentBands",
	"supportForDualCellMimoInDifferentBands",
	supportForDualCellMimoInDifferentBands_11_free,
	supportForDualCellMimoInDifferentBands_11_print,
	supportForDualCellMimoInDifferentBands_11_constraint,
	supportForDualCellMimoInDifferentBands_11_decode_ber,
	supportForDualCellMimoInDifferentBands_11_encode_der,
	supportForDualCellMimoInDifferentBands_11_decode_xer,
	supportForDualCellMimoInDifferentBands_11_encode_xer,
	supportForDualCellMimoInDifferentBands_11_decode_uper,
	supportForDualCellMimoInDifferentBands_11_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_supportForDualCellMimoInDifferentBands_tags_11,
	sizeof(asn_DEF_supportForDualCellMimoInDifferentBands_tags_11)
		/sizeof(asn_DEF_supportForDualCellMimoInDifferentBands_tags_11[0]) - 1, /* 1 */
	asn_DEF_supportForDualCellMimoInDifferentBands_tags_11,	/* Same as above */
	sizeof(asn_DEF_supportForDualCellMimoInDifferentBands_tags_11)
		/sizeof(asn_DEF_supportForDualCellMimoInDifferentBands_tags_11[0]), /* 2 */
	&asn_PER_type_supportForDualCellMimoInDifferentBands_constr_11,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_supportForDualCellMimoInDifferentBands_specs_11	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_UE_RadioAccessCapability_vaxyext_IEs_1[] = {
	{ ATF_POINTER, 1, offsetof(struct UE_RadioAccessCapability_vaxyext_IEs, supportedCarrierCombinationList),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SupportedCarrierCombinationList,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"supportedCarrierCombinationList"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UE_RadioAccessCapability_vaxyext_IEs, physicalChannelCapability),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PhysicalChannelCapability_vaxyext,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"physicalChannelCapability"
		},
	{ ATF_POINTER, 6, offsetof(struct UE_RadioAccessCapability_vaxyext_IEs, rlc_Capability),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RLC_Capability_vaxyext,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"rlc-Capability"
		},
	{ ATF_POINTER, 5, offsetof(struct UE_RadioAccessCapability_vaxyext_IEs, measurementCapability),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MeasurementCapability_vaxyext,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"measurementCapability"
		},
	{ ATF_POINTER, 4, offsetof(struct UE_RadioAccessCapability_vaxyext_IEs, supportOfMUMIMO),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_supportOfMUMIMO_6,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"supportOfMUMIMO"
		},
	{ ATF_POINTER, 3, offsetof(struct UE_RadioAccessCapability_vaxyext_IEs, ue_RadioAccessCapabBandFDDList4),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UE_RadioAccessCapabBandFDDList4,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ue-RadioAccessCapabBandFDDList4"
		},
	{ ATF_POINTER, 2, offsetof(struct UE_RadioAccessCapability_vaxyext_IEs, ue_BasedNetworkPerformanceMeasurementsParameters),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UE_BasedNetworkPerformanceMeasurementsParameters,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ue-BasedNetworkPerformanceMeasurementsParameters"
		},
	{ ATF_POINTER, 1, offsetof(struct UE_RadioAccessCapability_vaxyext_IEs, supportForDualCellMimoInDifferentBands),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_supportForDualCellMimoInDifferentBands_11,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"supportForDualCellMimoInDifferentBands"
		},
};
static int asn_MAP_UE_RadioAccessCapability_vaxyext_IEs_oms_1[] = { 0, 2, 3, 4, 5, 6, 7 };
static ber_tlv_tag_t asn_DEF_UE_RadioAccessCapability_vaxyext_IEs_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_UE_RadioAccessCapability_vaxyext_IEs_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* supportedCarrierCombinationList at 12963 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* physicalChannelCapability at 12964 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* rlc-Capability at 12965 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* measurementCapability at 12966 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* supportOfMUMIMO at 12967 */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* ue-RadioAccessCapabBandFDDList4 at 12969 */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* ue-BasedNetworkPerformanceMeasurementsParameters at 12971 */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 } /* supportForDualCellMimoInDifferentBands at 12972 */
};
static asn_SEQUENCE_specifics_t asn_SPC_UE_RadioAccessCapability_vaxyext_IEs_specs_1 = {
	sizeof(struct UE_RadioAccessCapability_vaxyext_IEs),
	offsetof(struct UE_RadioAccessCapability_vaxyext_IEs, _asn_ctx),
	asn_MAP_UE_RadioAccessCapability_vaxyext_IEs_tag2el_1,
	8,	/* Count of tags in the map */
	asn_MAP_UE_RadioAccessCapability_vaxyext_IEs_oms_1,	/* Optional members */
	7, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_UE_RadioAccessCapability_vaxyext_IEs = {
	"UE-RadioAccessCapability-vaxyext-IEs",
	"UE-RadioAccessCapability-vaxyext-IEs",
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
	asn_DEF_UE_RadioAccessCapability_vaxyext_IEs_tags_1,
	sizeof(asn_DEF_UE_RadioAccessCapability_vaxyext_IEs_tags_1)
		/sizeof(asn_DEF_UE_RadioAccessCapability_vaxyext_IEs_tags_1[0]), /* 1 */
	asn_DEF_UE_RadioAccessCapability_vaxyext_IEs_tags_1,	/* Same as above */
	sizeof(asn_DEF_UE_RadioAccessCapability_vaxyext_IEs_tags_1)
		/sizeof(asn_DEF_UE_RadioAccessCapability_vaxyext_IEs_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_UE_RadioAccessCapability_vaxyext_IEs_1,
	8,	/* Elements count */
	&asn_SPC_UE_RadioAccessCapability_vaxyext_IEs_specs_1	/* Additional specs */
};


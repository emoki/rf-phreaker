/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/ProtocolErrorCause.h"

int
ProtocolErrorCause_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
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
ProtocolErrorCause_1_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
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

void
ProtocolErrorCause_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	ProtocolErrorCause_1_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

int
ProtocolErrorCause_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	ProtocolErrorCause_1_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

asn_dec_rval_t
ProtocolErrorCause_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	ProtocolErrorCause_1_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

asn_enc_rval_t
ProtocolErrorCause_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	ProtocolErrorCause_1_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

asn_dec_rval_t
ProtocolErrorCause_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	ProtocolErrorCause_1_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

asn_enc_rval_t
ProtocolErrorCause_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	ProtocolErrorCause_1_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

asn_dec_rval_t
ProtocolErrorCause_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	ProtocolErrorCause_1_inherit_TYPE_descriptor(td);
	return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

asn_enc_rval_t
ProtocolErrorCause_encode_uper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	ProtocolErrorCause_1_inherit_TYPE_descriptor(td);
	return td->uper_encoder(td, constraints, structure, per_out);
}

static asn_per_constraints_t asn_PER_type_ProtocolErrorCause_constr_1 = {
	{ APC_CONSTRAINED,	 3,  3,  0,  7 }	/* (0..7) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_INTEGER_enum_map_t asn_MAP_ProtocolErrorCause_value2enum_1[] = {
	{ 0,	29,	"asn1-ViolationOrEncodingError" },
	{ 1,	22,	"messageTypeNonexistent" },
	{ 2,	37,	"messageNotCompatibleWithReceiverState" },
	{ 3,	23,	"ie-ValueNotComprehended" },
	{ 4,	25,	"informationElementMissing" },
	{ 5,	31,	"messageExtensionNotComprehended" },
	{ 6,	6,	"spare2" },
	{ 7,	6,	"spare1" }
};
static unsigned int asn_MAP_ProtocolErrorCause_enum2value_1[] = {
	0,	/* asn1-ViolationOrEncodingError(0) */
	3,	/* ie-ValueNotComprehended(3) */
	4,	/* informationElementMissing(4) */
	5,	/* messageExtensionNotComprehended(5) */
	2,	/* messageNotCompatibleWithReceiverState(2) */
	1,	/* messageTypeNonexistent(1) */
	7,	/* spare1(7) */
	6	/* spare2(6) */
};
static asn_INTEGER_specifics_t asn_SPC_ProtocolErrorCause_specs_1 = {
	asn_MAP_ProtocolErrorCause_value2enum_1,	/* "tag" => N; sorted by tag */
	asn_MAP_ProtocolErrorCause_enum2value_1,	/* N => "tag"; sorted by N */
	8,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static ber_tlv_tag_t asn_DEF_ProtocolErrorCause_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
asn_TYPE_descriptor_t asn_DEF_ProtocolErrorCause = {
	"ProtocolErrorCause",
	"ProtocolErrorCause",
	ProtocolErrorCause_free,
	ProtocolErrorCause_print,
	ProtocolErrorCause_constraint,
	ProtocolErrorCause_decode_ber,
	ProtocolErrorCause_encode_der,
	ProtocolErrorCause_decode_xer,
	ProtocolErrorCause_encode_xer,
	ProtocolErrorCause_decode_uper,
	ProtocolErrorCause_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_ProtocolErrorCause_tags_1,
	sizeof(asn_DEF_ProtocolErrorCause_tags_1)
		/sizeof(asn_DEF_ProtocolErrorCause_tags_1[0]), /* 1 */
	asn_DEF_ProtocolErrorCause_tags_1,	/* Same as above */
	sizeof(asn_DEF_ProtocolErrorCause_tags_1)
		/sizeof(asn_DEF_ProtocolErrorCause_tags_1[0]), /* 1 */
	&asn_PER_type_ProtocolErrorCause_constr_1,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_ProtocolErrorCause_specs_1	/* Additional specs */
};


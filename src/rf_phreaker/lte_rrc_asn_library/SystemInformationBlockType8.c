/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#include "rf_phreaker/lte_rrc_asn_library/SystemInformationBlockType8.h"

static int
memb_longCodeState1XRTT_constraint_7(asn_TYPE_descriptor_t *td, const void *sptr,
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
	
	if((size == 42)) {
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
csfb_DualRxTxSupport_r10_18_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
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
csfb_DualRxTxSupport_r10_18_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
	td->free_struct    = asn_DEF_NativeEnumerated.free_struct;
	td->print_struct   = asn_DEF_NativeEnumerated.print_struct;
	td->check_constraints = asn_DEF_NativeEnumerated.check_constraints;
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
csfb_DualRxTxSupport_r10_18_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	csfb_DualRxTxSupport_r10_18_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

static int
csfb_DualRxTxSupport_r10_18_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	csfb_DualRxTxSupport_r10_18_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

static asn_dec_rval_t
csfb_DualRxTxSupport_r10_18_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	csfb_DualRxTxSupport_r10_18_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

static asn_enc_rval_t
csfb_DualRxTxSupport_r10_18_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	csfb_DualRxTxSupport_r10_18_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

static asn_dec_rval_t
csfb_DualRxTxSupport_r10_18_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	csfb_DualRxTxSupport_r10_18_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

static asn_enc_rval_t
csfb_DualRxTxSupport_r10_18_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	csfb_DualRxTxSupport_r10_18_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

static asn_dec_rval_t
csfb_DualRxTxSupport_r10_18_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	csfb_DualRxTxSupport_r10_18_inherit_TYPE_descriptor(td);
	return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static asn_enc_rval_t
csfb_DualRxTxSupport_r10_18_encode_uper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	csfb_DualRxTxSupport_r10_18_inherit_TYPE_descriptor(td);
	return td->uper_encoder(td, constraints, structure, per_out);
}

static int
memb_searchWindowSize_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
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

static asn_per_constraints_t asn_PER_memb_longCodeState1XRTT_constr_9 GCC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 0,  0,  42,  42 }	/* (SIZE(42..42)) */,
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_csfb_DualRxTxSupport_r10_constr_18 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 0,  0,  0,  0 }	/* (0..0) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_searchWindowSize_constr_3 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 4,  4,  0,  15 }	/* (0..15) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_parametersHRPD_4[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SystemInformationBlockType8__parametersHRPD, preRegistrationInfoHRPD),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PreRegistrationInfoHRPD,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"preRegistrationInfoHRPD"
		},
	{ ATF_POINTER, 1, offsetof(struct SystemInformationBlockType8__parametersHRPD, cellReselectionParametersHRPD),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CellReselectionParametersCDMA2000,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"cellReselectionParametersHRPD"
		},
};
static int asn_MAP_parametersHRPD_oms_4[] = { 1 };
static ber_tlv_tag_t asn_DEF_parametersHRPD_tags_4[] = {
	(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_parametersHRPD_tag2el_4[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* preRegistrationInfoHRPD */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* cellReselectionParametersHRPD */
};
static asn_SEQUENCE_specifics_t asn_SPC_parametersHRPD_specs_4 = {
	sizeof(struct SystemInformationBlockType8__parametersHRPD),
	offsetof(struct SystemInformationBlockType8__parametersHRPD, _asn_ctx),
	asn_MAP_parametersHRPD_tag2el_4,
	2,	/* Count of tags in the map */
	asn_MAP_parametersHRPD_oms_4,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_parametersHRPD_4 = {
	"parametersHRPD",
	"parametersHRPD",
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
	asn_DEF_parametersHRPD_tags_4,
	sizeof(asn_DEF_parametersHRPD_tags_4)
		/sizeof(asn_DEF_parametersHRPD_tags_4[0]) - 1, /* 1 */
	asn_DEF_parametersHRPD_tags_4,	/* Same as above */
	sizeof(asn_DEF_parametersHRPD_tags_4)
		/sizeof(asn_DEF_parametersHRPD_tags_4[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_parametersHRPD_4,
	2,	/* Elements count */
	&asn_SPC_parametersHRPD_specs_4	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_parameters1XRTT_7[] = {
	{ ATF_POINTER, 3, offsetof(struct SystemInformationBlockType8__parameters1XRTT, csfb_RegistrationParam1XRTT),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CSFB_RegistrationParam1XRTT,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"csfb-RegistrationParam1XRTT"
		},
	{ ATF_POINTER, 2, offsetof(struct SystemInformationBlockType8__parameters1XRTT, longCodeState1XRTT),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BIT_STRING,
		memb_longCodeState1XRTT_constraint_7,
		&asn_PER_memb_longCodeState1XRTT_constr_9,
		0,
		"longCodeState1XRTT"
		},
	{ ATF_POINTER, 1, offsetof(struct SystemInformationBlockType8__parameters1XRTT, cellReselectionParameters1XRTT),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CellReselectionParametersCDMA2000,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"cellReselectionParameters1XRTT"
		},
};
static int asn_MAP_parameters1XRTT_oms_7[] = { 0, 1, 2 };
static ber_tlv_tag_t asn_DEF_parameters1XRTT_tags_7[] = {
	(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_parameters1XRTT_tag2el_7[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* csfb-RegistrationParam1XRTT */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* longCodeState1XRTT */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* cellReselectionParameters1XRTT */
};
static asn_SEQUENCE_specifics_t asn_SPC_parameters1XRTT_specs_7 = {
	sizeof(struct SystemInformationBlockType8__parameters1XRTT),
	offsetof(struct SystemInformationBlockType8__parameters1XRTT, _asn_ctx),
	asn_MAP_parameters1XRTT_tag2el_7,
	3,	/* Count of tags in the map */
	asn_MAP_parameters1XRTT_oms_7,	/* Optional members */
	3, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_parameters1XRTT_7 = {
	"parameters1XRTT",
	"parameters1XRTT",
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
	asn_DEF_parameters1XRTT_tags_7,
	sizeof(asn_DEF_parameters1XRTT_tags_7)
		/sizeof(asn_DEF_parameters1XRTT_tags_7[0]) - 1, /* 1 */
	asn_DEF_parameters1XRTT_tags_7,	/* Same as above */
	sizeof(asn_DEF_parameters1XRTT_tags_7)
		/sizeof(asn_DEF_parameters1XRTT_tags_7[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_parameters1XRTT_7,
	3,	/* Elements count */
	&asn_SPC_parameters1XRTT_specs_7	/* Additional specs */
};

static asn_INTEGER_enum_map_t asn_MAP_csfb_DualRxTxSupport_r10_value2enum_18[] = {
	{ 0,	4,	"true" }
};
static unsigned int asn_MAP_csfb_DualRxTxSupport_r10_enum2value_18[] = {
	0	/* true(0) */
};
static asn_INTEGER_specifics_t asn_SPC_csfb_DualRxTxSupport_r10_specs_18 = {
	asn_MAP_csfb_DualRxTxSupport_r10_value2enum_18,	/* "tag" => N; sorted by tag */
	asn_MAP_csfb_DualRxTxSupport_r10_enum2value_18,	/* N => "tag"; sorted by N */
	1,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static ber_tlv_tag_t asn_DEF_csfb_DualRxTxSupport_r10_tags_18[] = {
	(ASN_TAG_CLASS_CONTEXT | (10 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_csfb_DualRxTxSupport_r10_18 = {
	"csfb-DualRxTxSupport-r10",
	"csfb-DualRxTxSupport-r10",
	csfb_DualRxTxSupport_r10_18_free,
	csfb_DualRxTxSupport_r10_18_print,
	csfb_DualRxTxSupport_r10_18_constraint,
	csfb_DualRxTxSupport_r10_18_decode_ber,
	csfb_DualRxTxSupport_r10_18_encode_der,
	csfb_DualRxTxSupport_r10_18_decode_xer,
	csfb_DualRxTxSupport_r10_18_encode_xer,
	csfb_DualRxTxSupport_r10_18_decode_uper,
	csfb_DualRxTxSupport_r10_18_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_csfb_DualRxTxSupport_r10_tags_18,
	sizeof(asn_DEF_csfb_DualRxTxSupport_r10_tags_18)
		/sizeof(asn_DEF_csfb_DualRxTxSupport_r10_tags_18[0]) - 1, /* 1 */
	asn_DEF_csfb_DualRxTxSupport_r10_tags_18,	/* Same as above */
	sizeof(asn_DEF_csfb_DualRxTxSupport_r10_tags_18)
		/sizeof(asn_DEF_csfb_DualRxTxSupport_r10_tags_18[0]), /* 2 */
	&asn_PER_type_csfb_DualRxTxSupport_r10_constr_18,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_csfb_DualRxTxSupport_r10_specs_18	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_SystemInformationBlockType8_1[] = {
	{ ATF_POINTER, 12, offsetof(struct SystemInformationBlockType8, systemTimeInfo),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SystemTimeInfoCDMA2000,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"systemTimeInfo"
		},
	{ ATF_POINTER, 11, offsetof(struct SystemInformationBlockType8, searchWindowSize),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		memb_searchWindowSize_constraint_1,
		&asn_PER_memb_searchWindowSize_constr_3,
		0,
		"searchWindowSize"
		},
	{ ATF_POINTER, 10, offsetof(struct SystemInformationBlockType8, parametersHRPD),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		0,
		&asn_DEF_parametersHRPD_4,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"parametersHRPD"
		},
	{ ATF_POINTER, 9, offsetof(struct SystemInformationBlockType8, parameters1XRTT),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		0,
		&asn_DEF_parameters1XRTT_7,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"parameters1XRTT"
		},
	{ ATF_POINTER, 8, offsetof(struct SystemInformationBlockType8, lateNonCriticalExtension),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OCTET_STRING,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"lateNonCriticalExtension"
		},
	{ ATF_POINTER, 7, offsetof(struct SystemInformationBlockType8, csfb_SupportForDualRxUEs_r9),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"csfb-SupportForDualRxUEs-r9"
		},
	{ ATF_POINTER, 6, offsetof(struct SystemInformationBlockType8, cellReselectionParametersHRPD_v920),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CellReselectionParametersCDMA2000_v920,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"cellReselectionParametersHRPD-v920"
		},
	{ ATF_POINTER, 5, offsetof(struct SystemInformationBlockType8, cellReselectionParameters1XRTT_v920),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CellReselectionParametersCDMA2000_v920,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"cellReselectionParameters1XRTT-v920"
		},
	{ ATF_POINTER, 4, offsetof(struct SystemInformationBlockType8, csfb_RegistrationParam1XRTT_v920),
		(ASN_TAG_CLASS_CONTEXT | (8 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CSFB_RegistrationParam1XRTT_v920,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"csfb-RegistrationParam1XRTT-v920"
		},
	{ ATF_POINTER, 3, offsetof(struct SystemInformationBlockType8, ac_BarringConfig1XRTT_r9),
		(ASN_TAG_CLASS_CONTEXT | (9 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_AC_BarringConfig1XRTT_r9,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ac-BarringConfig1XRTT-r9"
		},
	{ ATF_POINTER, 2, offsetof(struct SystemInformationBlockType8, csfb_DualRxTxSupport_r10),
		(ASN_TAG_CLASS_CONTEXT | (10 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_csfb_DualRxTxSupport_r10_18,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"csfb-DualRxTxSupport-r10"
		},
	{ ATF_POINTER, 1, offsetof(struct SystemInformationBlockType8, sib8_PerPLMN_List_r11),
		(ASN_TAG_CLASS_CONTEXT | (11 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SIB8_PerPLMN_List_r11,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"sib8-PerPLMN-List-r11"
		},
};
static int asn_MAP_SystemInformationBlockType8_oms_1[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
static ber_tlv_tag_t asn_DEF_SystemInformationBlockType8_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_SystemInformationBlockType8_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* systemTimeInfo */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* searchWindowSize */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* parametersHRPD */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* parameters1XRTT */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* lateNonCriticalExtension */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* csfb-SupportForDualRxUEs-r9 */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* cellReselectionParametersHRPD-v920 */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 }, /* cellReselectionParameters1XRTT-v920 */
    { (ASN_TAG_CLASS_CONTEXT | (8 << 2)), 8, 0, 0 }, /* csfb-RegistrationParam1XRTT-v920 */
    { (ASN_TAG_CLASS_CONTEXT | (9 << 2)), 9, 0, 0 }, /* ac-BarringConfig1XRTT-r9 */
    { (ASN_TAG_CLASS_CONTEXT | (10 << 2)), 10, 0, 0 }, /* csfb-DualRxTxSupport-r10 */
    { (ASN_TAG_CLASS_CONTEXT | (11 << 2)), 11, 0, 0 } /* sib8-PerPLMN-List-r11 */
};
static asn_SEQUENCE_specifics_t asn_SPC_SystemInformationBlockType8_specs_1 = {
	sizeof(struct SystemInformationBlockType8),
	offsetof(struct SystemInformationBlockType8, _asn_ctx),
	asn_MAP_SystemInformationBlockType8_tag2el_1,
	12,	/* Count of tags in the map */
	asn_MAP_SystemInformationBlockType8_oms_1,	/* Optional members */
	4, 8,	/* Root/Additions */
	3,	/* Start extensions */
	13	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_SystemInformationBlockType8 = {
	"SystemInformationBlockType8",
	"SystemInformationBlockType8",
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
	asn_DEF_SystemInformationBlockType8_tags_1,
	sizeof(asn_DEF_SystemInformationBlockType8_tags_1)
		/sizeof(asn_DEF_SystemInformationBlockType8_tags_1[0]), /* 1 */
	asn_DEF_SystemInformationBlockType8_tags_1,	/* Same as above */
	sizeof(asn_DEF_SystemInformationBlockType8_tags_1)
		/sizeof(asn_DEF_SystemInformationBlockType8_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_SystemInformationBlockType8_1,
	12,	/* Elements count */
	&asn_SPC_SystemInformationBlockType8_specs_1	/* Additional specs */
};


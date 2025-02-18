/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "PDU-definitions"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/RadioBearerReconfiguration-v6f0ext-IEs.h"

static asn_per_constraints_t asn_PER_type_specificationMode_constr_2 = {
	{ APC_CONSTRAINED,	 0,  0,  0,  0 }	/* (0..0) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_complete_3[] = {
	{ ATF_POINTER, 1, offsetof(struct RadioBearerReconfiguration_v6f0ext_IEs__specificationMode__complete, rab_InformationMBMSPtpList),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RAB_InformationMBMSPtpList,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"rab-InformationMBMSPtpList"
		},
};
static int asn_MAP_complete_oms_3[] = { 0 };
static ber_tlv_tag_t asn_DEF_complete_tags_3[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_complete_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* rab-InformationMBMSPtpList at 5286 */
};
static asn_SEQUENCE_specifics_t asn_SPC_complete_specs_3 = {
	sizeof(struct RadioBearerReconfiguration_v6f0ext_IEs__specificationMode__complete),
	offsetof(struct RadioBearerReconfiguration_v6f0ext_IEs__specificationMode__complete, _asn_ctx),
	asn_MAP_complete_tag2el_3,
	1,	/* Count of tags in the map */
	asn_MAP_complete_oms_3,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_complete_3 = {
	"complete",
	"complete",
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
	asn_DEF_complete_tags_3,
	sizeof(asn_DEF_complete_tags_3)
		/sizeof(asn_DEF_complete_tags_3[0]) - 1, /* 1 */
	asn_DEF_complete_tags_3,	/* Same as above */
	sizeof(asn_DEF_complete_tags_3)
		/sizeof(asn_DEF_complete_tags_3[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_complete_3,
	1,	/* Elements count */
	&asn_SPC_complete_specs_3	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_specificationMode_2[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct RadioBearerReconfiguration_v6f0ext_IEs__specificationMode, choice.complete),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_complete_3,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"complete"
		},
};
static asn_TYPE_tag2member_t asn_MAP_specificationMode_tag2el_2[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* complete at 5286 */
};
static asn_CHOICE_specifics_t asn_SPC_specificationMode_specs_2 = {
	sizeof(struct RadioBearerReconfiguration_v6f0ext_IEs__specificationMode),
	offsetof(struct RadioBearerReconfiguration_v6f0ext_IEs__specificationMode, _asn_ctx),
	offsetof(struct RadioBearerReconfiguration_v6f0ext_IEs__specificationMode, present),
	sizeof(((struct RadioBearerReconfiguration_v6f0ext_IEs__specificationMode *)0)->present),
	asn_MAP_specificationMode_tag2el_2,
	1,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_specificationMode_2 = {
	"specificationMode",
	"specificationMode",
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
	&asn_PER_type_specificationMode_constr_2,
	asn_MBR_specificationMode_2,
	1,	/* Elements count */
	&asn_SPC_specificationMode_specs_2	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_RadioBearerReconfiguration_v6f0ext_IEs_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct RadioBearerReconfiguration_v6f0ext_IEs, specificationMode),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_specificationMode_2,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"specificationMode"
		},
};
static ber_tlv_tag_t asn_DEF_RadioBearerReconfiguration_v6f0ext_IEs_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_RadioBearerReconfiguration_v6f0ext_IEs_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* specificationMode at 5288 */
};
static asn_SEQUENCE_specifics_t asn_SPC_RadioBearerReconfiguration_v6f0ext_IEs_specs_1 = {
	sizeof(struct RadioBearerReconfiguration_v6f0ext_IEs),
	offsetof(struct RadioBearerReconfiguration_v6f0ext_IEs, _asn_ctx),
	asn_MAP_RadioBearerReconfiguration_v6f0ext_IEs_tag2el_1,
	1,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_RadioBearerReconfiguration_v6f0ext_IEs = {
	"RadioBearerReconfiguration-v6f0ext-IEs",
	"RadioBearerReconfiguration-v6f0ext-IEs",
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
	asn_DEF_RadioBearerReconfiguration_v6f0ext_IEs_tags_1,
	sizeof(asn_DEF_RadioBearerReconfiguration_v6f0ext_IEs_tags_1)
		/sizeof(asn_DEF_RadioBearerReconfiguration_v6f0ext_IEs_tags_1[0]), /* 1 */
	asn_DEF_RadioBearerReconfiguration_v6f0ext_IEs_tags_1,	/* Same as above */
	sizeof(asn_DEF_RadioBearerReconfiguration_v6f0ext_IEs_tags_1)
		/sizeof(asn_DEF_RadioBearerReconfiguration_v6f0ext_IEs_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_RadioBearerReconfiguration_v6f0ext_IEs_1,
	1,	/* Elements count */
	&asn_SPC_RadioBearerReconfiguration_v6f0ext_IEs_specs_1	/* Additional specs */
};


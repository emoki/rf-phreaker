/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#include "rf_phreaker/lte_rrc_asn_library/QuantityConfigEUTRA.h"

static int asn_DFL_2_set_4(int set_value, void **sptr) {
	FilterCoefficient_t *st = *sptr;
	
	if(!st) {
		if(!set_value) return -1;	/* Not a default value */
		st = (*sptr = CALLOC(1, sizeof(*st)));
		if(!st) return -1;
	}
	
	if(set_value) {
		/* Install default value 4 */
		*st = 4;
		return 0;
	} else {
		/* Test default value 4 */
		return (*st == 4);
	}
}
static int asn_DFL_3_set_4(int set_value, void **sptr) {
	FilterCoefficient_t *st = *sptr;
	
	if(!st) {
		if(!set_value) return -1;	/* Not a default value */
		st = (*sptr = CALLOC(1, sizeof(*st)));
		if(!st) return -1;
	}
	
	if(set_value) {
		/* Install default value 4 */
		*st = 4;
		return 0;
	} else {
		/* Test default value 4 */
		return (*st == 4);
	}
}
static asn_TYPE_member_t asn_MBR_QuantityConfigEUTRA_1[] = {
	{ ATF_POINTER, 2, offsetof(struct QuantityConfigEUTRA, filterCoefficientRSRP),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_FilterCoefficient,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		asn_DFL_2_set_4,	/* DEFAULT 4 */
		"filterCoefficientRSRP"
		},
	{ ATF_POINTER, 1, offsetof(struct QuantityConfigEUTRA, filterCoefficientRSRQ),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_FilterCoefficient,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		asn_DFL_3_set_4,	/* DEFAULT 4 */
		"filterCoefficientRSRQ"
		},
};
static int asn_MAP_QuantityConfigEUTRA_oms_1[] = { 0, 1 };
static ber_tlv_tag_t asn_DEF_QuantityConfigEUTRA_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_QuantityConfigEUTRA_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* filterCoefficientRSRP */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* filterCoefficientRSRQ */
};
static asn_SEQUENCE_specifics_t asn_SPC_QuantityConfigEUTRA_specs_1 = {
	sizeof(struct QuantityConfigEUTRA),
	offsetof(struct QuantityConfigEUTRA, _asn_ctx),
	asn_MAP_QuantityConfigEUTRA_tag2el_1,
	2,	/* Count of tags in the map */
	asn_MAP_QuantityConfigEUTRA_oms_1,	/* Optional members */
	2, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_QuantityConfigEUTRA = {
	"QuantityConfigEUTRA",
	"QuantityConfigEUTRA",
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
	asn_DEF_QuantityConfigEUTRA_tags_1,
	sizeof(asn_DEF_QuantityConfigEUTRA_tags_1)
		/sizeof(asn_DEF_QuantityConfigEUTRA_tags_1[0]), /* 1 */
	asn_DEF_QuantityConfigEUTRA_tags_1,	/* Same as above */
	sizeof(asn_DEF_QuantityConfigEUTRA_tags_1)
		/sizeof(asn_DEF_QuantityConfigEUTRA_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_QuantityConfigEUTRA_1,
	2,	/* Elements count */
	&asn_SPC_QuantityConfigEUTRA_specs_1	/* Additional specs */
};


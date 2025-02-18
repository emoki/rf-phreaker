/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 * 	`asn1c -fcompound-names -pdu=all`
 */

#include "rf_phreaker/lte_rrc_asn_library/BandClassInfoCDMA2000.h"

static int
memb_threshX_High_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 63)) {
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
memb_threshX_Low_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 63)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_per_constraints_t asn_PER_memb_threshX_High_constr_4 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 6,  6,  0,  63 }	/* (0..63) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_threshX_Low_constr_5 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 6,  6,  0,  63 }	/* (0..63) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_BandClassInfoCDMA2000_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct BandClassInfoCDMA2000, bandClass),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BandclassCDMA2000,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"bandClass"
		},
	{ ATF_POINTER, 1, offsetof(struct BandClassInfoCDMA2000, cellReselectionPriority),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CellReselectionPriority,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"cellReselectionPriority"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct BandClassInfoCDMA2000, threshX_High),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		memb_threshX_High_constraint_1,
		&asn_PER_memb_threshX_High_constr_4,
		0,
		"threshX-High"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct BandClassInfoCDMA2000, threshX_Low),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		memb_threshX_Low_constraint_1,
		&asn_PER_memb_threshX_Low_constr_5,
		0,
		"threshX-Low"
		},
};
static int asn_MAP_BandClassInfoCDMA2000_oms_1[] = { 1 };
static ber_tlv_tag_t asn_DEF_BandClassInfoCDMA2000_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_BandClassInfoCDMA2000_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* bandClass */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* cellReselectionPriority */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* threshX-High */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* threshX-Low */
};
static asn_SEQUENCE_specifics_t asn_SPC_BandClassInfoCDMA2000_specs_1 = {
	sizeof(struct BandClassInfoCDMA2000),
	offsetof(struct BandClassInfoCDMA2000, _asn_ctx),
	asn_MAP_BandClassInfoCDMA2000_tag2el_1,
	4,	/* Count of tags in the map */
	asn_MAP_BandClassInfoCDMA2000_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	3,	/* Start extensions */
	5	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_BandClassInfoCDMA2000 = {
	"BandClassInfoCDMA2000",
	"BandClassInfoCDMA2000",
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
	asn_DEF_BandClassInfoCDMA2000_tags_1,
	sizeof(asn_DEF_BandClassInfoCDMA2000_tags_1)
		/sizeof(asn_DEF_BandClassInfoCDMA2000_tags_1[0]), /* 1 */
	asn_DEF_BandClassInfoCDMA2000_tags_1,	/* Same as above */
	sizeof(asn_DEF_BandClassInfoCDMA2000_tags_1)
		/sizeof(asn_DEF_BandClassInfoCDMA2000_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_BandClassInfoCDMA2000_1,
	4,	/* Elements count */
	&asn_SPC_BandClassInfoCDMA2000_specs_1	/* Additional specs */
};


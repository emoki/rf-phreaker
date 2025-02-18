/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/E-TFCS-Info.h"

static int
memb_reference_Beta_QPSK_List_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
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
memb_reference_Beta_16QAM_List_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
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

static asn_per_constraints_t asn_PER_type_reference_Beta_QPSK_List_constr_2 = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 3,  3,  1,  8 }	/* (SIZE(1..8)) */,
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_reference_Beta_16QAM_List_constr_4 = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 3,  3,  1,  8 }	/* (SIZE(1..8)) */,
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_reference_Beta_QPSK_List_constr_2 = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 3,  3,  1,  8 }	/* (SIZE(1..8)) */,
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_reference_Beta_16QAM_List_constr_4 = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 3,  3,  1,  8 }	/* (SIZE(1..8)) */,
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_reference_Beta_QPSK_List_2[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_Reference_Beta_QPSK,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		""
		},
};
static ber_tlv_tag_t asn_DEF_reference_Beta_QPSK_List_tags_2[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_reference_Beta_QPSK_List_specs_2 = {
	sizeof(struct E_TFCS_Info__reference_Beta_QPSK_List),
	offsetof(struct E_TFCS_Info__reference_Beta_QPSK_List, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_reference_Beta_QPSK_List_2 = {
	"reference-Beta-QPSK-List",
	"reference-Beta-QPSK-List",
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
	asn_DEF_reference_Beta_QPSK_List_tags_2,
	sizeof(asn_DEF_reference_Beta_QPSK_List_tags_2)
		/sizeof(asn_DEF_reference_Beta_QPSK_List_tags_2[0]) - 1, /* 1 */
	asn_DEF_reference_Beta_QPSK_List_tags_2,	/* Same as above */
	sizeof(asn_DEF_reference_Beta_QPSK_List_tags_2)
		/sizeof(asn_DEF_reference_Beta_QPSK_List_tags_2[0]), /* 2 */
	&asn_PER_type_reference_Beta_QPSK_List_constr_2,
	asn_MBR_reference_Beta_QPSK_List_2,
	1,	/* Single element */
	&asn_SPC_reference_Beta_QPSK_List_specs_2	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_reference_Beta_16QAM_List_4[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_Reference_Beta_16QAM,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		""
		},
};
static ber_tlv_tag_t asn_DEF_reference_Beta_16QAM_List_tags_4[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_reference_Beta_16QAM_List_specs_4 = {
	sizeof(struct E_TFCS_Info__reference_Beta_16QAM_List),
	offsetof(struct E_TFCS_Info__reference_Beta_16QAM_List, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_reference_Beta_16QAM_List_4 = {
	"reference-Beta-16QAM-List",
	"reference-Beta-16QAM-List",
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
	asn_DEF_reference_Beta_16QAM_List_tags_4,
	sizeof(asn_DEF_reference_Beta_16QAM_List_tags_4)
		/sizeof(asn_DEF_reference_Beta_16QAM_List_tags_4[0]) - 1, /* 1 */
	asn_DEF_reference_Beta_16QAM_List_tags_4,	/* Same as above */
	sizeof(asn_DEF_reference_Beta_16QAM_List_tags_4)
		/sizeof(asn_DEF_reference_Beta_16QAM_List_tags_4[0]), /* 2 */
	&asn_PER_type_reference_Beta_16QAM_List_constr_4,
	asn_MBR_reference_Beta_16QAM_List_4,
	1,	/* Single element */
	&asn_SPC_reference_Beta_16QAM_List_specs_4	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_E_TFCS_Info_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct E_TFCS_Info, reference_Beta_QPSK_List),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_reference_Beta_QPSK_List_2,
		memb_reference_Beta_QPSK_List_constraint_1,
		&asn_PER_memb_reference_Beta_QPSK_List_constr_2,
		0,
		"reference-Beta-QPSK-List"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct E_TFCS_Info, reference_Beta_16QAM_List),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_reference_Beta_16QAM_List_4,
		memb_reference_Beta_16QAM_List_constraint_1,
		&asn_PER_memb_reference_Beta_16QAM_List_constr_4,
		0,
		"reference-Beta-16QAM-List"
		},
};
static ber_tlv_tag_t asn_DEF_E_TFCS_Info_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_E_TFCS_Info_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* reference-Beta-QPSK-List at 18286 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* reference-Beta-16QAM-List at 18288 */
};
static asn_SEQUENCE_specifics_t asn_SPC_E_TFCS_Info_specs_1 = {
	sizeof(struct E_TFCS_Info),
	offsetof(struct E_TFCS_Info, _asn_ctx),
	asn_MAP_E_TFCS_Info_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_E_TFCS_Info = {
	"E-TFCS-Info",
	"E-TFCS-Info",
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
	asn_DEF_E_TFCS_Info_tags_1,
	sizeof(asn_DEF_E_TFCS_Info_tags_1)
		/sizeof(asn_DEF_E_TFCS_Info_tags_1[0]), /* 1 */
	asn_DEF_E_TFCS_Info_tags_1,	/* Same as above */
	sizeof(asn_DEF_E_TFCS_Info_tags_1)
		/sizeof(asn_DEF_E_TFCS_Info_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_E_TFCS_Info_1,
	2,	/* Elements count */
	&asn_SPC_E_TFCS_Info_specs_1	/* Additional specs */
};


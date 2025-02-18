/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#include <rf_phreaker/umts_rrc_asn_library/asn_internal.h>

#include "rf_phreaker/umts_rrc_asn_library/PollingInfo.h"

static asn_TYPE_member_t asn_MBR_PollingInfo_1[] = {
	{ ATF_POINTER, 4, offsetof(struct PollingInfo, timerPollProhibit),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TimerPollProhibit,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"timerPollProhibit"
		},
	{ ATF_POINTER, 3, offsetof(struct PollingInfo, timerPoll),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TimerPoll,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"timerPoll"
		},
	{ ATF_POINTER, 2, offsetof(struct PollingInfo, poll_PDU),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Poll_PDU,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"poll-PDU"
		},
	{ ATF_POINTER, 1, offsetof(struct PollingInfo, poll_SDU),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Poll_SDU,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"poll-SDU"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct PollingInfo, lastTransmissionPDU_Poll),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"lastTransmissionPDU-Poll"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct PollingInfo, lastRetransmissionPDU_Poll),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"lastRetransmissionPDU-Poll"
		},
	{ ATF_POINTER, 2, offsetof(struct PollingInfo, pollWindow),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PollWindow,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"pollWindow"
		},
	{ ATF_POINTER, 1, offsetof(struct PollingInfo, timerPollPeriodic),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TimerPollPeriodic,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"timerPollPeriodic"
		},
};
static int asn_MAP_PollingInfo_oms_1[] = { 0, 1, 2, 3, 6, 7 };
static ber_tlv_tag_t asn_DEF_PollingInfo_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_PollingInfo_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* timerPollProhibit at 13940 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* timerPoll at 13941 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* poll-PDU at 13942 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* poll-SDU at 13943 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* lastTransmissionPDU-Poll at 13944 */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* lastRetransmissionPDU-Poll at 13945 */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* pollWindow at 13946 */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 } /* timerPollPeriodic at 13947 */
};
static asn_SEQUENCE_specifics_t asn_SPC_PollingInfo_specs_1 = {
	sizeof(struct PollingInfo),
	offsetof(struct PollingInfo, _asn_ctx),
	asn_MAP_PollingInfo_tag2el_1,
	8,	/* Count of tags in the map */
	asn_MAP_PollingInfo_oms_1,	/* Optional members */
	6, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_PollingInfo = {
	"PollingInfo",
	"PollingInfo",
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
	asn_DEF_PollingInfo_tags_1,
	sizeof(asn_DEF_PollingInfo_tags_1)
		/sizeof(asn_DEF_PollingInfo_tags_1[0]), /* 1 */
	asn_DEF_PollingInfo_tags_1,	/* Same as above */
	sizeof(asn_DEF_PollingInfo_tags_1)
		/sizeof(asn_DEF_PollingInfo_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_PollingInfo_1,
	8,	/* Elements count */
	&asn_SPC_PollingInfo_specs_1	/* Additional specs */
};


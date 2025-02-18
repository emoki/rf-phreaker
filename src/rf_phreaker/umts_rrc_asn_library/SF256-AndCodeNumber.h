/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_SF256_AndCodeNumber_H_
#define	_SF256_AndCodeNumber_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/NativeInteger.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum SF256_AndCodeNumber_PR {
	SF256_AndCodeNumber_PR_NOTHING,	/* No components present */
	SF256_AndCodeNumber_PR_sf4,
	SF256_AndCodeNumber_PR_sf8,
	SF256_AndCodeNumber_PR_sf16,
	SF256_AndCodeNumber_PR_sf32,
	SF256_AndCodeNumber_PR_sf64,
	SF256_AndCodeNumber_PR_sf128,
	SF256_AndCodeNumber_PR_sf256
} SF256_AndCodeNumber_PR;

/* SF256-AndCodeNumber */
typedef struct SF256_AndCodeNumber {
	SF256_AndCodeNumber_PR present;
	union SF256_AndCodeNumber_u {
		long	 sf4;
		long	 sf8;
		long	 sf16;
		long	 sf32;
		long	 sf64;
		long	 sf128;
		long	 sf256;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SF256_AndCodeNumber_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SF256_AndCodeNumber;

#ifdef __cplusplus
}
#endif

#endif	/* _SF256_AndCodeNumber_H_ */

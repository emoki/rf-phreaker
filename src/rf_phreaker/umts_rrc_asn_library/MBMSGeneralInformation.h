/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "PDU-definitions"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_MBMSGeneralInformation_H_
#define	_MBMSGeneralInformation_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include "rf_phreaker/umts_rrc_asn_library/MBMS-TimersAndCounters-r6.h"
#include "rf_phreaker/umts_rrc_asn_library/MBMS-MICHConfigurationInfo-r6.h"
#include "rf_phreaker/umts_rrc_asn_library/MBMS-CellGroupIdentity-r6.h"
#include "rf_phreaker/umts_rrc_asn_library/MBMSGeneralInformation-v6b0ext-IEs.h"
#include "rf_phreaker/umts_rrc_asn_library/MBMSGeneralInformation-v770ext-IEs.h"
#include "rf_phreaker/umts_rrc_asn_library/MBMSGeneralInformation-v860ext-IEs.h"
#include "rf_phreaker/umts_rrc_asn_library/MBMSGeneralInformation-v890ext-IEs.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct MBMS_PreferredFrequencyList_r6;
struct MBMS_MSCH_ConfigurationInfo_r6;

/* MBMSGeneralInformation */
typedef struct MBMSGeneralInformation {
	struct MBMS_PreferredFrequencyList_r6	*mbms_PreferredFrequencyInfo	/* OPTIONAL */;
	MBMS_TimersAndCounters_r6_t	 mbms_TimersAndCounters;
	MBMS_MICHConfigurationInfo_r6_t	 michConfigurationInfo;
	MBMS_CellGroupIdentity_r6_t	 cellGroupIdentity;
	struct MBMS_MSCH_ConfigurationInfo_r6	*mschDefaultConfigurationInfo	/* OPTIONAL */;
	struct MBMSGeneralInformation__v6b0NonCriticalExtensions {
		MBMSGeneralInformation_v6b0ext_IEs_t	 mbmsGeneralInformation_v6b0ext;
		struct MBMSGeneralInformation__v6b0NonCriticalExtensions__v770NonCriticalExtensions {
			MBMSGeneralInformation_v770ext_IEs_t	 mbmsGeneralInformation_v770ext;
			struct MBMSGeneralInformation__v6b0NonCriticalExtensions__v770NonCriticalExtensions__v860NonCriticalExtensions {
				MBMSGeneralInformation_v860ext_IEs_t	 mbmsGeneralInformation_v860ext;
				struct MBMSGeneralInformation__v6b0NonCriticalExtensions__v770NonCriticalExtensions__v860NonCriticalExtensions__v890NoncriticalExtensions {
					MBMSGeneralInformation_v890ext_IEs_t	 mbmsGeneralInformation_v890ext;
					struct MBMSGeneralInformation__v6b0NonCriticalExtensions__v770NonCriticalExtensions__v860NonCriticalExtensions__v890NoncriticalExtensions__nonCriticalExtensions {
						
						/* Context for parsing across buffer boundaries */
						asn_struct_ctx_t _asn_ctx;
					} *nonCriticalExtensions;
					
					/* Context for parsing across buffer boundaries */
					asn_struct_ctx_t _asn_ctx;
				} *v890NoncriticalExtensions;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} *v860NonCriticalExtensions;
			
			/* Context for parsing across buffer boundaries */
			asn_struct_ctx_t _asn_ctx;
		} *v770NonCriticalExtensions;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *v6b0NonCriticalExtensions;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MBMSGeneralInformation_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MBMSGeneralInformation;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/MBMS-PreferredFrequencyList-r6.h"
#include "rf_phreaker/umts_rrc_asn_library/MBMS-MSCH-ConfigurationInfo-r6.h"

#endif	/* _MBMSGeneralInformation_H_ */

/*
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "InformationElements"
 * 	found in "rcc.txt"
 * 	`asn1c -S/skeletons -fnative-types -fcompound-names`
 */

#ifndef	_LoggedMeasurementsConfigurationInfo_H_
#define	_LoggedMeasurementsConfigurationInfo_H_


#include <rf_phreaker/umts_rrc_asn_library/asn_application.h>

/* Including external dependencies */
#include <rf_phreaker/umts_rrc_asn_library/BIT_STRING.h>
#include <rf_phreaker/umts_rrc_asn_library/NativeEnumerated.h>
#include <rf_phreaker/umts_rrc_asn_library/OCTET_STRING.h>
#include "rf_phreaker/umts_rrc_asn_library/PLMN-Identity.h"
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE.h>
#include "rf_phreaker/umts_rrc_asn_library/CellIdentity.h"
#include <rf_phreaker/umts_rrc_asn_library/asn_SEQUENCE_OF.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_SEQUENCE_OF.h>
#include <rf_phreaker/umts_rrc_asn_library/constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum LoggedMeasurementsConfigurationInfo__loggingDuration {
	LoggedMeasurementsConfigurationInfo__loggingDuration_min10	= 0,
	LoggedMeasurementsConfigurationInfo__loggingDuration_min20	= 1,
	LoggedMeasurementsConfigurationInfo__loggingDuration_min40	= 2,
	LoggedMeasurementsConfigurationInfo__loggingDuration_hr1	= 3,
	LoggedMeasurementsConfigurationInfo__loggingDuration_hr1min30	= 4,
	LoggedMeasurementsConfigurationInfo__loggingDuration_hr2	= 5,
	LoggedMeasurementsConfigurationInfo__loggingDuration_spare1	= 6,
	LoggedMeasurementsConfigurationInfo__loggingDuration_spare2	= 7
} e_LoggedMeasurementsConfigurationInfo__loggingDuration;
typedef enum LoggedMeasurementsConfigurationInfo__loggingInterval {
	LoggedMeasurementsConfigurationInfo__loggingInterval_li128	= 0,
	LoggedMeasurementsConfigurationInfo__loggingInterval_li256	= 1,
	LoggedMeasurementsConfigurationInfo__loggingInterval_li512	= 2,
	LoggedMeasurementsConfigurationInfo__loggingInterval_li1024	= 3,
	LoggedMeasurementsConfigurationInfo__loggingInterval_li2048	= 4,
	LoggedMeasurementsConfigurationInfo__loggingInterval_li3072	= 5,
	LoggedMeasurementsConfigurationInfo__loggingInterval_li4096	= 6,
	LoggedMeasurementsConfigurationInfo__loggingInterval_li6144	= 7
} e_LoggedMeasurementsConfigurationInfo__loggingInterval;
typedef enum LoggedMeasurementsConfigurationInfo__areaConfiguration_PR {
	LoggedMeasurementsConfigurationInfo__areaConfiguration_PR_NOTHING,	/* No components present */
	LoggedMeasurementsConfigurationInfo__areaConfiguration_PR_cellIDList,
	LoggedMeasurementsConfigurationInfo__areaConfiguration_PR_locationAreaList,
	LoggedMeasurementsConfigurationInfo__areaConfiguration_PR_routingAreaList
} LoggedMeasurementsConfigurationInfo__areaConfiguration_PR;

/* Forward declarations */
struct LAI;
struct RAI;

/* LoggedMeasurementsConfigurationInfo */
typedef struct LoggedMeasurementsConfigurationInfo {
	BIT_STRING_t	 absoluteTimeInfo;
	long	 loggingDuration;
	long	 loggingInterval;
	struct LoggedMeasurementsConfigurationInfo__traceReference_r10 {
		PLMN_Identity_t	 plmn_Identity;
		OCTET_STRING_t	 traceId;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} traceReference_r10;
	OCTET_STRING_t	 traceRecordingSession;
	struct LoggedMeasurementsConfigurationInfo__areaConfiguration {
		LoggedMeasurementsConfigurationInfo__areaConfiguration_PR present;
		union LoggedMeasurementsConfigurationInfo__areaConfiguration_u {
			struct LoggedMeasurementsConfigurationInfo__areaConfiguration__cellIDList {
				A_SEQUENCE_OF(CellIdentity_t) list;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} cellIDList;
			struct LoggedMeasurementsConfigurationInfo__areaConfiguration__locationAreaList {
				A_SEQUENCE_OF(struct LAI) list;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} locationAreaList;
			struct LoggedMeasurementsConfigurationInfo__areaConfiguration__routingAreaList {
				A_SEQUENCE_OF(struct RAI) list;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} routingAreaList;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *areaConfiguration;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} LoggedMeasurementsConfigurationInfo_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_loggingDuration_3;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_loggingInterval_12;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_LoggedMeasurementsConfigurationInfo;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "rf_phreaker/umts_rrc_asn_library/LAI.h"
#include "rf_phreaker/umts_rrc_asn_library/RAI.h"

#endif	/* _LoggedMeasurementsConfigurationInfo_H_ */
